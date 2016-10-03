// Challenge 04: Card Rank
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include<vector>

using namespace std;
struct Player{
    
    Player(string in_name, int in_suit, int in_rank) : name(in_name), suit(in_suit), rank(in_rank) {}

    string name; 
    int suit; 
    int rank;

    
    
}; 
// Main Execution
bool compare_cards(const Player &a, const Player &b); 

int main(int argc, char *argv[]) {

    string line, userName, userRank, userSuit;
    int amount, intRank, intSuit; 
    vector<Player> players; 

    while(getline(cin, line)){
        if (stoi(line) < 0){
            break; 
        }
        else{
            amount = stoi(line); 
        }
        
        for(int i=0; i<amount; i++){
            getline(cin, userName, ' ');  
            getline(cin, userRank, ' '); 
            getline(cin, userSuit); 

            if (userRank == "J"){
                userRank = "11";
            }
            else if(userRank == "Q"){
                userRank = "12"; 
            }
            else if (userRank == "K"){
                userRank = "13"; 
            }
            else if (userRank == "A"){
                userRank ="14"; 
            }
            if(userSuit == "S"){
                userSuit = "4"; //highest suit
            }
            else if (userSuit == "H"){
                userSuit = "3"; 
            }
            else if (userSuit == "D"){
                userSuit = "2"; 
            }
            else if (userSuit == "C"){
                userSuit = "1"; //lowest suit
            }
            intRank = atoi(userRank.c_str()); 
            intSuit = atoi(userSuit.c_str());
            players.push_back(Player(userName, intSuit, intRank)); 
        }
        
        sort(players.begin(), players.end(), compare_cards); 
        
        //print results
        for (unsigned int i =0; i<=players.size() -1; i++){
            if (i != players.size() -1){
                cout<<players[i].name<<", "; 
            }
            else{
                cout<<players[i].name; 
            }
        }
        cout<<endl; 

        //clear vector
        players.clear(); 
    }//end while 


    return EXIT_SUCCESS;
}


bool compare_cards(const Player &a, const Player &b){

    if(a.rank == b.rank){
        return a.suit > b.suit;   
    }
    else{
        return a.rank > b.rank;   
    }


}


// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
