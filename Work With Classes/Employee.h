//
// Created by Muhammad Biadsy on 29/12/2021.
//

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
#include <iostream>
#include <memory>
#include <string>
#include "Citizen.h"
#include "Skill.h"
#include <set>

namespace mtm
{
    class Employee : public Citizen {
    private:
        int salary;
        int score;
        std::set<Skill> skills;
    public:
        explicit Employee(const int& id,const std::string& first_name,const std::string& last_name,
                          const int& birth_year);
        Employee(const Employee& src) = default;
        ~Employee() = default;
        Citizen* clone() const override;
        int getSalary() const;
        int getScore() const;
        void learnSkill(const Skill& skill);
        void forgetSkill(const int& skill_id);
        bool hasSkill(const int& skill_id) const;
        void setSalary(const int& add_salary);
        void setScore(const int& add_score);
        std::ostream& printShort(std::ostream &ostream) const override;
        std::ostream& printLong(std::ostream &ostream) const override;
    };
}

#endif
