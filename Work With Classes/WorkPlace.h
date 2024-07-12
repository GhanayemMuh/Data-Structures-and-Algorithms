//
// Created by Muhammad Ghanayem on 30/12/2021.
//

#ifndef WORKPLACE_H_
#define WORKPLACE_H_
#include <iostream>
#include <memory>
#include <string>
#include "Manager.h"
#include "Employee.h"
#include "exceptions.h"

namespace mtm
{
    class WorkPlace {
    private:
        int id;
        std::string name;
        int workers_salary;
        int managers_salary;
        std::set<Manager> managers;
    public:
        explicit WorkPlace(const int& id, const std::string& name,const int& workers_salary,
                           const int& managers_salary);
        WorkPlace(const WorkPlace& src) = default;
        ~WorkPlace() = default;
        int getId() const;
        const std::string& getName() const;
        int getWorkersSalary() const;
        int getManagersSalary() const;

        template<class FunctionObject>
        void hireEmployee(FunctionObject functionObject,Employee* employee,const int& manager_id);
        void hireManager(Manager* manager);
        void fireEmployee(const int& employee_id,const int& manager_id);
        void fireManager(const int& manager_id);
        friend std::ostream& operator<<(std::ostream& ostream, const WorkPlace& workplace);
    };
    std::ostream& operator<<(std::ostream& os, const WorkPlace& workplace);
    template<class FunctionObject>
    void WorkPlace::hireEmployee(FunctionObject functionObject,Employee* employee, const int &manager_id)
    {
        if (!functionObject(employee))
        {
            throw EmployeeNotSelected();
        }
        for (std::set<Manager>::iterator it = managers.begin(); it != managers.end(); it++)
        {
            if (it->getId() == manager_id)
            {
                employee->setSalary(workers_salary);
                Manager new_manager (*it);
                new_manager.addEmployee(employee);
                managers.erase(*it);
                managers.insert(new_manager);
                return;
            }
        }
        throw ManagerIsNotHired();
    }
}

#endif
