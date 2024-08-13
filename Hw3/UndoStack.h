#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <string>
using namespace std;

struct StackNode {
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode* next;


    StackNode(char op, const string& empName, const string& projName, int projPriority, StackNode* nxt = nullptr)
            : operation(op), employee_name(empName), project_name(projName), project_priority(projPriority), next(nxt) {}
};

class UndoStack {
public:
    UndoStack();
    ~UndoStack();

    void push(char operation, const string& employeeName, const string& projectName, int projectPriority);
    void pop(char& operation, string& employeeName, string& projectName, int& projectPriority);
    bool isEmpty() ;
    void clear();

private:
    StackNode* top;


};

#endif // UNDOSTACK_H
