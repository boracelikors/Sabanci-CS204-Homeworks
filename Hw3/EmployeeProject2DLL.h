#ifndef EMPLOYEEPROJECT2DLL_H
#define EMPLOYEEPROJECT2DLL_H

#include <string>
using namespace std;

struct ProjectNode {
    string project_name;
    int project_priority;
    ProjectNode* next;
    ProjectNode* prev;

    ProjectNode(const string& name, int priority) : project_name(name), project_priority(priority), next(nullptr), prev(nullptr) {}
};

struct EmployeeNode {
    string employee_name;
    ProjectNode* head;
    ProjectNode* tail;
    EmployeeNode* down;

    EmployeeNode(const string& name) : employee_name(name), head(nullptr), tail(nullptr), down(nullptr) {}
};

class EmployeeProject2DLL {
public:
    EmployeeProject2DLL();
    ~EmployeeProject2DLL();

    bool isEmployeeAssignedToProject(const string& employeeName, const string& projectName);
    bool updateProjectPriority(const string& employeeName, const string& projectName, int& projectPriority);
    bool assignEmployeeToProject(const string& employeeName, const string& projectName, int projectPriority);
    void withdrawEmployeeFromProject(const string& employeeName, const string& projectName, int& projectPriority);
    void printTheEntireList();
    void printEmployeeProjects(const string& employeeName, int order);
    void undo(char operationType, const string& employeeName, const string& projectName, int projectPriority);
    void clear();

private:
    EmployeeNode* head;


};

#endif // EMPLOYEEPROJECT2DLL_H
