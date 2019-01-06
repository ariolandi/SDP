#ifndef _FILEM_H_
#define _FILEM_H_

#include<iostream>
#include<string>
#include"students.h"
#include"orderedTree.h"
using namespace std;

class FileManager{
    OrderTree<Student> t;
    public:
        void insert(){
            Student st;
            cin>>st;
            t.insertNode(st);
            cout<<"Record inserted!\n";
        }
        void deleteNode(){
            long long fn;
            cin>>fn;
            Student st(fn);
            if(t.deleteNode(st))cout<<"Record deleted!\n";
            else cout<<"Record not found\n";
        }
        void traverseInorder(){
            t.print();
            cout<<endl;
        }

};


/*
Command parcer
*/
void CommandLine(){
    string command;
    FileManager f;
    cin>>command;
    while(command != "exit"){
        if(command == "insert")f.insert();
        else if(command == "delete")f.deleteNode();
        else f.traverseInorder();
        cin>>command;
    }

}

#endif // _FILEM_H_
