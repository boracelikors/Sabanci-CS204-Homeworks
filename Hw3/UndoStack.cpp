//
// Created by Bora on 31.03.2024.
//

#include "UndoStack.h"


UndoStack::UndoStack() : top(nullptr) {}

UndoStack::~UndoStack() {
    clear();
}

void UndoStack::push(char operation, const string& employee_name, const string& project_name, int project_priority) {
    StackNode* newNode = new StackNode(operation, employee_name, project_name, project_priority, top);


    if (isEmpty())
    {
        top = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }

}

void UndoStack::pop(char& operation, string& employee_name, string& project_name, int& project_priority) {



    if (top != nullptr) {

        StackNode *temp;
        operation = top->operation;
        employee_name = top->employee_name;
        project_name = top->project_name;
        project_priority = top->project_priority;

        temp = top->next;
        delete top;
        top = temp;

    }






}

bool UndoStack::isEmpty() {
    return top == nullptr;
}

void UndoStack::clear() {
    while (top != nullptr) {
        StackNode* temp = top->next;
        delete top;
        top = temp;
    }
}
