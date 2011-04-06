#include "xmlgenerator.h"

xmlgenerator::xmlgenerator()
{

}
QString xmlgenerator::patientOperationXML(QString operation, QString healthCard,int facilNum, int areaNum, bool remote,QString dateAdded, QString dateAdmitted, QString first, QString last, int reqCare, int occCare){        //facilNum = -1 means we are dealing with a waiting list
   QDomDocument message;

   QDomElement operationChild = message.createElement(operation);
   operationChild.setAttribute("remote",remote);
   message.appendChild(operationChild);


   QDomElement areaChild=message.createElement("Area");
   areaChild.setAttribute("ID",areaNum);
   operationChild.appendChild(areaChild);

   QDomElement facilityChild=message.createElement("Facility");
   QDomElement patientListChild=message.createElement("Unknown");
   if (facilNum!=-1){
       //facilityChild.setTagName("Facility");
       facilityChild.setAttribute("ID",facilNum);
       //facilityChild.setAttribute("name",DataStorage::getFacilityName(facilNum));
       //facilityChild.setAttribute("coordinateX",DataStorage::getFacilityX(facilNum));
       //facilityChild.setAttribute("coordinateY",DataStorage::getFacilityY(facilNum));
       //facilityChild.setAttribute("AC",DataStorage::getNumACBeds(facilNum));
       //facilityChild.setAttribute("CCC",DataStorage::getNumCCCBeds(facilNum));
       //facilityChild.setAttribute("LTC",DataStorage::getNumLTCBeds(facilNum));
       areaChild.appendChild(facilityChild);

       //Might have to take many of these out

       patientListChild.setTagName("PatientList");
       facilityChild.appendChild(patientListChild);
   }
   else {
       patientListChild.setTagName("WaitingList");
       areaChild.appendChild(patientListChild);
   }


    QDomElement patientChild=message.createElement("Patient");
    //patientChild.setTagName("Patient");
    if (dateAdded!="")patientChild.setAttribute("dateAdded",dateAdded);
    if (dateAdmitted!="")patientChild.setAttribute("dateAdmitted",dateAdmitted);
    if (first!="")patientChild.setAttribute("firstName",first);
    if (last!="")patientChild.setAttribute("lastName",last);
    if (reqCare!=-1)patientChild.setAttribute("reqCare",reqCare);
    if (occCare!=-1)patientChild.setAttribute("occCare",occCare);

    patientChild.setAttribute("healthCardNumber",healthCard);
    patientListChild.appendChild(patientChild);

    return message.toString();

}

QString xmlgenerator::rebuild(){
    QDomDocument message;

    QDomElement operationChild = message.createElement("Rebuild");
    operationChild.setAttribute("remote",false);
    message.appendChild(operationChild);


    QDomElement areaChild=message.createElement("Area");


qDebug()<<"prev";


    areaChild.setAttribute("ID",DataStorage::myArea());
    operationChild.appendChild(areaChild);



    QDomElement facilityChild=message.createElement("Facility");
    QDomElement patientListChild=message.createElement("PatientList");
    int facilNum=DataStorage::myFacilityID;


     facilityChild.setAttribute("ID",facilNum);
     facilityChild.setAttribute("name",DataStorage::getFacilityName(facilNum));
     facilityChild.setAttribute("coordinateX",DataStorage::getFacilityX(facilNum));
     facilityChild.setAttribute("coordinateY",DataStorage::getFacilityY(facilNum));
     facilityChild.setAttribute("AC",DataStorage::getTotalACBeds(facilNum));
     facilityChild.setAttribute("CCC",DataStorage::getTotalCCCBeds(facilNum));
     facilityChild.setAttribute("LTC",DataStorage::getTotalLTCBeds(facilNum));
     areaChild.appendChild(facilityChild);
     patientListChild.setTagName("PatientList");
     facilityChild.appendChild(patientListChild);


     QVector<Inpatient>patientList=DataStorage::getPatientsAtFacility(facilNum);
     for (int i=0;i<patientList.size();i++){
         Inpatient curPat=patientList[i];
        // QString dateAdded=curPat->getDateAdded();
         QString dateAdmitted=curPat.getDateAdmitted();
         QString first=curPat.getFirstname();
         QString last=curPat.getLastname();
         int reqCare=DataStorage::getCareType(curPat.getRequiredCare());
         int occCare=DataStorage::getCareType(curPat.getCurrentCare());
         QString healthCard=curPat.getHCN();

         QDomElement patientChild=message.createElement("Patient");
        // if (dateAdded!="")patientChild.setAttribute("dateAdded",dateAdded);
         if (dateAdmitted!="")patientChild.setAttribute("dateAdmitted",dateAdmitted);
         if (first!="")patientChild.setAttribute("firstName",first);
         if (last!="")patientChild.setAttribute("lastName",last);
         if (reqCare!=-1)patientChild.setAttribute("reqCare",reqCare);
         if (occCare!=-1)patientChild.setAttribute("occCare",occCare);

         patientChild.setAttribute("healthCardNumber",healthCard);
         patientListChild.appendChild(patientChild);
     }

     if (DataStorage::isMainFacility()){
         QDomElement waitingListChild=message.createElement("WaitingList");
         QVector<Patient>waitingList=DataStorage::getWaitingListPatients(DataStorage::myArea());
         for (int i=0;i<waitingList.size();i++){
             Patient curPat=waitingList[i];
             //QString dateAdded=curPat->getDateAdded();


             QString dateAdded=DataStorage::getPatientDateAdded(curPat.getHCN(),DataStorage::myArea());

             //QString dateAdmitted=curPat->getDateAdmitted();
             QString first=curPat.getFirstname();
             QString last=curPat.getLastname();
             //int reqCare=curPat->getRequiredCare();
             //int occCare=curPat->getOccupiedCare();
             QString healthCard=curPat.getHCN();

             QDomElement patientChild=message.createElement("Patient");
             if (dateAdded!="")patientChild.setAttribute("dateAdded",dateAdded);
             //if (dateAdmitted!="")patientChild.setAttribute("dateAdmitted",dateAdmitted);
             if (first!="")patientChild.setAttribute("firstName",first);
             if (last!="")patientChild.setAttribute("lastName",last);
             //if (reqCare!=-1)patientChild.setAttribute("reqCare",reqCare);
             //if (occCare!=-1)patientChild.setAttribute("occCare",occCare);

             patientChild.setAttribute("healthCardNumber",healthCard);
             waitingListChild.appendChild(patientChild);
         }
         areaChild.appendChild(waitingListChild);
     }

     return message.toString();
}

QString xmlgenerator::rebuildResponse(){
    QDomDocument message;

    QDomElement operationChild = message.createElement("Add");
    operationChild.setAttribute("remote","false");
    message.appendChild(operationChild);


    QDomElement areaChild=message.createElement("Area");
    areaChild.setAttribute("ID",DataStorage::myArea());
    operationChild.appendChild(areaChild);

    QDomElement facilityChild=message.createElement("Facility");
    QDomElement patientListChild=message.createElement("PatientList");
    int facilNum=DataStorage::myFacilityID;


     facilityChild.setAttribute("ID",facilNum);
     facilityChild.setAttribute("name",DataStorage::getFacilityName(facilNum));
     facilityChild.setAttribute("coordinateX",DataStorage::getFacilityX(facilNum));
     facilityChild.setAttribute("coordinateY",DataStorage::getFacilityY(facilNum));
     facilityChild.setAttribute("AC",DataStorage::getTotalACBeds(facilNum));
     facilityChild.setAttribute("CCC",DataStorage::getTotalCCCBeds(facilNum));
     facilityChild.setAttribute("LTC",DataStorage::getTotalLTCBeds(facilNum));
     areaChild.appendChild(facilityChild);
     patientListChild.setTagName("PatientList");
     facilityChild.appendChild(patientListChild);



     QVector<Inpatient>patientList=DataStorage::getPatientsAtFacility(facilNum);
     for (int i=0;i<patientList.size();i++){
         Inpatient curPat=patientList[i];
         //QString dateAdded=curPat->getDateAdded();
         QString dateAdmitted=curPat.getDateAdmitted();
         QString first=curPat.getFirstname();
         QString last=curPat.getLastname();
         int reqCare=DataStorage::getCareType(curPat.getRequiredCare());
         int occCare=DataStorage::getCareType(curPat.getCurrentCare());
         QString healthCard=curPat.getHCN();


         QDomElement patientChild=message.createElement("Patient");
         //if (dateAdded!="")patientChild.setAttribute("dateAdded",dateAdded);
         if (dateAdmitted!="")patientChild.setAttribute("dateAdmitted",dateAdmitted);
         if (first!="")patientChild.setAttribute("firstName",first);
         if (last!="")patientChild.setAttribute("lastName",last);
         if (reqCare!=-1)patientChild.setAttribute("reqCare",reqCare);
         if (occCare!=-1)patientChild.setAttribute("occCare",occCare);

         patientChild.setAttribute("healthCardNumber",healthCard);
         patientListChild.appendChild(patientChild);
     }

     QDomElement waitingListChild=message.createElement("WaitingList");
     if (DataStorage::isMainFacility()){
         QVector<Patient>waitingList=DataStorage::getWaitingListPatients(DataStorage::myArea());
         for (int i=0;i<waitingList.size();i++){
             Patient curPat=waitingList[i];

             //QString dateAdded=curPat->getDateAdded();
             QString dateAdded=DataStorage::getPatientDateAdded(curPat.getHCN(),DataStorage::myArea());
             //QString dateAdmitted=curPat->getDateAdmitted();
             QString first=curPat.getFirstname();
             QString last=curPat.getLastname();
             //int reqCare=curPat->getRequiredCare();
             //int occCare=curPat->getOccupiedCare();
             QString healthCard=curPat.getHCN();

             QDomElement patientChild=message.createElement("Patient");
             //if (dateAdded!="")patientChild.setAttribute("dateAdded",dateAdded);
             //if (dateAdmitted!="")patientChild.setAttribute("dateAdmitted",dateAdmitted);
             if (first!="")patientChild.setAttribute("firstName",first);
             if (last!="")patientChild.setAttribute("lastName",last);
             //if (reqCare!=-1)patientChild.setAttribute("reqCare",reqCare);
             //if (occCare!=-1)patientChild.setAttribute("occCare",occCare);

             patientChild.setAttribute("healthCardNumber",healthCard);
             waitingListChild.appendChild(patientChild);
         }
         areaChild.appendChild(waitingListChild);
     }

     return message.toString();
}

QString xmlgenerator::addBeds(int facilNum, int areaNum, int ac, int ccc, int ltc, bool remote){
    QDomDocument message;

    QDomElement operationChild = message.createElement("Add");
    operationChild.setAttribute("remote",remote);
    message.appendChild(operationChild);


    QDomElement areaChild=message.createElement("Area");
    areaChild.setAttribute("ID",areaNum);
    operationChild.appendChild(areaChild);

    QDomElement facilityChild=message.createElement("Facility");

     facilityChild.setAttribute("ID",facilNum);
     //facilityChild.setAttribute("name",DataStorage::getFacilityName(facilNum));
     facilityChild.setAttribute("AC",ac);
     facilityChild.setAttribute("CCC",ccc);
     facilityChild.setAttribute("LTC",ltc);
     areaChild.appendChild(facilityChild);


     return message.toString();
}

QString xmlgenerator::addFacility(int facilNum, int areaNum,int xcoor, int ycoor, int ac, int ccc, int ltc, QString name, bool remote,QString type){
    QDomDocument message;

    QDomElement operationChild = message.createElement("Add");
    operationChild.setAttribute("remote",remote);
    message.appendChild(operationChild);


    QDomElement areaChild=message.createElement("Area");
    areaChild.setAttribute("ID",areaNum);
    operationChild.appendChild(areaChild);

    QDomElement facilityChild=message.createElement("Facility");

     facilityChild.setAttribute("coordinateX",xcoor);
     facilityChild.setAttribute("coordinateY",ycoor);
     facilityChild.setAttribute("ID",facilNum);
     facilityChild.setAttribute("name",name);
     if (type=="Hospital"){
         facilityChild.setAttribute("AC",ac);
         facilityChild.setAttribute("CCC",ccc);
     }
     else{
         facilityChild.setAttribute("LTC",ltc);
     }

     areaChild.appendChild(facilityChild);

     return message.toString();
}

