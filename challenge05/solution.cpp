// Challenge 05: BST
// Emily Obaditch eobaditc
// 28 Sept 2016
#include <sstream>
#include <iostream>
#include <string>
#include<vector>
#include <climits>
using namespace std;


bool isBST(vector<int>, int); 

bool search(vector<int>, int, int, int, int); 

// Main Execution

int main(int argc, char *argv[]) {
    
    string line, num, value; 
    int count = 1; 

    while(getline(cin, line)){
        stringstream s(line); 
        getline(s, num, ' '); 
        vector<int> values;  
        for(int i=0; i<stoi(num); i++){
            getline(s, value, ' ');             
            values.push_back(stoi(value));  
        }

        int offset = 0; 
        bool bst = isBST(values, offset); // =  search(values, root, root, root); 
        if(bst){
            cout<<"Tree "<<count<<" is a BST"<<endl; 
        }
        else{
            cout<<"Tree "<<count<<" is not a BST"<<endl; 
        }
        count++; 
    
    }
    
    return EXIT_SUCCESS;
}

bool isBST(vector<int> values, int offset){
   
    //inital min and max are  root value 
    return search(values, values[0], values[0], values[0], offset);

}

bool search(vector<int> values, int curr, int max, int min, int i ){
    
    if (values.size() <= (unsigned int)(2*i + 2)){
        return true; 
    }


    int curr_left = values[ 2*i + 1 ];   //left node value in BFS traversal
    int curr_right = values[ 2 * i+2 ];  //right node value in BFS traversal
    
    //set new max and min 
    if (curr_right > curr && curr_right > max ){
        max = curr_right; 
    }
    if (curr_left < curr && curr_left < min){
        min = curr_left; 
    }

    //check if current is within max and min 
    if( i % 2 == 0 && curr > max){
        return false; 
    }
    else if ( i % 2 != 0 && curr < min){
        return false; 
    }

    //check direct children 
    if((curr_left > curr && curr != -1 && curr_left != -1 ) || (curr_right <=curr && curr != -1 && curr_right!= -1)){
        return false; 
    }
    else{ 
        return  search(values, curr_left, max, min, i+1 );  
    }
    return true; 
    
}



// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
