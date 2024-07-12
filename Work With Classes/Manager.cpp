//
// Created by Muhammad Ghanayem on 29/12/2021.
//

#include "Manager.h"
#include "exceptions.h"

using namespace mtm;

Manager::Manager(const int &id, const std::string &first_name, const std::string &last_name,
                 const int &birth_year):
                 Citizen(id,first_name,last_name,birth_year),salary(0),employees({}){}

Citizen *Manager::clone() const
{
    return new Manager(*this);
}

int Manager::getSalary() const
{
    return this->salary;
}

void Manager::addEmployee(Employee *employee)
{
    for (std::set<Employee>::iterator it = employees.begin(); it != employees.end(); it++)
    {
        if (*it == *employee)
        {
            throw EmployeeAlreadyHired();
        }
    }
    employees.insert(*employee);
}

void Manager::removeEmployee(const int &employee_id)
{
    std::set<Employee>::iterator iterator = employees.begin();
    while (iterator != employees.end())
    {
        if (iterator->getId() == employee_id)
        {
            employees.erase(*iterator);
            return;
        }
        iterator++;
    }
    throw EmployeeIsNotHired();
}

void Manager::setSalary(const int &add_salary)
{
    if (this->salary <= - add_salary)
    {
        this->salary = 0;
        return;
    }
    this->salary+=add_salary;
}

std::ostream& Manager::printShort(std::ostream &ostream) const
{
    Citizen::printShort(ostream);
    ostream << "Salary: " << this->salary << std::endl;
    return ostream;
}

std::ostream& Manager::printLong(std::ostream &ostream) const
{
    Citizen::printLong(ostream);
    ostream << "Salary: " << this->salary << std::endl << "Employees:" << std::endl;
    for (std::set<Employee>::iterator it = employees.begin(); it != employees.end(); it++)
    {
        it->printShort(ostream);
    }
    return ostream;
}

bool Manager::hasEmployee(const int &employee_id) const
{
    for (std::set<Employee>::iterator it = employees.begin(); it != employees.end(); it++)
    {
        if (it->getId() == employee_id)
        {
            return true;
        }
    }
    return false;
}
