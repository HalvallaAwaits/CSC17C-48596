/* 
 * File:   main.cpp
 * Author: Joe
 *
 * Created on November 5, 2014, 3:44 PM
 */

//Libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

//Function Prototypes
int sum(int *,int);
float savings(float,float,int);

//Execution Begins Here
int main(int argc, char** argv) {    
    //Declare variables for sum function
    int size=100;
    int array[size];
    //fill array and calculate sum
    cout<<"Sum function (100 elements in array): "<<endl;
    for(int i=0;i<size;i++){
        array[i]=i+1;
    }
    //calculate sum
    float sav;
    float rate;
    int yrs;
    cout<<"Sum of Array is "<<sum(array,size)<<endl<<endl;
    
    //Recursive savings function
    cout<<"Recursive savings function"<<endl;
    //Get information from user
    cout<<"Enter current savings amount: $";
    cin>>sav;
    cout<<"Enter interest rate: ";
    cin>>rate;
    rate=rate/100.0f;
    cout<<"Enter number of years: ";
    cin>>yrs;
    
    cout<<"Interest: "<<rate<<endl;
    
    //calculate savings
    cout<<"Amount in account after "<<yrs<<" year(s): $"
        <<setprecision(2)<<fixed<<savings(sav,rate,yrs)<<endl;
    
    return 0;
}

int sum(int *a,int n){
    if(n==0){
        return 0;
    }
    else{
        return a[0]+sum(a+1,n-1);
    }
}

float savings(float pVal, float i, int n){
    if(n<=0)return pVal;
    else{
        return (1+i)*savings(pVal,i,n-1);
    }
}