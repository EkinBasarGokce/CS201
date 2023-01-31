// Ekin Başar Gökçe
// Section 1
// 22201373
#ifndef FLIGHTMAP_H
#define FLIGHTMAP_H
#include<string>
#include<list>
#include<vector>
#include<iostream>
using namespace std;

class Flight{
    public:
        string originCity;
        string destinationCity;
        int flightNumber;
        int cost;

        Flight(string originCity, string destinationCity, int flightNumber, int cost){
            this->originCity = originCity;
            this->destinationCity = destinationCity;
            this->flightNumber = flightNumber;
            this->cost = cost;
        };   
        ~Flight(){};

        friend ostream& operator<<(ostream& os, const Flight *f){
            os <<f->destinationCity<<" "<<f->flightNumber<<" "<<f->cost;
            return os;
        }
        
};

class City{
    public:
        string name;
        vector<Flight*> flights;
        vector<string> visited;

        City(string name){
            this->name = name;
        };

        ~City(){};

        friend ostream& operator<<(ostream& os, const City *c){
            os << c->name;
            return os;
        };

};

struct myTuple{
    string path;
    int cost;
    
    friend bool operator < (const myTuple& tp1, const myTuple& tp2){
        return (tp1.cost < tp2.cost);
    };
};



class FlightMap {
    public:
        vector<City*> adjacencyList;  // City cities yani aslında 
        FlightMap( const string cityFile, const string flightFile );
        ~FlightMap();
        void printAdjacencyList();
        City* findCity(string name) const;
        vector<City*> getNextCity(string cityName);
        void displayAllCities() const;
        void displayAdjacentCities( const string cityName ) const;
        void displayFlightMap() const;
        void findFlights( const string deptCity, const string destCity ); // const da olabilir 
};
#endif // FLIGHTMAP_H




/*
bool Map::isPath(City originCity, City destinationCity) {
            bool success; Stack aStack;
            unvisitAll(); // Clear marks on all cities
            // Push origin city onto aStack and mark it as visited
            aStack.push(originCity);
            markVisited(originCity);
            City topCity = aStack.peek();
            while (!aStack.isEmpty() && (topCity != destinationCity)) {
            // The stack contains a directed path from the origin city // at the bottom of the stack to the city at the top of
            // the stack
            // Find an unvisited city adjacent to the city on the // top of the stack
            City nextCity = getNextCity(topCity, nextCity);
            if (nextCity == NO_CITY)
            aStack.pop(); // No city found; backtrack
            else // Visit city {
                    aStack.push(nextCity);
            markVisited(nextCity); } // end if
            if (!aStack.isEmpty()) topCity = aStack.peek();
            }
        return !aStack.isEmpty();
            // end while } // end isPath

};*/