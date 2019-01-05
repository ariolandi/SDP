#ifndef _FILEM_H_
#define _FILEM_H_

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include"students.h"
using namespace std;
const char* fileName = "StudentGrade.db";
const char* indexName = "FacultyNumber.ids";

int binarySearch(int s, int n, int lineSize, long long x){
    if(n<=s)return -1;
    int m = (s+n)/2;
    ifstream fin(indexName);
    fin.seekg(m*lineSize);
    pair<long long, int>p;
    fin>>p.first>>p.second;
    fin.close();
    if(p.first==x)return p.second;
    if(p.first>x)return binarySearch(s, m, lineSize, x);
    return binarySearch(m, n, lineSize, x);
}

/*
File manager - static DB management class
update, delete and search methods
*/
class FileManager{

    public:
        static void buildIndex(){
            priority_queue<pair<long long, int> >index;
            ifstream fin(fileName);
            Student st;
            int p = fin.tellg();
            while(fin>>st){
                long long int fn = st.getFN();
                index.push(make_pair(fn, p));
                p = fin.tellg();
            }
            fin.close();
            ofstream fout(indexName);
            while(!index.empty()){
                pair<long long, int>front = index.top();
                index.pop();
                fout<<front.first<<" "<<front.second<<endl;
            }
            cout<<"Index is built!\n";
            fout.close();
        }
        static void search(){
            ifstream fin(indexName, ios::binary);
            int lineSize = sizeof(int)+sizeof(long long)-2;
            fin.seekg(0, ios::end);
            int size = fin.tellg();
            int n = size/lineSize;
            unsigned long long fn;
            fin.close();
            cin>>fn;
            int index = binarySearch(0, n, lineSize, fn);
            if(index==-1){
                cout<<"Record not found!"<<endl;
                return;
            }
            fin.open(fileName);
            fin.seekg(index);
            Student st;
            fin>>st;
            cout<<st;
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
        if(command == "buildIndex")FileManager::buildIndex();
        else if(command == "search")FileManager::search();
        else FileManager::sequentialSearch();
        cin>>command;
    }

}

#endif // _FILEM_H_
