/* 
 * File:   HandTree.h
 * Author: Joe
 *
 * Created on December 6, 2014, 11:18 AM
 */

//Libraries
#include <iostream>
#include <cstdlib>
#include "HandTree.h"
using namespace std;

//Constructor
HandTree::HandTree(){
    root=NULL;
    numHand=0;
}

//public insert function
void HandTree::insertNode(Card crd){
    //create new node to hold value
    TreeNode *newNode=new TreeNode;    //points to new node
    newNode->data=crd;
    newNode->left=newNode->right=NULL;
    
    //Insert the node
    insert(root,newNode);
    numHand++;
}

//insert function
void HandTree::insert(TreeNode *&nodePtr, TreeNode *&newNode){
    //if insert location is NULL then insert
    if(nodePtr==NULL)
        nodePtr=newNode;
    //if node exists, compare new value, if lesser, continue search left
    else if(newNode->data.getValue()<nodePtr->data.getValue())
        insert(nodePtr->left,newNode);
    //if node exists, compare new value, if greater, continue search right
    else
        insert(nodePtr->right,newNode);
}

//in order display function
void HandTree::displayInOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        displayInOrder(nodePtr->left);
        cout<<nodePtr->data.getName()<<nodePtr->data.getSuit()<<" ";
        displayInOrder(nodePtr->right);
    }
}

//pre order display function
void HandTree::displayPreOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        cout<<nodePtr->data.getName()<<nodePtr->data.getSuit()<<" ";
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
}

//post order display function
void HandTree::displayPostOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        cout<<nodePtr->data.getName()<<nodePtr->data.getSuit()<<" ";
    }
}

//search function
bool HandTree::searchNode(Card crd){
    TreeNode *nodePtr=root;
    while (nodePtr){
        if(nodePtr->data.getName()==crd.getName()&&nodePtr->data.getSuit()==crd.getSuit())
            return true;
        else if(crd.getValue()<nodePtr->data.getValue())
            nodePtr=nodePtr->left;
        else
            nodePtr=nodePtr->right;
    }
    return false;    
}

//public delete function which calls the delete node function
void HandTree::remove(Card crd){
    deleteNode(crd,root);
}

//delete node function which determines which node to delete
void HandTree::deleteNode(Card crd, TreeNode *&nodePtr){
    //if less than, keep searching to the left
    if(crd.getValue()<nodePtr->data.getValue())
        deleteNode(crd,nodePtr->left);
    //if greater than, keep searching to the right
    else if(crd.getValue()>nodePtr->data.getValue())
        deleteNode(crd,nodePtr->right);
    //if equal, move on with deletion
    else
        makeDeletion(nodePtr);
}

//actual deletion of node takes place here
void HandTree::makeDeletion(TreeNode *&nodePtr){
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
void HandTree::destroySubTree(TreeNode *nodePtr){
    if(nodePtr){
        if(nodePtr->left)
            destroySubTree(nodePtr->left);
        if(nodePtr->right)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}