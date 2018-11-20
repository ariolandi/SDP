#ifndef _FILEM_H_
#define _FILEM_H_

#include<fstream>
#include"students.h"
using namespace std;
const char* file = "StudentGrade.db";

/*
File manager - static DB management class
create and search methods
*/
class FileManager{
    public:
        static void create(){
            Student st;
            cin>>st;
            ofstream ofile(file, ios::app);
            ofile<<st;
            ofile.close();
            cout<<"Record saved!"<<endl;
        }
        static void sequentialSearch(){
            ifstream ifile(file);
            Student st;
            unsigned long long fn;
            cin>>fn;
            bool found = false;
            while(ifile>>st){
                if(st.getFN() == fn){
                    cout<<st;
                    found = true;
                    break;
                }
            }
            ifile.close();
            if(!found)cout<<"Record not found!"<<endl;

        }
};


/*
Command parcer
*/
void CommandLine(){
    string command;
    cin>>command;
    while(command != "exit"){
        if(command == "create")FileManager::create();
        else FileManager::sequentialSearch();
        cin>>command;
    }

}

#endif // _FILEM_H_
