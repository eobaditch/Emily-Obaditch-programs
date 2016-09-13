//Emily Obaditch Fund Comp II Lab 6
//
//Sets up and solves a sudoku board using class Puzzle

#include <iostream> 
#include "Puzzle.h"

using namespace std; 

int main(){

    Puzzle<int> puzz; 
    cout<<"Original Board"<<endl; 
    puzz.display(); 

    puzz.solve();  

    cout<<endl; 
    cout<<"Solved Board: "<<endl; 

    puzz.display();  
}
