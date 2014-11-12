/* 
 * File:   main.cpp
 * Author: Joe
 * Created on November 8, 2014, 10:46 AM
 * 
 * Project 1: Black Jack
 * 
 * To Do List:
 * Project and writeup.
 * Utilize STL library - DONE
 * Maps - score keeping - DONE
 * Dynamic Stack - (linked list) shuffled deck to deal cards from - DONE
 * Queues - (dynamic queue) player hand - DONE
 * Iterators - use to traverse where applicable - DONE
 * Algorithms - use random_shuffle - DONE
 * Post to your repository, here and send an email.
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
using namespace std;

//Our Libraries
#include "Card.h"
#include "DeckStack.h"
#include "HandQueue.h"
#include "Player.h"

//Function Prototypes
vector<Card> bldDck(int);
void shuffle(vector<Card> &,int,DeckStack &);
void frstDeal(DeckStack &,HandQueue &,HandQueue &,int &, Player &, Player &);
void deal(DeckStack &,HandQueue &,int &,Player &);
void result(Player &,Player &,bool &,bool &,map<string,int> &,int);
void reset(HandQueue &,HandQueue &,DeckStack &,Player &,Player &,int,int &,bool &,bool &);

//Execution Begins Here
int main(int argc, char** argv) {
    //Declare variables
    int nCards=52;               //number of cards in deck
    int nDealt=0;                //number of cards dealt
    vector<Card> unshflDck;      //holds an un-shuffled deck
    DeckStack myDeck;            //holds a shuffled deck in stack form
    std::srand(std::time(0));    //seed random number generator
    Card crdCatch;               //holds popped cards from stack/queue
    HandQueue p1Hand;            //player's hand in queue form
    HandQueue cpuHand;           //cpu's hand in queue form
    Player p1;                   //holds player's info
    string p1name;               //take input for player's name
    Player cpu;                  //holds cpu's info
    int choice;                  //holds decision to hit, stand, etc
    char again;                  //holds decision to play again
    bool p1bj=false;             //player got a blackjack
    bool cpubj=false;            //cpu got a blackjack
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
    //Get name from user
    cout<<"Please enter your name:";
    cin>>p1name;
    p1.setName(p1name);
    cout<<endl;
    //Begin Play
    do{
        //Create an un-shuffled deck using a vector
        unshflDck=bldDck(nCards);
        //shuffle the deck and put into a DeckStack to begin play with
        shuffle(unshflDck,nCards,myDeck);        
        //deal and continue play
        cout<<"Current funds: "<<p1.getFunds()<<endl;
        do{
            //ask player how much to bet
            cout<<"How much would you like to bet (min 5)? ";
            cin>>betAmnt;
        }while(betAmnt>p1.getFunds()||betAmnt<5);
        frstDeal(myDeck,p1Hand,cpuHand,nDealt,p1,cpu);
        if(p1.getValue()==21){
            cout<<"Blackjack!"<<endl;
            p1bj=true;
        }
        //Player decides hit or stand if no blackjack drawn
        if(p1.getValue()<21){
            do{
                cout<<p1.getName()<<" hand total: "<<p1.getValue()<<endl;
                cout<<"What would you like to do?"<<endl;
                cout<<"1. Hit"<<endl<<"2. Stand"<<endl;
                cin>>choice;
                cout<<endl;
                if(choice==1){
                    deal(myDeck,p1Hand,nDealt,p1);
                }
            }while(choice==1&&p1.getValue()<=21);
            //output result of player's hits/stand
            if(choice==2)cout<<"You stayed at "<<p1.getValue()<<"."<<endl;
            if(p1.getValue()==21)cout<<"You got 21!"<<endl;
        }
        cout<<endl;
        //CPUs hit/stand phase
        if(p1.getValue()<=21){
            cout<<"The CPU is now going to hit/stand."<<endl;
            //if cpu has blackjack
            if(cpu.getValue()==21){
                cout<<"The CPU has a blackjack!"<<endl;
                cpubj=true;
            }
            //if cpu has 17or greater, stand
            else if(cpu.getValue()>=17){
                cout<<"The CPU stands at "<<cpu.getValue()<<"."<<endl;
            }
            //hit if under 17
            else if(cpu.getValue()<=16){
                deal(myDeck,cpuHand,nDealt,cpu);
            }
        }
        //determine winner/loss/push
        result(p1,cpu,p1bj,cpubj,score_map,betAmnt);
        cout<<"Total cards dealt: "<<nDealt<<endl;        
        //reset game for additional plays
        reset(p1Hand,cpuHand,myDeck,p1,cpu,nCards,nDealt,p1bj,cpubj);
        shuffle(unshflDck,nCards,myDeck);
        //Ask if user would like to play the game again
        cout<<"Would you like to play again? (Y/N)"<<endl;
        cin>>again;
        cout<<endl<<endl;
    }while(again=='y'||again=='Y');
    //output overall score and end funds
    cout<<"Final Score:"<<endl;
    map<string,int>::iterator iter;
    for (iter=score_map.begin(); iter!=score_map.end(); ++iter){
        cout<<iter->first<<": "<<iter->second<<endl;
    }
    cout<<"Funds: "<<p1.getFunds()<<endl;
    if(p1.getFunds()<0)cout<<"You're now in debt! Woops!"<<endl;
    else if(p1.getFunds()>100)cout<<"You made a profit! Congrats!"<<endl;
    else if(p1.getFunds()==100)cout<<"You broke even!"<<endl;
    else
        cout<<"You lost money..."<<endl;
    
    //Exit stage right
    return 0;
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

void frstDeal(DeckStack &myDeck,HandQueue &p1Hand,HandQueue &cpuHand,int &nDealt, Player &p1, Player &cpu){
    //initial deal to players
    Card crdCatch;          //holds cards popped
    for(int i=0;i<4;i++){
        if(i%2==0){
            myDeck.pop(crdCatch);
            p1Hand.enqueue(crdCatch);
            //if first draw is ace set val to 11 instead of 1
            if(crdCatch.getName()=='A'&&nDealt==0)
                p1.setValue(11);
            //if first draw is not ace and second is, set ace to 11 value
            else if(crdCatch.getName()=='A'&&p1.getValue()<11)
                p1.setValue(11);
            //if first two draws are aces
            else if(crdCatch.getName()=='A'&&p1.getValue()==11)
                p1.setValue(1);
            //Any other value
            else
                p1.setValue(crdCatch.getValue());
            nDealt++;
            cout<<p1.getName()<<" receives card: "<<crdCatch.getName()<<crdCatch.getSuit()
                <<endl<<"P1 hand value: "<<p1.getValue()<<endl;
            cout<<p1.getName()<<" has "<<p1Hand.getNumHand()<<" cards in hand."<<endl<<endl;
        }
        if(i%2==1){
            myDeck.pop(crdCatch);
            cpuHand.enqueue(crdCatch);
            //if first draw is ace set val to 11 instead of 1
            if(crdCatch.getName()=='A'&&nDealt==0)
                cpu.setValue(11);
            //if first draw is not ace and second is, set ace to 11 value
            else if(crdCatch.getName()=='A'&&cpu.getValue()<11)
                cpu.setValue(11);
            //if first two draws are aces
            else if(crdCatch.getName()=='A'&&cpu.getValue()==11)
                cpu.setValue(1);
            else
                cpu.setValue(crdCatch.getValue());
            if(nDealt==1)
                cout<<"CPU receives hidden card."<<endl<<endl;
            else{
                cout<<"CPU receives card: "<<crdCatch.getName()<<crdCatch.getSuit()<<endl;
                cout<<"CPU has "<<cpuHand.getNumHand()<<" cards in hand."<<endl<<endl;
            }
            nDealt++;
        }
    }    
}

void deal(DeckStack &myDeck,HandQueue &hand,int &nDealt,Player &plyr){
    Card crdCatch;       //holds popped cards
    myDeck.pop(crdCatch);
    hand.enqueue(crdCatch);
    //determine value of aces drawn
    if(crdCatch.getName()=='A'){
        if(plyr.getValue()<=10)
            plyr.setValue(11);
        else
            plyr.setValue(1);
    }
    else
        plyr.setValue(crdCatch.getValue());
    cout<<plyr.getName()<<" hits and receives card: "<<crdCatch.getName()<<crdCatch.getSuit()<<endl;
    cout<<plyr.getName()<<" has "<<hand.getNumHand()<<" cards in hand."<<endl<<endl;
    nDealt++;
}

void result(Player &p1, Player &cpu,bool &p1bj,bool &cpubj,map<string,int> &score,int bet){
    //if you bust, you lose
    cout<<"Your Hand: "<<p1.getValue()<<"     CPU's Hand: "<<cpu.getValue()<<endl;
    if(p1.getValue()>21){
        cout<<"You busted with "<<p1.getValue()<<"!"<<endl;
        p1.setLosses(1);
        cpu.setWins(1);
        score["P1 Losses: "]++;
        score["CPU Wins: "]++;
        p1.setFunds(-bet);
    }
    //if the cpu busts, you win
    else if(cpu.getValue()>21){
        cout<<"CPU busted with "<<cpu.getValue()<<"!"<<endl;
        p1.setWins(1);
        cpu.setLosses(1);
        score["P1 Wins: "]++;
        score["CPU Losses: "]++;
        p1.setFunds(bet);
    }
    //if both have blackjack, push
    else if(p1bj&&cpubj){
        cout<<"This game is a push!"<<endl;
        p1.setPushes(1);
        cpu.setPushes(1);
        score["Pushes: "]++;
    }
    //if both have same value, push
    else if(p1.getValue()==cpu.getValue()){
        //if p1 has blackjack, p1 wins
        if(p1bj){
            cout<<p1.getName()<<" wins!"<<endl;
            p1.setWins(1);
            cpu.setLosses(1);
            score["P1 Wins: "]++;
            score["CPU Losses: "]++;
            p1.setFunds(bet*3/2);
        }
        //if cpu has blackjack, cpu wins
        else if(cpubj){
            cout<<"CPU wins with Blackjack!"<<endl;
            p1.setLosses(1);
            cpu.setWins(1);
            score["P1 Losses: "]++;
            score["CPU Wins: "]++;
            p1.setFunds(-bet);
        }
        //if just same value, push
        else{
            cout<<"This game is a push!"<<endl;
            p1.setPushes(1);
            cpu.setPushes(1);
            score["Pushes: "]++;
        }
    }
    //if p1 is closer to 21, p1 wins
    else if(p1.getValue()>cpu.getValue()&&p1.getValue()<=21){
        cout<<p1.getName()<<" wins!"<<endl;
        p1.setWins(1);
        cpu.setLosses(1);
        score["P1 Wins: "]++;
        score["CPU Losses: "]++;
        p1.setFunds(bet);
    }
    //if cpu is closer to 21, cpu wins
    else{
        cout<<"CPU wins with "<<cpu.getValue()<<"!"<<endl;
        p1.setLosses(1);
        cpu.setWins(1);
        score["P1 Losses: "]++;
        score["CPU Wins: "]++;
        p1.setFunds(-bet);
    }
}

void reset(HandQueue &p1Hand,HandQueue &cpuHand,DeckStack &dckStck,Player &p1,Player &cpu,int n,int &nDealt,bool &p1bj,bool &cpubj){
    Card card;       //used to pop cards out of deck
    //empty player and CPU hands
    p1Hand.clear();
    cpuHand.clear();
    //clear current deck stack to put fresh shuffled deck in
    while(!dckStck.isEmpty()){
        dckStck.pop(card);
    }
    //clear player info and cards dealt
    p1Hand.resetNumHand();
    cpuHand.resetNumHand();
    p1.resetValue();
    cpu.resetValue();
    p1bj=false;
    cpubj=false;
    nDealt=0;
}