#include "Scanner.h"
// #include <iostream>
#include <cctype>

// #include <fstream>
#include <vector>
#include <algorithm>
#include "AuditFile.h"
#include "Candidate.h"
#include "Cpl.h"
#include "CplBallot.h"
#include "Ir.h"
#include "IrBallot.h"
#include "Party.h"
#include "Scanner.h"

using namespace std;

// A string ToUpper function found on stackoverflow @ https://stackoverflow.com/a/5222874
string StringToUpper(string strToConvert)
{
    transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

// A helper function to split a string by "," character.
vector<string> splitByComma(string str){
    vector<string> temp;
    string delimiter = ",";
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        temp.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    temp.push_back(str);
    return temp;
}

// Helper function to find index of a string in a vector.
int find(vector<string> strVector, string seek){
    for (int i = 0; i < strVector.size(); ++i){
        if (strVector.at(i) == seek) return i;
    }
    return -1;
}

Scanner::Scanner(string filename){
    this->filename = filename;
}

string Scanner::promptForFile(){
    string name;
    cout << "Please enter filename. " << endl;
    cin >> name;
    return name;
}

string Scanner::promptForElectionType(){
    bool cont = true;
    string type;
    while(cont){
        cout << "Please enter election type (CPL/IR): " << endl;
        cin >> type;
        type = StringToUpper(type);
        if (type == "IR" || type == "CPL"){
            cont = false;
        }
        else {
            cout << "Invalid input. Try again." << endl;
        }
    }
    return type;
}

int Scanner::promptForNumSeats(){
    bool cont = true;
    while(cont){
        string numSeats;
        cout << "Please enter number of seats(#): " << endl;
        cin >> numSeats;
        try {
            int numSeatsInt = stoi(numSeats);
            cont = false;
        }
        catch (...){
            cout << "Invalid input. Try again.";
        }
    }
    return numSeats;
}

int Scanner::promptForNumCandidates(){
    bool cont = true;
    while(cont){
        string numCandidates;
        cout << "Please enter number of Candidates(#): " << endl;
        cin >> numCandidates;
        try {
            int numCandidatesInt = stoi(numCandidates);
            cont = false;
        }
        catch (...){
            cout << "Invalid input. Try again.";
        }
    }
    return numCandidates;
}

void Scanner::openFile(){
    bool cont = true;
    while(cont){
        if (filename == "NOFILE"){
            // cout << "openFile 2" << endl;
            // cout << "filename value: " << filename << endl;
            this->filename = promptForFile();
        }
        try {
            this->inputFile.open(filename);
            cout << "Opened: " << filename << endl;
            cont = false;
        }
        catch(...) {
            cout << "Could not open file with filename " << filename << endl;
            cout << "Try again." << endl;
        }
    }
}

void Scanner::cplParse(){
    int numParties;
    vector<Party> parties;
    int numSeats;
    int numBallots;
    int index; //to find index of party from ballot
    string line;
    getline(this->inputFile, line);
    numParties = stoi(line);

    for (int i =0 ; i < numParties; i++){
        Party p = Party();
        parties.push_back(p);
    }
    getline(this->inputFile, line);  // line 3 of csv. Parties separated by commas. 
    
    vector<string> splitLine = splitByComma(line);
    for (int j = 0; j < numParties; j++){
        parties.at(j).setName(splitLine.at(j));
    
    }

    //reading candidates in party (next numParties # of lines)
    for(int i = 0; i < numParties; i++){
        getline(this->inputFile, line);
        parties.at(i).setCandidateList(splitByComma(line));
    }

   
    getline(this->inputFile, line);
    numSeats = stoi(line);
    getline(this->inputFile, line);
    numBallots = stoi(line);


    for (int l = 0; l < numBallots; l++){
        CplBallot *ballot = new CplBallot();
        getline(this->inputFile, line);
        splitLine = splitByComma(line);
        index = find(splitLine, "1");

        //set the ballot's vote to the name of the party it is being assigned to (this is found via the index the vote is within a line)
        ballot->setVote(parties.at(index).getName());

            //temporaty vector to add an individual ballot, used to add to a party's ballots vector
           
            vector<Ballot*> temp = parties.at(index).getVotes();
            temp.push_back(ballot);
            parties.at(index).setVotes(temp); 
    
    }
    this->election = new Cpl(numParties, parties, numSeats, numBallots);
    cout << "finished CPL parsing" << endl;
   // cout << "end of scanner size of parties = " << parties.size() << endl;
    
    //use this to test how many votes one party has gotten
    //cout << parties.at(0).getName() << " -- " << parties.at(0).getVotes().size() << endl;
}

void Scanner:: irParse(){
    int numCandidates, numBallots, index;
    vector<Candidate> candidateList;
    string line;
    vector<string> splitLine;
    vector<Ballot*> ballots;

    getline(this->inputFile, line); // line 2 of file. Number of candidates
    numCandidates = stoi(line);

    getline(this->inputFile,line);  // line 3 of file, list of candidates sepearated by commas
    splitLine = splitByComma(line);

    for (int j = 0; j < numCandidates; j++) {
        splitLine.at(j);
        Candidate candidate = splitLine.at(j);
        candidate.setVotes(ballots);
        candidate.setParty(splitLine.at(j));
        candidate.setCandidateID(j);  // sets candidateIDs starting from 0
        candidateList.push_back(candidate);
    }

    getline(this->inputFile, line); 
    numBallots = stoi(line);    // line 4 of file

    for (int l = 0; l < numBallots; l++) {
        IrBallot *ballot = new IrBallot();
        getline(this->inputFile, line);
        splitLine = splitByComma(line);
        ballot->setRanks(splitLine);
        index = find(splitLine, "1");
        ballot->setVote(candidateList.at(index).getCandidateName());
        ballot->setCurrentRank(1);
        // cout << "current ballots rank = " << ballot->getCurrentRank() << endl;
        vector<Ballot*> temp = candidateList.at(index).getVotes();
        temp.push_back(ballot);
        candidateList.at(index).setVotes(temp);
    }

    // TESTING BALLOT STRUCTURE DATA

//    int k = 0;

//     for (k ; k < candidateList.size(); k++){
//         Candidate candidate = candidateList.at(k);
//         cout << candidate.getCandidateName() + ", ID = " << 
//         candidate.getCandidateID() << endl;
//         cout << "number or votes = " << candidate.getVotes().size() << endl;
//         int h = 0;
//         for (h; h < candidate.getVotes().size(); h++){
//             cout << candidate.getVotes().at(h)->getCurrentRank() << endl;
//         }
//     }
   
    // END TESTING

    this->election = new Ir(numCandidates, candidateList, numBallots);
    auditFile.log("Election Type: Instant Runoff\n");
    auditFile.log("Candidates: ");
    for (int i = 0; i < numCandidates; i++){
        auditFile.log(candidateList[i].getCandidateName());
    }
    auditFile.log("\n");
    string nBallots = to_string(numBallots);
    auditFile.log("Number of ballots: " + nBallots);
    // cout << "Finished IR parsing" << endl;  // this and 5 next lines are for debugging.
    // cout << numCandidates << endl;
    // cout << numBallots << endl;
    // cout << candidateList.size() << endl;
    // for (int a = 0; a < candidateList.size(); a++) {
    //     cout << candidateList[a].getCandidateName() << endl;
    // }
}

void Scanner::parseFile(){
    string temp;
    getline(this->inputFile, temp);
    electionType = StringToUpper(temp);
    if (this->electionType != "IR" && this->electionType != "CPL"){
        this->electionType = promptForElectionType();
    }
    if (this->electionType == "IR"){
        if (promptForConfirmType() != "YES"){
            cout << "Declined parse." << endl;
        }
        else{
            cout << "Begin parsing IR" << endl;
            Scanner::setUpAuditFile("IR");
            auditFile.log("Parsing IR input file.");
            irParse();
            this->election->setElectionType("IR");
        }
    }
    else if (this->electionType == "CPL"){
        if (promptForConfirmType() != "YES"){
            cout << "Declined parse." << endl;
        }
        else {
            cout << "Begin parsing CPL" << endl;
            Scanner::setUpAuditFile("CPL");
            auditFile.log("Parsing CPL input file.");
            cplParse();
            this->election->setElectionType("CPL");

        }
    }
}

string Scanner::promptForConfirmType(){
    cout << "Parse " << this->electionType << " type of election? (YES/NO)" << endl;
    string answer;
    cin >> answer;
    answer = StringToUpper(answer);
    return answer;
}

Election* Scanner::getElection(){
    return this->election;
}

void Scanner::setUpAuditFile(string electionType){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    string yr = to_string(year);
    string mon = to_string(month);
    string d = to_string(day);
    string date = electionType + mon + d + yr;
    auditFile = AuditFile(date);
    auditFile.promptForFileName();
    auditFile.createAuditFile();
}