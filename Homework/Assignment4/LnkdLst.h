/* 
 * File:   LnkdLst.h
 * Author: Joe
 *
 * Created on October 18, 2014, 9:37 AM
 */

#ifndef LNKDLST_H
#define	LNKDLST_H

#include <string>
using namespace std;

class LnkdLst {
public:
    LnkdLst(int);
    void append(int);
    string toString();
    virtual ~LnkdLst();
private:
    struct Node{
         int data;
         Node *next;
    };
    Node *head;
    Node *worker;
};

#endif	/* LNKDLST_H */