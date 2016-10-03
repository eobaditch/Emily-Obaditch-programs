// merge.cpp

#include "lsort.h"

#include <iostream>

// Prototypes

Node *msort(Node *head, CompareFunction compare);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, CompareFunction compare);

// Implementations

void merge_sort(List &l, bool numeric) {

    //dump_node(l.head); 
    if(numeric){
        l.head = msort(l.head, node_number_compare); 
    }
    else{
        l.head = msort(l.head, node_string_compare); 
    }

}

Node *msort(Node *head, CompareFunction compare) {

    Node * left = head;   
    Node * right = nullptr; 
    
    //dump_node(head); 
    
    //handle base case
    if(head == nullptr || head -> next == nullptr){
        //std::cout<<"head is null"; 
        return head; 
    }

    //divide into left and right 
    split(head, left, right);  
     
    //conquer left and right sublists
    left = msort(left, compare); 
    right = msort(right, compare); 
    
    //combine left and right sublists
    return merge(left, right, compare); 

}

void split(Node *head, Node *&left, Node *&right) {

    Node *temp = head;
    Node *slow_ptr = head; 
    Node  *fast_ptr = head; 
    
    while(fast_ptr != nullptr && fast_ptr->next != nullptr){
        
        temp = slow_ptr;
        slow_ptr = slow_ptr->next; 
        fast_ptr = fast_ptr->next->next; 
    
    }
    temp->next = nullptr; 

    left = head;     
    right = slow_ptr;  


}

Node *merge(Node *left, Node *right, CompareFunction compare) {
    
    Node *head;

    if (compare(left,right)){
        head = left;
        left = left->next;
    }
    else{
        head = right;        
        right = right->next;
    }

    Node * curr = head;

    while((left != nullptr ) || (right != nullptr )){
        
        if (right == nullptr){
            curr->next = left; 
            left = left->next; 
        }
        else if (left == nullptr){
            curr->next = right; 
            right = right->next; 
        }
        else if(compare(left, right)){
            curr->next = left; 
            left = left->next;
            
        } 
        else{
            curr->next = right; 
            right = right->next; 
        }
        curr= curr->next; 
    }
    return head; 
    
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
