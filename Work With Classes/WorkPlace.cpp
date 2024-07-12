//
// Created by Muhammad Ghanayem on 30/12/2021.
//

#include "WorkPlace.h"
#include "exceptions.h"

using namespace mtm;

WorkPlace::WorkPlace(const int &id, const std::string &name, const int &workers_salary, const int &managers_salary):
id(id),name(name),workers_salary(workers_salary),managers_salary(managers_salary),managers({}) {}

int WorkPlace::getId() const
{
    return this->id;
}

const std::string &WorkPlace::getName() const
{
    return this->name;
}

int WorkPlace::getWorkersSalary() const
{
    return this->workers_salary;
}

int WorkPlace::getManagersSalary() const
{
    return this->managers_salary;
}

void WorkPlace::hireManager(Manager* manager)
{
    for (std::set<Manager>::iterator it = managers.begin(); it != managers.end(); it++)
    {
        if (it->getId() == manager->getId())
        {
            throw ManagerAlreadyHired();
        }
    }
    if (manager->getSalary() > 0)
    {
        throw CanNotHireManager();
    }
    manager->setSalary(managers_salary);
    managers.insert(*manager);
}

void WorkPlace::fireEmployee(const int &employee_id, const int &manager_id)
{
    for (std::set<Manager>::iterator it = managers.begin(); it != managers.end(); it++)
    {
        if (it->getId() == manager_id)
        {
            Manager new_manager(*it);
            new_manager.removeEmployee(employee_id);
            managers.erase(*it);
            managers.insert(new_manager);
            return;
        }
    }
    throw ManagerIsNotHired();
}

void WorkPlace::fireManager(const int &manager_id)
{
    std::set<Manager>::iterator iterator = managers.begin();
    while (iterator != managers.end())
    {
        if (iterator->getId() == manager_id)
        {
            managers.erase(*iterator);
            return;
        }
        iterator++;
    }
    throw ManagerIsNotHired();
}

std::ostream &mtm::operator<<(std::ostream &ostream, const WorkPlace &workplace)
{
    if (workplace.managers.empty())
    {
        ostream << "Workplace name - " << workplace.name << std::endl;
        return ostream;
    }
    ostream << "Workplace name - " << workplace.name << " Groups:" << std::endl;
    for (std::set<Manager>::iterator it = workplace.managers.begin(); it != workplace.managers.end(); it++)
    {
        ostream << "Manager ";
        it->printLong(ostream);
    }
    return ostream;
}

