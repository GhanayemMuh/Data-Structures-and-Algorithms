//
// Created by Muhammad Ghanayem& Muhammad Biadsy on 4.1.2022
//
#include "City.h"
#include "exceptions.h"

using namespace mtm;

City::City(const std::string& name):city_name(name),employees({}),managers({}),faculties({}),workplaces({}){}

static void CitizenAlreadyExists(const std::set<Manager>& managers,const std::set<Employee>& employees,const int& citizen_id)
{
    for(std::set<Manager>::iterator manager_it = managers.begin() ; manager_it != managers.end(); manager_it++)
    {
        if(manager_it->getId() == citizen_id)
        {
            throw CitizenAlreadyExists();
        }
    }
    for(std::set<Employee>::iterator employee_it = employees.begin() ; employee_it != employees.end(); employees_it++)
    {
        if(employee_it->getId() == citizen_id)
        {
            throw CitizenAlreadyExists();
        }
    }
}

void City::addEmployee(const int& id,const std::string& first_name,const std::string& last_name,
                          const int& birth_year)
{
    CitizenAlreadyExists(managers,employees,id);
    Employee new_employee(id,first_name,last_name,birth_year);
    employees.insert(new_employee);
}

void City::addManager(const int& id,const std::string& first_name,const std::string& last_name,
                         const int& birth_year)
{
    CitizenAlreadyExists(managers,employees,id);
    Manager new_manager(id,first_name,last_name,birth_year);
    managers.insert(new_manager);
}

void City::createWorkplace(const int& id, const std::string& name,const int& workers_salary,
                           const int& managers_salary)
{
    for(std::set<WorkPlace>::iterator workplace_it = workplaces.begin() ; workplace_it != workplaces.end(); workplace_it++)
    {
        if(workplace_it->getId() == id)
        {
            throw WorkplaceAlreadyExists();
        }
    }
    WorkPlace new_workplace(id,name,workers_salary,managers_salary);
    workplaces.insert(new_workplace);
}

void City::teachAtFaculty(const int& employee_id, const int& faculty_id)
{
    for(std::set<Employee>::iterator employee_it = employees.begin() ; employee_it != employees.end(); employees_it++)
    {
        if(employee_it->getId() == employee_id)
        {
            for(std::set<Faculty<Condition>>::iterator faculty_it = faculties.begin() ; faculty_it != faculties.end() ; faculty_it++)
            {
                if(faculty_it->getId() == faculty_id)
                {
                    Faculty<Condition> new_faculty(*faculty_it);
                    Employee new_employee(*employee_it);
                    new_faculty.teach(&new_employee);
                    employees.erase(*employee_it);
                    employees.insert(new_employee);
                    return;
                }
            }
            throw FacultyDoesNotExist();
        }
    }
    throw EmployeeDoesNotExist();
}

void City::hireManagerAtWorkplace(const int& manager_id, const int& const int& workplace_id)
{
    for(std::set<Manager>::iterator manager_it = managers.begin() ; manager_it != managers.end() ; manager_it++)
    {
        if(manager_it->getId() == manager_id)
        {
            for(std::set<WorkPlace>::iterator workplace_it = workplaces.begin() ; workplace_it != workplaces.end() ; workplace_it++)
            {
                if(workplace_it->getId() == workplace_it)
                {
                    WorkPlace new_workplace(*workplace_it);
                    Manager new_manager(*manager_it);
                    new_workplace.hireManager(&new_manager);
                    managers.erase(*manager_it);
                    workplaces.erase(*workplace_it);
                    managers.insert(new_manager);
                    workplaces.insert(new_workplace);
                    return;
                }
            }
            throw WorkplaceDoesNotExist();
        }
    }
    throw ManagerDoesNotExist();
}

void City::fireEmployeeAtWorkplace(const int& employee_id, const int& manager_id, const int& workplace_id)
{
    for(std::set<Employee>::iterator employee_it = employees.begin() ; employee_it != employees.end() ; employee_it++)
    {
        if(employee_it->getId() == employee_id)
        {
            for(std::set<Manager>::iterator manager_it = managers.begin() ; manager_it != managers.end(); manager_it++)
            {
                if(manager_it->getId() == manager_id)
                {
                    for(std::set<WorkPlace>::iterator workplace_it = workplaces.begin() ; workplace_it != workplaces.end() ; workplace_it++)
                    {
                        if(workplace_it->getId() == workplace_id)
                        {
                            Employee new_employee(*employee_it);
                            WorkPlace new_workplace(*workplace_it);
                            new_workplace.fireEmployee(employee_id,manager_id);
                            new_employee.setSalary(-new_workplace.getWorkersSalary());
                            employees.erase(*employee_it);
                            workplaces.erase(*workplace_it);
                            employees.insert(new_employee);
                            workplaces.insert(new_workplace);
                            return;
                        }
                    }
                    throw WorkplaceDoesNotExist();
                }
            }
            throw ManagerDoesNotExist();
        }
    }
    throw EmployeeDoesNotExist();
}

static void resetEmployeesSalary(std::set<Employee>& employees, const WorkPlace& workplace)
{
    for(std::set<Employee>::iterator employee_it = employees.begin() ; employee_it != employees.end();)
    {
        if(workplace.hasEmployee(employee_it->getId()))
        {
            Employee new_employee(*employee_it);
            new_employee.setSalary(-workplace.getWorkersSalary());
            employee_it++;
            employees.erase(new_employee);
            employees.insert(new_employee);
            continue;
        }
        employee_it++;
    }
}

void City::fireManagerAtWorkplace(const int& manager_id, const int& workplace_id)
{
    for(std::set<Manager>::iterator manager_it = managers.begin() ; manager_it != managers.end() ; manager_it++)
    {
        if(manager_it->getId() == manager_id)
        {
            for(std::set<WorkPlace>::iterator workplace_it = workplaces.begin() ; workplace_it != workplaces.end() ; workplace_it++)
            {
                if(workplace_it->getId() == workplace_it)
                {
                    WorkPlace new_workplace(*workplace_it);
                    Manager new_manager(*manager_it);
                    resetEmployeesSalary(employees,new_workplace);
                    new_workplace.fireManager(manager_id);
                    new_manager.setSalary(-new_workplace.getManagersSalary());
                    managers.erase(*manager_it);
                    workplaces.erase(*workplace_it);
                    managers.insert(new_manager);
                    workplaces.insert(new_workplace);
                    return;
                }
            }
            throw WorkplaceDoesNotExist();
        }
    }
    throw ManagerDoesNotExist();
}

int City::getAllAboveSalary(std::ostream& os, const int& salary)
{
    std::set<Employee>::iterator employee_it = employees.begin();
    std::set<Manager>::iterator manager_it = managers.begin();
    int counter = 0;
    while(employee_it != employees.end() && manager_it != managers.end())
    {
        if(employee_it->getId() < manager_it->getId() && employee_it->getSalary() >= salary)
        {
            counter++;
            employee_it->printLong(os);
            employee_it++; 
        }
        else if(employee_it->getId() > manager_it->getId() && manager_it->getSalary() >= salary)
        {
            counter++;
            manager_it->printLong(os);
            manager_it++;
        }
        else if(employee_it->getId() < manager_it->getId() && manager_it->getSalary() >= salary)
        {
            counter++;
            manager_it->printLong(os);
            manager_it++;
        }
        else if(employee_it->getId() > manager_it->getId() && employee_it->getSalary() >= salary)
        {
            counter++;
            employee_it->printLong(os);
            employee_it++;
        }
        else
        {
            employee_it++;
            manager_it++;
        }
    }
    if(employee_it != employees.end())
    {
        while(employee_it != employees.end())
        {
            if(employee_it->getSalary() >= salary)
            {
                counter++;
                employee_it->printLong(os);
                employee_it++;
            }
        }
    }
    if(manager_it != managers.end())
    {
        while(manager_it != managers.end())
        {
            if(manager_it->getSalary() >= salary)
            {
                counter++;
                manager_it->printLong(os);
                manager_it++;
            }
        }
    }
    return counter;

}


bool City::isWorkingInTheSameWorkplace(const int& first_employee, const int& second_employee)
{
    for(std::set<WorkPlace>::iterator workplace_it = workplaces.begin() ; workplace_it != workplaces.end(); workplace_it++)
    {
        if (workplace_it->hasEmployee(first_employee) && workplace->hasEmployee(second_employee))
        {
            return true;
        }
    }
    return false;
}

void City::printAllEmployeesWithSkill(std::ostream& os,const int& skill_id)
{
    for(std::set<Employee>::iterator employee_it = employees.begin() ; employee_it != employees.end(); employees_it++)
    {
        if(employee_it->hasSkill(skill_id))
        {
            employee->printLong(os);
        }
    }
}
