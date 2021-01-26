#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"
using namespace std;

Course::Course(string id,string title, Date startTime, Date endTime) : 
id(id), title(title), startTime(startTime), endTime(endTime) {}

void Course::addAttendanceRecord(AttendanceRecord ar) {
	if ((this->getStartTime() <= ar.getDate()) && (this->getEndTime() >= ar.getDate())) {
		attendanceRecords.push_back(ar);
	}
}

void Course::outputAttendance() {
	if (attendanceRecords.size() == 0) {
		cout << "No Records" << endl;
	}
	else {
		for (int i = 0; i < attendanceRecords.size(); ++i) {
			cout << attendanceRecords[i].getDate().getDate() << ',' << attendanceRecords[i].getCourseID() << ',' << attendanceRecords[i].getStudentID() << endl;
		}
	}
}

void Course::outputAttendance(std::string student_id) {
	if (attendanceRecords.size() == 0) {
		cout << "No Records" << endl;
	}
	else {
		for (int i = 0; i < attendanceRecords.size(); ++i) {
			if (student_id == attendanceRecords[i].getStudentID()) {
				cout << attendanceRecords[i].getDate().getDate() << ',' << attendanceRecords[i].getCourseID() << ',' << attendanceRecords[i].getStudentID() << endl;
			}
		}
	}
}
