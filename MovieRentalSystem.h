// Ekin Başar Gökçe
// Section 1
// 22201373
#ifndef MOVIERENTALSYSTEM_H
#define MOVIERENTALSYSTEM_H
using namespace std;

template<class ItemType>
class Node {
     public:
          ItemType* data;
          Node<ItemType>* next;
          Node()
          {
               data = NULL;
               next = NULL;
          };

          ~Node(){
               delete(this->data);
          };
          
          Node(ItemType* data)
          {
               this->data = data;
               this->next = NULL;
          };

          Node(ItemType data)
          {
               this->data = new ItemType(data);
               this->next = NULL;
          };
};

template<class ItemType>
class LinkedList {
     public:
          Node<ItemType>* head;

          LinkedList() 
          {
               this->head = NULL; 
          }
          
          ~LinkedList(){ 
               if (this->head != NULL) {
                    Node<ItemType>* temp = this->head;
                    Node<ItemType>* next = this->head;

                    while (temp->next != NULL){
                         next = temp->next;
                         delete(temp);
                         temp = next;
                    }
                    delete(temp);        
               }
                      
          };

          void insertNode(ItemType* data) 
          {
               Node<ItemType>* newNode = new Node<ItemType>(data);
               if (this->head == NULL)
               {
                    this->head = newNode;      
               }
               else{
                    Node<ItemType>* temp = this->head;
                    if (*head->data >= *newNode->data){
                         temp = head;
                         head = newNode;
                         head -> next = temp;
                    }
                    else{
                         while(temp->next != NULL && *temp->next->data < *newNode->data){
                              temp = temp->next;
                         } 
                         Node<ItemType>* temp2;
                         temp2 = temp -> next;
                         temp -> next = newNode;
                         newNode -> next = temp2;
                    }
               }
               return;
          };

          void insertNode(ItemType data) 
          {
               Node<ItemType>* newNode = new Node<ItemType>(data);
               if (this->head == NULL)
               {
                    this->head = newNode;      
               }
               else{
                    Node<ItemType>* temp = this->head;
                    if (*head->data >= *newNode->data){
                         temp = head;
                         head = newNode;
                         head -> next = temp;
                    }
                    else{
                         while(temp->next != NULL && *temp->next->data < *newNode->data){
                              temp = temp->next;
                         }

                         Node<ItemType>* temp2;
                         temp2 = temp -> next;
                         temp -> next = newNode;
                         newNode -> next = temp2;
                    }
                   
               }
               return;
          };  

          void removeNode(int data) 
               {    
                    Node<ItemType>* temp = this->head;
                    Node<ItemType>* prev = NULL;

                    if (temp != NULL && *temp -> data == data)
                    {
                         head = temp -> next; 
                         delete temp;            
                         return;
                    }
                    else{
                         while (temp != NULL && (*temp->data == data) == false)
                         {
                              prev = temp;
                              temp = temp->next;
                         }
                         if (temp == NULL)
                              return;
                         prev -> next = temp -> next;
                         delete temp;
                    }
                    return;
               };  

          ItemType* findItem(const int itemId) const{
               if (this->head == NULL)
               {
                    return NULL;    
               }
               else{
                    if ( *head->data > itemId){
                        return NULL;
                    }
                    else{
                         if ( *head->data == itemId ){
                              return head->data;
                         }
                         else{
                              Node<ItemType>* temp = this->head;
                              while(temp->next != NULL && *temp->data != itemId){
                                   temp = temp->next;
                              }
                              if ( *temp->data == itemId ){
                                   return temp->data;
                              }
                              else{
                                   return NULL;
                              }
                         }
                    }
               }

          }

          void replaceNode(int data)
               {    
                    Node<ItemType>* temp = this->head;
                    if (temp != NULL){
                         if(*temp -> data == data){
                              *temp -> data = -1;
                              return;
                         }     
                         else{
                              while (temp != NULL && (*temp->data == data) == false)
                              {
                                   temp = temp->next;
                              }
                              if (temp != NULL) {
                                   if (*temp->data == data){
                                        *temp->data = -1;
                                        return;       
                                   }
                              }
                              return;
                         }
                    return;
                    }
               };  

          friend ostream& operator<<(ostream& os, const LinkedList<ItemType>* ll){
               if (ll->head == NULL)
               {
                    os << "head->NULL";   
               }
               else{
                    Node<ItemType>* temp = ll->head;
                    os << "head->" << *temp->data << "->";
                    while(temp->next != NULL){
                         temp = temp->next;
                         os << *temp->data << "->";
                    }
                    os << "NULL";
               }
               return os;
          }
};


class Movie{
     public:
          int movieID;
          int replicateAmount;
          int ogReplicateAmount;
          LinkedList<int> activeSubscribers;
          LinkedList<int> allSubscribers;

          Movie(const int id, const int replicates){ 
               movieID = id;
               replicateAmount = replicates;
               ogReplicateAmount = replicates;

          }
          ~Movie() {
          }     
          friend bool operator >= (const Movie& m1, const Movie& m2){
               return (m1.movieID >= m2.movieID);
          }
          friend bool operator < (const Movie& m1, const Movie& m2){
               return (m1.movieID < m2.movieID);
          }

          friend bool operator > (const Movie& m, const int id){
               return (m.movieID > id);
          }
          friend bool operator < (const Movie& m, const int id){
               return (m.movieID < id);
          }
          friend bool operator == (const Movie& m, const int id){
               return (m.movieID == id);
          }
          friend bool operator != (const Movie& m, const int id){
               return (m.movieID != id);
          }
          friend ostream& operator<<(ostream& os, const Movie& m){
               os << m.movieID;
               return os;
          }
          friend ostream& operator<<(ostream& os, const Movie* m){
               os << m->movieID;
               return os;
          }
};

class Subscriber{
     public:
          int subscriberID;
          LinkedList<int> transactions;
          LinkedList<int> activeMovies;

          Subscriber(const int id){ 
               subscriberID = id;
          }
           ~Subscriber() {}     
          friend bool operator >= (const Subscriber& sub1, const Subscriber& sub2){
               return (sub1.subscriberID >= sub2.subscriberID);
          }
          friend bool operator < (const Subscriber& sub1, const Subscriber& sub2){
               return (sub1.subscriberID < sub2.subscriberID);
          }

          friend bool operator > (const Subscriber& m, const int id){
               return (m.subscriberID > id);
          }
          friend bool operator < (const Subscriber& m, const int id){
               return (m.subscriberID < id);
          }
          friend bool operator == (const Subscriber& m, const int id){
               return (m.subscriberID == id);
          }
          friend bool operator != (const Subscriber& m, const int id){
               return (m.subscriberID != id);
          }
          friend ostream& operator<<(ostream& os, const Subscriber& sub){
               os << sub.subscriberID;
               return os;
          }
          friend ostream& operator<<(ostream& os, const Subscriber* sub){
               os << sub->subscriberID;
               return os;
          }
};


class MovieRentalSystem {
public:
    LinkedList<Movie> movieList;
    LinkedList<Subscriber> subscriberList;
    MovieRentalSystem( const string movieInfoFileName,
                      const string subscriberInfoFileName );
    ~MovieRentalSystem();
void removeMovie( const int movieId );
void addMovie( const int movieId, const int numCopies );
void removeSubscriber( const int subscriberId );
void rentMovie( const int subscriberId, const int movieId );
void returnMovie( const int subscriberId, const int movieId );
void showMoviesRentedBy( const int subscriberId ) const;
void showSubscribersWhoRentedMovie( const int movieId ) const;
void showAllMovies() const;
void showAllSubscribers() const;
}; 

#endif // MOVIERENTALSYSTEM_H

