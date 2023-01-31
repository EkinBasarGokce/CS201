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


void MovieRentalSystem::showAllMovies() const {
     cout << "Movies in the movie rental system:" << endl;
     Node<Movie>* temp = this ->movieList.head;
     while(temp->next != NULL){
          cout<<temp->data<< " "<< temp->data->ogReplicateAmount <<endl;
          temp = temp->next;
     }
     cout<<temp->data<< " "<< temp->data->ogReplicateAmount <<endl;
};


void MovieRentalSystem::showAllSubscribers() const {
     cout << "Subscribers in the movie rental system:" << endl;
     Node<Subscriber>* temp = this->subscriberList.head;
     while(temp->next != NULL){
          cout<<temp->data<<endl;
          temp = temp->next;
     }
     cout<<temp->data<<endl;
};


void MovieRentalSystem::addMovie( const int movieId, const int numCopies ){
     if (this->movieList.findItem(movieId) == NULL ){
          Movie* movie = new Movie(movieId, numCopies); 
          this->movieList.insertNode(movie);
          cout << "Movie " << movieId << " has been added" << endl;
     }
     else{
          cout << "Movie " << movieId << " already exists" << endl;
     }
};


void MovieRentalSystem::removeMovie (const int movieId){
     Movie* movie = movieList.findItem(movieId);
     if ( movie != NULL ){
          if ( movie->replicateAmount == movie->ogReplicateAmount ){
               this->movieList.removeNode(movieId);
               cout << "Movie " << movieId << " has been removed" << endl;
          }
          else {
               cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned" << endl;
          }
     }
     else{
          cout << "Movie " << movieId << " does not exist" << endl;
     }
};


void MovieRentalSystem::removeSubscriber( const int subscriberId ){
     Subscriber* subs = subscriberList.findItem(subscriberId);

     if(subs != NULL){ // checks whether the subscriber even exists
          if(subs -> activeMovies.head != NULL){ 
               Node<int>* temp = subs -> activeMovies.head;
               while(temp->next != NULL){
                    if( *temp->data != -1){ 
                         cout << "Subscriber " << subscriberId << " cannot be removed -- at least one movie has not been returned" << endl;
                         return;
                         }
                         temp = temp->next;
                    }
               if( *temp->data == -1){
                         this->subscriberList.removeNode(subscriberId);
                         cout << "Subscriber " << subscriberId << " has been removed" << endl;
                         return;
                         }
               this->subscriberList.removeNode(subscriberId);
               cout << "Subscriber " << subscriberId << " has been removed" << endl;
               return;  
          }
          else{ 
               this->subscriberList.removeNode(subscriberId);
               cout << "Subscriber " << subscriberId << " has been removed" << endl;
          }
     }
     else{
          cout << "Subscriber " << subscriberId << " does not exist" << endl;
     }
}; 


void MovieRentalSystem::rentMovie( const int subscriberId, const int movieId ){ 

     if (this->movieList.findItem(movieId) == NULL && this->subscriberList.findItem(subscriberId) == NULL) {
          cout<<"Subscriber " << subscriberId <<" and movie "<< movieId <<" do not exist"<<endl;
          return;
     }
     else {    
          if (this->movieList.findItem(movieId) != NULL){
               if (this->subscriberList.findItem(subscriberId) != NULL){
                    Movie* movie = this->movieList.findItem(movieId);
                    Subscriber* subs = this->subscriberList.findItem(subscriberId);
                    if (movie -> replicateAmount > 0){
                         movie->activeSubscribers.insertNode(subs->subscriberID);
                         movie->allSubscribers.insertNode(subs->subscriberID);
                         subs->transactions.insertNode(movie->movieID);
                         subs->activeMovies.insertNode(movie->movieID);
                         movie->replicateAmount = movie->replicateAmount - 1;
                         cout << "Movie " << movieId << " has been rented by subscriber " << subscriberId << endl;
                         return;
                    }
                    else{
                         cout << "Movie " << movieId << " has no available copy for renting" << endl;
                         return;
                    }
               }
               else{
                    cout << "Subscriber " << subscriberId << " does not exist" << endl;
                    return;
               }
          }  
          else{
               cout<<"Movie " << movieId << " does not exist"<<endl;
               return;
          }
     }  
};


void MovieRentalSystem::returnMovie( const int subscriberId, const int movieId ){
     
     Movie* movie = this->movieList.findItem(movieId);
     Subscriber* subs = this->subscriberList.findItem(subscriberId);

     if(movie != NULL){
          if(subs != NULL){
               // Node for movies in transaction list
               Node<int>* temp = subs->activeMovies.head;
               int count = 0; 
               while (temp->next != NULL){
                    if (*temp->data == movie->movieID){
                         count ++;
                         break;
                    }
                    temp = temp->next;
               }
               if (*temp->data == movie->movieID){
                         count ++;
                    }
               // Node for subs in allSubs list
               Node<int>* temp1 = movie->activeSubscribers.head;
               int count1 = 0; 
               while (temp1->next != NULL){
                    if (*temp1->data == subs->subscriberID){
                         count1 ++;
                         break;
                    }
                    temp1 = temp1->next;
               }
               if (*temp1->data == subs->subscriberID){
                         count1 ++;
                    } 
               // Now the fun part!!
               if (count != 0 || count1 != 0 ){
                    movie->activeSubscribers.replaceNode(subs->subscriberID);
                    subs->activeMovies.replaceNode(movie->movieID);
                    movie->replicateAmount = movie->replicateAmount + 1;
                    cout << "Movie " << movieId << " has been returned by subscriber " << subscriberId << endl;
               }
               else {
                    cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
               }    
          }
          else{
               cout << "Subscriber " << subscriberId << " does not exist" << endl;
          }
     }
     else{
          cout<<"Movie " << movieId << " does not exist"<<endl;
     }
};


void MovieRentalSystem::showMoviesRentedBy( const int subscriberId ) const{

     Subscriber* subs = this->subscriberList.findItem(subscriberId);
     if(subs != NULL){
          Node<int>* temp = subs->transactions.head;
          Node<int>* temp1 = subs->activeMovies.head;
          if (temp != NULL){
               cout<< "Subscriber "<< subscriberId << " has rented the following movies:"<< endl;
               while(temp->next != NULL && temp1->next != NULL){
                    if(*temp->data == *temp1->data){
                         cout<< *temp->data << " not returned" << endl;
                    } 
                    else if (*temp1->data == -1){
                         cout<< *temp->data << " returned" << endl;
                    }
                    temp = temp->next;
                    temp1 = temp1->next;
               }
               if(*temp->data == *temp1->data){
                    cout<< *temp->data << " not returned" << endl;
               } 
               else if (*temp1->data == -1){
                    cout<< *temp->data << " returned" << endl;
               }
          }
          else{
               cout<< "Subscriber "<< subscriberId << " has not rented any movies"<< endl;
          }
     }
     else{
          cout << "Subscriber " << subscriberId<<" does not exist" << endl;
     }
}; 


void MovieRentalSystem::showSubscribersWhoRentedMovie( const int movieId ) const{
     
     Movie* movie = this->movieList.findItem(movieId);
     if(movie != NULL){
          Node<int>* temp = movie->allSubscribers.head; // to iterate over allSubs

          if (temp != NULL) {
               cout<< "Movie "<< movieId << " has been rented by the following subscribers:" << endl;
               while(temp->next != NULL){
                    
                    Node<int>* allCountPtr = movie->allSubscribers.head; // to iterate over allSubs
                    Node<int>* activeCountPtr = movie->activeSubscribers.head; // to iterate over activeSubs
                    // Get the counts of the element in allSubs list 
                    int allCount = 0;
                    while (allCountPtr->next!=NULL){
                         if (*allCountPtr->data == *temp->data){
                              allCount ++;
                         }
                         allCountPtr = allCountPtr->next;
                    }
                    if (*allCountPtr->data == *temp->data){ // for the last subscriber
                              allCount ++;
                         }
                    // Get the counts of the element in activeSubs list 
                    int activeCount = 0;
                    while (activeCountPtr->next!=NULL){
                         if (*activeCountPtr->data == *temp->data){
                              activeCount ++;
                         }
                         activeCountPtr = activeCountPtr->next;
                    }
                    if (*activeCountPtr->data == *temp->data){ // for the last subscriber
                              activeCount ++;
                    }
                    // use these counts to decide what happened (returned / not returned) 
                    int returnedCount;
                    returnedCount = allCount - activeCount;
                    for (int m = 0; m < returnedCount; m++){
                         cout<< *temp->data << " returned" << endl;
                    }
                    for (int n = 0; n < activeCount; n++){
                         cout<< *temp->data << " not returned" << endl;
                    }                               
                    // If we have multiple copies of a subscriber,
                    // Then we need to step further for the amount of repetitions 
                    // to prevent printing out the same thing for each repetition!!!!!
                    // GREEAAAAAATTTTTTTTTTT!!!!!!!!
                    for (int sameTurn = 0; sameTurn < allCount; sameTurn++){
                         temp = temp->next;
                    }
               }
               // Repeat everyting inside of the while loop for the last element (below!!)
               Node<int>* allCountPtr = movie->allSubscribers.head; // to iterate over allSubs
               Node<int>* activeCountPtr = movie->activeSubscribers.head; // to iterate over activeSubs

               int allCount = 0;
               while (allCountPtr->next!=NULL){
                    if (*allCountPtr->data == *temp->data){
                         allCount ++;
                    }
                    allCountPtr = allCountPtr->next;
               }
               if (*allCountPtr->data == *temp->data){ // son element için
                         allCount ++;
                    }
               // Get the counts of the element in activeSubs list 
               int activeCount = 0;
               while (activeCountPtr->next!=NULL){
                    if (*activeCountPtr->data == *temp->data){
                         activeCount ++;
                    }
                    activeCountPtr = activeCountPtr->next;
               }
               if (*activeCountPtr->data == *temp->data){ // son element için
                         activeCount ++;
               }
               // use these counts to decide what happened with 
               int returnedCount;
               returnedCount = allCount - activeCount;
               for (int m = 0; m < returnedCount; m++){
                    cout<< *temp->data << " returned" << endl;
               }
               for (int n = 0; n < activeCount; n++){
                    cout<< *temp->data << " not returned" << endl;
               }  
          }
          else{
               cout << "Movie " << movieId << " has not been rented by any subscriber" << endl;
          }       
     }
     else{
          cout<<"Movie " << movieId << " does not exist"<<endl;
     }
}

