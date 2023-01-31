// Ekin Başar Gökçe
// Section 1
// 22201373
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include "FlightMap.h"
#include<vector>
#include<iterator>
#include<list>
#include<stack>
#include <algorithm>
//#include<tuple>

using namespace std;

bool cityComparison(City* c1, City* c2){
    return std::strcmp(c1->name.c_str(), c2->name.c_str()) < 0;
};

bool flightComparison(Flight* f1, Flight* f2){
    return std::strcmp(f1->destinationCity.c_str(), f2->destinationCity.c_str()) < 0;
};

bool costComparison(Flight* f1, Flight* f2){
    return f1->cost < f2->cost;
};

bool isElement(vector <string> liste, string item){
    return std::find(liste.begin(), liste.end(), item) != liste.end();
};

bool compare( myTuple mytup1, myTuple mytup2){
    return mytup1.cost < mytup2.cost;
};


FlightMap::FlightMap( const string cityFile, const string flightFile ){

    ifstream cityInfoFile; 
    cityInfoFile.open(cityFile);
    if (!cityInfoFile) 
    {
        cout << "Input file " << cityFile << " does not exist" << endl;
        return;
    }
    else{
        ifstream flightInfoFile; 
        flightInfoFile.open(flightFile);
        if (!flightInfoFile) 
        {
            cout << "Input file " << flightFile << " does not exist" << endl;
            return;
        }
        else{
            //cout << "Here we are" << endl;
            string cityName;
            while (getline(cityInfoFile, cityName))
            {
                //cout << cityName << endl;
                City* city = new City(cityName);                
                this->adjacencyList.push_back(city);
            }
            
            sort(this->adjacencyList.begin(), this->adjacencyList.end(), cityComparison);

            cout << endl; // ekstra boşluk olsundu

            string flightInfo;
            int flightCount = 0;
            while(getline(flightInfoFile, flightInfo))
            {
                //cout << flightInfo << endl;
                int first_s = flightInfo.find(";");
                int second_s = flightInfo.find(";",first_s + 1);
                int third_s = flightInfo.find(";",second_s + 1);

                string originCity = flightInfo.substr(0, first_s); 
                string destinationCity = flightInfo.substr(first_s+1, second_s-first_s-1); 
                string flightNumber = flightInfo.substr(second_s+1, third_s-second_s-1); 
                string cost = flightInfo.substr(third_s+1);
                
                //cout<<originCity<<" "<<destinationCity<<" "<<flightNumber<<" "<<cost<<endl; 

                Flight* flight = new Flight(originCity, destinationCity, stoi(flightNumber), stoi(cost));
                
                City* city = findCity(originCity);
                if(city){
                    //cout<<isElement(city->flights, flight)<<endl;
                    city->flights.push_back(flight);
                    //cout<<isElement(city->flights, flight)<<endl;
                }
                flightCount ++;   
            }
            flightInfoFile.close();

            for(size_t i=0; i < this->adjacencyList.size(); i++ ){
                City* temp = this->adjacencyList[i];
                sort(temp->flights.begin(), temp->flights.end(), flightComparison);
            }
            
            cout<< this->adjacencyList.size() <<" cities and " << flightCount <<" flights have been loaded"<<endl;
        }
    }
};

FlightMap::~FlightMap(){}; 

vector<City*> FlightMap::getNextCity(string cityName){
    City * city = this->findCity(cityName);
    vector<City*> cities;
    vector<Flight*> fligths;

    if(city){
        if(!city->flights.empty()){
            //sort(city->flights.begin(), city->flights.end(), costComparison);
            City* temp = NULL;
            for(size_t j = 0; j<city->flights.size(); j++){
                temp = this->findCity(city->flights[j]->destinationCity); 
                if(temp){
                    cities.push_back(temp);
                }
            }
        }
    }
    //sort(city->flights.begin(), city->flights.end(), flightComparison);
    return cities;
}

void FlightMap::printAdjacencyList(){
    for(size_t i=0; i < this->adjacencyList.size(); i++ ){
        City* temp = this->adjacencyList[i];
        cout<<temp->name<<": ";
        for(size_t j=0; j < temp->flights.size(); j++ ){
            cout<<temp->flights[j]<<" / ";
        }
        cout<<endl;
    }
}

City* FlightMap::findCity(string name) const{
    for(size_t i=0; i < this->adjacencyList.size(); i++ ){
        if(this->adjacencyList[i]->name == name){
            return this->adjacencyList[i];
        }
    }
    return NULL;
};

void FlightMap::displayAllCities() const {
    cout<<"The list of the cities that HPAir serves is given below:"<<endl;
    for(size_t i=0; i < this->adjacencyList.size(); i++ ){
        cout<<this->adjacencyList[i]<<", ";
    }
    cout<<endl;
};


void FlightMap::displayAdjacentCities( const string cityName ) const{
    City * city = this->findCity(cityName);
    if(city){
        cout<<"The cities adjacent to "<<city->name<<" are:"<<endl;
        cout<<city->name<<" -> ";
        for(size_t j=0; j < city->flights.size(); j++ ){
            cout<<city->flights[j]->destinationCity<< ", ";
        }
        cout<<endl;
    }
};


void FlightMap::displayFlightMap() const{
    cout<<"The whole flight map is given below: "<<endl;
    for(size_t i=0; i < this->adjacencyList.size(); i++ ){
        City* city = this->adjacencyList[i];   
        cout<<city->name<<" -> ";
        for(size_t j=0; j < city->flights.size(); j++ ){
            cout<<city->flights[j]->destinationCity<< ", ";
        }
        cout<<endl;
    }    
};


void FlightMap::findFlights( const string deptCity, const string destCity ){
    vector<string> visited; 
    stack<City*> aStack;
    stack<City*> costStack; // coastal heritage of Turkey
    City* originCity = this->findCity(deptCity);
    //vector<tuple < int, string > > paths;
    vector<myTuple> paths;

    for(size_t i=0; i < this->adjacencyList.size(); i++ ){
        this->adjacencyList[i]->visited.clear();
    }

    if(originCity){
        cout<<"Request is to fly from "<< deptCity <<" to "<<destCity<<":"<<endl;
        aStack.push(originCity);
        visited.push_back(originCity->name);

        City* topCity = aStack.top();
        City* prev = NULL;
        
        while (!aStack.empty()){
            vector<City*> cities = getNextCity(topCity->name);
            int found=0;
/*
            cout<<"top Cirt "<<topCity<<endl;
            for(int m=0; m < visited.size(); m++ ){
                cout<<visited[m]<<", ";
            }
            cout<<endl;
 
            cout<< topCity<<" -> ";
            for(int m=0; m < cities.size(); m++ ){
                cout<<cities[m]<<", ";
            }
            cout<<endl;

//            cout << aStack.top()<<endl;

            cout<< topCity<<" VV ";
            for(int m=0; m < topCity->visited.size(); m++ ){
                cout<<topCity->visited[m]<<", ";
            }
            cout<<endl;
*/
            for(size_t k=0; k<cities.size(); k++){
                City* nextCity = cities[k];
                
                //cout<<"next "<<nextCity<<endl;

                if(!isElement(topCity->visited, nextCity->name) && !isElement(visited, nextCity->name) ) { 
                    aStack.push(nextCity);
                    visited.push_back(nextCity->name);
                    //cout<<"lets look"<<endl;

                    found = 1;
                    if (nextCity->name == destCity){ 
                        if(prev != NULL && prev->name == topCity->name){ 
                            //cout<<"prev "<<prev<<endl;
                            aStack.pop();
                            visited.pop_back();
                            found = 0;
                            prev = NULL;
                            continue;
                        }
                        
                        string path = "";
                        //cout<<"path found!"<<endl;

                        prev = topCity;
                        City* temp;
                        City* next;
                        int totalCost=0;
                        while(!aStack.empty()){
                            costStack.push(aStack.top());
                            aStack.pop();
                        }
                        temp = costStack.top();
                        aStack.push(temp);
                        costStack.pop();
                        while(!costStack.empty()){
                            next = costStack.top(); 
                            int cost = 0;
                            for(size_t j=0; j<temp->flights.size();j++)
                                if(temp->flights[j]->destinationCity == next->name){
                                    cost = temp->flights[j]->cost;
                                    path += "Flight #"+ to_string(temp->flights[j]->flightNumber) + " from " + temp->name + " to " + next->name + ", Cost: " + to_string(cost) + " TL\n";
                                    break;
                                }   
                            totalCost += cost;
                            aStack.push(next);
                            temp = next;
                            costStack.pop();
                        }
                        path += "Total Cost: " + to_string(totalCost) + " TL\n";
                        
                        /////////
                        myTuple tempTuple;
                        tempTuple.cost = totalCost;
                        tempTuple.path= path;
                        paths.push_back(tempTuple);
                        /////////

                        //paths.push_back(make_tuple(totalCost,path));
                    } // bulduk mu bulmadık mı
                    else{
                        topCity->visited.push_back(nextCity->name);
                    }    
                } // visited'da mı değil mi
                if(found){
                    break; // for'dan çık
                }
            } // büyük for
            if(!found){
                aStack.pop();
                visited.pop_back();
            }
            if (!aStack.empty()){ //
                topCity = aStack.top();   
            }
            // break;
        } // end while

        if(paths.empty()){
            cout<<"Sorry. HPAir does not fly from "<< deptCity <<" to "<<destCity<<"."<<endl;
        }
        else{
            sort(paths.begin(), paths.end(), compare);

            for(size_t l=0; l<paths.size(); l++){
                //cout<<get<1>(paths[l]);
                cout<<paths[l].path<<endl;
            }
        }
    }
    else{
        cout<<"There is no origin city named "<<originCity<<endl;
    }
};
