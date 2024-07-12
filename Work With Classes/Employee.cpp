//
// Created by Muhammad Biadsy on 29/12/2021.
//

#include "Employee.h"
#include "exceptions.h"

using namespace mtm;

Employee::Employee(const int &id,const std::string& first_name,const std::string& last_name,
                   const int &birth_year):
                   Citizen(id,first_name,last_name,birth_year),salary(0),score(0),skills({}){}

Citizen *Employee::clone() const
{
    return new Employee(*this);
}

int Employee::getSalary() const
{
    return this->salary;
}

int Employee::getScore() const
{
    return this->score;
}

void Employee::learnSkill(const Skill& skill)
{
    for (std::set<Skill>::iterator it = skills.begin(); it != skills.end(); it++)
    {
        if (*it == skill)
        {
            throw SkillAlreadyLearned();
        }
    }
    if (this->getScore() < skill.getRequiredPoints())
    {
        throw CanNotLearnSkill();
    }
    skills.insert(skill);
}

void Employee::forgetSkill(const int &skill_id)
{
    std::set<Skill>::iterator iterator = skills.begin();
    while (iterator != skills.end())
    {
        if (iterator->getId() == skill_id)
        {
            skills.erase(iterator);
            return;
        }
        iterator++;
    }
    throw DidNotLearnSkill();
}

bool Employee::hasSkill(const int &skill_id) const
{
    for (std::set<Skill>::iterator it = skills.begin(); it != skills.end(); it++)
    {
        if (it->getId() == skill_id)
        {
            return true;
        }
    }
    return false;
}

void Employee::setSalary(const int &add_salary)
{
    if (this->salary <= - add_salary)
    {
        this->salary = 0;
        return;
    }
    this->salary+=add_salary;
}

void Employee::setScore(const int &add_score)
{
    if (this->score < - add_score)
    {
        this->score = 0;
        return;
    }
    this->score+=add_score;
}

std::ostream& Employee::printShort(std::ostream &ostream) const
{
    Citizen::printShort(ostream);
    ostream << "Salary: " << this->salary << " Score: " << this->getScore() << std::endl;
    return ostream;
}

std::ostream& Employee::printLong(std::ostream &ostream) const
{
    Citizen::printLong(ostream);
    ostream << "Salary: " << this->salary << " Score: " << this->getScore() << " Skills:" << std::endl;
    for (std::set<Skill>::iterator it = skills.begin(); it != skills.end(); it++)
    {
        ostream << *it;
    }
    return ostream;
}