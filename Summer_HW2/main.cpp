// Bora Celikors 30900
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
struct MazeNode {
    char cellContent;
    char previousContent; // To keep track of what was here before the player
    MazeNode *right, *left, *up, *down;

    MazeNode(char c) : cellContent(c), previousContent(c), right(nullptr), left(nullptr), up(nullptr), down(nullptr) {}
};

class LinkedList {
public:
    LinkedList() : head(nullptr), score(0) {}
    ~LinkedList(){ // Destructor to free allocated memory
        freeMemory();
    }
    void add(char c, int r){
        if (head == nullptr) { // If list is empty
            head = new MazeNode(c);
        } else {
            if (r == 0) { // if it is the first row
                MazeNode* ptr = head;
                while (ptr->right != nullptr) {
                    ptr = ptr->right;
                }
                MazeNode* new_node = new MazeNode(c);
                ptr->right = new_node;
                new_node->left = ptr;
            } else { // The all other cases can be handled with this logic
                MazeNode* ptr = head;
                int rows = 0;
                while (ptr->down != nullptr) {
                    rows++;
                    ptr = ptr->down;
                }
                if (rows != r) {
                    MazeNode* new_node = new MazeNode(c);
                    ptr->down = new_node;
                    new_node->up = ptr;
                } else {
                    while (ptr->right != nullptr) {
                        ptr = ptr->right;
                    }
                    MazeNode* new_node = new MazeNode(c);
                    ptr->right = new_node;
                    ((ptr->up)->right)->down = new_node;
                    new_node->left = ptr;
                    new_node->up = (ptr->up)->right;
                }
            }
        }
    }
    void print(){ // prints the list
        MazeNode* ptr = head;
        MazeNode* temp = head;
        while (temp != nullptr) {
            while (ptr != nullptr) {
                cout << ptr->cellContent;
                ptr = ptr->right;
            }
            temp = temp->down;
            ptr = temp;
            cout << endl;
        }
        cout << "Current score: " << score << endl;
    }
    void move(char dir) { // Performs a single move
        MazeNode* ptr = findX();
        if (ptr == nullptr) return; // Checks if the list is empty

        MazeNode* target = nullptr;
        // This parts checks if the move is possible
        if (dir == 'U') {
            target = ptr->up;
            if (target == nullptr) {
                cout << "Cannot move: Out of the maze bound." << endl;
                return;
            }
        } else if (dir == 'D') {
            target = ptr->down;
            if (target == nullptr) {
                cout << "Cannot move: Out of the maze bound." << endl;
                return;
            }
        } else if (dir == 'R') {
            target = ptr->right;
            if (target == nullptr) {
                cout << "Cannot move: Out of the maze bound." << endl;
                return;
            }
        } else if (dir == 'L') {
            target = ptr->left;
            if (target == nullptr) {
                cout << "Cannot move: Out of the maze bound." << endl;
                return;
            }
        } else {
            cout << "Invalid input. Please try again." << endl;
            return;
        }

        if (target->cellContent == '#') {
            cout << "Cannot move: There is a wall in that direction." << endl;
        } else { // If the move is possible, this block will work

            cout << "You moved " << ((dir == 'U') ? "up." : (dir == 'D') ? "down." : (dir == 'L') ? "left." : "right.") << endl;
            if (target->cellContent == 'I') {
                cout << "You found an item worth 204 points!" << endl;
            } else if (target->cellContent == 'E') {
                cout << "Congratulations! You reached the exit!" << endl;
                cout << "Final score: " << score << endl;
                freeMemory();
                exit(0);
            }

            // Move player to the target
            target->previousContent = target->cellContent;
            target->cellContent = 'X';

            // Restore previous content of the cell
            ptr->cellContent = (ptr->previousContent == 'I') ? 'I' : '.';


        }
    }
    void endGame(bool win){ // ends the game
        if (win) {
            cout << "Congratulations! You reached the exit!" << endl;
        } else {
            cout << "Game ended by the player." << endl;
        }
        cout << "Final score: " << score << endl;
        freeMemory(); // Free the allocated memory
        exit(0);
    }
    MazeNode* findX(){ // this helper function finds the cell that restores 'X'
        MazeNode* ptr = head;
        MazeNode* temp = head;
        while (temp != nullptr) {
            while (ptr != nullptr) {
                if (ptr->cellContent == 'X') {
                    return ptr;
                }
                ptr = ptr->right;
            }
            temp = temp->down;
            ptr = temp;
        }
        return nullptr;
    }
    int score;

private:
    MazeNode* head;
    void freeMemory(){// Helper function to free memory
        MazeNode* row = head;
        while (row != nullptr) {
            MazeNode* current = row;
            row = row->down;
            while (current != nullptr) {
                MazeNode* next = current->right;
                delete current; // Delete the current node
                current = next;
            }
        }
    }

};

int main() {
    LinkedList maze;
    string filename;
    cout << "Enter the maze file name: "<<endl;
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cout << "Unable to open file." << endl;
        cout << "Failed to load maze. Exiting..." << endl;
        return 0;
    }

    cout << "Maze loaded. Start exploring!" << endl;

    string line;
    int row = 0;
    while (getline(infile, line)) {
        // Remove trailing carriage return if it exists
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        for (char c : line) {
            maze.add(c, row); // I used my class function to read the content
        }
        row++;
    }

    infile.close();

    char input;
    do { // This part is the game loop, works with the help of class functions
        cout << "Enter input (R/L/U/D/P/C/Q): "<<endl;
        cin >> input;

        if (input == 'R' || input == 'L' || input == 'U' || input == 'D') {
            maze.move(input);
        } else if (input == 'P') {
            maze.print();
        } else if (input == 'C') {
            MazeNode* ptr = maze.findX();
            if (ptr && ptr->previousContent == 'I') {
                cout << "Item collected! Your score is now " << (maze.score += 204) << "." << endl;
                ptr->previousContent = '.'; // Update the previous content to reflect item collection
            } else {
                cout << "No item to collect here." << endl;
            }
        } else if (input == 'Q') {
            maze.endGame(false);
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    } while (input != 'Q');

    return 0;
}
