#include "AuditFile.h"
#include <algorithm>
#include <iostream>
#include <fstream>

// A string ToUpper function found on stackoverflow @ https://stackoverflow.com/a/5222874
string StringToUpper2(string strToConvert)
{
    transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

AuditFile :: AuditFile(string date){
    this->date = date;
    //I am struggling with file stuff here
}

// AuditFile::AuditFile(){}

void AuditFile :: promptForFileName(){
    cout << "Do you want to name the audit file of the election? (YES or NO)" << endl;
    string answer;
    cin >> answer;
    answer = StringToUpper2(answer);
    if (answer == "YES"){
        cout << "What name do you want to give to the auditFile?: " << endl;
        string fileName;
        cin >> fileName;
        fileName = fileName + date + ".txt";
        this->auditFileName = fileName;
    }
    else {
        auditFileName = date + ".txt";
    }
}

void AuditFile :: createAuditFile(){
    bool cont = true;
    while(cont){
        try {
            cout << "Creating " + auditFileName << endl;
            //ofstream aFile(auditFileName);
            this->aFile.open(auditFileName, ios::out);
            
            cont = false;
        }
        catch(...) {
            cout << "Could not open file with filename " << auditFileName << endl;
            cout << "Try again." << endl;
        }
    }  
 }

bool AuditFile :: log(string action){
    aFile << action << endl;
    //error handling
    return true;
}

string AuditFile::finalizeAuditFile(){
    //permissions
    aFile.close();
    return "change this";
}

void AuditFile::displayAuditToUser(){
    cout << getAuditFileName();
    return;
}

