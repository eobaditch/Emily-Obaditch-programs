// Challenge 01: Rotating Arrays
//eobaditc
//Emily Obaditch

#include<iostream>
#include<vector>
#include<string>

using namespace std; 


// Main Execution

int main(int argc, char *argv[]) {
    
    int n, r; 
    vector<char> initial; 
    vector<char> rotated; 
    string line, arr; 
    
    while(getline(cin,line)){
        n = line[0]-48; 
        r = line[2]-48; 
       
        //make all rotations on a scale of 1-5 to the RIGHT
        if (line[4] != 'R'){
            r = n-r; 
        }
        if (r > n){
            r = r-n; 
        }
        if (r < 0){
            r = n+r; 
        }

        //get next line to be rotated 
        getline(cin,arr); 
        for (int i=0; i<arr.length(); i++){
            if (arr[i] != ' '){
                initial.push_back(arr[i]); 
            }
        } 
        for(int i=(n-r); i <n; i++){
            rotated.push_back(initial[i]);
            rotated.push_back(' '); 
        }
        for (int i=0; i<n-r; i++){
            rotated.push_back(initial[i]);
            rotated.push_back(' '); 
        }
        rotated.pop_back(); 
        for(int i=0; i<rotated.size(); i++){
            cout<<rotated[i]; 
        }
        cout<<endl; 
        initial.clear();
        rotated.clear(); 
    }    
    
    
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
