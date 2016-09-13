#ifndef PUZZLE_H
#define PUZZLE

//Emily Obaditch Fund Comp II Lab 6
//Sudoku Solver uses singleton and single elimination methods to colve sudoku board


#include <iostream>
#include <vector>
#include <string> 
#include <fstream> 

using namespace std; 

template<typename T>
class Puzzle{
    public: 
        Puzzle(); 
        void display();
        int checkSpot(int, int, int); 
        void scan();
        void solve(); 
        void place(int, int); 
        void placeSingleton(int, int, int); 
        int fullBoard();
        int checkRow(int, int, int); 
        int checkCol(int, int, int); 
        int checkMini(int, int, int); 
    private:
        vector<vector<T> > puzzle;
        vector<vector<vector<T> > > puzzlePos; 

}; //end class Puzzle

template<typename T>
Puzzle<T>::Puzzle(){

    string fileName; 
    T value; 
    vector<T> temp; 

    cout<< "Enter file name: "<<endl; 
    cin >>fileName; 
    
    ifstream inFile; 
    inFile.open(fileName.c_str()); 
    
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            inFile >> value; //read in value
            temp.push_back(value); //place in vector
        }
        puzzle.push_back(temp);
        temp.clear(); 
    }
   //create 3D vector of 0's to store posibilites
   //0 if empty, 1 is filled 
    vector<T> tempPos1; 
    vector<vector<T> > tempPos2; 

    for(int i=0; i<10; i++){
        tempPos1.push_back(0); 
    }
    
    for (int j=0; j<9; j++){
         tempPos2.push_back(tempPos1); 
    }

    for (int k=0; k<9; k++){
        puzzlePos.push_back(tempPos2); 
    }

  
}

template<typename T>
void Puzzle<T>::display(){

    for (int i=0; i < 9; i++){
        for (int j=0; j<9; j++){
            cout<<puzzle[i][j]<<" "; //add a space between elements 
        }
        cout<<endl; 
    }
}

template<typename T>
void Puzzle<T>::scan(){

int spot; 

for (int i=0; i <9; i ++){
        for(int j=0; j < 9; j++){
            for(int k=1; k < 10; k++){
                if (!checkSpot(i,j,k)){ //each layer of 3D vector is the possiblities for each number 
                    puzzlePos[i][j][k]=1; //1 if the cell is not a valid option for k 
                }
            }
        }
    }
   

}

template<typename T>
int Puzzle<T>::fullBoard(){

    for(int i=0; i <9; i++){
        for (int j=0; j<9; j++){
            if (puzzle[i][j] ==0){
                return 0; 
            }
                //if there is still an empty spot return false
        }
    }
return 1; 
}


template<typename T>
void Puzzle<T>::solve(){

    int count =0; 
    int spot=0; 
    int sum=0; 
    int currRow, currCol, i, j, k, value, m, n; 
    int singleCount=0; 
scan(); 

while (fullBoard()==0){
         
   //single elimination 
    for (i=0; i< 9; i++){
       for (j=0; j < 9; j++){
            for (k=1; k<10; k++){
                    sum+=puzzlePos[i][j][k];
        
            }
           if (sum == 8){
                place(i,j);
                scan(); 
            }
            sum=0; 
        }
    }
    
    
    //singleton
        for (i=0; i < 9; i ++){
           for (j=0; j <9; j++){
               for (k=0; k<10; k++){
                   if (checkRow(i,j,k)){
                        placeSingleton(i,j,k); 
                        scan(); 
                           }
                    else if (checkCol(i,j,k)){
                        placeSingleton(i,j,k); 
                        scan(); 
                    }
                    else if (checkMini(i,j,k)){
                        placeSingleton(i,j,k); 
                        scan(); 
                    }
               }
           }
        }
    }//end while
}



template<typename T>
void Puzzle<T>::place(int row, int col){

    for(int k=1; k<10; k++){
        if(puzzlePos[row][col][k]==0){
            puzzle[row][col]=k;
            puzzlePos[row][col][k]=1; 
        }
    }

}

template<typename T> 
void Puzzle<T>::placeSingleton(int row, int col, int num){

    puzzle[row][col]=num;

}

template<typename T> 
int Puzzle<T>::checkRow(int row, int col, int num){

    int count=0, location; 

    for(int i=0; i <9; i++){
        if (puzzlePos[row][i][num] == 0){
            count++; 
            location =i; 
        }
    }
//there is only one possible position AND it is in the correct location
    if (count ==1 && location==col){
        return 1; 
    }
    else {
        return 0; 
    }  
 
}

template<typename T> 
int Puzzle<T>::checkCol(int row, int col, int num){

    int count=0, location; 
    for(int i=0; i <9; i++){
        if (puzzlePos[i][col][num] == 0){
            count++; 
            location =i; 
        }
    }
//there is only one possible position AND it is in correct location
    if (count ==1 && location==row){
        return 1; 
    }
    else {
        return 0; 
    }

}

template<typename T>
int Puzzle<T>::checkMini(int row, int col, int num){

    int count=0, locationRow, locationCol; 

    int k; // to iterate rows in box
    int l; // to iterate cols in box


        if( row % 3 == 0 ) k = row;
        if( row % 3 == 1 ) k = row - 1;
        if( row % 3 == 2 ) k = row - 2;
                    
        if( col % 3 == 0 ) l = col;
        if( col % 3 == 1 ) l = col - 1;
        if( col % 3 == 2 ) l = col - 2;

       for( int i = k; i < (k+3); i++ ){
            for( int j = l; j < (l+3); j++ ){
                if (puzzlePos[i][j][num] == 0){
                    count++; 
                    locationRow=i; 
                    locationCol=j; 
                }
            }
        }

       //have to check ROW and COL locations 
       if (count ==1 && locationRow==row && locationCol==col){
           return 1; 
        }
       else{
           return 0; 
        }

}


template<typename T>
int Puzzle<T>::checkSpot(int row, int col, int num){
   
    int k, l; 

    //check position 
    if (puzzle[row][col] != 0){
        return 0; 
    }

    //check col
    for(int i=0; i<9; i++){
        if (num == puzzle[i][col]){
            return 0;
        }
    }
    //check row
    for (int i=0; i<9; i++){
        if (num == puzzle[row][i]){
            return 0; 
        }
    }

    //check mini-grid

        if( row % 3 == 0 ) k = row;
        if( row % 3 == 1 ) k = row - 1;
        if( row % 3 == 2 ) k = row - 2;
                    
        if( col % 3 == 0 ) l = col;
        if( col % 3 == 1 ) l = col - 1;
        if( col % 3 == 2 ) l = col - 2;

       for( int i = k; i < (k+3); i++ ){
            for( int j = l; j < (l+3); j++ ){
                if( puzzle[i][j] == num ){
                     return 0;
                                                                                                                        
                }
            } 
        }
 return 1; // valid entry
}






#endif
