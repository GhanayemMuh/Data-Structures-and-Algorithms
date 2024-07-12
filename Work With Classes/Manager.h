//
// Created by Muhammad Ghanayem on 29/12/2021.
//

#ifndef MANAGER_H_
#define MANAGER_H_
#include <iostream>
#include <memory>
#include <string>
#include "Citizen.h"
#include "Skill.h"
#include "Employee.h"
#include <set>

namespace mtm
{
    class Manager : public Citizen {
    private:
        int salary;
        std::set<Employee> employees;
    public:
        explicit Manager(const int& id,const std::string& first_name,const std::string& last_name,
                         const int& birth_year);
        Manager(const Manager& src) = default;
        ~Manager() = default;
        Citizen* clone() const override;
        int getSalary() const;
        void addEmployee(Employee* employee);
        void removeEmployee(const int& employee_id);
        void setSalary(const int& add_salary);
        std::ostream& printShort(std::ostream &ostream) const override;
        std::ostream& printLong(std::ostream &ostream) const override;
        bool hasEmployee(const int& employee_id) const;/////////////////////////
    };
}

#endif