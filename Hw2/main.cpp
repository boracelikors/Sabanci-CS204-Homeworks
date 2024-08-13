// Bora Çelikörs 30900

#include <iostream>
#include <fstream>
#include "vector"
#include "string"
using namespace std;

struct NodeLike
{


    string subject;
    string object;
    NodeLike *next;
    NodeLike(string sub, string obj, NodeLike* nxt = nullptr) : subject(sub), object(obj), next(nxt) {}
    // default next value is null
};
struct NodeTaken
{
    string name;
    NodeTaken *next;
    NodeTaken(string n, NodeTaken* nxt = nullptr) : name(n), next(nxt) {}
    // default next value is null
};

// This function checks if name is in Taken list
bool inTaken(NodeTaken* head, const string& name) {
    NodeTaken* current = head;
    while (current != nullptr) {
        if (current->name == name)
            return true;
        current = current->next;
    }
    return false;
}

// This function checks if node is in Likes list
bool nodeInLikes(NodeLike* head, const string& subject, const string& object){
    NodeLike* current = head;
    while (current != nullptr) {
        if (current->subject == subject && current->object == object)
            return true;
        current = current->next;
    }
    return false;
}

// This function checks if reverse of node is in Likes list
bool reverseInLikes(NodeLike* head, const string& subject, const string& object){
    NodeLike* current = head;
    while (current != nullptr) {
        if (current->subject == object && current->object == subject){
            return true;
        }

        current = current->next;
    }
    return false;
}

// This function checks if subject is in Taken list
bool subjectInlike(NodeLike* head, const string& subject){

    NodeLike* current = head;
    while (current != nullptr) {
        if (current->subject == subject ){
            return true;}
        current = current->next;

    }
return false;
}

// This function prints both linked lists
void printLists(NodeLike* headLikes, NodeTaken* headTaken) {

    cout << "Likes list: " ;
    NodeLike* currentLike = headLikes;
    while (currentLike != nullptr) {
        cout <<"(" <<currentLike->subject << ", " << currentLike->object <<")"<< " ";
        currentLike = currentLike->next;
    }

    cout << endl;


    cout << "Taken list: " ;
    NodeTaken* currentTaken = headTaken;
    while (currentTaken != nullptr) {
        cout << currentTaken->name << " ";
        currentTaken = currentTaken->next;
    }
    cout << endl;

}

// This function adds the node at the end of the Likes list
void addEndLike(NodeLike** head, const string &subject, const string& object){
    NodeLike* newNode = new NodeLike(subject, object);
    if(*head == nullptr){
        *head = newNode;
    }else{

        NodeLike* last = *head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = newNode;


    }
}

// This function adds name to Taken list with alphabetic order
void addTaken(NodeTaken*& head, const string& name) {
    NodeTaken* newNode = new NodeTaken(name);

    if (head == nullptr || name < head->name) {
        newNode->next = head;
        head = newNode;
    } else {
        NodeTaken* current = head;

        while (current->next != nullptr && current->next->name < name) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

// This function adds the node at the next of last appearance of subject in the Likes list
void addLike(NodeLike*& head, const string& sub, const string& ob) {
    NodeLike* newNode = new NodeLike(sub, ob);

    NodeLike* current = head;
    NodeLike* lastMatch = nullptr;

    while (current != nullptr) {
        if (current->subject == sub) {
            lastMatch = current;
        }
        current = current->next;
    }

    if (lastMatch != nullptr) {

        newNode->next = lastMatch->next;
        lastMatch->next = newNode;
    } else {
        delete newNode;
    }
}


// This function deletes the taken names from Likes list
void deleteMatchingNodes(NodeLike*& head, const string& sub, const string& ob) {
    NodeLike* current = head;
    NodeLike* prev = nullptr;


    while (current != nullptr && (current->subject == sub || current->object == ob || current->subject == ob || current->object == sub)) {
        head = current->next;
        delete current;
        current = head;
    }


    while (current != nullptr) {

        if (current->subject == sub || current->object == ob || current->subject == ob || current->object == sub) {
            prev->next = current->next;
            delete current;
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}




int main() {
    string fileName ;
    ifstream file;

    cout << "Please enter the file name: "<<endl;
    cin >> fileName;

// I checked if the file is open

    file.open(fileName);
    if (!file.is_open()) {

        cout <<"Unable to open file."<<endl<<" Failed to load maze. Exiting... " << endl;
        cin >> fileName;
        file.open(fileName.c_str());
    }

    string line;
    NodeLike * headLikes = nullptr;


    NodeTaken * headTaken = nullptr;


    int line_num = 1;

    // I read the file here
    while (getline(file,line)){
        int pos1, pos2;

        pos1 = line.find(" ");
        pos2 = line.rfind(" ");
        string subject = line.substr(0,pos1);
        string object = line.substr(pos2+1,line.size());
        cout << "Read line number ("<< line_num<<"): "<<line<<endl;



        bool subject_intaken, object_intaken;
        subject_intaken = inTaken(headTaken, subject);
        object_intaken = inTaken(headTaken, object);

        bool same_node = nodeInLikes(headLikes, subject, object);

        bool reverse_node = reverseInLikes(headLikes, subject, object);

        bool subject_likes = subjectInlike(headLikes, subject);

        // Here I created a conditional structure that handles all possible cases

        if(subject_intaken || object_intaken){

            cout << "Either "<< subject <<" or "<< object <<" or both is/are already taken, so the like relation is not added."<<endl;

        }else if(same_node){
            cout << subject << " likes " << object << " relation already exists in the likes list, so it is not added to it." << endl;
        }else if(reverse_node){
            deleteMatchingNodes(headLikes, subject, object );
            cout << "Match found: "<<subject <<" likes "<<object<<" and "<<object<<" likes "<<subject<<"."<<endl;
            cout << "Added to taken list: "<<subject<<endl;
            cout << "Added to taken list: "<<object<<endl;

                addTaken(headTaken, object);
                addTaken(headTaken, subject);

                cout << "Any node that has "<< subject <<" or "<< object <<" or both in it is removed from the likes list." << endl;

        }
        else if (subject_likes){
            addLike(headLikes, subject, object);
            cout << subject << " likes "<< object <<" relation has been added to the likes list."<< endl;
        }
        else{

            addEndLike(&headLikes,subject,object);
            cout << subject << " likes "<< object <<" relation has been added to the likes list."<< endl;

        }

        printLists(headLikes, headTaken);
    line_num++;
    cout << endl;


    }




    cout << "Lists are deleted and the program ends successfully. ";



}
