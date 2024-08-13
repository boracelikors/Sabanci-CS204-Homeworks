#include <iostream>
#include "vector"
#include "string"
using namespace std;

int find_word(string s, vector<vector<char>> mtx);

int main() {
    int num_rows;
    cin >> num_rows;
    string row;
    vector<vector<char>> matrix(num_rows);

    for (int i = 0; i < num_rows; ++i) {

        cin >> row;
        vector<char> v(row.size());
        for(int j = 0;j<row.size();j++){
            v[j]=row[j];
        }
        matrix[i] = v;
    }


    int words;
    cin >> words;
    string word;
    int score = 0;
    for(int i = 0; i<words;i++){
        cin >> word;
        score += find_word(word, matrix);
    }

    cout << score;




    return 0;
}
int find_word(string s, vector<vector<char>> mtx){


    char first = s[0];
    int size = s.size();
    int rows = mtx.size();
    int cols = mtx[0].size();

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(mtx[i][j] == first) {
                // Horizontal right
                bool match = true;
                if (j + size <= cols) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i][j + k] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size + (size > 5 ? 2 : 0);
                    }
                }

                // Horizontal left
                match = true;
                if (j - size + 1 >= 0) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i][j - k] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size + (size > 5 ? 2 : 0);
                    }
                }

                // Vertical down
                match = true;
                if (i + size <= rows) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i + k][j] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size + (size > 5 ? 2 : 0);
                    }
                }

                // Vertical up
                match = true;
                if (i - size + 1 >= 0) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i - k][j] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size + (size > 5 ? 2 : 0);
                    }
                }

                // Diagonal down-right
                match = true;
                if (i + size <= rows && j + size <= cols) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i + k][j + k] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size * 2 + (size > 5 ? 2 : 0);
                    }
                }

                // Diagonal up-left
                match = true;
                if (i - size + 1 >= 0 && j - size + 1 >= 0) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i - k][j - k] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size * 2 + (size > 5 ? 2 : 0);
                    }
                }

                // Diagonal down-left
                match = true;
                if (i + size <= rows && j - size + 1 >= 0) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i + k][j - k] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size * 2 + (size > 5 ? 2 : 0);
                    }
                }

                // Diagonal up-right
                match = true;
                if (i - size + 1 >= 0 && j + size <= cols) {
                    for (int k = 1; k < size; k++) {
                        if (mtx[i - k][j + k] != s[k]) {
                            match = false;
                        }
                    }
                    if (match) {
                        return size * 2 + (size > 5 ? 2 : 0);
                    }
                }
            }
        }
    }

    return -5; // Word not found




}