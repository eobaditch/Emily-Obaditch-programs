// qsort.cpp

#include "lsort.h"

#include <cstdlib>
#include <array>
#include <iostream>
#include <vector>
#include <algorithm>

void qsort_sort(List &l, bool numeric) {
   
    int i = 0; 

    
    Node **nodeArray = new Node*[l.size];  
    
    for(Node * curr = l.head; curr !=nullptr; curr = curr->next){
        
        nodeArray[i] = curr; 
        i++; 

    }

    if(numeric){
        qsort(nodeArray, l.size, sizeof(Node*), void_number_compare);
    }
    else{
        qsort(nodeArray, l.size,  sizeof(Node*), void_string_compare);
    }

    l.head = nodeArray[0]; 
    size_t j;   
    for(j = 0; j< l.size - 1; j++){
        nodeArray[j]->next = nodeArray[j+1]; 
    }
    nodeArray[j]->next = nullptr; 
    delete[] nodeArray;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
