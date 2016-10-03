// Challenge 02: Adding List-Based Integers
//Emily Obaditch eobaditc

#include <iostream> 
#include <string>
using namespace std; 

template<typename T>
struct Node{
    T data; 
    struct Node *next; 
}; 


template <typename T>
struct List{

        Node<T> head; 
        List() : head ({'\0', NULL}) {}  //constructor 
        void prepend(const T &data){            
            head.next =  new Node<T>{data, head.next}; 
        
        }
        ~List(){
            Node<T> * next = NULL; 
            for(Node<T> * curr = head.next; curr !=NULL; curr = next){
                next = curr->next; 
                delete curr; 
            }
        }
        
}; 

template <typename T>
struct List<T> combine(struct List<T> &first, struct List<T> &second){

    struct List<int> newList; 

    int sum; 
    bool carry = false;  
    string sumString; 
    Node<T> *  curr = &first.head; 
    Node<T> *  curr2 = &second.head; 
    
    carry = false; 
    
    while( curr!=NULL ||  curr2!=NULL){
        if (curr !=NULL && curr2!= NULL){
            sum = (curr->data)+(curr2->data); 
            curr = curr->next; 
            curr2 = curr2->next; 
        }
        else if (curr != NULL){
            sum = (curr->data); 
            curr = curr->next; 
        }
        else if (curr2 !=NULL){
            sum = (curr2->data); 
            curr2 = curr2->next; 
        }
        
        if(carry == false && sum <10 ){
            newList.prepend(sum);
            carry = false; 
        }
        else if (carry == false && sum >=10){
            newList.prepend(sum-10);  
            carry = true; 
        }
        else if (carry == true && sum <9){
            newList.prepend(sum + 1); 
            carry = false; 
        }
        else if (carry == true && sum >= 9 ){
            newList.prepend((sum +1)-10); 
            carry = true; 
        }       
        //check for extra carry 
        if (curr == NULL && curr2 == NULL && carry){
            newList.prepend(1); 
        }
    }
    return newList;
    
}

template <typename T>
void print(struct List<T> &source){
    
    Node<T> *curr = &source.head; 
    for(curr = curr->next; curr->next != NULL; curr = curr ->next){
        cout<<curr->data; 
    }
    cout<<endl; 
    
        
}

int main(int argc, char *argv[]) {


    string line; 
    bool second = false; 

    

    while(getline(cin, line)){
        struct List<int> list1; 
        struct List<int> list2; 
        for(unsigned int i=0; i<line.size(); i++){
            if(line[i] == ' '){
                second = true; 
            }
            else if (second){
                list2.prepend(line[i]-48); 
            }
            else{
                list1.prepend(line[i]-48); 
            }

        }
       
        second = false;
        struct List<int> list3 = combine(list1, list2); 
   
        print(list3); 
    }
    
    return 0;
}


// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
