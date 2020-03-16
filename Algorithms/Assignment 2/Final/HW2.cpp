// Anthony Rizzo
// Homework 2 - Fundamentals of Algorithms
// Due: Thursday, January 31, 2019
// cpp file w/ function definitions

#include "HW2.h"    //include header file
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>

using namespace std;


// ------------------------------ P E R S O N   C L A S S ------------------------------ //

//Constructor assigns values to variables
Person::Person() {
	name = address = strAge = "Empty";
	age = -1;
}

//Asks keyboard inputs of the person's three private attributes
void Person::readPersonInfo(ifstream *pf) {
	getline(*pf, name);
	getline(*pf, address);
	getline(*pf, strAge);
	age = stoi(strAge);     //Convert age string to integer
}

// Displays the person's three private attributes
// Work on formatting later
void Person::printPersonInfo() {
	cout << setw(20) << name;
	cout << setw(5) << age;
	cout << setw(20) << address;
}

// Returns the person's age
int Person::personAGE() {
	return age;
}

// Returns the person's name
string Person::personName() {
	return name;
}


// ------------------------------ S T U D E N T   C L A S S ------------------------------ //

//Constructor assigns values to variables
Student::Student() {
	ID = major = strGPA = "Empty";
	gpa = 0;
}

//Read student information
//Includes information associated with a Person
void Student::readStudentInfo(ifstream *pf) {
	readPersonInfo(pf);	//Call to base class function

	getline(*pf, ID);
	getline(*pf, major);
	getline(*pf, strGPA);
	gpa = stof(strGPA);     //Convert string to float
}

void Student::printStudentInfo() {
	printPersonInfo();	//Call to base class function (i.e. Name, Address, Age)

	// Print student attributes
	cout << setw(12) << ID;
	cout << setw(8) << major;
	cout << setw(8) << gpa << endl;
}

//Return floating point of Student's GPA
float Student::studentGPA() {
	return gpa;
}

// ------------------------------ C O U R S E   C L A S S ------------------------------ //

//Constructor takes arguments for class ID, title, & credits
Course::Course(string ID, string title, int credits) {
	//Assign constructor arguments to private variable fields
	this->ID = ID;
	this->title = title;
	this->credits = credits;
}

//Print title Sequence
void Course::printTableTitles() {
	cout << setw(20) << right << "Name" << setw(5) << right << "Age" << setw(20) << right
		<< "Address" << setw(12) << right << "ID" << setw(8) << right << "Major" << setw(8)
		<< right << "GPA" << endl;

	cout << setw(20) << right << "==========" << setw(5) << right << "===" << setw(20) << right
		<< "=======" << setw(12) << right << "=====" << setw(8) << right << "====" << setw(8)
		<< right << "====" << endl;

}

//Outputs course information to console
void Course::printCourseInfo() {
	cout << title << " (" << ID << ") -- " << credits << " Credit Course\n\n";
	printTableTitles();	//table headers
}

// ------------------------------ C O U R S E S E C T I O N   C L A S S ------------------------------ //	

//Class constructor initializes variables from CourseSection class & Course class
//Variables in CourseSection constructor applied to Course constructor
CourseSection::CourseSection(string ID, string title, int credits, int sectionSize) :Course::Course(ID, title, credits) {
	this->sectionSize = sectionSize;
	roster = new Student[sectionSize];	//roster points to dynamic array of type Student
}

//read the info of all students in the
 //section and store them in the roster. The students’ info is stored in the
 //text file whose stream is pointed to by rf.
void CourseSection::fillRosterInfo(ifstream *rf) {
	//Loop thru all students
	for (int i = 0; i < sectionSize; i++) {
		roster[i].readStudentInfo(rf);	//Store info in i'th element of Student array
	}
}

//Output Section Information to Console
void CourseSection::printSectionInfo() {
	printCourseInfo();		//i.e. Title, ID, Credits

	//Print all information for each student
	//Condition to ensure array access is within array size (no seg faults)
	if (sectionSize > 0) {
		for (int i = 0; i < sectionSize; i++) {
			roster[i].printStudentInfo();			//Print info of Student located in i'th element of array
		}
	}
}

//Returns a pointer to the ith student
Student* CourseSection::getStudent(int index) {
	return &roster[index];
}

CourseSection::~CourseSection() {
	delete[] roster;	//Free roster memory
}


// ------------------------------A N Y L I S T   C L A S S ------------------------------ //

//constructor with list size as argument
template <class T, class P>
anyList<T,P>::anyList(int LCapacity){
	this -> LCapacity = LCapacity;

	LSize = 0;		//Grow list from 0th element

	ListKeys = new T[LCapacity];
	ListObjectsP = new P[LCapacity];
}

//Fill list with index and value to be saved as arguments
template <class T, class P>
void anyList<T, P>::addListKey(T ky, P objp){
	ListKeys[LSize] = ky;
	ListObjectsP[LSize] = objp;

	LSize++;
}

//Display elements
template <class T, class P>
void anyList<T, P>::dispList() {
	//Format Ex: "Element #1: 20"
	for (int i = 0; i < LCapacity; i++) {
		ListObjectsP[i]->printStudentInfo();
	}
}


//Sort in ascending order
template <class T, class P>
void anyList<T, P> ::sortList(){
	T tempKey;
	P tempObjP;		//Temp variable of P data type

	//Loop thru all elements and organize
	for(int i = 0; i < LSize; i++){
		for(int j = 0; j < LSize; j++){

			if (ListKeys[i] < ListKeys[j]) {
				tempKey = ListKeys[i];
				ListKeys[i] = ListKeys[j];
				ListKeys[j] = tempKey;

				tempObjP = ListObjectsP[i];
				ListObjectsP[i] = ListObjectsP[j];
				ListObjectsP[j] = tempObjP;
			}
		}
	}
}

//Destructor
template <class T, class P>
anyList<T, P>::~anyList(){
	delete[] ListObjectsP;		//Clear memory
	delete[] ListKeys;
}

// define potential data types
template class anyList<string, Student*>;
template class anyList<int, Student *>;
template class anyList<float, Student*>;

