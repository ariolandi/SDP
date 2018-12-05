#ifndef _FILEM_H_
#define _FILEM_H_

#include<fstream>
#include"students.h"
using namespace std;
const char* fileName = "StudentGrade.db";

/*
File manager - static DB management class
update, delete and search methods
*/
class FileManager{
    public:
        static void update(){
            Student st;
            fstream file(fileName);
            unsigned long long fn;
            int grade;
            cin>>fn>>grade;
            bool found = false;
            int n=0;
            //searches for the record
            while(file>>st){
                if(st.getFN() == fn){
                    found = true;
                    break;
                }
                n++;
            }
            //updates the record
            if(found) {
                file.seekp(n*sizeof(st));
                st.setGrade(grade);
                file<<st;
                cout<<"Record saved!"<<endl;
            }
            else cout<<"Record not found!"<<endl;
            file.close();
        }

        static void Delete(){
            ifstream file(fileName);
            ofstream temp("temp.db");
            Student st;
            unsigned long long fn;
            cin>>fn;
            bool found = false;
            //searches for the record
            while(file>>st){
                if(st.getFN() == fn){
                    found = true;
                    cout<<"Record deleted!"<<endl;
                }
                //writes the other records in temporary file
                else temp<<st;
            }
            if(!found)cout<<"Record not found!"<<endl;
            file.close();
            temp.close();
            //replaces files
            remove(fileName);
            rename("temp.db", fileName);
        }

        static void sequentialSearch(){
            ifstream ifile(fileName);
            Student st;
            unsigned long long fn;
            cin>>fn;
            bool found = false;
            //searches for the record
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
        if(command == "update")FileManager::update();
        else if(command == "delete")FileManager::Delete();
        else FileManager::sequentialSearch();
        cin>>command;
    }

}

#endif // _FILEM_H_
