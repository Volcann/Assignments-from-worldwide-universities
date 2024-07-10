#include<iostream>
using namespace std;

class A {
public:
    A(){
        cout<<"# Object existed"<<endl;
    }
};
// 1 function
// 2 parameters object array , size , newly made array size
A func(A array[],int size,int &newsize) {
//arrays objects are equal only if size of object array are same
    A newarray[newsize];
    if(size==newsize){
        cout<<"They were Equal ";
        return newarray[newsize];
    }
    else {
        newsize=0;
        cout<<"They were not Equal ";
    }
    return array[size];
}

int main()
{
    int b = 0 , c;
    A a[b];
    cout<<"Enter the first array object size : "<<endl;
    cin>>b;
    cout<<"Enter the second array object size : "<<endl;
    cin>>c;
    func(a,b,c);
    return 0;
}
