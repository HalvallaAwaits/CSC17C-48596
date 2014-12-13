/* 
 * File:   main.cpp
 * Author: Joe
 *
 * Created on December 5, 2014, 4:04 PM

 * Tree completed   - Player and CPU hands are stored in binary trees
 * Hash completed   - Password is hashed and stored, compared when attempting
 *                    to log into an existing player account.
 * Queue removed    - Was demonstrated in midterm, previously the hand was
 *                    stored as a queue
 */

//Libraries
#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

//Our Libraries
#include "Card.h"
#include "DeckStack.h"
#include "Player.h"
#include "HandTree.h"

//Function Prototypes
vector<Card> bldDck(int);
void shuffle(vector<Card> &,int,DeckStack &);
void frstDeal(DeckStack &,int &, Player &, Player &,HandTree &,HandTree &);
void deal(DeckStack &,int &,Player &,HandTree &,bool);
void plyrTrn(Player &,DeckStack &,bool &,int &,HandTree &,bool);
void cpuTrn(Player &,DeckStack &,bool &,int &,HandTree &,bool &);
void result(Player &,Player &,bool &,bool &,map<string,int> &,int);
void reset(DeckStack &,Player &,Player &,int,int &,bool &,bool &,HandTree &,HandTree &, vector<Card>,bool &);
void userInfo(Player &);
void write(Player);
void display(Player &,HandTree &,bool);

//Execution Begins Here
int main(int argc, char** argv) {
    //Declare variables
    int nCards=52;               //number of cards in deck
    int nDealt=0;                //number of cards dealt
    vector<Card> unshflDck;      //holds an un-shuffled deck
    DeckStack myDeck;            //holds a shuffled deck in stack form
    std::srand(std::time(0));    //seed random number generator
    Card crdCatch;               //holds popped cards from stack/queue
    HandTree p1HandT;             //player's hand
    HandTree cpuHandT;            //cpu's hand
    char user;                   //if player is new to game or not
    Player p1;                   //holds player's info
    Player cpu;                  //holds cpu's info
    int strtFnd;                 //holds player starting funds
    int choice;                  //holds decision to hit, stand, etc
    char again;                  //holds decision to play again
    bool p1bj=false;             //player got a blackjack
    bool cpubj=false;            //cpu got a blackjack
    bool gameEnd=false;          //holds game end state 
    int betAmnt;
    
    //Create map for score
    map <string,int> score_map; //holds wins, losses and pushes
    score_map["P1 Wins: "]=0;
    score_map["P1 Losses: "]=0;
    score_map["CPU Wins: "]=0;
    score_map["CPU Losses: "]=0;
    score_map["Pushes: "]=0;
    
    //Introduce the game
    cout<<"Welcome to Black Jack!"<<endl<<endl;
    
    //get user information
    userInfo(p1);
    
    //set starting fund for end game comparison
    strtFnd=p1.getFunds();
    
    //Begin Play
    do{
        //Create an un-shuffled deck using a vector
        unshflDck=bldDck(nCards);
        
        //shuffle the deck and put into a DeckStack to begin play with
        shuffle(unshflDck,nCards,myDeck);        
        cout<<"\nBeginning Play!"<<endl<<"Current funds: "<<p1.getFunds()<<endl;
        
        //ask player how much to bet
        do{
            cout<<"How much would you like to bet (min 5)? ";
            cin>>betAmnt;
        }while(betAmnt<5);
        cout<<endl;
        
        //initial deal of two cards to player and cpu
        frstDeal(myDeck,nDealt,p1,cpu,p1HandT,cpuHandT);
        
        //Player's hit/stand phase
        plyrTrn(p1,myDeck,p1bj,nDealt,p1HandT,gameEnd);
        
        //CPU's hit/stand phase
        cpuTrn(cpu,myDeck,cpubj,nDealt,cpuHandT,gameEnd);
        
        //display both player hands
        cout<<"Here is your final hand:"<<endl;
        display(p1,p1HandT,gameEnd);
        cout<<"\nHere is the CPU's final hand:"<<endl;
        display(cpu,cpuHandT,gameEnd);
        
        //determine winner/loss/push
        result(p1,cpu,p1bj,cpubj,score_map,betAmnt);
        
        //reset and reshuffle for continued play
        reset(myDeck,p1,cpu,nCards,nDealt,p1bj,cpubj,p1HandT,cpuHandT,unshflDck,gameEnd);
        shuffle(unshflDck,nCards,myDeck);
        
        //Ask if user would like to play the game again
        cout<<"Would you like to play again? (Y/N)"<<endl;
        cin>>again;
        cout<<endl<<endl;
    }while(again=='y'||again=='Y');
    
    //output overall score and final funds
    cout<<"This Session's Results:"<<endl;
    map<string,int>::iterator iter;
    for (iter=score_map.begin(); iter!=score_map.end(); ++iter){
        cout<<iter->first<<": "<<iter->second<<endl;
    }
    cout<<"Funds: "<<p1.getFunds()<<endl;
    if(p1.getFunds()<0)cout<<"You're now in debt! Woops!"<<endl;
    else if(p1.getFunds()>strtFnd)cout<<"You made a profit! Congrats!"<<endl;
    else if(p1.getFunds()==strtFnd)cout<<"You broke even!"<<endl;
    else
        cout<<"You lost money..."<<endl;
    
    //update file data before exit
    write(p1);
    
    //Exit stage right
    return 0;
}

void userInfo(Player &p1){
    string p1name;                      //take input for player's name
    string pass;                        //player input for password
    string fName;                       //holds file name
    fstream myFile;                     //to output player info to file
    size_t pwhash;                      //holds password hash
    int funds, wins, losses, pushes;    //holds funds, wins, losses, pushes
    unsigned int seed=0;
    unsigned hash=seed;
    
    //prompt for user info
    cout<<"Enter a user ID (if new, will be created): "<<endl;
    cin>>p1name;
    
    //attempt to open file based on given ID
    fName=p1name+".txt";
    myFile.open(fName.c_str());
    
    //check to see if file was opened
    if(!myFile.is_open()){
        //if file not opened, create new user
        cout<<"ID not recognized, creating new user."<<endl;
        p1.setName(p1name);
        cout<<"Enter a password: ";
        cin>>pass;
        
        //Hash user's password and store this for future log in comparison
        p1.hash(pass);
        
        //create file based on player name
        myFile.open(fName.c_str());
        
        //write player info to file to store for later use
        myFile<<p1.getName()<<"\r\n";
        myFile<<p1.getHash()<<"\r\n";
        myFile<<p1.getFunds()<<"\r\n";
        myFile<<p1.getWins()<<"\r\n";
        myFile<<p1.getLosses()<<"\r\n";
        myFile<<p1.getPushes()<<"\r\n";
    }
    else{
        //if file is opened, check password
        cout<<"User located!"<<endl;
        myFile>>p1name;
        p1.setName(p1name);
        myFile>>pwhash;
        p1.setHash(pwhash);
        
        //loop until password is correct
        do{
            cout<<"Enter your password: ";
            cin>>pass;
            
            //compare hash on file with hash of password player just entered
            for (int i=0;i<pass.length();i++){
                hash = hash * 101  +  pass[i];
            }
            
            //if password hash comparison is correct
            if(hash==pwhash){
                cout<<"Correct password entered!"<<endl;
                
                //read in rest of player information
                myFile>>funds;
                p1.setFunds(funds);
                myFile>>wins;
                p1.setWins(wins);
                myFile>>losses;
                p1.setLosses(losses);
                myFile>>pushes;
                p1.setPushes(pushes);
                
                //output all information
                cout<<"Name: "<<p1.getName()<<endl;
                cout<<"Funds: "<<p1.getFunds()<<endl;
                cout<<"Wins: "<<p1.getWins()<<endl;
                cout<<"Losses: "<<p1.getLosses()<<endl;
                cout<<"Pushes: "<<p1.getPushes()<<endl;
            }
            
            //if comparison fails
            else{
                cout<<"Incorrect password!"<<endl;
                hash=seed;
            }
        }while(hash!=pwhash);
    }                            
    myFile.close();
}

vector<Card> bldDck(int n){
    //Create an un-shuffled deck using a vector
    vector<Card> deck;
    for(int i=0;i<n;i++){
        Card card(i);
        deck.push_back(card);
    }
    return deck;
}

void shuffle(vector<Card> &deck,int n,DeckStack &dckStck){
    //shuffle vector card deck
    random_shuffle(deck.begin(),deck.end());
    
    //take vector deck and convert to stack to deal from
    vector<Card>::iterator iter;       //iterator to move through vector
    for(iter=deck.begin();iter!=deck.end();iter++){
        dckStck.push(*iter);
    }
}

void frstDeal(DeckStack &myDeck,int &nDealt, Player &p1, Player &cpu,
        HandTree &p1HandT,HandTree &cpuHandT){
    Card crdCatch;          //holds cards popped
    for(int i=0;i<4;i++){
        if(i%2==0){
            //deal a card
            myDeck.pop(crdCatch);
            p1HandT.insertNode(crdCatch);
            p1HandT.addCard(crdCatch);
            
            //if first draw is ace set val to 11 instead of 1
            if(crdCatch.getName()=='A'&&nDealt==0)
                p1.setValue(11);
            
            //if first draw is not ace and second is, set ace to 11 value
            else if(crdCatch.getName()=='A'&&p1.getValue()<11)
                p1.setValue(11);
            
            //if first two draws are aces
            else if(crdCatch.getName()=='A'&&p1.getValue()==11){
                p1.setValue(1);
                p1HandT.addAce(1);
            }
            
            //Any other value
            else
                p1.setValue(crdCatch.getValue());
            nDealt++;
        }
        if(i%2==1){
            //deal a card
            myDeck.pop(crdCatch);
            cpuHandT.insertNode(crdCatch);
            cpuHandT.addCard(crdCatch);            
            
            //if first draw is ace set val to 11 instead of 1
            if(crdCatch.getName()=='A'&&nDealt==0)
                cpu.setValue(11);
            
            //if first draw is not ace and second is, set ace to 11 value
            else if(crdCatch.getName()=='A'&&cpu.getValue()<11)
                cpu.setValue(11);
            
            //if first two draws are aces
            else if(crdCatch.getName()=='A'&&cpu.getValue()==11){
                cpu.setValue(1);
                cpuHandT.addAce(1);
        }
            else
                cpu.setValue(crdCatch.getValue());
            nDealt++;
        }
    }
    
    //output from initial deal
    cout<<p1.getName()<<"'s hand:"<<endl;
    cout<<"  ____ ________"<<endl;
    cout<<" |"<<p1HandT.getCard(0).getName()<<p1HandT.getCard(0).getSuit()<<"  |"<<p1HandT.getCard(1).getName()<<p1HandT.getCard(1).getSuit()<<"      |"<<endl;
    cout<<" |    |        |"<<endl;
    cout<<" |    |        |"<<endl;
    cout<<" |    |        |"<<endl;
    cout<<" |____|______"<<p1HandT.getCard(1).getName()<<p1HandT.getCard(1).getSuit()<<"|"<<endl<<endl<<endl;
    cout<<cpu.getName()<<"'s hand:"<<endl;
    cout<<"  ____ ________"<<endl;
    cout<<" |    |"<<cpuHandT.getCard(1).getName()<<cpuHandT.getCard(1).getSuit()<<"      |"<<endl;
    cout<<" |    |        |"<<endl;
    cout<<" |    |        |"<<endl;
    cout<<" |    |        |"<<endl;
    cout<<" |____|______"<<cpuHandT.getCard(1).getName()<<cpuHandT.getCard(1).getSuit()<<"|"<<endl<<endl<<endl;
    
}

void deal(DeckStack &myDeck,int &nDealt,Player &plyr,HandTree &handT,bool gameEnd){
    Card crdCatch;       //holds popped cards
    
    //deal a card
    myDeck.pop(crdCatch);
    handT.insertNode(crdCatch);
    handT.addCard(crdCatch);
    
    //determine value of aces drawn
    if(crdCatch.getName()=='A'){
        if(plyr.getValue()<=10){
            plyr.setValue(11);
            handT.addAce(1);
        }
        else
            plyr.setValue(1);
    }
    else
        plyr.setValue(crdCatch.getValue());
    
    //display draw result
    cout<<plyr.getName()<<" hits and receives card: "<<crdCatch.getName()<<crdCatch.getSuit()<<endl;
    cout<<plyr.getName()<<" has "<<handT.getNumHand()<<" cards in hand."<<endl;
    cout<<endl;
}

void plyrTrn(Player &p1,DeckStack &myDeck,bool &p1bj,int &nDealt,
        HandTree &p1HandT,bool gameEnd){
    int choice;                  //holds decision to hit, stand, etc
    
    //check for blackjack from initial deal
    if(p1.getValue()==21){
        cout<<"You got a Blackjack!"<<endl;
        p1bj=true;
    }
    
    //if not 21
    if(p1.getValue()<21){
        do{
            //prompt user for hit or stand decision
            cout<<endl<<p1.getName()<<" hand total: "<<p1.getValue()<<endl;
            cout<<"What would you like to do?"<<endl;
            cout<<"1. Hit"<<endl<<"2. Stand"<<endl;
            do{
                cin>>choice;
            }while(choice!=1&&choice!=2);
            cout<<endl;
            
            //if choice is 1, deal another card
            if(choice==1){
                deal(myDeck,nDealt,p1,p1HandT,gameEnd);
                
                //display hand
                display(p1,p1HandT,gameEnd);
            }
            
            //if player has aces still at value 11 and this draw busts,
            //reduce value of existing ace to 1
            if(p1.getValue()>21&&p1HandT.getNumAces()>0){
                p1.setValue(-10);
                p1HandT.addAce(-1);
            }
            
        }while(choice==1&&p1.getValue()<=21);
        
        //output result of player's hits/stand
        if(choice==2)cout<<"You stayed at "<<p1.getValue()<<"."<<endl;
        if(p1.getValue()==21)cout<<"You got 21!"<<endl;
        }
    cout<<endl;
}

void cpuTrn(Player &cpu,DeckStack &myDeck,bool &cpubj,int &nDealt,
        HandTree &cpuHandT,bool &gameEnd){
    cout<<"The CPU is now going to hit/stand."<<endl;
    
    //if cpu has blackjack
    if(cpu.getValue()==21){
        cout<<"The CPU has a blackjack!"<<endl;
        cpubj=true;
    }
    
    //if cpu has 17 or greater, stand
    else if(cpu.getValue()>=17){
        cout<<"The CPU stands at "<<cpu.getValue()<<"."<<endl;
    }
    
    //hit if under 17
    else{
        do{
            deal(myDeck,nDealt,cpu,cpuHandT,gameEnd);
        }while(cpu.getValue()<=16);
    }
    cout<<endl;
    gameEnd=true;
}

void result(Player &p1, Player &cpu,bool &p1bj,bool &cpubj,map<string,
        int> &score,int bet){
    int tempFunds=0;           //used to increase/decrease when winning/losing
    cout<<"Your hand value: "<<p1.getValue()<<"     CPU's hand value: "<<cpu.getValue()<<endl;
    
    //if you bust, you lose
    if(p1.getValue()>21){
        cout<<"You busted with "<<p1.getValue()<<"!"<<endl;
        p1.setLosses(1);
        cpu.setWins(1);
        score["P1 Losses: "]++;
        score["CPU Wins: "]++;
        tempFunds=p1.getFunds();
        tempFunds-=bet;
        p1.setFunds(tempFunds);
        write(p1);
    }
    
    //if the cpu busts, you win
    else if(cpu.getValue()>21){
        cout<<"CPU busted with "<<cpu.getValue()<<"!"<<endl;
        p1.setWins(1);
        cpu.setLosses(1);
        score["P1 Wins: "]++;
        score["CPU Losses: "]++;
        tempFunds=p1.getFunds();
        if(p1bj){
            tempFunds+=bet*3/2;
            p1.setFunds(tempFunds);
            write(p1);
        }
        else{
            tempFunds+=bet;
            p1.setFunds(tempFunds);
            write(p1);
        }
    }
    
    //if both have blackjack, push
    else if(p1bj&&cpubj){
        cout<<"This game is a push!"<<endl;
        p1.setPushes(1);
        cpu.setPushes(1);
        score["Pushes: "]++;
        write(p1);
    }
    
    //if both have same value
    else if(p1.getValue()==cpu.getValue()){
        
        //if p1 has blackjack, p1 wins
        if(p1bj){
            cout<<p1.getName()<<" wins!"<<endl;
            p1.setWins(1);
            cpu.setLosses(1);
            score["P1 Wins: "]++;
            score["CPU Losses: "]++;
            tempFunds=p1.getFunds();
            tempFunds+=bet*3/2;
            p1.setFunds(tempFunds);
            write(p1);
        }
        
        //if cpu has blackjack, cpu wins
        else if(cpubj){
            cout<<"CPU wins with Blackjack!"<<endl;
            p1.setLosses(1);
            cpu.setWins(1);
            score["P1 Losses: "]++;
            score["CPU Wins: "]++;
            tempFunds=p1.getFunds();
            tempFunds-=bet;
            p1.setFunds(tempFunds);
            write(p1);
        }
        
        //if just same value, push
        else{
            cout<<"This game is a push!"<<endl;
            p1.setPushes(1);
            cpu.setPushes(1);
            score["Pushes: "]++;
            write(p1);
        }
    }
    
    //if p1 is closer to 21, p1 wins
    else if(p1.getValue()>cpu.getValue()&&p1.getValue()<=21){
        cout<<p1.getName()<<" wins!"<<endl;
        p1.setWins(1);
        cpu.setLosses(1);
        score["P1 Wins: "]++;
        score["CPU Losses: "]++;
        tempFunds=p1.getFunds();
        tempFunds+=bet;
        p1.setFunds(tempFunds);
        write(p1);
    }
    
    //if cpu is closer to 21, cpu wins
    else{
        cout<<"CPU wins with "<<cpu.getValue()<<"!"<<endl;
        p1.setLosses(1);
        cpu.setWins(1);
        score["P1 Losses: "]++;
        score["CPU Wins: "]++;
        tempFunds=p1.getFunds();
        tempFunds-=bet;
        p1.setFunds(tempFunds);
        write(p1);
    }
}

void reset(DeckStack &dckStck,Player &p1,Player &cpu,int n,int &nDealt,
           bool &p1bj,bool &cpubj,HandTree &p1HandT,HandTree &cpuHandT, 
           vector<Card> deck,bool &gameEnd){
    Card card;       //used to pop cards out of deck
    //empty player and CPU hands
    for(int i=0;i<deck.size();i++){
        if(p1HandT.searchNode(deck[i]))p1HandT.remove(deck[i]);
        if(cpuHandT.searchNode(deck[i]))cpuHandT.remove(deck[i]);
    }
    for(int i=0;i<deck.size();i++){
        if(p1HandT.searchNode(deck[i]))p1HandT.remove(deck[i]);
        if(cpuHandT.searchNode(deck[i]))cpuHandT.remove(deck[i]);
    }
    //clear current deck stack to put fresh shuffled deck in
    while(!dckStck.isEmpty()){
        dckStck.pop(card);
    }
    //clear player info
    p1HandT.resetNumHand();
    p1HandT.resetNumAces();
    p1HandT.clearHand();
    cpuHandT.resetNumHand();
    cpuHandT.resetNumAces();
    cpuHandT.clearHand();
    p1.resetValue();
    cpu.resetValue();
    p1bj=false;
    cpubj=false;
    gameEnd=false;
    nDealt=0;
}

void write(Player p1){
    string fName;                 //holds file name
    ofstream outFile;            //to output player info to file
    
    //open file based on player name
    fName=p1.getName()+".txt";
    outFile.open(fName.c_str());
    //write gameplay changes to file
    outFile<<p1.getName()<<"\r\n";
    outFile<<p1.getHash()<<"\r\n";
    outFile<<p1.getFunds()<<"\r\n";
    outFile<<p1.getWins()<<"\r\n";
    outFile<<p1.getLosses()<<"\r\n";
    outFile<<p1.getPushes()<<"\r\n";
    outFile.close();
}

void display(Player &plyr,HandTree &handT,bool gameEnd){
    //output hand
    cout<<plyr.getName()<<"'s hand:"<<endl;
    if(handT.getNumHand()==2){
        cout<<"  ____ ________"<<endl;
        cout<<" |"<<handT.getCard(0).getName()<<handT.getCard(0).getSuit()
                <<"  |"<<handT.getCard(1).getName()<<handT.getCard(1).getSuit()
                <<"      |"<<endl;
        cout<<" |    |        |"<<endl;
        cout<<" |    |        |"<<endl;
        cout<<" |    |        |"<<endl;
        cout<<" |____|______"<<handT.getCard(1).getName()
                <<handT.getCard(1).getSuit()<<"|"<<endl<<endl<<endl;
    }
    else if(handT.getNumHand()==3){
        cout<<"  ____ ____ ________"<<endl;
        cout<<" |"<<handT.getCard(0).getName()<<handT.getCard(0).getSuit()
                <<"  |"<<handT.getCard(1).getName()<<handT.getCard(1).getSuit()
                <<"  |"<<handT.getCard(2).getName()<<handT.getCard(2).getSuit()
                <<"      |"<<endl;
        cout<<" |    |    |        |"<<endl;
        cout<<" |    |    |        |"<<endl;
        cout<<" |    |    |        |"<<endl;
        cout<<" |____|____|______"<<handT.getCard(2).getName()
                <<handT.getCard(2).getSuit()<<"|"<<endl<<endl<<endl;
    }
    else if(handT.getNumHand()==4){
        cout<<"  ____ ____ ____ ________"<<endl;
        cout<<" |"<<handT.getCard(0).getName()<<handT.getCard(0).getSuit()
                <<"  |"<<handT.getCard(1).getName()<<handT.getCard(1).getSuit()
                <<"  |"<<handT.getCard(2).getName()<<handT.getCard(2).getSuit()
                <<"  |"<<handT.getCard(3).getName()<<handT.getCard(3).getSuit()
                <<"      |"<<endl;
        cout<<" |    |    |    |        |"<<endl;
        cout<<" |    |    |    |        |"<<endl;
        cout<<" |    |    |    |        |"<<endl;
        cout<<" |____|____|____|______"<<handT.getCard(3).getName()
                <<handT.getCard(3).getSuit()<<"|"<<endl<<endl<<endl;
    }
    else if(handT.getNumHand()==5){
        cout<<"  ____ ____ ____ ____ ________"<<endl;
        cout<<" |"<<handT.getCard(0).getName()<<handT.getCard(0).getSuit()
                <<"  |"<<handT.getCard(1).getName()<<handT.getCard(1).getSuit()
                <<"  |"<<handT.getCard(2).getName()<<handT.getCard(2).getSuit()
                <<"  |"<<handT.getCard(3).getName()<<handT.getCard(3).getSuit()
                <<"  |"<<handT.getCard(4).getName()<<handT.getCard(4).getSuit()
                <<"      |"<<endl;
        cout<<" |    |    |    |    |        |"<<endl;
        cout<<" |    |    |    |    |        |"<<endl;
        cout<<" |    |    |    |    |        |"<<endl;
        cout<<" |____|____|____|____|______"<<handT.getCard(4).getName()
                <<handT.getCard(4).getSuit()<<"|"<<endl<<endl<<endl;
    }
    else if(handT.getNumHand()==6){
        cout<<"  ____ ____ ____ ____ ____ ________"<<endl;
        cout<<" |"<<handT.getCard(0).getName()<<handT.getCard(0).getSuit()
                <<"  |"<<handT.getCard(1).getName()<<handT.getCard(1).getSuit()
                <<"  |"<<handT.getCard(2).getName()<<handT.getCard(2).getSuit()
                <<"  |"<<handT.getCard(3).getName()<<handT.getCard(3).getSuit()
                <<"  |"<<handT.getCard(4).getName()<<handT.getCard(4).getSuit()
                <<"  |"<<handT.getCard(5).getName()<<handT.getCard(5).getSuit()
                <<"      |"<<endl;
        cout<<" |    |    |    |    |    |        |"<<endl;
        cout<<" |    |    |    |    |    |        |"<<endl;
        cout<<" |    |    |    |    |    |        |"<<endl;
        cout<<" |____|____|____|____|____|______"<<handT.getCard(5).getName()
                <<handT.getCard(5).getSuit()<<"|"<<endl<<endl<<endl;
    }
    else if(handT.getNumHand()==7){
        cout<<"  ____ ____ ____ ____ ____ ____ ________"<<endl;
        cout<<" |"<<handT.getCard(0).getName()<<handT.getCard(0).getSuit()
                <<"  |"<<handT.getCard(1).getName()<<handT.getCard(1).getSuit()
                <<"  |"<<handT.getCard(2).getName()<<handT.getCard(2).getSuit()
                <<"  |"<<handT.getCard(3).getName()<<handT.getCard(3).getSuit()
                <<"  |"<<handT.getCard(4).getName()<<handT.getCard(4).getSuit()
                <<"  |"<<handT.getCard(5).getName()<<handT.getCard(5).getSuit()
                <<"  |"<<handT.getCard(6).getName()<<handT.getCard(6).getSuit()
                <<"      |"<<endl;
        cout<<" |    |    |    |    |    |    |        |"<<endl;
        cout<<" |    |    |    |    |    |    |        |"<<endl;
        cout<<" |    |    |    |    |    |    |        |"<<endl;
        cout<<" |____|____|____|____|____|____|______"<<handT.getCard(6).getName()
                <<handT.getCard(6).getSuit()<<"|"<<endl<<endl<<endl;
    }    
}