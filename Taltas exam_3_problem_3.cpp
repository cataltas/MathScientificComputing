//Exam 3 Exercise 3
//Collaboration with Nick Rossiter 

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include " Student.h"
#include <sstream>
#include<algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

bool sortingstudents(Student_Grade x,Student_Grade y);

int main() {
    ifstream input_file;
    input_file.open ("student_data.dat");

    string line;
    string last_n;
    string first_n;

    vector <double> homework; 
    vector <double> exams;
    double finalex;
    vector <Student_Grade> students;

    while (getline(input_file,line)) {
        istringstream iss(line);
        iss>>first_n>>last_n;
        getline(input_file, line);
        istringstream iss2(line);
        for (int i=0; i<6; i++){
            double t; 
            iss2>>t;
            homework.push_back(t);
        }
        getline(input_file, line);
        istringstream iss3(line);
        for (int i=0; i<3; i++){
            double t; 
            iss3>>t;
            exams.push_back(t);

        }
    getline(input_file, line);
        istringstream iss4(line);
            iss4>>finalex;
    getline(input_file, line);
    students.push_back(Student_Grade(first_n,last_n,homework,exams,finalex));
    } 
    
    sort(students.begin(),students.end(),sortingstudents);
    for (int j = 0; j<students.size();j++) {
        cout << "The student: " << students[j].full_name() << " has a final score of " << students[j].final_score()<< endl;
    }
}

bool sortingstudents(Student_Grade x,Student_Grade y){
    return x.get_ln().compare(y.get_ln())<0;
}