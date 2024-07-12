//
// Created by Muhammad Biadsy on 28/12/2021.
//

#include "Skill.h"
#include "exceptions.h"

using namespace mtm;

Skill::Skill(const int &id, const std::string &name, const int &required_points):
id(id),name(name),required_points(required_points) {}

int Skill::getId() const
{
    return this->id;
}

const std::string& Skill::getName() const
{
    return this->name;
}

int Skill::getRequiredPoints() const
{
    return this->required_points;
}

bool Skill::operator<(const Skill &skill) const
{
    if (this->id >= skill.id)
    {
        return false;
    }
    return true;
}

bool Skill::operator>(const Skill &skill) const
{
    if (this->id <= skill.id)
    {
        return false;
    }
    return true;
}

bool Skill::operator==(const Skill &skill) const
{
    if (this->id == skill.id)
    {
        return true;
    }
    return false;
}

Skill Skill::operator++(int)
{
    Skill skill = *this;
    this->required_points++;
    return skill;
}

Skill &Skill::operator+=(const int &points)
{
    if (points < 0)
    {
        throw NegativePoints();
    }
    this->required_points+=points;
    return *this;
}

Skill mtm::operator+(const Skill &skill, const int &points)
{
    if (points < 0)
    {
        throw NegativePoints();
    }
    return Skill(skill)+=points;
}

Skill mtm::operator+(const int &points, const Skill &skill)
{
    if (points < 0)
    {
        throw NegativePoints();
    }
    Skill skill1 = skill;
    for (int i = points;i > 0;i--)
    {
        skill1++;
    }
    return skill1;
}

bool mtm::operator<=(const Skill &skill1, const Skill &skill2)
{
    if (skill1 > skill2)
    {
        return false;
    }
    return true;
}

bool mtm::operator>=(const Skill &skill1, const Skill &skill2)
{
    if (skill1 < skill2)
    {
        return false;
    }
    return true;
}

bool mtm::operator!=(const Skill &skill1, const Skill &skill2)
{
    if (skill1 == skill2)
    {
        return false;
    }
    return true;
}

std::ostream& mtm::operator<<(std::ostream &ostream, const Skill &skill)
{
    return ostream << skill.name << std::endl;
}