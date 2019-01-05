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
        int grade;
        void copyStudent(const Student&);
    public:
        Student(const unsigned long long, const char*, const char*, const int);
        Student(const Student&);
        Student& operator=(const Student&);

        unsigned long long getFN()const {
            return fn;
        }
        void setGrade(unsigned long long _grade){
            grade = _grade;
        }

        friend ostream& operator<<(ostream&, const Student&);

};

void Student::copyStudent(const Student& other){
    fn = other.fn;
    grade = other.grade;
    strcpy(firstName, other.firstName);
    strcpy(lastName, other.lastName);
}

Student::Student(const unsigned long long _fn = 0, const char* _firstName = "", const char* _lastName = "", const int _grade = 0){
    fn = _fn;
    grade = _grade;
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

istream& operator>>(istream& ifs, Student& st){
    unsigned long long fn;
    char firstName[257], lastName[257];
    int grade;
    ifs>>fn>>firstName>>lastName>>grade;
    st = Student(fn, firstName, lastName, grade);
    return ifs;
}
ostream& operator<<(ostream& ofs, const Student& st){
    ofs<<st.fn<<" "<<st.firstName<<" "<<st.lastName<<" "<<st.grade<<endl;
    return ofs;
}



#endif // _STUDENTS_H_
