//
//Created By Muhammad Ghanayem on 4.1.2022
//

#ifndef CITY_H_
#define CITY_H_
#include <iostream>
#include <memory>
#include <string>
#include "Manager.h"
#include "Employee.h"
#include "exceptions.h"
#include "WorkPlace.h"
#include "Faculty.h"

namespace mtm
{
    class City
    {
        private:
            std::string city_name;
            std::set<Employee> employees;
            std::set<Manager> managers;
            std::set<Faculty<Condition>> faculties;
            std::set<WorkPlace> workplaces;

        public:
            explicit City(const std::string& name);
            ~City() = default;
            void addEmployee(const int& id,const std::string& first_name,const std::string& last_name,
                          const int& birth_year);
            void addManager(const int& id,const std::string& first_name,const std::string& last_name,
                         const int& birth_year);
            template<class FunctionObject>
            void addFaculty(const int& id, const Skill& skill, const int& added_points,FunctionObject* functionObject);
            void createWorkplace(const int& id, const std::string& name,const int& workers_salary,
                           const int& managers_salary);
            void teachAtFaculty(const int& employee_id, const int& faculty_id);
            template <class FunctionObject>
            void hireEmployeeAtWorkplace(FunctionObject functionObject, const int& employee_id,
                            const int& manager_id, const int& workplace_id);
            void hireManagerAtWorkplace(const int& manager_id, const int& const int& workplace_id);
            void fireEmployeeAtWorkplace(const int& employee_id, const int& manager_id, const int& workplace_id);
            void fireManagerAtWorkplace(const int& manager_id, const int& workplace_id);
            int getAllAboveSalary(std::ostream& os, const int& salary);
            bool isWorkingInTheSameWorkplace(const int& first_employee, const int& second_employee);
            void printAllEmployeesWithSkill(std::ostream& os,const int& skill_id);

            

    }
    template <class FunctionObject>
    void City::addFaculty(const int& id, const Skill& skill, const int& added_points,FunctionObject* functionObject)
    {
        for(std::set<Faculty<Condition>>::iterator it = faculties.begin(); it != faculties.end() ; it++)
        {
            if(it->getId() == id)
            {
                throw FacultyAlreadyExists();
            }
        }
        Faculty<Condition> new_faculty(Faculty<Condition>(id,skill,added_points,functionObject));
        faculties.insert(new_faculty);

    }

    template<class FunctionObject>
    void City::hireEmployeeAtWorkplace(FunctionObject functionObject, const int& employee_id,
                            const int& manager_id, const int& workplace_id)
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
                                Employee new_employe(*employee_it);
                                WorkPlace new_workplace(*workplace_it);
                                new_workplace.hireEmployee(functionObject,&new_employee,manager_id);
                                employees.erase(employee_it);
                                workplaces.erase(workplace_it);
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
}
















#endif 