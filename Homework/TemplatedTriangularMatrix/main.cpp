/* 
 * File:   main.cpp
 * Author: Joe Reimbold
 * Created on September 10, 2014, 4:00 PM
 * Purpose:  Assignment 1: Template a Triangular Matrix
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

//User Libraries
#include "template.h"

//No Global Constants

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare variables
    int rows=5;
    
    //create int matrix
    TriMatrix<int> intTri(rows);
    //Print int matrix
    intTri.print();
    
    //Create float matrix
    TriMatrix<float> fTri(rows);
    //Print float matrix
    fTri.print();
    
    //Exit stage right
    return 0;
}

void destroy(int *array){
    //Destroy row pointers
    delete []array;
}

void destroy(int **array,int rows){
    //Destroy cols
    for(int row=0;row<rows;row++){
        delete []array[row];
    }
    //Destroy row pointers
    delete []array;
}

void printArray(int*array,int cols,int perLine){
    //Print the Array
    cout<<endl;
    for(int col=0;col<cols;col++){
       cout<<array[col]<<" ";
       if(col%perLine==(perLine-1))cout<<endl; 
    }
    cout<<endl;
}

void printArray(int**array,int rows,int *colAry){
    //Print the Array
    cout<<endl;
    for(int row=0;row<rows;row++){
        for(int col=0;col<colAry[row];col++){
            cout<<array[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int* fillArray(int cols){
    //Declare the 1-D Array
    int * array=new int[cols];
    //Fill the array with random 1 digit numbers
    for(int col=0;col<cols;col++){
        array[col]=rand()%9+1;
    }
    return array;
}

int** fillArray(int rows,int *colAry){
    //Declare the 2-D Array
    int ** array=new int*[rows];
    for(int row=0;row<rows;row++){
        array[row]=new int[colAry[row]];
    }
    //Fill the array with random 2 digit numbers
    for(int row=0;row<rows;row++){
        for(int col=0;col<colAry[row];col++){
            array[row][col]=rand()%90+10;
        }
    }
    return array;
}