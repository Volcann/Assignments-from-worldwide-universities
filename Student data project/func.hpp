#ifndef func_h
#define func_h
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "class student.h"
using namespace std;
void startup();
void menu();
void adddata();
void searchdata();
void wholedata();
void deldata();
                        fstream file ;
                        string option,
                             password,
                         name1, name2,
         actualpassword = "volisend" ,
                                  id ,
                         departments ,
                        rigistrationo;
                        int tries = 0,
                            srno = 0 ;

void deldata(){
    cout<<"Enter Password "<<endl;
    cin.ignore();
    while (true) {
        tries--;
        getline(cin,password);
        if(password==actualpassword)
            break;
        if(tries==0){
            cout<<"Too many wrong ATTEMPTS"<<endl;
            menu();
        }
        else
            cout<<"Wrong Password Entered only "<<tries<<" tries left "<<endl;
    }
    if(password==actualpassword){
        cout<<"ENTER CONFIRM to delete the data "<<endl;
        cin>>option;
        cin.ignore();
        if(option=="CONFIRM"){
            cout<<endl;cout<<endl;cout<<endl;cout<<endl;
            file.open("/Users/volcann/Library/Mobile Documents/com~apple~CloudDocs/Student data project/data.txt",ios::out|ios::trunc);
            file.close();
            file.open("/Users/volcann/Library/Mobile Documents/com~apple~CloudDocs/Student data project/data.txt",ios::out);
            file<<"StudentNO      First Name      Last Name      Id      Department      Section\n";
            file.close();
        }
        else{
            cout<<endl;cout<<endl;cout<<endl;cout<<endl;
            cout<<"TRY AGAIN !!"<<endl;
            menu();
        }
    }
}

void wholedata(){
    string data;
    file.open("/Users/volcann/Library/Mobile Documents/com~apple~CloudDocs/Student data project/data.txt",ios::in);
    while(file){
        getline(file,data);
        cout<<data<<endl;
    }
    file.close();
    cout<<endl;cout<<endl;cout<<endl;cout<<endl;
    menu();
}

void searchdata(){
    bool status = 0;
    string data1 , data2;
    file.open("/Users/volcann/Library/Mobile Documents/com~apple~CloudDocs/Student data project/data.txt",ios::in);
    cout<<"Enter the Member First Name to Search in data :"<<endl;
    cin>>data1;
    while(file){
        file >> data2;
        if(data1 == data2){
            cout<<endl;cout<<endl;cout<<endl;cout<<endl;
            cout<<"Data Found____"<<endl;
            status = 1;
            getline(file,data2);
            cout << data1 << data2 << endl;
            if(data2=="\n")break;
        }
    }
    file.close();
    if(status==0){
        cout<<"No data "<<endl;
        cout<<"Enter 0 to exit "<<endl;
        cout<<"Want to search more enter 1 "<<endl;
        while(true){
            cin>>option;
            if(option=="0"){
                menu();
                break;;
            }
            if(option=="1"){
                searchdata();
                break;;
            }
        }
    }
//    cout<<"Enter 0 to exit "<<endl;
//    cout<<"Want to add changes to that data enter 1 !!"<<endl;
//    while(true){
//        cin>>option;
//        if(option=="0"){
//            menu();
//            break;;
//        }
//        if(option=="1"){
//            searchdata();
//            break;;
//        }
//    }
}

void startup(){
    cout<<"-----Goverment College Gulberg Lahore-----\n";
    cout<<"Enter Password "<<endl;
    while (true) {
        tries--;
        getline(cin,password);
        if(password==actualpassword)
            break;
        if(tries==0){
            cout<<"Too many wrong ATTEMPTS"<<endl;
            exit(0);
        }
        else
            cout<<"Wrong Password Entered only "<<tries<<" tries left "<<endl;
    }
    if(password==actualpassword){
        cout<<endl;cout<<endl;cout<<endl;cout<<endl;
        menu();
    }
}
    
void adddata(){
    int N = 0;
    cout<<"ENTER how many students you want to add "<<endl;
    cin>>N;
    cout<<endl;cout<<endl;
    unique_ptr<student[]>std(new student[N]);
    if(N==0){
        cout<<"No member will be added "<<endl;
        cout<<endl;
        menu();
    }
    file.open("/Users/volcann/Library/Mobile Documents/com~apple~CloudDocs/Student data project/data.txt",ios::in);
    char data ;
    while(file>>data){
        file.get(data);
        if(data=='\n'){
            srno++;
        }
    }
    file.close();
    if(srno==1){srno=1;}
    for(int i = 0 ; i < N ; i++) {
        //serialnumber
        file.open("/Users/volcann/Library/Mobile Documents/com~apple~CloudDocs/Student data project/data.txt",ios::app|ios::ate|ios::out);
        cout<<"Student number : "<<srno<<endl;
        file<<srno;
        file<<"              ";
        
        //firstname
        cout<<"First name : "<<endl;
        cin.ignore();
        getline(cin,name1);
        std[i].setdataname1(&name1);
        //Name to file
        file<<name1;
        file<<"           ";
        
        //lastname
        cout<<"Last name : "<<endl;
        cin.ignore();
        getline(cin,name2);
        std[i].setdataname2(&name2);
        file<<name2;
        file<<"       ";
        
        //id
        cout<<"Id : "<<endl;
        cin>>id;
        std[i].setdataid(&id);
        file<<id;
        file<<"      ";
        
        //section
        cout<<"Section : "<<endl;
        while (true) {
            cin>>departments;
            if(departments=="1"||departments=="cs"||departments=="CS"||departments=="computer"||departments=="computerscience"||departments=="bscs"||departments=="BSCS"){
                break;
            }
            if(departments=="2"||departments=="it"||departments=="IT"||departments=="information"||departments=="informationtechnology"||departments=="bsit"||departments=="BSIT"){
                break;
            }
            else{
                cout<<"Wrong entered !!"<<endl;
            }
        }
        std[i].setdataid(&departments);
        file<<depart(departments);
        file<<"      ";
        
        //section
        cout<<"Rigistration Number : "<<endl;
        cin>>rigistrationo;
        std[i].setdataid(&rigistrationo);
        file<<rigistrationo;
        file<<"\n";
        file.close();
        srno++;
    }
    menu();
}
    
void menu(){
    cout<<"-----Govt Gulberg College (For Boys)-----"<<endl;
    cout<<"Press 0 to Exit"<<endl;
    cout<<"Press 1 to ADD students data "<<endl;
    cout<<"Press 2 to Search for students data "<<endl;
    cout<<"Press 3 to Check all students data from file "<<endl;
    cout<<"Press 4 to DELETE Students data from file "<<endl;
    while (true) {
        cin>>option;
        if(option=="0"){
            cout<<"Ended"<<endl;
            exit(0);
        }
        if(option=="1")break;
        if(option=="2")break;
        if(option=="3")break;
        if(option=="4")break;
        else
            cout<<"Enter right command"<<endl;
    }
    if(option=="1"){
        cout<<endl;cout<<endl;cout<<endl;cout<<endl;
        adddata();
    }
    if(option=="2"){
        cout<<endl;cout<<endl;cout<<endl;cout<<endl;
        searchdata();
    }
    if(option=="3"){
        cout<<endl;cout<<endl;cout<<endl;cout<<endl;
        wholedata();
    }
    if(option=="4"){
        cout<<endl;cout<<endl;cout<<endl;cout<<endl;
        deldata();
    }
}

#endif /* func_hpp */
