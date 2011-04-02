#include "xmlparser.h"
/*
//don't forget to have QT += xml in your project class

    XMLParser::XMLParser(QString msg)      //passing by value or reference - need to be sure I'm doing it right
    {

       // dateFormat = "ddMMyy";          //MAY NEED TO CHANGE!


        //TO DO:
        //  - add facility
        //  - rebuild and reporting features
        //  data storage should remove patient from wl when it is placed
        //  ds should also update history




        //QFile myFile(msg);

        QDomDocument doc("aMessage");
        original = doc;






        doc.setContent(msg );

        //will this work?









        QDomElement docElement = doc.documentElement();

        //std::cout<<"boom ";
        //std::cout<<doc.toString().toStdString();

        //if (!docElement.hasAttribute("remote")){
            //std::cout<<"next";
          //  docElement=docElement.firstChildElement();
        //}

        startParsing(docElement);

    }

    int XMLParser::startParsing(QDomElement rootElement){       //don't we need "public" ?
        QString remoteString= rootElement.attribute("remote","error");

        if (remoteString == "error")return 1;

        QString operation=rootElement.tagName();



        QDomElement areaElement = rootElement.firstChild().toElement();

        QString areaString=areaElement.attribute("ID","error");

        if (areaString == "error")return 1;

        int areaVal = areaString.toInt();                            //make sure the conversion works the way you want

        QDomElement facilityOrWL=areaElement.firstChild().toElement();

        bool remoteBool=true;
        if (remoteString=="false")remoteBool=false;

        bool here=false;
        while (!facilityOrWL.isNull()){
            XMLParser::parseFacilityOrWaitingList(facilityOrWL,remoteBool,areaVal,operation);

            if (facilityOrWL.attribute("ID","error")!="error")
                if (facilityOrWL.attribute("ID","error").toInt()==DataStorage::getMyFacilityID())
                    here=true;

            facilityOrWL=facilityOrWL.nextSiblingElement();
        }

        //for now, I will send it even if the message was faulty

        if (remoteBool&&here){
            original.documentElement().setAttribute("remote",false);
            MessageControl::sendMessageToAll(original.toString());
        }

        return 0;
    }

    int XMLParser::parseFacilityOrWaitingList(QDomElement ForW,bool remote, int area, QString operation){

//cout<<"aboutToParseForW";

        if (ForW.tagName()=="Facility")return parseFacility(ForW,remote,area,operation);
        else if (ForW.tagName()=="WaitingList")return XMLParser::parseWaitingList(ForW,remote,area,operation);
        return 1;
    }

    int XMLParser::parseFacility(QDomElement facility,bool remote, int area, QString operation){
        int facilityNumber = facility.attribute("ID","error").toInt();
        //case 1: remote and other
        if (remote&&facilityNumber!=DataStorage::getMyFacilityID())return 1;   //nothing happens if its remote and has got the wrong facility

        //case 2: remote and here
        if (remote&&facilityNumber==DataStorage::getMyFacilityID()){

            facilityOperation(facility, operation, area);

            //re-send slightly updated message if it was a change OR
            //send a reply if it was a request

        }

        //case 3:not remote
        else if (!remote){

            facilityOperation(facility, operation, area);

        }

        return 0;

    }

    int XMLParser::parseWaitingList(QDomElement waitingList,bool remote, int area, QString operation){
        //case 1: remote and other - do nothing
        if (remote&&!DataStorage::isMainFacility())return 1;         //nothing happens if its remote and this has no waiting lists
        if (remote&&area!=DataStorage::myArea())return 1;           //...or if its the wrong area

        //case 2: remote and here
        if (remote&&area==DataStorage::myArea()&&DataStorage::isMainFacility()){

            parseWaitingListOperation(waitingList, area, operation);


            //re-send message with remote flag set to off
        }
        //case 3: not remote
        else{

            parseWaitingListOperation(waitingList, area, operation);

        }
        return 0;
    }

    int XMLParser::facilityOperation(QDomElement facility,QString operation, int area){
        int facilNum = facility.attribute("ID","error").toInt();

        if (operation=="Rebuild"){
            DataStorage::clearPatientsAtFacility(facilNum);
            operation="Add";

            MessageControl::sendMessage(xmlgenerator::rebuildResponse(),facilNum);

        }


        if (operation=="Add"){
            if (!facility.hasChildNodes()){

                if (!DataStorage::facilityExists(facilNum))parseAddNewFacility(facility,facilNum,area);
                else parseAddBeds(facility,facilNum);

            }
            else {

                parseAddBeds(facility,facilNum);        //based on webct discussion

               QDomElement patList=facility.firstChild().toElement();

               QDomElement curChild=patList.firstChild().toElement();
               while (!curChild.isNull()){
                      parsePlacePatient(curChild, facilNum);
                      curChild=curChild.nextSiblingElement();
                }
            }

        }
        else if (operation=="Delete"){
            QDomElement patList=facility.firstChild().toElement();

            QDomElement curChild=patList.firstChild().toElement();
            while (!curChild.isNull()){
                   parseEjectPatient(curChild, facilNum);
                   curChild=curChild.nextSiblingElement();
             }
        }
        else if (operation=="Rebuild"){
            //should never get this far because we switched it at the start
            return 3;


        }
        else if (operation=="Request"){
            return 3;
        }
        else if (operation=="Response"){
            return 3;
        }
        return 0;
    }

    int XMLParser::parsePlacePatient(QDomElement patient, int facilNum){
        QString patientID = patient.attribute("healthCardNumber","error");
        //QDateTime dateAdmitted = QDateTime::fromString(patient.attribute("dateAdded","error"),dateFormat);
        //QDateTime dateAdmitted = DataStorage::currentDate();


        //QDateTime current = QDateTime::currentDateTime();
        //QString dateAdmitted = current.toString("yyyy-MM-ddThh:mm:ss");



        DataStorage::assignPatientToBed(facilNum,patientID);
        return 0;
    }

    int XMLParser::parseEjectPatient(QDomElement patient, int facilNum){
        QString patientID = patient.attribute("healthCardNumber","error");
        //QDateTime dateAdmitted = QDateTime::fromString(patient.attribute("dateAdmitted","error"),dateFormat);
        //QDateTime dateRemoved = DataStorage::currentDate();

        //QDateTime current = QDateTime::currentDateTime();
        //QString dateRemoved = current.toString("yyyy-MM-ddThh:mm:ss");


        DataStorage::removePatientFromBed(facilNum,patientID);
        return 0;
    }

    int XMLParser::parseWaitingListOperation(QDomElement waitingList, int area, QString operation){
        if (operation=="Rebuild"){
            DataStorage::clearPatientsOnAreaWL(area);
            operation="Add";
        }


        if (operation=="Add"){
               QDomElement curChild=waitingList.firstChild().toElement();
               while (!curChild.isNull()){
                      parseAddPatientToWL(curChild, area);
                      curChild=curChild.nextSiblingElement();

            }

        }
        else if (operation=="Delete"){
            QDomElement curChild=waitingList.firstChild().toElement();
            while (!curChild.isNull()){
                   parseRemovePatientFromWL(curChild, area);
                   curChild=curChild.nextSiblingElement();
             }
        }
        else if (operation=="Rebuild"){
            //should never get this far because we switched it at the start
            return 3;
        }
        else if (operation=="Request"){
            return 3;
        }
        else if (operation=="Response"){
            return 3;
        }
        return 0;
    }

    int XMLParser::parseAddPatientToWL(QDomElement patient, int area){
        QString healthCard = patient.attribute("healthCardNumber","error");
        QString firstName = patient.attribute("firstName","error");
        QString lastName = patient.attribute("lastName","error");

        //QDateTime dateAdded = QDateTime::fromString(patient.attribute("dateAdded","error"),dateFormat);
        //QDateTime dateAdded=DataStorage::currentDate();

        QDateTime current = QDateTime::currentDateTime();
        QString dateAdded = current.toString("yyyy-MM-ddThh:mm:ss");

        QString dateAdmitted=patient.attribute("dateAdmitted","error");

        //QDateTime dateAdmitted;
        //if (dateAdmittedString != "error")dateAdmitted = QDateTime::fromString(patient.attribute("dateAdmitted","error"),dateFormat);

        int ctCare = patient.attribute("occCare","error").toInt();

        QString currentCare = DataStorage::getCareType(ctCare);


        //add outpatient
        if (!DataStorage::isInpatient(healthCard)){
            DataStorage::addPatientToWaitingList(healthCard,firstName,lastName,area,dateAdded);
        }
        //add inpatient
        else{
            //dateAdmitted=DataStorage::getDateAdmitted(healthCard);
            QDateTime current = QDateTime::currentDateTime();
            QString dateAdmitted = current.toString("yyyy-MM-ddThh:mm:ss");


            int currentFacility = DataStorage::getCurrentFacilityForPatient(healthCard);
            DataStorage::addPatientToWaitingList(healthCard,firstName,lastName,area,dateAdded,currentFacility,currentCare);
        }

    }

    int XMLParser::parseRemovePatientFromWL(QDomElement patient, int area){
        DataStorage::removePatientFromWaitingList(area,patient.attribute("ID","error"));
    }

    int XMLParser::parseAddNewFacility(QDomElement facility, int facilNum, int area){
        QString  acBeds = facility.attribute("AC","error");
        QString cccBeds = facility.attribute("CCC","error");
        QString ltcBeds = facility.attribute("LTC","error");
        QString id = facility.attribute("ID","error");
        QString x = facility.attribute("coordinateX","error");
        QString y = facility.attribute("coordinateY","error");
        QString name = facility.attribute("name","error");

        if ((x!="error")&&(y!="error")&&(id!="error")&&(name!="error")){
            DataStorage::addFacility(name,x.toFloat(),y.toFloat(),area,id.toInt());
        }

    }

    int XMLParser::parseAddBeds(QDomElement facility, int facilNum){
        QString  acBeds = facility.attribute("AC","error");
        QString cccBeds = facility.attribute("CCC","error");
        QString ltcBeds = facility.attribute("LTC","error");

        if ((acBeds != "error")&&(acBeds != "0")){
            DataStorage::addBeds(facilNum, acBeds.toInt(),"AC");
        }
        if ((cccBeds != "error")&&(cccBeds != "0")){
            DataStorage::addBeds(facilNum, cccBeds.toInt(),"CCC");
        }
        if ((ltcBeds != "error")&&(ltcBeds != "0")){
            DataStorage::addBeds(facilNum, ltcBeds.toInt(),"LTC");
        }


    }*/
