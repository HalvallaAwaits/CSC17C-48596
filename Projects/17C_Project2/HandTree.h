/* 
 * File:   HandTree.h
 * Author: Joe
 *
 * Created on December 6, 2014, 11:18 AM
 */

//Libraries
#include <iostream>
#include "Card.h"
#include "Player.h"
using namespace std;

#ifndef HANDTREE_H
#define	HANDTREE_H

class HandTree{
private:
    struct TreeNode{
        Card data;            //Holds card data
        TreeNode *left;       //Points to the left child node
        TreeNode *right;      //Points to the right child node
    };
    TreeNode *root;           //Points to the root node
    int numHand;              //number of cards in hand
    int numAces;              //number of aces in hand
    vector<Card> hand;        //holds hand in vector form, for display
    
    //Private Member functions
    void insert(TreeNode *&, TreeNode *&);
    void destroySubTree(TreeNode *);
    void deleteNode(Card,TreeNode *&);
    void makeDeletion(TreeNode *&);
    void displayInOrder(TreeNode *,Player) const;
    void displayPreOrder(TreeNode *) const;
    void displayPostOrder(TreeNode *) const;
public:
    //Private Member Functions
    //Constructor
    HandTree();
    //Destructor
    ~HandTree()
        {destroySubTree(root);}
    //Mutators
    void insertNode(Card);
    void remove(Card);
    void resetNumHand()
        {numHand=0;}
    void addCard(Card crd)
        {hand.push_back(crd);}
    void addAce(int n)
        {numAces+=n;}
    void resetNumAces()
        {numAces=0;}
    //Accessors
    bool searchNode(Card);
    //Displays using all 3 versions of traversal
    void displayInOrder(Player) const;
    void displayPreOrder() const
        {displayPreOrder(root);}
    void displayPostOrder() const
        {displayPostOrder(root);}    
    int getNumHand()
        {return numHand;}
    int getNumAces()
        {return numAces;}
    Card getCard(int n)
        {return hand[n];}
    void clearHand()
        {hand.clear();}
};

#endif	/* HANDTREE_H */