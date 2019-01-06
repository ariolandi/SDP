#ifndef _STUDENTS_H_
#define _STUDENTS_H_

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

/*
Students class - fn, name, grade
(Default) Constructor, copy constructor, assignment operator
FN getter
in/out operators
*/
class Student{
    private:
        unsigned long long fn;
        char firstName[257], lastName[257];
        void copyStudent(const Student&);
    public:
        Student(const unsigned long long, const char*, const char*);
        Student(const Student&);
        Student& operator=(const Student&);
        bool operator>(const Student&)const;
        bool operator==(const Student&)const;

        unsigned long long getFN()const {
            return fn;
        }

        friend ostream& operator<<(ostream&, const Student&);

};

void Student::copyStudent(const Student& other){
    fn = other.fn;
    strcpy(firstName, other.firstName);
    strcpy(lastName, other.lastName);
}

Student::Student(const unsigned long long _fn = 0, const char* _firstName = "", const char* _lastName = ""){
    fn = _fn;
    strcpy(firstName, _firstName);
    strcpy(lastName, _lastName);
}
Student::Student(const Student& other){
    copyStudent(other);
}
Student& Student::operator=(const Student& other){
    if(this != &other){
        copyStudent(other);
    }
    return *this;
}

bool Student::operator>(const Student& other)const{
    return fn>other.fn;
}

bool Student::operator==(const Student& other)const{
    return fn==other.fn;
}

istream& operator>>(istream& ifs, Student& st){
    unsigned long long fn;
    char firstName[257], lastName[257];
    ifs>>fn>>firstName>>lastName;
    st = Student(fn, firstName, lastName);
    return ifs;
}
ostream& operator<<(ostream& ofs, const Student& st){
    ofs<<st.fn<<" ";
    return ofs;
}



#endif // _STUDENTS_H_
