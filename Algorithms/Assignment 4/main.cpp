//Anthony Rizzo
//Algo Homework 4
//March 9, 2019

#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdexcept>

static int eventsQCapacity = 100;
static int waitingQCapacity = 100;


/* --------------------- Bank Customer --------------------- */ 

class BankCustomer{
public:
    int ID;
    int ArrivalTime;
    int ServiceStartTime;
    int TransactionLength;   
};

/* ------------------------- Event ------------------------- */

class Event{
public:
    char EventType; //'A' = arrival, 'D' = departure
    int CustID;     //ID of customer who created event
    int ADTime;     //Arrival or departure time

    //Empty constructor does nothing
    Event(){}

    //Constructor assigns values to variables
    Event(char et, int cid, int ad): 
        EventType(et), CustID(cid),ADTime(ad){}
    
};

/* ------------------------- PQueue ------------------------ */

class PQueue{
private:
    int QCapacity;  //Max size of queue
    Event *events;   //Ptr to array that holds arr. & dep. events
    int count;      //Number of events in queue
    int i;

    //insert a new event to a sorted list
    bool listInsert(Event ev){
        //check if there's room to add
        if(count == QCapacity){
            return false;
        }
        
        i = count - 1;
       
        while(events[i].ADTime < ev.ADTime && i >= 0){
            events[i+1] = events[i];    //shift
            i--;    //look at prior element 
        }

        events[i + 1] = ev; //insert

        count++;
        
        return true;
    } 

    //Delete the event at the end of the list
    bool listDelete(){
        //if list is empty, nothing to delete
        if(isEmpty()){
            return false;
        }

        //if list is not empty, remove front element
        else{
            count--;
            return true;
        }
    } 

    //get the event at the end of the list
    Event listPeek(){
        assert(!isEmpty());
        return events[count - 1];
    }

public:
    //initialize capacity in constructor
    PQueue(int c) : QCapacity(c){
        events = new Event[QCapacity];
        count = 0;
        i = 0;
    }

    //check for content within list
    bool isEmpty(){
        return count == 0;
    }

    //insert new event
    bool enqueue(Event ev){
        //calls listInsert to insert a new event
        return listInsert(ev);
    }

    //remove queue's front event
    bool dequeue(){
        //calls listDelete to remove the queue's front event
        return listDelete();
    }

    //returns queue's front event
    Event peekFront(){
        //calls listPeek to return the queue's front event
        return listPeek();
    }

    ~PQueue(){
        delete[] events;
    }

};

/* ---------------------- Array Queue ---------------------- */


class ArrayQueue{
private:
    int QCapacity;
    int *IDs;   //array of queue items
    int front;  //index to front of queue
    int back;   //index to back of queue
    int count;  //number of items in queue

public:
    ArrayQueue(int c) : QCapacity(c){
        IDs = new int[QCapacity];
        front = count = 0;
        back = QCapacity - 1;
    }

    bool isEmpty(){
        return count == 0;
    }

    bool enqueue(const int newID){

        if(count < QCapacity){
            back = (back + 1) % QCapacity; //handles rotation
            IDs[back] = newID;
            count++;
            return true;
        }

        return false;
    }

    bool dequeue(){
        if(!isEmpty()){
            front = (front + 1) % QCapacity;
            count--;
            return true;
        }

        return false;

    }

    int peekFront(){
        assert(!isEmpty());
        return IDs[front];
    }
    
    //number of items in queue
    int queueLength(){
        return count;
    }

    ~ArrayQueue(){
        delete[] IDs;
    }
};

/* -------------------- Bank Teller Service ------------------- */ 

class BankTellerService{
private:
    bool BusyTeller;    //indicates if teller is busy or available
    int CustomersNum;   //total number of customers in simulation
    std::ifstream inf;       //txt file of arrival & transaction times
    std::ofstream otf;       //txt file with trace messages & final stats
    ArrayQueue WaitingQ = ArrayQueue(waitingQCapacity);
    PQueue EventsQ = PQueue(eventsQCapacity);
    BankCustomer *Customers;   //array of customer objects
    int waitingQMax;    //max length of the waiting queue
    std::string tempS;

public:

    BankTellerService(std::string infS, std::string otfS){

        BusyTeller = false; //originally available

        inf.open(infS);  //open input file
        otf.open(otfS);  //open output file

        //check for errors w/ opening output file
        if(otf.fail() || inf.fail()){
            std::cerr << "Error: Could not open file\n";
            exit(1);
        }

        //activate the exception handling of inf stream
	    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        CustomersNum = 0;

        //count number of lines in text file
        while(!inf.eof()){
            getline(inf, tempS, '\n');
            CustomersNum++;
        }

        //return to beginning of file 
        inf.clear();
        inf.seekg(0, std::ios::beg);
        
        Customers = new BankCustomer[CustomersNum]; //array of Customers
    }

    ~BankTellerService(){
        delete[] Customers; //free memory
        inf.close();        //close txt files
        otf.close();

    }

    void readCustomersInfo(){
        BankCustomer tempCustomer;
               
        for(int i = 0; i < CustomersNum; i++){
            tempCustomer.ID = i;

            getline(inf, tempS, ' ');   //read arrival time
            tempCustomer.ArrivalTime = stoi(tempS); //convert to integer

            getline(inf, tempS, '\n');  //read trans length 
            tempCustomer.TransactionLength = stoi(tempS);   //convert to integer

            Customers[i] = tempCustomer;    //save to array
            Event newEvent('A', Customers[i].ID, Customers[i].ArrivalTime); 
            EventsQ.enqueue(newEvent);  //add event to events queue
        }
    }

    //for debugging
    void displayCustomersinfo(){
        for(int i = 0; i < 10; i++){
            std::cout << Customers[i].ID << '\t' << Customers[i].ArrivalTime << '\t' << Customers[i].TransactionLength << '\n';
        }
    }

    void serveCustomers(){

        int depTime;
        waitingQMax = 0;

        while(!EventsQ.isEmpty()){

            Event currEvent = EventsQ.peekFront();

            //arrival event
            if(currEvent.EventType == 'A'){
                
                otf << "Processing an arrival event at time <-- " << currEvent.ADTime << '\n';

                //if teller available, add departure event
                if(!BusyTeller){
                    depTime = currEvent.ADTime + Customers[currEvent.CustID].TransactionLength;
                    Event depEvent('D', currEvent.CustID, depTime);

                    Customers[currEvent.CustID].ServiceStartTime = currEvent.ADTime;

                    EventsQ.enqueue(depEvent);
                    BusyTeller = true;
                }

                //if people already waiting, add to waiting queue
                else{
                    WaitingQ.enqueue(currEvent.CustID);
                 
                }
            }

            //departure event
            if(currEvent.EventType == 'D'){

                otf << "Processing an departure event at time <-- " << depTime << '\n';

                if(!WaitingQ.isEmpty()){
                    
           
                    depTime = currEvent.ADTime + Customers[currEvent.CustID].TransactionLength; //calc dep time
                    Event depEvent('D', currEvent.CustID, depTime); //create event

                
                    Customers[WaitingQ.peekFront()].ServiceStartTime = currEvent.ADTime;    //next customers start time

                    EventsQ.enqueue(depEvent);     //enqueue

                    WaitingQ.dequeue();     //dequeue

                    BusyTeller = true;
                }

                else{
                    BusyTeller = false;
                }     
            }

            // event handled -> dequeue
            EventsQ.dequeue();

            //calc queue length
            if(WaitingQ.queueLength() > waitingQMax){
                waitingQMax = WaitingQ.queueLength();
            }
       }
    }

    void getStatistics(){

        int maxWaitTime = Customers[0].ServiceStartTime - Customers[0].ArrivalTime; //initial condition
        int totWaitTime = 0;
        float avgWaitTime;

        //loop thru all customers
        for(int i = 1; i < CustomersNum; i++){
            int tempWaitTime = Customers[i].ServiceStartTime - Customers[i].ArrivalTime;    //wait time for each customer

            totWaitTime += tempWaitTime;

            //determine maxWaitTime by comparing to current wait time
            if(tempWaitTime > maxWaitTime){
                maxWaitTime = tempWaitTime;
            }
        }

        avgWaitTime = (float)totWaitTime/(float)CustomersNum;   //calc avg time


        //Output statistics
        otf << std::endl << "Final Statistics:";
        otf << std::endl << "Total number of customers processed: " << CustomersNum;
        otf << std::endl << "Average Waiting Time: " << avgWaitTime;
        otf << std::endl << "Max waiting time: " << maxWaitTime;
        otf << std::endl << "Max waiting queue length: " << waitingQMax;
    }

};

/* ------------------------- Main ------------------------- */ 

int main(){

    BankTellerService myBank("HW4TXT.txt","output.txt");
    myBank.readCustomersInfo();
    //myBank.displayCustomersinfo();    //debug
    myBank.serveCustomers(); 
    myBank.getStatistics();

    return 0;
}