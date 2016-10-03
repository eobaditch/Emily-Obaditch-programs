// stl.cpp

#include "lsort.h"
#include <vector>
#include <algorithm>
#include <iostream>

void stl_sort(List &l, bool numeric) {

    std::vector<Node *> v; 

    for(Node * curr = l.head; curr != nullptr; curr = curr->next){
        
        v.push_back(curr); 

    }
    if(numeric){
        std::sort(v.begin(), v.end(), node_number_compare); 
    }
    else{
        std::sort(v.begin(), v.end(), node_string_compare); 
    
    }
    l.head = v[0]; 
    Node * curr = l.head; 
    for(size_t i = 1; i< v.size(); i++){
        curr->next = v[i]; 
        curr = curr->next;  
    }
    curr->next = nullptr; 
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
