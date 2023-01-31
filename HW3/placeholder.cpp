// Ekin Başar Gökçe
// Section 1
// 22201373
#include<iostream>
#include<fstream>
#include <string>
#include "MovieRentalSystem.h"
using namespace std;

MovieRentalSystem::MovieRentalSystem( const std::string movieInfoFileName, const std::string subscriberInfoFileName )
{
     ifstream movieFile; 
     movieFile.open(movieInfoFileName);
     if (!movieFile) 
     {
          cout << "Input file " << movieInfoFileName << " does not exist" << endl;
          return;
     }
     else{
          int movieCount = 0; 
          movieFile >> movieCount; 
          for(int i = 0; i < movieCount; i++){ 
               int movieID; 
               int movieReplicate; 
               movieFile >> movieID;
               movieFile >> movieReplicate;
               Movie* movie = new Movie(movieID, movieReplicate); 
               this->movieList.insertNode(movie);
          }
          movieFile.close(); 
               
          ifstream subscriberFile; 
          subscriberFile.open(subscriberInfoFileName);

          if (!subscriberFile) 
          {
               cout << "Input file " << subscriberInfoFileName << " does not exist" << endl;
               return;
          }
          else{
               int subscriberCount = 0; 
               subscriberFile >> subscriberCount;

               for(int j = 0; j < subscriberCount; j++)
               { 
                    int subscriberID = 0; 
                    subscriberFile >> subscriberID; 
                    Subscriber* sub = new Subscriber(subscriberID); 
                    this->subscriberList.insertNode(sub);
               }
               subscriberFile.close(); 

               cout << subscriberCount << " subscribers and " << movieCount << " movies have been loaded" << endl;

               return;
          }
          
     }      
};


MovieRentalSystem::~MovieRentalSystem(){};
