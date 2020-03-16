// Anthony Rizzo
// Homework 1 - Fundamentals of Algorithms
// Due: Thursday, January 17, 2019

#include <iostream>
#include <string>

using namespace std;

class Person{
private:
	//Person variable declaration
	string name, address;
	int age;

public:
	//Constructor assigns values to variables
	Person(){
		name = address= "Empty";
		age = 0;
	}

	//Asks keyboard inputs of the person's three private attributes
	void readPersonInfo(){
		cout << "Name: "; 
		cin.get();			//Clear input buffer 
		getline(cin, name);	//Reads input including spaces
		cout << "Address: "; 
		getline(cin,address);
		cout << "Age: "; 
		cin >> age;
	}
	
	// Displays the person's three private attributes
	void printPersonInfo(){
		//Formatting Ex: "Bob Smith, Age: 45, Address: 22 Stereotypical Drive,"
		cout << name << ", Age: "  << age << ", Address: "  << address << ",";
	}

	// Returns the person's age
	int personAGE(){
		return age;
	}

	// Returns the person's name
	string personName(){
		return name;
	}
};

//Student is child class of Person
//All public functions of Person are accessible by Student
class Student : public Person{
private:
	//Student variable declaration
	string ID, major;
	float gpa;

public:
	//Constructor assigns values to variables
	Student(){
		ID = major = "Empty";	
		gpa = 0;
	}

	//Read student information
	//Includes information associated with a Person
	void readStudentInfo(){
		readPersonInfo();	//Call to base class function

		cin.get();		//Clear buffer 

		//Ask for inputs of student attributes	
		//getline used to handle strings with spaces
		cout << "ID: "; getline(cin, ID);
		cout << "Major: "; getline(cin, major);
		cout << "GPA: "; cin >> gpa;
	}

	void printStudentInfo(){
		printPersonInfo();	//Call to base class function (i.e. Name, Address, Age)
	
		// Print student attributes
		// Formatting Ex: "ID: 098765, Major: Computer Engineering, GPA: 3.65"
		cout << "\n\tID: " << ID << ", Major: " << major << ", GPA: " << gpa << '\n';
	}

	//Return floating point of Student's GPA
	float studentGPA(){
		return gpa;
	}
};

class Course{
private:
	//Declaration of Course variables
	string ID, title;
	int credits;

public:
	//Constructor takes arguments for class ID, title, & credits
	Course(string ID, string title, int credits){
		//Assign constructor arguments to private variable fields
		this -> ID = ID;
		this -> title = title;
		this -> credits = credits;
	}
	
	//Outputs course information to console
	void printCourseInfo(){
		cout << title << " (" << ID << ") -- " << credits << " Credit Course\n";
	}
};	
	
class CourseSection : public Course{
private: 
	int sectionSize;	//# of students enrolled in section
	Student *roster;	//pointer for list of student objects enrolled in section
public:
	//Class constructor initializes variables from CourseSection class & Course class
	//Variables in CourseSection constructor applied to Course constructor
	CourseSection(string ID, string title, int credits, int sectionSize)
				:Course(ID,title,credits){
		this -> sectionSize = sectionSize;	
		roster = new Student[sectionSize];	//roster points to dynamic array of type Student
	}
	
	//Read the info of all students in the section & store them in the roster
	//roster is array of Students, therefore we can call Student (and Person) 
	//functions on roster[element]
	void fillRosterInfo(){
		//Loop thru all students
		for(int i = 0; i < sectionSize; i++){		
			cout << "\nStudent #" << i+1 << '\n'; //Formatting "Student #1"
			roster[i].readStudentInfo();	//Store info in i'th element of Student array
		}
	}

	//Output Section Information to Console
	void printSectionInfo(){
		printCourseInfo();		//i.e. Title, ID, Credits
		
		//Print all information for each student
		//Condition to ensure array access is within array size (no seg faults)
		if(sectionSize > 0){
			for(int i = 0; i < sectionSize; i++){
				cout << "\nStudent #" << i+1 << '\n';	//Formatting "Student #1"
				roster[i].printStudentInfo();			//Print info of Student located in i'th element of array
			}	
		}
		
	}

	void printTopGPAStudent(){
		int GPAindex = 0;		//Assume 0th student to have highest GPA to start

		for(int i = 1; i < sectionSize; i++){
			float CurrentGPA = roster[i].studentGPA();		//GPA of i'th student
			float TopGPA = roster[GPAindex].studentGPA();	//index of student with highest GPA

			//Change index if greater GPA is found
			if(CurrentGPA > TopGPA){
				GPAindex = i;	//Assign index to current element
			}
		}	

		//Condition to ensure array access is within array size (no seg faults)
		if(sectionSize > 0){
			roster[GPAindex].printStudentInfo();	//Print info of Student with highest GPA
		}
		cout << endl;
	}

	//Return Person name based on index in roster
	string returnName(int index){
		return roster[index].personName();
	}

	//Return Person age based on index in roster
	int returnAge(int index){
		return roster[index].personAGE();
	}

	//Return Student GPA based on index in roster
	float returnGPA(int index){
		return roster[index].studentGPA();
	}

	~CourseSection(){
		delete[] roster;	//Free roster memory
	}
};

//Template Class to manipulate lists of any data type
template <class T> class anyList {
private:
	T *ListElements;		//Pointer of data type T
	int LSize;				//Size of List
	
public:
	//constructor with list size as argument
	anyList(int LSize){
		this -> LSize = LSize;
		ListElements = new T[LSize];	//Array of list elements
	}

	//Fill list with index and value to be saved as arguments
	void fillList(int index, T value){
		ListElements[index] = value;
	}

	//Display elements
	void dispList(){
		cout << "Elements in Order Are: \n";
		
		//Format Ex: "Element #1: 20"
		for(int i = 0; i < LSize; i++){
			cout << "Element #" << i+1 << ": " << ListElements[i] << '\n';
		}

		cout << endl;
	}

	//Sort in ascending order
	void sortList(){
		int j;
		T temp;		//Temp variable of T data type

		//Loop thru all elements and organize
		for(int i = 0; i < LSize; i++){
			j = i;

			//Reorganization logic
			while(j > 0 && ListElements[j] < ListElements[j-1]){
				temp = ListElements[j];
				ListElements[j] = ListElements[j-1];
				ListElements[j-1] = temp;
				j--;	//Decrement
			}
		}
	}

	//Destructor
	~anyList(){
		delete[] ListElements;		//Clear memory
	}
};

int main(){
	int num, cr;	//# of students (i.e. SectionSize), # of credits
	string id, tl;	//Course ID, Course Title
	string nameValue;
	int ageValue;
	float gpaValue;

	cout << "Course ID: "; 
	cin.get();					//Clear buffer by reading input char, do not store 
	getline(cin,id);			//Read ID string
	cout << "Course Title: ";
	getline(cin,tl); 			//Read Title string
	cout << "Course credits: "; 
	cin >> cr;					//Read credit integer
	cout << "Students in the Section: "; 
	cin >> num;					//Read sectionsize # integer
	CourseSection sec(id, tl, cr, num);	//Make CourseSection class with constructor arguments
	cout << "Input the data of all students in the section:\n";
	sec.fillRosterInfo();		//Read data for students 

	cout << "\n\nC O U R S E   R O S T E R\n";
	sec.printSectionInfo();		//Print formatted roster to console

	cout << "\nThe student with the highest GPA:\n";
	sec.printTopGPAStudent();	//Print data of student with highest GPA

	////// Extra Credit //////

	//anyList with <data type>
	anyList<string> nameList(num);		
	anyList<int> ageList(num);
	anyList<float> gpaList(num);
	
	//Loop through CourseSection class data
	for(int i = 0; i < num; i++){
		
		//Assign variable to value at index
		nameValue = sec.returnName(i);
		ageValue = sec.returnAge(i);
		gpaValue = sec.returnGPA(i);

		//Fill template array at index with value
		nameList.fillList(i,nameValue);
		ageList.fillList(i,ageValue);
		gpaList.fillList(i,gpaValue);
	}

	//Sort lists
	nameList.sortList();
	ageList.sortList();
	gpaList.sortList();

	//Display ascending list with attributes
	cout << "Name ";
	nameList.dispList(); 
	
	//Age list
	cout << "Age ";
	ageList.dispList();

	//GPA list
	cout << "GPA ";
	gpaList.dispList();

	//Finish
	return 0;
}