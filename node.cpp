// node.cpp

#include "lsort.h"
#include <string> 
#include <iostream>

bool node_number_compare(const Node *a, const Node *b) {
    return (a->number < b->number); 
}

bool node_string_compare(const Node *a, const Node *b) {
    return (a->string < b->string); 
}

int void_number_compare(const void *a, const void *b) {
 
    Node *na = *(Node **)a;
    Node *nb = *(Node **)b;
   
    return (na->number > nb->number); 
}

int void_string_compare(const void *a, const void *b) {
    
    Node *na = *(Node **)a;
    Node *nb = *(Node **)b;   

    std::string first = na->string; 
    std::string second = nb->string; 

    return (first > second);
}

//helper function outputs contents of each node from n to nullptr
void dump_node(Node *n) {

    for(Node * curr = n; curr != nullptr; curr = curr->next){
        std::cout<<"Number: "<<curr->number<<" String: "<<curr->string<<std::endl; 
    }

}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
