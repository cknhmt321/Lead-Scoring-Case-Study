#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept> 

using namespace std;

struct Employee {
    int employee_id = 0;
    string first_name = "";
    string last_name = "";
    string email = "";
    string phone_number = "";
    string hire_date = "";
    string job_id = "";
    double salary = 0.0;
    string commission_pct = "-"; 
    int manager_id = 0;
    int department_id = 0;
};


void readEmployeesFromFile(const string& filename, vector<Employee>& employees) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1); 
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Employee emp;
        string salary_str, commission_pct_str;

        try {
            getline(ss, line, ','); emp.employee_id = stoi(line);
            getline(ss, emp.first_name, ',');
            getline(ss, emp.last_name, ',');
            getline(ss, emp.email, ',');
            getline(ss, emp.phone_number, ',');
            getline(ss, emp.hire_date, ',');
            getline(ss, emp.job_id, ',');
            getline(ss, salary_str, ','); emp.salary = stod(salary_str);
            getline(ss, commission_pct_str, ','); emp.commission_pct = commission_pct_str; 
            getline(ss, line, ','); emp.manager_id = stoi(line);
            getline(ss, line, ','); emp.department_id = stoi(line);

            employees.push_back(emp);
        }
        catch (const invalid_argument&) {
            cerr << "Invalid data found in line: " << line << endl;
            continue; 
        }
        catch (const out_of_range&) {
            cerr << "Out of range error in line: " << line << endl;
            continue; 
        }
    }
    file.close();
}

void fetchSalaryById(const vector<Employee>& employees, int emp_id) {
    bool found = false;
    for (const auto& emp : employees) {
        if (emp.employee_id == emp_id) {
            cout << "Salary of " << emp.first_name << " " << emp.last_name
                << " (Employee ID: " << emp_id << ") is: $" << emp.salary << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << emp_id << " not found." << endl;
    }
}

int main() {
    vector<Employee> employees;
    string filename = "C:\\Users\\bhagy\\source\\repos\\mkraghuang\\CPPTasks\\Harsha\\exmployees.txt";  
    readEmployeesFromFile(filename, employees);

    int emp_id;
    cout << "Enter Employee ID to fetch salary: ";
    cin >> emp_id;

    fetchSalaryById(employees, emp_id);

    return 0;

}