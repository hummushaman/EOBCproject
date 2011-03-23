#include "facility.h"



facility::facility(int anID, QString aName, QString aType)
{
    id = anID;
    name = aName;
    type = aType;
}

int facility::getID()
{
    return id;
}

QString facility::getName()
{
    return name;
}

QString facility::getType()
{
    return type;
}
