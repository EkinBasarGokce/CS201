#include "FlightMap.h"

int main() {

    FlightMap fm( "cityFile.txt", "flightFile.txt" );
    cout << endl;
    fm.displayAllCities();
    cout << endl;
    fm.displayAdjacentCities( "W" );
    cout << endl;
    fm.displayAdjacentCities( "X" );
    cout << endl;
    fm.displayFlightMap();
    cout << endl;
    fm.findFlights( "W", "Z" );
    cout << endl;
    fm.findFlights( "S", "P" );
    cout << endl;
    fm.findFlights( "Y", "Z" );
    cout << endl;
    fm.findFlights( "P", "Z" );
    cout << endl;
    
    /*
    myTuple tuple1;
    tuple1.path = "Ekin Basar Goekce";
    tuple1.cost = 10;
    
    cout << "cost: " << tuple1.cost << endl; 
    cout << "info: " << tuple1.path << endl; 
    */
    return 0;
}