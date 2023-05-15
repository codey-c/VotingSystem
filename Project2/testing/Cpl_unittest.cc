#include <gtest/gtest.h>
#include "../src/Cpl.h"
#include "../src/Party.h"
#include <iostream>
#include <string>
#include <cmath>

class CplTest : public ::testing::Test {
    public:
        void SetUp( ) {
            // party1 = Party("Democratic");
            // party2 = Party("Republican");
            // party3 = Party("Independent");

            // parties.push_back(party1);
            // parties.push_back(party2);

            // parties2.push_back(party1);
            // parties2.push_back(party2);
            // parties2.push_back(party3);

            // candidate1 = Candidate(1);
            // candidate2 = Candidate(2);
            // candidate3 = Candidate(3);

            // candidates.push_back(candidate1);
            // candidates.push_back(candidate2);

            // candidates2.push_back(candidate1);
            // candidates2.push_back(candidate2);
            // candidates2.push_back(candidate3);

            // cpl = Cpl(2, parties, 5, 10);  //num parties, parties vector, num seats, num ballots
            // cpl2 = Cpl(3, parties2, 5, 11);

            // party1.setName"Democratic"();
        }

    protected: 
        // Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        // Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        // Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        // Party party4 = Party("Reform", {"McClure", "Berg"});
        // Party party5 = Party("Green", {"Zheng", "Melvin"});
        // Party party6 = Party("Independent", {"Peters"});
        // Candidate candidate1;
        // Candidate candidate2;
        // Candidate candidate3;
        // vector<Party> parties;
        // vector<Party> parties2;
        // // vector<Candidate> candidates;
        // // vector<Candidate> candidates2;
        // Cpl cpl = Cpl(2, parties, 5, 10);
        // Cpl cpl2 = Cpl(3, parties2, 5, 11);
};

TEST_F(CplTest, CplConstructorTest) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
    Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
    Party party3 = Party("New Wave", {"Jacks", "Rosen"});
    Party party4 = Party("Reform", {"McClure", "Berg"});
    Party party5 = Party("Green", {"Zheng", "Melvin"});
    Party party6 = Party("Independent", {"Peters"});

    CplBallot *ballot1 = new CplBallot(",,1,,,");
    CplBallot *ballot12 = new CplBallot(",,1,,,");
    CplBallot *ballot13 = new CplBallot(",,1,,,");
    CplBallot *ballot14 = new CplBallot(",,1,,,");
    CplBallot *ballot15 = new CplBallot(",,1,,,");
    CplBallot *ballot16 = new CplBallot(",,1,,,");
    CplBallot *ballot17 = new CplBallot(",,1,,,");
    CplBallot *ballot18 = new CplBallot(",,1,,,");
    CplBallot *ballot19 = new CplBallot(",,1,,,");
    vector<Ballot*> cplVotes{ballot1, ballot12, ballot13, ballot14, ballot15, ballot16, ballot17, ballot18, ballot19};
    party1.setVotes(cplVotes);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    cout << "party1 name " << party1.getName() << endl;
    cout << "party0 name " << parties.at(0).getName() << endl;

    cout << "candidate 1 " << party1.getCandidateList().at(1) << endl;
    cout << "candidate 1 " << parties.at(0).getCandidateList().at(1) << endl;

    Cpl cpl = Cpl(6, parties, 5, 10);
    cout << "party0 name after " << cpl.getParties().at(0).getName() << endl;
    cout << "candidate1 after " << cpl.getParties().at(0).getCandidateList().at(1) << endl;

    // EXPECT_EQ(cpl.getNumParties(), 6);
    // for (int i = 0; i < parties.size(); i++) {
    //     EXPECT_EQ(cpl.getParties().at(i).getName(), parties.at(i).getName());
    // }

    // EXPECT_EQ(cpl.getNumSeats(), 5);
    // EXPECT_EQ(cpl.getNumBallots(), 10);
}

TEST_F(CplTest, CplUnanimousTest) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        Party party4 = Party("Reform", {"McClure", "Berg"});
        Party party5 = Party("Green", {"Zheng", "Melvin"});
        Party party6 = Party("Independent", {"Peters"});
    // Results : democratic wins all three seats to foster, voltz, pike
    CplBallot *ballot1 = new CplBallot(",,1,,,");
    CplBallot *ballot12 = new CplBallot(",,1,,,");
    CplBallot *ballot13 = new CplBallot(",,1,,,");
    CplBallot *ballot14 = new CplBallot(",,1,,,");
    CplBallot *ballot15 = new CplBallot(",,1,,,");
    CplBallot *ballot16 = new CplBallot(",,1,,,");
    CplBallot *ballot17 = new CplBallot(",,1,,,");
    CplBallot *ballot18 = new CplBallot(",,1,,,");
    CplBallot *ballot19 = new CplBallot(",,1,,,");
    vector<Ballot*> cplVotes{ballot1, ballot12, ballot13, ballot14, ballot15, ballot16, ballot17, ballot18, ballot19};
    party1.setVotes(cplVotes);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    Cpl cpl = Cpl(6, parties, 3, 9);

    cpl.runCpl();

    EXPECT_EQ(cpl.getParties().at(0).getFinalSeatsWon(), 3);
    EXPECT_EQ(cpl.getParties().at(1).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(2).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(3).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getFinalSeatsWon(), 0);
}

TEST_F(CplTest, CplMoreSeatsThanCandidatesTest) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        Party party4 = Party("Reform", {"McClure", "Berg"});
        Party party5 = Party("Green", {"Zheng", "Melvin"});
        Party party6 = Party("Independent", {"Peters"});
    // Results : new wave wins 2: jacks, Rosen. Tie breaker for the last seat (one seat given to one of the other parties)
    CplBallot *ballot1 = new CplBallot(",,1,,,");
    CplBallot *ballot12 = new CplBallot(",,1,,,");
    CplBallot *ballot13 = new CplBallot(",,1,,,");
    CplBallot *ballot14 = new CplBallot(",,1,,,");
    CplBallot *ballot15 = new CplBallot(",,1,,,");
    CplBallot *ballot16 = new CplBallot(",,1,,,");
    CplBallot *ballot17 = new CplBallot(",,1,,,");
    CplBallot *ballot18 = new CplBallot(",,1,,,");
    CplBallot *ballot19 = new CplBallot(",,1,,,");
    vector<Ballot*> cplVotes{ballot1, ballot12, ballot13, ballot14, ballot15, ballot16, ballot17, ballot18, ballot19};
    party3.setVotes(cplVotes);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    Cpl cpl = Cpl(6, parties, 3, 9);

    cpl.runCpl();

    EXPECT_EQ(cpl.getParties().at(0).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(1).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(2).getInitialSeatsWon(), 2);
    EXPECT_EQ(cpl.getParties().at(3).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getInitialSeatsWon(), 0);
}

TEST_F(CplTest, CplAvgElectionNoTies) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        Party party4 = Party("Reform", {"McClure", "Berg"});
        Party party5 = Party("Green", {"Zheng", "Melvin"});
        Party party6 = Party("Independent", {"Peters"});
    // Results : democratic, republican and new wave each win one seat : dem (foster), rep (green), new wave (jacks)
    CplBallot *ballot1 = new CplBallot("1,,,,,");
    CplBallot *ballot14 = new CplBallot("1,,,,,");
    CplBallot *ballot12 = new CplBallot("1,,,,,");
    CplBallot *ballot13 = new CplBallot("1,,,,,");
    CplBallot *ballot2 = new CplBallot(",1,,,,");
    CplBallot *ballot22 = new CplBallot(",1,,,,");
    CplBallot *ballot3 = new CplBallot(",,1,,,");
    CplBallot *ballot32 = new CplBallot(",,1,,,");
    CplBallot *ballot33 = new CplBallot(",,1,,,");
    vector<Ballot*> cplVotes1{ballot1, ballot12, ballot13, ballot14};
    vector<Ballot*> cplVotes2{ballot2, ballot22};
    vector<Ballot*> cplVotes3{ballot3, ballot32, ballot33};
    party1.setVotes(cplVotes1);
    party2.setVotes(cplVotes2);
    party3.setVotes(cplVotes3);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    Cpl cpl = Cpl(6, parties, 3, 9);

    cpl.runCpl();

    EXPECT_EQ(cpl.getParties().at(0).getInitialSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(1).getInitialSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(2).getInitialSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(3).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getInitialSeatsWon(), 0);
}

TEST_F(CplTest, CplAvgElectionTies) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        Party party4 = Party("Reform", {"McClure", "Berg"});
        Party party5 = Party("Green", {"Zheng", "Melvin"});
        Party party6 = Party("Independent", {"Peters"});
    // Results : democratic wins first round and wins one seat: foster republican and new wave tie but there are two seats left, so each gets one: rep (green), new (jacks)
    CplBallot *ballot1 = new CplBallot("1,,,,,");
    CplBallot *ballot12 = new CplBallot("1,,,,,");
    CplBallot *ballot13 = new CplBallot("1,,,,,");
    CplBallot *ballot2 = new CplBallot(",1,,,,");
    CplBallot *ballot22 = new CplBallot(",1,,,,");
    CplBallot *ballot3 = new CplBallot(",,1,,,");
    CplBallot *ballot32 = new CplBallot(",,1,,,");
    CplBallot *ballot5 = new CplBallot(",,,,1,");
    CplBallot *ballot6 = new CplBallot(",,,,,1");
    vector<Ballot*> cplVotes1{ballot1, ballot12, ballot13};
    vector<Ballot*> cplVotes2{ballot2, ballot22};
    vector<Ballot*> cplVotes3{ballot3, ballot32};
    vector<Ballot*> cplVotes5{ballot5};
    vector<Ballot*> cplVotes6{ballot6};
    party1.setVotes(cplVotes1);
    party2.setVotes(cplVotes2);
    party3.setVotes(cplVotes3);
    party5.setVotes(cplVotes5);
    party6.setVotes(cplVotes6);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    Cpl cpl = Cpl(6, parties, 3, 9);

    cpl.runCpl();

    EXPECT_EQ(cpl.getParties().at(0).getInitialSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(1).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(2).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(3).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getInitialSeatsWon(), 0);

    EXPECT_EQ(cpl.getParties().at(0).getFinalSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(1).getFinalSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(2).getFinalSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(3).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getFinalSeatsWon(), 0);
}

TEST_F(CplTest, CplLayeredTies) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        Party party4 = Party("Reform", {"McClure", "Berg"});
        Party party5 = Party("Green", {"Zheng", "Melvin"});
        Party party6 = Party("Independent", {"Peters"});
    // Results: democratic wins first seat: foster
    // Then tie breaker between republican, new wave, and independent: one seat goes to one of those
    // Second tie breaker between loser of above: one seat goes to one of those
    CplBallot *ballot1 = new CplBallot("1,,,,,");
    CplBallot *ballot12 = new CplBallot("1,,,,,");
    CplBallot *ballot13 = new CplBallot("1,,,,,");
    CplBallot *ballot2 = new CplBallot(",1,,,,");
    CplBallot *ballot22 = new CplBallot(",1,,,,");
    CplBallot *ballot3 = new CplBallot(",,1,,,");
    CplBallot *ballot32 = new CplBallot(",,1,,,");
    CplBallot *ballot6 = new CplBallot(",,,,,1");
    CplBallot *ballot62 = new CplBallot(",,,,,1");
    vector<Ballot*> cplVotes1{ballot1, ballot12, ballot13};
    vector<Ballot*> cplVotes2{ballot2, ballot22};
    vector<Ballot*> cplVotes3{ballot3, ballot32};
    vector<Ballot*> cplVotes6{ballot6, ballot62};
    party1.setVotes(cplVotes1);
    party2.setVotes(cplVotes2);
    party3.setVotes(cplVotes3);
    party6.setVotes(cplVotes6);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    Cpl cpl = Cpl(6, parties, 3, 9);

    cpl.runCpl();

    EXPECT_EQ(cpl.getParties().at(0).getInitialSeatsWon(), 1);
    EXPECT_EQ(cpl.getParties().at(1).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(2).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(3).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getInitialSeatsWon(), 0);

    EXPECT_EQ(cpl.getParties().at(0).getFinalSeatsWon(), 1);
    EXPECT_GE(cpl.getParties().at(1).getFinalSeatsWon(), 0);
    EXPECT_GE(cpl.getParties().at(2).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(3).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getFinalSeatsWon(), 0);
    EXPECT_GE(cpl.getParties().at(5).getFinalSeatsWon(), 0);

    EXPECT_EQ(cpl.getParties().at(2).getFinalSeatsWon() + cpl.getParties().at(1).getFinalSeatsWon() + cpl.getParties().at(5).getFinalSeatsWon(), 2);
}

TEST_F(CplTest, CplTie) {
    Party party1 = Party("Democratic", {"Foster", "Voltz", "Pike"});
        Party party2 = Party("Republican", {"Green", "Xu", "Wang"});
        Party party3 = Party("New Wave", {"Jacks", "Rosen"});
        Party party4 = Party("Reform", {"McClure", "Berg"});
        Party party5 = Party("Green", {"Zheng", "Melvin"});
        Party party6 = Party("Independent", {"Peters"});
    // Results: tie breaker between democratic and republican: winner gets one seat
    CplBallot *ballot1 = new CplBallot("1,,,,,");
    CplBallot *ballot12 = new CplBallot("1,,,,,");
    CplBallot *ballot2 = new CplBallot(",1,,,,");
    CplBallot *ballot22 = new CplBallot(",1,,,,");
    vector<Ballot*> cplVotes1{ballot1, ballot12};
    vector<Ballot*> cplVotes2{ballot2, ballot22};
    party1.setVotes(cplVotes1);
    party2.setVotes(cplVotes2);
    vector<Party> parties{party1, party2, party3, party4, party5, party6};
    Cpl cpl = Cpl(6, parties, 1, 4);

    cpl.runCpl();

    EXPECT_EQ(cpl.getParties().at(0).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(1).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(2).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(3).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getInitialSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getInitialSeatsWon(), 0);

    EXPECT_GE(cpl.getParties().at(0).getFinalSeatsWon(), 0);
    EXPECT_GE(cpl.getParties().at(1).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(2).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(3).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(4).getFinalSeatsWon(), 0);
    EXPECT_EQ(cpl.getParties().at(5).getFinalSeatsWon(), 0);

    EXPECT_EQ(cpl.getParties().at(0).getFinalSeatsWon() + cpl.getParties().at(1).getFinalSeatsWon(), 1);
}

// TEST_F(CplTest, RunCpl) {
//     //2 parties test, no extras, no remainders
//     //cpl 5 seats, 10 ballots
//     party1.setVoteCount(6);
//     party2.setVoteCount(4);

//     party1.setCandidateList(["Jane", "Jill", "Bella"]);
//     party2.setCandidateList(["Tom", "Joe"]);

//     // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
//     cpl.runCpl();
//     // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
//     EXPECT_EQ(party1.getSeatsWon(), 3);
//     EXPECT_EQ(party2.getSeatsWon(), 2);
//     // party seats EXtra
//     EXPECT_EQ(party1.getSeatsExtra(), 0);
//     EXPECT_EQ(party2.getSeatsExtra(), 0);
//     // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num

//     //2 parties test, extras, no remainders
//     //cpl 5 seats, 10 ballots
//     party1.setVoteCount(6);
//     party2.setVoteCount(4);

//     party1.setCandidateList(["Tom", "Joe"]);
//     party2.setCandidateList(["Jane", "Jill", "Bella"]);

//     // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
//     cpl.runCpl();
//     // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
//     EXPECT_EQ(party1.getSeatsWon(), 3);
//     EXPECT_EQ(party2.getSeatsWon(), 2);
//     // party seats EXtra
//     EXPECT_EQ(party1.getSeatsExtra(), 1);
//     EXPECT_EQ(party2.getSeatsExtra(), 0);
//     // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num

//     //remainder test
//     //2 parties test, extras, remainders
//     //cpl 5 seats, 10 ballots
//     party1.setVoteCount(7);
//     party2.setVoteCount(3);

//     party1.setCandidateList(["Tom", "Joe"]);
//     party2.setCandidateList(["Jane", "Jill", "Bella"]);

//     // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
//     cpl.runCpl();
//     // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
//     EXPECT_EQ(party1.getSeatsWon(), 3);
//     EXPECT_EQ(party2.getSeatsWon(), 1);
    
//     EXPECT_EQ(party1.getSeatsExtra(), 1);
//     EXPECT_EQ(party2.getSeatsExtra(), 0);
//     // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num
//     // not sure how to test to make sure last seat got allocated

//     //3 parties test, 2 extra seats
//     //cpl2 5 seats, 11 ballots
//     party1.setVoteCount(6);
//     party2.setVoteCount(4);
//     party3.setVoteCount(1);

//     party1.setCandidateList(["Jane", "Jill", "Bella"]);
//     party2.setCandidateList(["Tom", "Joe"]);
//     party3.setCandidateList(["Zach"]);

//     // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
//     cpl.runCpl();
//     // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
//     EXPECT_EQ(party1.getSeatsWon(), 2);
//     EXPECT_EQ(party2.getSeatsWon(), 1);
//     EXPECT_EQ(party3.getSeatsWon(), 0);

//     EXPECT_EQ(party1.getSeatsExtra(), 0);
//     EXPECT_EQ(party2.getSeatsExtra(), 0);
//     EXPECT_EQ(party3.getSeatsExtra(), 0);
//     // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num
//     // not sure how to test to make sure last seats got allocated
//     // EXPECT_EQ(party1.getSeatsWon() + party2.getSeatsWon() + party3.getSeatsWon(), 5);
// }

// TEST_F(CplTest, DetermineQuota) {
//     int expectedOutput;

//     //even % test
//     party1.setVoteCount(4);
//     expectedOutput = 4 / 10; //party votes / total votes

//     EXPECT_EQ(cpl.determineQuota(party1), expectedOutput);
//     EXPECT_EQ(cpl.determineQuota(party1) - expectedOutput, 0);

//     //non even % test
//     party2.setVoteCount(4);
//     expectedOutput = 4 / 11; //party votes / total votes

//     EXPECT_EQ(cpl2.determineQuota(party2), expectedOutput);
//     EXPECT_EQ(cpl2.determineQuota(party2) - expectedOutput, 0);

//     //100% test
//     party1.setVoteCount(10);
//     expectedOutput = 10 / 10; //party votes / total votes

//     EXPECT_EQ(cpl.determineQuota(party1), expectedOutput);
//     EXPECT_EQ(cpl.determineQuota(party1), 1); // might need to change
//     EXPECT_EQ(cpl.determineQuota(party1) - expectedOutput, 0);

//     //0% test
//     party2.setVoteCount(0);
//     expectedOutput = 0 / 11; //party votes / total votes

//     EXPECT_EQ(cpl2.determineQuota(party2), expectedOutput);
//     EXPECT_EQ(cpl2.determineQuota(party2), 0); //might need to change
//     EXPECT_EQ(cpl2.determineQuota(party2) - expectedOutput, 0);
// }

