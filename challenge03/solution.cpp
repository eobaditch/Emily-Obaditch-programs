// Challenge 03: Closest Numbers

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Main Execution

int main(int argc, char *argv[]) {
    
    string line; 
    int min_dif = INT_MAX; 
    int curr_dif;  
    int amount; 
    string num; 
    vector<int> numbers; 
    vector<int> minPairs;


    while(getline(cin, line)){
        
        amount = stoi(line);
        getline(cin, line); 
    
        stringstream s(line); 
        while(s >> num){
            numbers.push_back(stoi(num));  
        }
        
        sort(numbers.begin(), numbers.end());  

        for(unsigned int i=0; i<numbers.size()-1; i++){
            curr_dif = abs(numbers[i] - numbers[i+1]); 
            if (minPairs.empty()){
                min_dif = curr_dif; 
                minPairs.push_back(numbers[i]); 
                minPairs.push_back(numbers[i+1]); 
            }
            else if (curr_dif < min_dif){
                min_dif = curr_dif; 
                minPairs.clear();  
                minPairs.push_back(numbers[i]); 
                minPairs.push_back(numbers[i+1]); 
            }
            else if(curr_dif == min_dif){
                min_dif = curr_dif; 
                minPairs.push_back(numbers[i]); 
                minPairs.push_back(numbers[i+1]); 
            }
        }  
        
        for(unsigned int i=0; i<minPairs.size(); i++){
            cout<<minPairs[i]; 
            if (i != minPairs.size() -1){
                cout<<" "; 
            }
        }
        cout<<endl; 
        numbers.clear(); 
        minPairs.clear(); 
        min_dif = INT_MAX; 
    }
         
    return EXIT_SUCCESS;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
