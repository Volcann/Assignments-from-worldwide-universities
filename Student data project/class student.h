#ifndef class_student_h
#define class_student_h
#include <iostream>
#include <string>
using namespace std;

class student {
private:
       string name1 , name2 , Id;
    void intitlization(void) {
        Id = "\0";
        name1 = "\0";
        name2 = "\0";
    }
public:
    void setdataname1(string *n1){
        name1=*n1;
    }
    void setdataname2(string *n1){
        name2=*n1;
    }
    void setdataid(string *i) {
        Id = *i;
    }
    string getname1(void)const{
           return name1;
    }
    string getname2(void)const{
           return name2;
    }
    string getid(void)const{
        return Id;
    }

};

string depart(string dept){
    if(dept=="1"||dept=="cs"||dept=="CS"||dept=="computer"||dept=="computerscience"||dept=="bscs"||dept=="BSCS"){
        dept = "Computer Science";
    }
    if(dept=="2"||dept=="it"||dept=="IT"||dept=="information"||dept=="informationtechnology"||dept=="bsit"||dept=="BSIT"){
        dept = "Information Technology";
    }
    return dept;
}

#endif /* class_student_h */
