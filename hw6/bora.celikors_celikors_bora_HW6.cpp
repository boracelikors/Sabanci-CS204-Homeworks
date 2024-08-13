
// bora_celikors_30900


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;




mutex mtx; // Global mutex for shared data
mutex cout_mtx; // Global mutex for cout statements
bool round_active = false;
int round_winner; // after each round, id of round winner assigns
int current_round = 0;


int target_number;
int num_players;
int num_rounds;
int lower;
int upper;

vector<int> scores; // Scores of the players

// Function to generate random number within a range
int random_range(const int &min, const int &max) {
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// Function to get formatted current time
string get_current_time() {
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm *ptm = new tm;
    localtime_s(ptm, &tt);
    stringstream ss;
    ss << put_time(ptm, "%X");
    return ss.str();
}



// Function for the host thread
void host_thread() {


    while (current_round < num_rounds) {
        if (!round_active) {
            mtx.lock();
            current_round++;
            // updates score
            if (current_round >= 1) { scores[round_winner] += 1; }

                // generates the target number each round
            target_number = random_range(lower, upper);
            // starts the game

            round_active = true;
            mtx.unlock();

            cout_mtx.lock();
            cout << "---------------------------------------------------" << endl;
            if (current_round == 1) {
                cout << "Game started at: " << get_current_time() << endl;
                cout << "Round " << current_round << " will start 3 seconds later" << endl;

            } else {
                cout << "Round " << current_round << " started at: " << get_current_time() << endl;
            }
            cout << "Target is " << target_number << endl;
            cout_mtx.unlock();


        }
    }
}

// Function for the player threads
void player_thread(int player_id) {
// 3 seconds sleep before game starts
    if (current_round == 1) {
        this_thread::sleep_for(chrono::seconds(3));
    }

    while (round_active) {
// Guess the number
        int guess = random_range(lower, upper); // Example range

        if (guess == target_number) {
            mtx.lock();
            round_winner = player_id;
            round_active = false;
            mtx.unlock();

            cout_mtx.lock();

            cout << "Player with id " << player_id << " guessed " << guess << " correctly " << "at: " << get_current_time()<< endl;
            cout_mtx.unlock();

        } else {
            cout_mtx.lock();

            cout << "Player with id " << player_id << " guessed " << guess << " incorrectly " << "at: " << get_current_time()<< endl;
            cout_mtx.unlock();
        }

// Sleep for a second
        this_thread::sleep_for(chrono::seconds(1));

    }
}

int main() {


    // Take inputs for number of players, rounds and randomization range
    cout << "Please enter number of players" << endl;
    cin >> num_players;
    while (num_players < 1) {
        cout << "Number of players must be at least 1. Enter again: ";
        cin >> num_players;
    }

    cout << "Please enter number of rounds" << endl;
    cin >> num_rounds;
    while (num_rounds < 1) {
        cout << "Number of rounds must be at least 1. Enter again: ";
        cin >> num_rounds;
    }

    cout << "Please enter the randomization range" << endl;
    cin >> lower >> upper;
    while (lower > upper) {
        cout << "Lower bound must be less than or equal to upper bound. Enter again: ";
        cin >> lower >> upper;
    }

    // Initialize scores
    scores.resize(num_players, 0);


    // Create host and player threads
    vector<thread> threads;
    threads.push_back(thread(host_thread));
    for (int i = 0; i < num_players; ++i) {
        threads.push_back(thread(player_thread, i));
    }

    // Join threads
    for (int i = 0; i <= num_players; ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
    cout_mtx.lock();
    cout << "---------------------------------------------------" << endl;
    cout << "Game is over!" << endl;
    cout << "Leaderboard:" << endl;
    for (int i = 0; i < num_players; ++i) {
        cout << "Player " << i << " has won " << scores[i] << " times" << endl;
    }
    cout_mtx.unlock();

    return 0;
}