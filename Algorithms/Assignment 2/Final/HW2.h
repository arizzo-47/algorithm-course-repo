
// Anthony Rizzo
// Homework 2 - Fundamentals of Algorithms
// Due: Thursday, January 31, 2019
// Header File

#ifndef HW2_H
#define HW2_H

#include <string>
#include <fstream>	
#include <iostream>
#include <stdexcept>

using namespace std;

// ------------------------------ P E R S O N   C L A S S ------------------------------ //

class Person {
private:
	//Person variable declaration
	string name, address, strAge;
	int age;

public:
	//Constructor
	Person();

	//Pulls person's data from text file
	void readPersonInfo(ifstream *pf);

	// Displays the person's three private attributes
	void printPersonInfo();

	// Returns the person's age
	int personAGE();

	// Returns the person's name
	string personName();
};


// ------------------------------ S T U D E N T   C L A S S ------------------------------ //

//Student is derived class of Person
//All public functions of Person are accessible by Student
class Student : public Person {
private:
	//Student variable declaration
	string ID, major, strGPA;
	float gpa;

public:
	//Constructor
	Student();

	//Read the person's three private attributes from the txt file
	//whose stream is pointed to by pf
	void readStudentInfo(ifstream *pf);

	//Display person's three private attributes
	void printStudentInfo();

	//Return floating point of Student's GPA
	float studentGPA();
};


// ------------------------------ C O U R S E   C L A S S ------------------------------ //

class Course {
private:
	//Declaration of Course variables
	string ID, title;
	int credits;

public:
	//Constructor takes arguments for class ID, title, & credits
	Course(string ID, string title, int credits);

	//Format output
	void printTableTitles();

	//Display ID, title, credits of course
	void printCourseInfo();
};


// ------------------------------ C O U R S E S E C T I O N   C L A S S ------------------------------ //	

//CourseSection is derived class of Course	
class CourseSection : public Course {
private:
	int sectionSize;	//# of students enrolled in section
	Student *roster;	//pointer for list of student objects enrolled in section
public:
	//Class constructor initializes variables from CourseSection class & Course class
	//Variables in CourseSection constructor applied to Course constructor
	CourseSection(string ID, string title, int credits, int sectionSize);

	//Read the info of all students in the section and store them in the roster
	//The students’ info is stored in the text file whose stream is pointed to by rf
	void fillRosterInfo(ifstream *rf);

	//Prints the section info starting with its course info,
	//followed by printing, in a tabular format, the info of all students in the section
	void printSectionInfo();

	//Returns a p---ointer to the ith student
	Student* getStudent(int index);

	~CourseSection();
};


// ------------------------------A N Y L I S T   C L A S S ------------------------------ //	

//Template Class to manipulate lists of any data type
template <class T, class P>
class anyList {
private:
	//To store a list of type T keys to be sorted (e.g., GPA)
	T* ListKeys;

	//To store a list of type P, which is a pointer to an object
	//(e.g.,Student*) that is associated with the corresponding key.
	P* ListObjectsP;

	int LCapacity; 		//Max number of elements allowed in the list
	int LSize; 			//current number of elements in the list

public:
	//constructor with list size as argument
	anyList(int LSize);

	//adds ky to the ListKeys
	//and objp to the ListObjects, then updates the LSize.
	void addListKey(T ky, P objp);

	//Display elements
	void dispList();

	//Sort in ascending order
	void sortList();

	//Delete allocated memory
	~anyList();
};

#endif