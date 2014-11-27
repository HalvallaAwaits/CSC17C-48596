/* 
 * File:   BinaryTree.h
 * Author: Joe
 *
 * Created on November 26, 2014, 5:21 PM
 */

//Libraries
#include <iostream>
using namespace std;

#ifndef BINARYTREE_H
#define	BINARYTREE_H

class BinaryTree{
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
    BinaryTree()
        {root=NULL;}
    //Destructor
    ~BinaryTree()
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
#endif	/* BINARYTREE_H */