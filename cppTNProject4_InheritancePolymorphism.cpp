/*
 UCSC Extension, C++ Comprehensive, Spring 2016
 Assignment #4
 Project Name: using of virtual functions, Polymorphism and Inheritance
 input file name: airshipProj4.txt
 Compiler: XCode Version 7.2, Mac OS 10.10.5
 Due Date: June 11, 2016
 Student: Truc Ngo
 truc.dinh.ngo@gmail.com
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
using namespace std;

struct AirshipData {
    
    int airshipType;
    string airshipName;
    int numberOfPassengers;
    int amountOfCargo;
    int engineType;
    int maximumRange;
};

enum AirShipType {AIRPLANE = 0, BALOON = 1};
enum EngineType {Jet = 0, Propeller = 1};
enum GasType {Helium = 0, Hydrogen = 1};

class Airship {
public:
    Airship() {}
    virtual void GetData(AirshipData &data) = 0;
    virtual void ShowData() = 0;
    const char * setEngineType(EngineType engine);
    const char * setGasType(GasType gas);
    AirShipType getAirShipType() { return airShipTypeItem; }
    virtual ~Airship() { }
protected:
    AirShipType airShipTypeItem;
    string airshipName;
    int maxPassengerCount;
    int maxCargoWeight;
};

const char * Airship::setEngineType(EngineType engine)
{
    switch (engine) {
        case Jet:
            return "Jet";
            break;
        case Propeller:
            return "Propeller";
            break;
        default:
            return "Not defined engine";
            break;
    }
}

const char * Airship::setGasType(GasType gas)
{
    switch (gas) {
        case Helium:
            return "Helium";
            break;
        case Hydrogen:
            return "Hydrogen";
            break;
        default:
            return "Not defined gasType";
            break;
    }
}

/***************************************************************/
class Airplane : public Airship {
public:
    Airplane() : Airship() {}
    void GetData(AirshipData &data);
    void ShowData();
    ~Airplane() {}
private:
    EngineType engine_type;
    int maxium_range;
};

//Airplane: {airshipType, airplaneName, maxPassengerCount, maxCargoWeight, engineType, range}
void Airplane::GetData(AirshipData &data)
{
    //cast integer to enum
    airShipTypeItem = AirShipType(data.airshipType);
    airshipName  = data.airshipName;
    maxPassengerCount = data.numberOfPassengers;
    maxCargoWeight = data.amountOfCargo;
    engine_type = EngineType(data.engineType);
    maxium_range = data.maximumRange;
}

void Airplane::ShowData() {
    cout << setw(40) << left << airshipName << setw(30) << left << setEngineType(engine_type) << setw(20) << left
         << maxium_range << "\n";
}

/***************************************************************/
class Baloon : public Airship {
public:
    Baloon() : Airship() {}
    void GetData(AirshipData &data);
    void ShowData();
    ~Baloon() {}
private:
    GasType gas_type;
    int maximum_altitude;
};

//Baloon: {airshipType, balloonName, maxPassengerCount, maxCargoWeight, gasType, maxAltitude}
void Baloon::GetData(AirshipData &data)
{
    airShipTypeItem = AirShipType(data.airshipType);
    airshipName  = data.airshipName;
    maxPassengerCount = data.numberOfPassengers;
    maxCargoWeight = data.amountOfCargo;
    gas_type = GasType(data.engineType);
    maximum_altitude = data.maximumRange;
}

void Baloon::ShowData()
{
    cout << setw(40) << left << airshipName << setw(30) << left << setGasType(gas_type)
         << setw(20) << left << maximum_altitude << "\n";
}

/***************************************************************/

//AirShipType {Airplane=0,Ballon=1}
//{Engine Type [Jet = 0, Propeller = 1] Gas Type [Helium = 0, Hydrogen = 1]}
int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: PR <filename>\n";
        return 1;
    }
    ifstream inputFile(argv[1]);
    
    if (!inputFile) {
        cout << "Cannot open file\n";
        return 1;
    }
    char LineBuf[100];
    char d[] = ",";
    Airship *pAirship[10];
    int i=0;
    
    while (inputFile.getline(LineBuf, 100) && !inputFile.eof()) {
        AirshipData data;
        data.airshipType = atoi (strtok(LineBuf, d));
        switch (data.airshipType) {
            case AIRPLANE:
                // Create Airplan object
                pAirship[i] = new Airplane();
                data.airshipName = strtok(NULL, d);
                data.numberOfPassengers = atoi(strtok(NULL, d));
                data.amountOfCargo = atoi(strtok(NULL, d));
                data.engineType = atoi(strtok(NULL, d));
                data.maximumRange = atoi(strtok(NULL, d));
                break;
            case BALOON:
                // Create Baloon object
                pAirship[i] = new Baloon();
                data.airshipName = strtok(NULL, d);
                data.numberOfPassengers = atoi(strtok(NULL, d));
                data.amountOfCargo = atoi(strtok(NULL, d));
                data.engineType = atoi (strtok(NULL, d));
                data.maximumRange = atoi (strtok(NULL, d));
                break;
            default:
                break;
        }
        // call appropriate function
        pAirship[i++]->GetData(data);
        memset(LineBuf,'\0',100);
    }
    
    cout << "Listing of all Airplanes\n";
    cout << setw(40) << left << "Name" << setw(30) << "Engine Type" << setw(20) << "Maximum Range";
    cout << endl;
    for (int i = 0; i <90; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        if (pAirship[i]->getAirShipType() == AIRPLANE)
            pAirship[i]->ShowData();
    }

    
    cout << "\n\nListing of all Balloons\n";
    cout << setw(40) << left << "Name" << setw(30) << "Gas Type" << setw(20) << "Maximum Altitude";
    cout << endl;
    for (int i = 0; i <90; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        if (pAirship[i]->getAirShipType() == BALOON)
            pAirship[i]->ShowData();
    }

    
    for (int i = 0; i < 10; i++) {
        if (pAirship[i])
            delete pAirship[i];
    }
    inputFile.close();
    return 0;
}








