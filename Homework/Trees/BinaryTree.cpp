/* 
 * File:   BinaryTree.cpp
 * Author: Joe
 *
 * Created on November 26, 2014, 5:21 PM
 */

//Libraries
#include <iostream>
#include <cstdlib>
#include "BinaryTree.h"
using namespace std;

//public insert function
void BinaryTree::insertNode(int num){
    //create new node to hold value
    TreeNode *newNode=new TreeNode;    //points to new node
    newNode->value=num;
    newNode->left=newNode->right=NULL;
    
    //Insert the node
    insert(root,newNode);
    
}

//insert function
void BinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode){
    //if insert location is NULL then insert
    if(nodePtr==NULL)
        nodePtr=newNode;
    //if node exists, compare new value, if lesser, continue search left
    else if(newNode->value<nodePtr->value)
        insert(nodePtr->left,newNode);
    //if node exists, compare new value, if greater, continue search right
    else
        insert(nodePtr->right,newNode);
}

//in order display function
void BinaryTree::displayInOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        displayInOrder(nodePtr->left);
        cout<<nodePtr->value<<endl;
        displayInOrder(nodePtr->right);
    }
}

//pre order display function
void BinaryTree::displayPreOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        cout<<nodePtr->value<<endl;
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
}

//post order display function
void BinaryTree::displayPostOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        cout<<nodePtr->value<<endl;
    }
}

//search function
bool BinaryTree::searchNode(int num){
    TreeNode *nodePtr=root;
    while (nodePtr){
        if(nodePtr->value==num)
            return true;
        else if(num<nodePtr->value)
            nodePtr=nodePtr->left;
        else
            nodePtr=nodePtr->right;
    }
    return false;    
}

//public delete function which calls the delete node function
void BinaryTree::remove(int num){
    deleteNode(num,root);
}

//delete node function which determines which node to delete
void BinaryTree::deleteNode(int num, TreeNode *&nodePtr){
    //if less than, keep searching to the left
    if(num<nodePtr->value)
        deleteNode(num,nodePtr->left);
    //if greater than, keep searching to the right
    else if(num>nodePtr->value)
        deleteNode(num,nodePtr->right);
    //if equal, move on with deletion
    else
        makeDeletion(nodePtr);
}

//actual deletion of node takes place here
void BinaryTree::makeDeletion(TreeNode *&nodePtr){
    //make temp pointer for use in re-attaching
    TreeNode *tempNodePtr;
    //make sure nodes exist
    if(nodePtr==NULL)cout<<"Empty node cannot be deleted."<<endl;
    //if only left child, re-attach to previous node
    else if(nodePtr->right==NULL){
        tempNodePtr=nodePtr;
        nodePtr=nodePtr->left;
        delete tempNodePtr;
    }
    //if only right child, re-attach to previous node
    else if(nodePtr->left==NULL){
        tempNodePtr=nodePtr;
        nodePtr=nodePtr->right;
        delete tempNodePtr;
    }
    //if the node has two children
    else{
        //move temp to to the right
        tempNodePtr=nodePtr->right;
        //traverse to end of left node
        while(tempNodePtr->left)
            tempNodePtr=tempNodePtr->left;
        //re-attach left subtree
        tempNodePtr->left=nodePtr->left;
        tempNodePtr=nodePtr;
        //re-attach right subtree
        nodePtr=nodePtr->right;
        delete tempNodePtr;
    }
}

//Destructor
void BinaryTree::destroySubTree(TreeNode *nodePtr){
    if(nodePtr){
        if(nodePtr->left)
            destroySubTree(nodePtr->left);
        if(nodePtr->right)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}