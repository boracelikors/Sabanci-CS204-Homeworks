//
// Bora Celikors 30900
//

#include "EmployeeProject2DLL.h"
#include "vector"
#include <iostream>

// default constructor
EmployeeProject2DLL::EmployeeProject2DLL() : head(nullptr) {}

// destructor
EmployeeProject2DLL::~EmployeeProject2DLL() {
    clear();
}

// this function checks if an employee assigned a project of not.
bool EmployeeProject2DLL::isEmployeeAssignedToProject(const string &employeeName, const string& projectName) {
    EmployeeNode* currentEmployee = head;


    while (currentEmployee != nullptr) {
        if (currentEmployee->employee_name == employeeName) {

            ProjectNode* currentProject = currentEmployee->head;


            while (currentProject != nullptr) {
                if (currentProject->project_name == projectName) {
                    return true;
                }
                currentProject = currentProject->next;
            }


            return false;
        }
        currentEmployee = currentEmployee->down;
    }


    return false;
}

// updates priority and re-sorts the list
bool EmployeeProject2DLL:: updateProjectPriority(const string& employeeName, const string& projectName, int& projectPriority) {
    EmployeeNode* currentEmployee = head;


    while (currentEmployee && currentEmployee->employee_name != employeeName) {
        currentEmployee = currentEmployee->down;
    }
    if (!currentEmployee) return false;


    ProjectNode* targetProject = nullptr;
    ProjectNode* currentProject = currentEmployee->head;
    while (currentProject) {
        if (currentProject->project_name == projectName) {
            targetProject = currentProject;
        } else if (currentProject->project_priority == projectPriority) {
            cout << "The project priority has not been updated because there is another project with the same priority." << endl;
            return false;
        }
        currentProject = currentProject->next;
    }

    if (!targetProject) return false;


    if (targetProject->project_priority == projectPriority) {
        cout << "The project priority is already the same as the new priority." << endl;
        return false;
    }


    if (targetProject->prev) targetProject->prev->next = targetProject->next;
    if (targetProject->next) targetProject->next->prev = targetProject->prev;


    if (targetProject == currentEmployee->head) currentEmployee->head = targetProject->next;
    if (targetProject == currentEmployee->tail) currentEmployee->tail = targetProject->prev;

    targetProject->prev = targetProject->next = nullptr;


    ProjectNode* prev = nullptr;
    currentProject = currentEmployee->head;
    int oldPriority = targetProject->project_priority;
    targetProject->project_priority = projectPriority;

    while (currentProject && currentProject->project_priority < projectPriority) {
        prev = currentProject;
        currentProject = currentProject->next;
    }


    if (prev) {
        targetProject->next = prev->next;
        targetProject->prev = prev;
        prev->next = targetProject;
    } else {
        targetProject->next = currentEmployee->head;
        currentEmployee->head = targetProject;
    }

    if (targetProject->next) targetProject->next->prev = targetProject;
    if (!targetProject->next) currentEmployee->tail = targetProject;


    projectPriority = oldPriority;

    return true;
}


// assignt a project to an employee
bool EmployeeProject2DLL::assignEmployeeToProject(const string& employeeName, const string& projectName, int projectPriority) {

    EmployeeNode* currentEmployee = head;
    EmployeeNode* prevEmployee = nullptr;

    while (currentEmployee != nullptr && currentEmployee->employee_name < employeeName) {
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee->down;
    }

    if (currentEmployee == nullptr || currentEmployee->employee_name != employeeName) {

        EmployeeNode* newEmployee = new EmployeeNode(employeeName);
        if (prevEmployee == nullptr) {
            newEmployee->down = head;
            head = newEmployee;
        } else {
            newEmployee->down = prevEmployee->down;
            prevEmployee->down = newEmployee;
        }
        currentEmployee = newEmployee;
    }


    ProjectNode* currentProject = currentEmployee->head;
    ProjectNode* prevProject = nullptr;

    while (currentProject != nullptr && currentProject->project_priority < projectPriority) {
        prevProject = currentProject;
        currentProject = currentProject->next;
    }


    if (currentProject != nullptr && currentProject->project_priority == projectPriority) {
        cout << "The project has not been added because there is another project with the same priority." << endl;
        return false;
    }


    ProjectNode* newProject = new ProjectNode(projectName, projectPriority);
    if (prevProject == nullptr) {
        newProject->next = currentEmployee->head;
        if (currentEmployee->head != nullptr) {
            currentEmployee->head->prev = newProject;
        }
        currentEmployee->head = newProject;
    } else {
        newProject->next = prevProject->next;
        newProject->prev = prevProject;
        if (prevProject->next != nullptr) {
            prevProject->next->prev = newProject;
        }
        prevProject->next = newProject;
    }


    if (currentEmployee->tail == nullptr || currentEmployee->tail->project_priority < projectPriority) {
        currentEmployee->tail = newProject;
    }

    return true;
}

// deletes a project from an employee
void EmployeeProject2DLL::withdrawEmployeeFromProject(const string& employeeName,const string& projectName, int& projectPriority) {
    EmployeeNode* currentEmployee = head;
    EmployeeNode* prevEmployee = nullptr;


    while (currentEmployee != nullptr && currentEmployee->employee_name != employeeName) {
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee->down;
    }

    if (currentEmployee == nullptr) {

        return;
    }


    ProjectNode* currentProject = currentEmployee->head;
    ProjectNode* prevProject = nullptr;
    while (currentProject != nullptr && currentProject->project_name != projectName) {
        prevProject = currentProject;
        currentProject = currentProject->next;
    }

    if (currentProject == nullptr) {

        return;
    }


    projectPriority = currentProject->project_priority;


    if (prevProject == nullptr) {

        currentEmployee->head = currentProject->next;
        if (currentProject->next != nullptr) {
            currentProject->next->prev = nullptr;
        }
    } else {
        prevProject->next = currentProject->next;
        if (currentProject->next != nullptr) {
            currentProject->next->prev = prevProject;
        }
    }


    if (currentEmployee->tail == currentProject) {
        currentEmployee->tail = prevProject;
    }

    delete currentProject;


    if (currentEmployee->head == nullptr) {

        if (prevEmployee == nullptr) {
            head = currentEmployee->down;
        } else {
            prevEmployee->down = currentEmployee->down;
        }
        delete currentEmployee;
    }
}

// prints all employees and projects
void EmployeeProject2DLL::printTheEntireList() {
    if (head == nullptr) {

        cout << "The list is empty." << endl;
        return;
    }

    EmployeeNode* currentEmployee = head;

    while (currentEmployee != nullptr) {
        cout  << currentEmployee->employee_name << ": ";

        ProjectNode* currentProject = currentEmployee->head;



            while (currentProject != nullptr) {
                cout << "(" << currentProject->project_name
                     << ", " << currentProject->project_priority<<") ";
                currentProject = currentProject->next;
            }


        currentEmployee = currentEmployee->down;
        cout << endl;
    }
}

// prins the projects of an employee
void EmployeeProject2DLL::printEmployeeProjects(const string& employeeName, int order) {
    EmployeeNode* currentEmployee = head;
    while (currentEmployee != nullptr) {
        if (currentEmployee->employee_name == employeeName) {

            vector<ProjectNode*> projects;


            for (ProjectNode* pn = currentEmployee->head; pn != nullptr; pn = pn->next) {
                projects.push_back(pn);
            }

            if (projects.empty()) {
                cout << "The employee has no projects assigned." << endl;
                return;
            }




            if (order == 1) {
                for (size_t i = 0; i < projects.size(); ++i) {
                    cout << "(" << projects[i]->project_name << ", " << projects[i]->project_priority << ") ";
                }
            }

            else if (order == 0) {
                for (size_t i = projects.size(); i-- > 0;) {
                    cout << "(" << projects[i]->project_name << ", " << projects[i]->project_priority << ") ";
                }
            }
            cout << endl;

            return;
        }
        currentEmployee = currentEmployee->down;
    }


    if (head == nullptr) {
        cout << "There are no employees in the list." << endl;
    } else {
        cout << "The employee is not in the list." << endl;
    }
}


// undoes the last operation
void EmployeeProject2DLL::undo(char operationType, const string& employeeName, const string& projectName, int projectPriority) {
    if (operationType == 'a') {

        cout << "Undoing the assignment of a project." << endl;

        withdrawEmployeeFromProject(employeeName, projectName, projectPriority);
    } else if (operationType == 'w') {

        cout << "Undoing the withdrawal of a project." << endl;

        assignEmployeeToProject(employeeName, projectName, projectPriority);
    } else if (operationType == 'u') {

        cout << "Undoing the update of a project priority." << endl;

        updateProjectPriority(employeeName, projectName, projectPriority);
    } else {
        cout << "Invalid operation type." << endl;
    }
}

// clears the list
void EmployeeProject2DLL::clear() {
    while (head != nullptr) {
        EmployeeNode* temp = head;
        head = head->down;


        ProjectNode* project = temp->head;
        while (project != nullptr) {
            ProjectNode* nextProject = project->next;
            delete project;
            project = nextProject;
        }
        delete temp;
    }
}

