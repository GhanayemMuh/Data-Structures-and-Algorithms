//
// Created by Muhammad Biadsy on 29/12/2021.
//

#include "Citizen.h"

using namespace mtm;

Citizen::Citizen(const int &id, const std::string& first_name, const std::string& last_name,
                 const int &birth_year): id(id),first_name(first_name),last_name(last_name),birth_year(birth_year){}

int Citizen::getId() const
{
    return this->id;
}

const std::string& Citizen::getFirstName() const
{
    return this->first_name;
}

const std::string& Citizen::getLastName() const
{
    return this->last_name;
}

int Citizen::getBirthYear() const
{
    return this->birth_year;
}

bool Citizen::operator<(const Citizen &citizen) const
{
    if (this->id >= citizen.id)
    {
        return false;
    }
    return true;
}

bool Citizen::operator>(const Citizen &citizen) const
{
    if (this->id <= citizen.id)
    {
        return false;
    }
    return true;
}

bool Citizen::operator==(const Citizen &citizen) const
{
    if (this->id == citizen.getId())
    {
        return true;
    }
    return false;
}

bool mtm::operator<=(const Citizen &citizen1, const Citizen &citizen2)
{
    if (citizen1 > citizen2)
    {
        return false;
    }
    return true;
}

bool mtm::operator>=(const Citizen &citizen1, const Citizen &citizen2)
{
    if (citizen1 < citizen2)
    {
        return false;
    }
    return true;
}

bool mtm::operator!=(const Citizen &citizen1, const Citizen &citizen2)
{
    if (citizen1 == citizen2)
    {
        return false;
    }
    return true;
}

std::ostream& Citizen::printShort(std::ostream &ostream) const
{
    ostream << this->getFirstName() << " " << this->getLastName() << std::endl;
    return ostream;
}

std::ostream& Citizen::printLong(std::ostream &ostream) const
{
    ostream << this->getFirstName() << " " << this->getLastName() << std::endl;
    ostream << "id - " << this->getId() << " birth_year - " << this->getBirthYear() << std::endl;
    return ostream;
}