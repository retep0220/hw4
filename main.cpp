//
//  main.cpp
//  HW4
//
//  Created by 王吉朗 on 2023/4/24.
//

#include <iostream>
#include "fstream"
#include "string"
#include "vector"
#include "cstdio"
#include "algorithm"
#include "chrono"
#include "ctime"
#include "sstream"
#include "time.h"
#include "iomanip"

using namespace std;

class Employee {
public:
    int id, contiworkday = 1;
    vector<time_t> workdate;
    vector<string> workday;
    Employee(int id) {
        this -> id = id;
    }
    
    
private:
    string signInTime, signOutTime;
};

bool compare (const Employee e1, const Employee e2) {
    return e1.contiworkday > e2.contiworkday;
}


int main(int argc, const char * argv[]) {
    string filename = argv[1];
    ifstream fin(filename);
    if (!fin) {
        cout << "unable to open file\n";
    }
    string line;
    vector<Employee> employees;
    while (getline(fin, line)) {
        char signType[9], date[12];
        int id;
        sscanf(line.c_str(), "%d,%s,%s", &id, signType, date);
        auto iter = find_if(employees.begin(), employees.end(),[id](const Employee& e) {
            return e.id == id;
        });
        if (iter != employees.end()) {
            iter->workday.push_back(date);
        }
        else {
            Employee e = Employee(id);
            e.workday.push_back(date);
            employees.push_back(e);
        }
    }
    //neew
    
    for (int i = 0; i < employees.size(); i++) {
        for (int j = 0; j < employees[i].workday[j].size(); j++) {
            employees[i].workday[j].resize(8);
        }
    }
    
    for (int i = 0; i < employees.size(); i++) {
        for (int j = 0; j < employees[i].workday.size(); j++) {
            tm t = {};
            istringstream ss(employees[i].workday[j]);
            ss >> get_time(&t, "%Y%m%d");
            employees[i].workdate[j] = mktime(&t);
        }
    }
    //new
    for (int i = 0; i < employees.size(); i++) {
        int temp = 1;
        for (int j = 0; j < employees[i].workday.size() - 1; j++) {
            if (employees[i].workdate[j] - employees[i].workdate[j+1] == -1) {
                temp++;
                if (temp > employees[i].contiworkday) {
                    employees[i].contiworkday = temp;
                }
            }
            else {
                temp = 1;
            }
        }
    }
    
    sort(employees.begin(), employees.end(), compare);
    
    for (int i = 0; i < 3; i++) {
        printf("%d,%d,",employees[i].id,employees[i].contiworkday);
        for (int j = 0; j < employees[i].workday.size(); j++) {
            if (employees[i].workdate[j] + employees[i].contiworkday  - 1== employees[i].workdate[j+employees[i].contiworkday - 1]) {
                cout << employees[i].workdate[j] << "," << employees[i].workdate[j+employees[i].contiworkday - 1] << endl;
            }
        }
    }
    return 0;
}
