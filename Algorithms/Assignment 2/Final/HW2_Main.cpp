// Anthony Rizzo
// Homework 2 - Fundamentals of Algorithms
// Due: Thursday, January 31, 2019
// cpp file for main()

#include <iostream>
#include <fstream>
#include "HW2.h"
#include <string>
#include <stdexcept>

using namespace std;

int main() {
	int num, cr, maxStudents;
	string id, tl;
	ifstream inf;

	maxStudents = 10;

	inf.open("section01.txt");		//open file descriptor
	if (inf.fail()) {
		cerr << "Error: Could not open input file\n";
		exit(1);	//terminate
	}

	//activate the exception handling of inf stream
	inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	cout << "Course ID? ";
	cin.get();					//remove the leftover "new line" character from cin
	getline(cin, id);			//Read ID string

	cout << "Course Title? ";
	getline(cin, tl);

	cout << "Course Credits? ";
	cin >> cr;

	cout << "How many students in the course section? ";
	cin >> num; //remove the leftover "new line" character from cin

	//Catch invalid student amount
	if (num > maxStudents) {
		cout << "\nWarning: Entered student count greater than the total number of students in the section.\n";
		cout << "Only " << maxStudents << " students in the course section.\n\n";
		num = maxStudents;
	}

	cin.get();
	CourseSection sec(id, tl, cr, num);
	sec.fillRosterInfo(&inf); //ifstream cannot be passed by value
	cout << "The following is the section info (course and students info):\n\n";
	sec.printSectionInfo();
	inf.close(); //closes the file stream

	
	//Displaying the students info sorted by name
	anyList<string, Student*> nameList(num);
	for (int i = 0; i < num; i++){
		//Pass parameter to sort by & student info
		nameList.addListKey(sec.getStudent(i)->personName(), sec.getStudent(i));	
	}

	nameList.sortList();

	cout << "\nRoster sorted by name:\n"; nameList.dispList();

	//Displaying the students ino sorted by age
	anyList<int, Student*> ageList(num);
	for (int i = 0; i < num; i++){
		ageList.addListKey(sec.getStudent(i)->personAGE(), sec.getStudent(i));
	}

	ageList.sortList();

	cout << "\nRoster sorted by age:\n"; ageList.dispList();

	//Displaying the students info sorted by GPA
	anyList<float, Student*> gpaList(num);

	for (int i = 0; i < num; i++){
		gpaList.addListKey(sec.getStudent(i)->studentGPA(), sec.getStudent(i));
	}

	gpaList.sortList();

	cout << "\nRoster sorted by GPA:\n"; 
	gpaList.dispList();
	

	cin.get();

	return 0;
}