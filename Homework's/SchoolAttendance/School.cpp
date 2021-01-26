#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"
using namespace std;


void School::addStudents(string filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	while (!ifs.eof()) {
		string line;
		getline(ifs, line);
		if (line.empty()) {
			break;
		}
		istringstream ss(line);
		string uin;
		getline(ss, uin, ',');
		string name;
		getline(ss, name);
		if (!ss.fail()) {
			School::students.push_back(Student(uin, name));
		}
	}
}

void School::addCourses(string filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	while (!ifs.eof()) {
		string line;
		getline(ifs, line);
		if (line.empty()) {
			break;
		}
		istringstream ss(line);
		string classID;
		getline(ss, classID, ',');
		string startH, startMin;
		int sSec = 0;
		getline(ss, startH, ':');
		getline(ss, startMin, ',');
		Date start(stoi(startH), stoi(startMin), sSec);
		string endH, endMin;
		getline(ss, endH, ':');
		getline(ss, endMin, ',');
		Date end(stoi(endH), stoi(endMin), sSec);
		string title;
		getline(ss, title);
		if (!ss.fail()) {
			courses.push_back(Course(classID, title, start, end)); //
		}	
	}
}

void School::listStudents() {
	if (students.size() == 0) {
		cout << "No Students" << endl;
	}
	else {
		for (int i = 0; i < students.size(); ++i) {
			cout << students[i].get_id() << ',' << students[i].get_name() << endl;
		}
	}
}

void School::listCourses() {
	if (courses.size() == 0) {
		cout << "No Courses" << endl;
	}
	else {
		for (int i = 0; i < courses.size(); ++i) {
			cout << courses[i].getID() << ',' << setw(2) << setfill('0') << courses[i].getStartTime().getHour() << ":" << setw(2) << setfill('0') << courses[i].getStartTime().getMin() << ',' << setw(2) << setfill('0') << courses[i].getEndTime().getHour() << ':' << setw(2) << setfill('0') << courses[i].getEndTime().getMin() << ',' << courses[i].getTitle()<< endl;
		}
	}
}

void School::addAttendanceData(string filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	while (!ifs.eof()) {
		string line;
		getline(ifs, line);
		if (line.empty()) {
			break;
		}
		istringstream ss(line);
		string month, day, year; 
		getline(ss, year, '-');
		getline(ss, month, '-');
		getline(ss, day, ' ');
		string hour, min, sec;
		getline(ss, hour, ':');
		getline(ss, min, ':');
		getline(ss, sec, ',');
		Date signIn(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(min), stoi(sec));
		string class_id;
		getline(ss, class_id, ',');
		string studID;
		getline(ss, studID);
		if (!ss.fail()) {
			AttendanceRecord courseAttendance(class_id, studID, signIn);
			for (int i = 0; i < courses.size(); ++i) {
				if (courses[i].getID() == class_id) {
					courses[i].addAttendanceRecord(courseAttendance);
				}
			}
		}
	}	
}

void School::outputCourseAttendance(string course_id) {
	if (courses.size() == 0) {
		cout << "No Records" << endl;
	}
	else {
		for (int i = 0; i < courses.size(); ++i) {
			if (courses[i].getID() == course_id) {
				courses[i].outputAttendance();
			}
		}
	}
}

void School::outputStudentAttendance(string student_id, string course_id) {
	// int count = 0;
	// for (int i = 0; i < courses.size(); ++i) {
		// string temp = AttendanceRecord[i].getStudentID();   //courses.get_id(); 
		// if (temp == student_id) {
			// count++;
		// }
	// }
	// if (count == 0) {
		// cout << "No Records" << endl;
	//}
	if (courses.size() == 0) {
		cout << "No Records" << endl;
	}
	else {
		for (int i = 0; i < courses.size(); ++i) {
			if (courses[i].getID() == course_id) {
				courses[i].outputAttendance(student_id);
			}
		}
	}
}
