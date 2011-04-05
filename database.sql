CREATE TABLE area (
    areaid INTEGER PRIMARY KEY NOT NULL,
    name TEXT NOT NULL
);
CREATE TABLE facilityTypes (
    facilitytypeid INTEGER PRIMARY KEY NOT NULL,
    facilitytype TEXT
);
CREATE TABLE facility (
    facilityid INTEGER PRIMARY KEY NOT NULL,
    areaid INTEGER NOT NULL,
    facilitytypeid INTEGER NOT NULL,
    name TEXT NOT NULL UNIQUE,
    totalBeds INTEGER DEFAULT 0,
    numBedsOccupied INTEGER DEFAULT 0,
    x INTEGER NOT NULL,
    y INTEGER NOT NULL,
    FOREIGN KEY (areaid) REFERENCES area (areaid),
    FOREIGN KEY (facilityTypeid) REFERENCES facilityTypes (facilitytypeid)
);
CREATE TABLE hospital (
    hospitalid INTEGER PRIMARY KEY NOT NULL,
    totalACBeds INTEGER DEFAULT 0,
    numACBedsOccupied INTEGER DEFAULT 0,
    totalCCCBeds INTEGER DEFAULT 0,
    numCCCBedsOccupied INTEGER DEFAULT 0,
    FOREIGN KEY (hospitalid) REFERENCES facility(facilityid)
);
CREATE TABLE careTypes (
    caretypeid INTEGER PRIMARY KEY NOT NULL,
    caretype TEXT
);
CREATE TABLE userTypes (
    usertypeid INTEGER PRIMARY KEY NOT NULL,
    usertype TEXT
);
CREATE TABLE occupancyratelog (
    occupancyratelogid INTEGER NOT NULL,
    facilityid INTEGER NOT NULL,
    dateOfChange TEXT NOT NULL,
    careTypeid INTEGER NOT NULL,
    occupanyRate FLOAT NOT NULL,
    PRIMARY KEY (occupancyratelogid, facilityid),
    FOREIGN KEY (facilityid) REFERENCES facility(facilityid),
    FOREIGN KEY (careTypeid) REFERENCES careTypes(caretypeid)
);
CREATE TABLE patient (
    healthcarenumber TEXT PRIMARY KEY NOT NULL,
    firstName TEXT NOT NULL,
    lastName TEXT NOT NULL,
    requiredCareTypeid INTEGER NOT NULL,
    FOREIGN KEY (requiredCareTypeid) REFERENCES careTypes(caretypeid)
);
CREATE TABLE inpatient (
    inpatienthealthcarenumber TEXT PRIMARY KEY NOT NULL,
    currentFacilityid INTEGER NOT NULL,
    dateAdmittedToFacility TEXT NOT NULL,
    currentCareTypeid INTEGER NOT NULL,
    FOREIGN KEY (inpatienthealthcarenumber) REFERENCES patient(healthcarenumber),
    FOREIGN KEY (currentFacilityid) REFERENCES facility(facilityid),
    FOREIGN KEY (currentCareTypeid) REFERENCES careTypes(caretypeid)
);
CREATE TABLE waitinglistentries (
    healthcarenumber TEXT NOT NULL,
    areaid INTEGER NOT NULL,
    dateAddedToList TEXT NOT NULL,
    PRIMARY KEY (healthcarenumber, areaid),    
    FOREIGN KEY (healthcarenumber) REFERENCES patient(healthcarenumber),
    FOREIGN KEY (areaid) REFERENCES area(areaid)
);
CREATE TABLE waittimeslog (
    waittimeslogid INTEGER NOT NULL,
    waitingListareaid INTEGER NOT NULL,
    dateRemoved TEXT NOT NULL,
    waitTimesInDays INTEGER NOT NULL,
    PRIMARY KEY (waittimeslogid, waitingListareaid),
    FOREIGN KEY (waitingListareaid) REFERENCES area(areaid)
);
CREATE TABLE numpatientslog (
    numpatientslogid INTEGER NOT NULL,
    waitingListareaid INTEGER NOT NULL,
    dateChangedNumPatients TEXT NOT NULL,
    numPatients INTEGER NOT NULL,
    PRIMARY KEY (numpatientslogid, waitingListareaid),
    FOREIGN KEY (waitingListareaid) REFERENCES area(areaid)
);
CREATE TABLE users (
    username TEXT PRIMARY KEY NOT NULL,
    password TEXT NOT NULL,
    userTypeid INTEGER NOT NULL,
    FOREIGN KEY (userTypeid) REFERENCES userTypes(usertypeid)
);
