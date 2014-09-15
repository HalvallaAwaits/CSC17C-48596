/* 
 * File:   template.h
 * Author: Joe
 *
 * Created on September 10, 2014, 4:18 PM
 */

#ifndef TEMPLATE_H
#define	TEMPLATE_H

//Triangular Matrix Class
template <class T> class TriMatrix
{
    private:
        int rows; //holds # of rows
        int* colAry; //array holding # of cols per row
        T** triAry; //triangular matrix
    public:
        //Constructors
        TriMatrix(int);
        //Destructor
        ~TriMatrix();
        //Fill colAry
        int* filAry(int);
        //Fill triAry
        T** filTri(int,int*);
        //Generate int or float based on type
        T random();
        //Print Triangular Matrix
        void print();
};

//Constructor
template<class T>
TriMatrix<T>::TriMatrix(int r){
    rows=r;
    colAry=filAry(rows);
    triAry=filTri(rows,colAry);
}

//Destructor
template<class T>
TriMatrix<T>::~TriMatrix(){
    //Destroy columns first
    for(int row=0;row<rows;row++){
        delete []triAry[row];
    }
    //Destroy rows
    delete []triAry;
}

//Fill col array
template<class T>
int* TriMatrix<T>::filAry(int cols){
    int* array= new int[cols];
    for(int i=0;i<cols;i++){
        array[i]=rand()%9+1;
    }
    return array;
}

//Fill triangular matrix
template<class T>
T** TriMatrix<T>::filTri(int rows,int* colAry){
    T** array=new T*[rows];
    for(int i=0;i<rows;i++){
        array[i]=new T[colAry[i]];
    }
    
    //Fill with random 2 digit numbers
    for(int r=0;r<rows;r++){
        for(int c=0;c<colAry[r];c++){
            array[r][c]=random();
        }
    }
    return array;
}

template<class T>
T TriMatrix<T>::random(){
    T num = static_cast<T>(rand()%90.0f+10.0f);
    return num;
}

//Print matrix
template<class T>
void TriMatrix<T>::print(){
    cout<<endl;
    for(int r=0;r<rows;r++){
        for(int c=0;c<colAry[r];c++){
            cout<<triAry[r][c]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

#endif	/* TEMPLATE_H */

