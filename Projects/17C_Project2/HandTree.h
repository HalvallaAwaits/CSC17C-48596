/* 
 * File:   HandTree.h
 * Author: Joe
 *
 * Created on December 6, 2014, 11:18 AM
 */

//Libraries
#include <iostream>
using namespace std;

#ifndef HANDTREE_H
#define	HANDTREE_H

class HandTree{
private:
    struct TreeNode{
        int value;            //Holds the value in the node
        TreeNode *left;       //Points to the left child node
        TreeNode *right;      //Points to the right child node
    };
    TreeNode *root;           //Points to the root node
    
    //Private Member functions
    void insert(TreeNode *&, TreeNode *&);
    void destroySubTree(TreeNode *);
    void deleteNode(int,TreeNode *&);
    void makeDeletion(TreeNode *&);
    void displayInOrder(TreeNode *) const;
    void displayPreOrder(TreeNode *) const;
    void displayPostOrder(TreeNode *) const;
    
public:
    //Private Member Functions
    //Constructor
    HandTree()
        {root=NULL;}
    //Destructor
    ~HandTree()
        {destroySubTree(root);}
    //Mutators
    void insertNode(int);
    void remove(int);
    //Accessors
    bool searchNode(int);
    //Displays using all 3 versions of traversal
    void displayInOrder() const
        {displayInOrder(root);}
    void displayPreOrder() const
        {displayPreOrder(root);}
    void displayPostOrder() const
        {displayPostOrder(root);}    
};

#endif	/* HANDTREE_H */