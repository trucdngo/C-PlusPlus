/*
 UCSC Extension, C++ Comprehensive, Spring 2016
 Project #2
 Project Name: Simulation of Parking Lot using Linklist as Stack
 Compiler: XCode Version 7.2
 Due Date: May 14, 2016
 Student: Truc Ngo
 truc.dinh.ngo@gmail.com
 */


#include <iostream>
using namespace std;

enum PARKING_COMMAND_BOOTH {PARKING='P', DISPLAY='D', RETRIEVE='R', QUIT='Q'};

class ParkingLot
{
public:
    ParkingLot(int capacity) {
        topCar = NULL;
        parkingLotCapacity = capacity;
        //set first parking ticket = 1
        generatedTicket = 1;
        ticketCounter = 0;
    }
    
    void programIntroduction();
    void displayControlPanel();
    void parkOneCar(int parkingTicket);
    void retrieveOneCar();
    void displayCarsInParkingLot();
    void quitProgram(ParkingLot *pkPtr);
    bool carIsInParkingLot(int parkingTicket);
    int getTicket() {return generatedTicket;}
    
private:
    struct Node
    {
    public:
        int data;
        Node *next;
    };
    /* point to last car that enters the parking lot.
    "top" means top of the stack */
    Node *topCar;
    
    //issue new tickets in increasing order
    int generatedTicket;
    //keep track of total of tickets in the Parking lot (Alley-A)
    int ticketCounter;
    //define maxium how many cars can be stored in Parking lot (Alley-A)
    int parkingLotCapacity;
};

/* Park one car in the parking lot.  Check if lot is FULL */
void ParkingLot::parkOneCar(int parkingTicket)
{
    if (parkingLotCapacity == ticketCounter)
        cout << "PARKING LOT FULL.";
    else
    {
        //a new car that enters parking lot
        Node *newCar = new Node;
        //if this car is the first car to enter parking lot
        if(topCar == NULL)
        {
            newCar->data = parkingTicket;
            newCar->next = NULL;
            topCar = newCar;
            cout << "Ticket No: " << parkingTicket;
            ticketCounter++;
            generatedTicket++;
        }
        //if this car is not the first car to enter parking lot
        else
        {
            newCar->data = parkingTicket;
            newCar->next = topCar;
            topCar = newCar;
            cout << "Ticket No: " << parkingTicket;
            ticketCounter++;
            generatedTicket++;
        }
    }
}

/* Show all cars currently in the parking lot 
 ordered by time of entry */
void ParkingLot::displayCarsInParkingLot() {
    Node *tempNode;
    tempNode = topCar;
    if (tempNode == NULL) {
        cout << "THE PARKING LOT IS EMPTY.";
    }
    while (tempNode != NULL)
    {
        cout << tempNode->data << " ";
        tempNode = tempNode->next;
    }
}

/* Retrieve the designated car (X) from Alley-A by doing these 3 steps:
 1. Move all cars that arrived after car (X) to Alley-B
 2. Remove car (X) off Alley-A
 3. Move all cars in Alley-B back to Alley-A
 Check if Alley-A is empty
 Check if Alley-A contains car (X) or not
 */
void ParkingLot::retrieveOneCar() {
    int parkingTicket = 0;
    cout << "Ticket no. : ";
    cin >> parkingTicket;
    if (topCar == NULL) {
        cout << endl << "THE PARKING LOT IS EMPTY.";
    } else if (!carIsInParkingLot(parkingTicket)) {
        cout << endl << "CAR NOT PARKED IN MY LOT.";
    } else {
        //if car is @ the top of the stack (the last car that entered Alley-A)
        Node *deletedNode = NULL;
        if (topCar->data == parkingTicket) {
            deletedNode = topCar;
            topCar = deletedNode->next;
            delete deletedNode;
            ticketCounter--;
            return;
        //if car is not @ the Top of the stack
        } else {
            Node *previousNode = topCar;
            deletedNode = topCar->next;
            //traverse the list searching for the car
            while (deletedNode != NULL)
            {
                if (deletedNode->data == parkingTicket) {
                    previousNode->next = deletedNode->next;
                    delete deletedNode;
                    ticketCounter--;
                    break;
                }
                //if car still not yet found, move on to next car in list
                previousNode = deletedNode;
                deletedNode = deletedNode->next;
            }
        }
    }
}

/* Check if there is a car in parking lot */
bool ParkingLot::carIsInParkingLot(int parkingTicket) {
    Node *tempNode;
    tempNode = topCar;
    while (tempNode != NULL)
    {
        if (tempNode->data == parkingTicket) return true;
        tempNode = tempNode->next;
    }
    return false;
}

/* Display welcome message */
void ParkingLot::programIntroduction() {
    cout << "This program simulates operation of a parkinglot using stack and linked-list." << endl;
    cout << "Alley is wide enough for one car and is closed at one end." << endl;
}

/* Display control panel of the parking booth */
void ParkingLot::displayControlPanel() {
    cout << endl << "D)isplay" << "\t" << "P)Park" << "\t" << "R)etrieve" << "\t" << "Q)uit:";
}

/* Clear up memory and exit program */
void ParkingLot::quitProgram(ParkingLot *pkPtr) {
    Node *tempNode = topCar;
    while (tempNode != NULL) {
        Node* nextNode = tempNode->next;
        delete tempNode;
        tempNode = nextNode;
    }
    topCar = NULL;
    delete topCar;
    delete pkPtr;
}

/* MAIN PROGRAM */
int main() {
    
    char parkingLotControlBoothCommand;
    ParkingLot *pk_lot = new ParkingLot(10);

    pk_lot->programIntroduction();
    pk_lot->displayControlPanel();
    
    while (cin >> parkingLotControlBoothCommand || !cin.eof()) {
        
        switch (toupper(parkingLotControlBoothCommand)) {
            case PARKING:
                pk_lot->parkOneCar(pk_lot->getTicket());
                pk_lot->displayControlPanel();
                break;
            case DISPLAY:
                pk_lot->displayCarsInParkingLot();
                pk_lot->displayControlPanel();
                break;
            case RETRIEVE:
                pk_lot->retrieveOneCar();
                pk_lot->displayControlPanel();
                break;
            case QUIT:
                pk_lot->quitProgram(pk_lot);
                cout << "Bye bye!" << endl;
                return 0;
            default:
                cout << "Invalid Command! Please try again.";
                pk_lot->displayControlPanel();
                break;
        }
    }
}