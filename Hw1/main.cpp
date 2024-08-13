#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "vector"
using namespace std;

bool isEmpty(const vector<vector<char>>& mat);
bool canMove(const vector<vector<char>>& mat);
void move(vector<vector<char>>& mat, int row, int column);
bool movePossible(const vector<vector<char>>& mat, int row, int column);
int main() {
    string fileName ;
    ifstream file;

    cout << "Please enter the file name: "<<endl;
    cin >> fileName;

// I checked if the file is open

    file.open(fileName);
    while (!file.is_open()) {

        cout <<"Could not open the file. Please enter a valid file name: " << endl;
        cin >> fileName;
        file.open(fileName.c_str());
    }


    vector<vector<char>> mat;

    string line;
// then read the file here
    while (getline(file, line)) {
        vector<char> row;
        for (char ch : line) {
            row.push_back(ch);
        }
        mat.push_back(row);
    }
    file.close();
// there is my inputs checks on if the file is valid
    bool same_len = true;
    bool valid_char = true;
    int len = mat.at(0).size();
    for (vector<char>& row : mat) {
        if (row.size() != len) {
            same_len = false;

        }
        for (char ch : row) {
            if (!(ch == 'r' || ch == 'l' || ch == 'u' || ch == 'd' || ch == '-')) {
                valid_char = false;

            }
        }

    }

    if (!(valid_char && same_len)) {
        cout << "Erroneous file content. Program terminates." << endl;
        return 1;
    }

    cout << "The matrix file contains:" << endl;
    for (const vector<char>& row : mat) {
        for (char ch : row) {
            cout << ch;
        }
        cout << endl;
    }
// here i am checking is the matrix is playable
    bool is_empty = isEmpty(mat);
    bool can_move = canMove(mat);
    if(is_empty){
        cout << "The matrix is empty.";
        return 1;
    }
    if(!can_move){
        cout << "No more moves are possible.";
        return 1;
    }
// there, user plays the game with keyboard inputs
    while(!is_empty && can_move){
        int col;
        int row;
        cout << "Please enter the row and column of the tile that you want to move: " << endl;
        cin >> row >> col;


        if (row < 0 || row >= mat.size() || col < 0 || col >= mat[0].size()) {
            cout << "Invalid row or column index." << endl;
        }else{

            move(mat, row, col);
            is_empty = isEmpty(mat);
            can_move = canMove(mat);

            for (const vector<char>& row : mat) {
                for (char ch : row) {
                    cout << ch;
                }
                cout << endl;
            }



        }










    }











// finally the end of the game
    if(is_empty){
        cout << "The matrix is empty. ";

    }
    else if(!can_move){
        cout << "No more moves are possible.";

    }





    return 0;
}
// function that checks if the matrix is playable
bool canMove(const vector<vector<char>>& mat){

    for (int row = 0; row < mat.size(); ++row) {
        for (int column = 0; column < mat[0].size(); ++column) {
            bool isPossible = movePossible(mat, row, column);
            if (isPossible) {
                return true;
            }
        }
    }
    return false;
}



// function that checks a particular move is playable
bool movePossible(const vector<vector<char>>& mat, int row, int column){
    char ch = mat.at(row).at(column);
    int num_rows = mat.size();
    int num_cols = mat.at(0).size();


    if(ch == 'r'){
        if(column == (num_cols-1)){
            return true;
        }
        else{
            char next = mat.at(row).at(column + 1);
            if(next == '-'){
                return true;
            }else{
                return false;}
            }
        }

    else if(ch == 'l'){
        //case 1
        if(column == 0){
            return true;

        }else{
            char next = mat.at(row).at(column-1);
            if(next == '-'){
                return true;
            }else{
                return false;
            }


        }

    }
    else if(ch == 'u'){

        if(row == 0){
            return true;
        }else{
            char next = mat.at(row-1).at(column);
            if(next == '-'){
                return true;
            }else{
                return false;
            }
        }

    }
    else if(ch == 'd'){

        if(row == (num_rows-1)){
            return true;
        }
        else{
            char next = mat.at(row+1).at(column );
            if(next == '-'){
                return true;
            }else{
                return false;}
        }

    }else{
        return false;
    }

}
// function that checks if the matrix is empty
bool isEmpty(const vector<vector<char>>& mat) {
    for (const vector<char>& row : mat) {
        for (char ch : row) {
            if (ch != '-') {
                return false;
            }
        }
    }
    return true;
}

// the function that makes the changes on the matrix based on keyboard input
// however, this function is not working perfectly, i realy tried to debug it lot but there is something that i miss. so, i am submitting like this.
void move(vector<vector<char>>& mat, int row, int column) {

     char ch = mat.at(row).at(column);
     int num_rows = mat.size();
     int num_cols = mat.at(0).size();
     bool possible = movePossible(mat, row, column);
     if(possible){
         cout << "Tile at (" << row << ","<< column << ") has been moved." << endl;
     }else{
         cout << "No tiles have been moved."<< endl;
     }


     if(ch == 'r'){
         //case 1
         if(column == (num_cols-1)){
             mat.at(row).at(column) = '-';



         }
         //case 2 and 3
         else{
             int n = 1;
             char next = mat.at(row).at(column+n);
             while(next == '-' && (column +n)<num_cols){

                 if((column +n ) == (num_cols-1)){
                     mat.at(row).at(column+n) = '-';
                     mat.at(row).at(column+n-1) = '-';
                     next = 'a';
                 }else{
                     mat.at(row).at(column+n) = 'r';
                     mat.at(row).at(column+n-1) = '-';
                     n++;
                     next = mat.at(row).at(column+n);}


             }

         }


     }
     else if(ch == 'l'){
         //case 1
         if(column == 0){
             mat.at(row).at(column) = '-';


         }else{
             int n = 1;
             char next = mat.at(row).at(column-n);
             while(next == '-'){

                 if((column -n ) == (0)){
                     mat.at(row).at(column-n) = '-';
                     mat.at(row).at(column-n+1) = '-';
                     next = 'a';
                 }else{
                     mat.at(row).at(column-n) = 'l';
                     mat.at(row).at(column-n+1) = '-';
                     n++;
                     next = mat.at(row).at(column-n);}

             }

         }

     }
     else if(ch == 'u'){
         //case 1
         if(row == 0){
             mat.at(row).at(column) = '-';


         }else{
             int n = 1;
             char next = mat.at(row-n).at(column);
             while(next == '-' ){

                 if((row -n ) == (0)){
                     mat.at(row-n).at(column) = '-';
                     mat.at(row-n+1).at(column) = '-';
                     next = 'a';
                 }else{
                     mat.at(row-n).at(column) = 'u';
                     mat.at(row-n+1).at(column) = '-';
                     n++;
                     next = mat.at(row-n).at(column);
                 }

             }

         }

     }
     else if(ch == 'd'){
         //case 1
         if(row == (num_rows-1)){
             mat.at(row).at(column) = '-';


         }else{
             int n = 1;
             char next = mat.at(row+n).at(column);
             while(next == '-' && (row+n)<num_rows){

                 if((row +n ) == (num_rows-1)){
                     mat.at(row+n).at(column) = '-';
                     mat.at(row+n-1).at(column) = '-';
                     next = 'a';
                 }else{
                     mat.at(row+n).at(column) = 'd';
                     mat.at(row+n-1).at(column) = '-';
                     n++;
                     next = mat.at(row+n).at(column);
                 }

             }

         }

     }




}
















