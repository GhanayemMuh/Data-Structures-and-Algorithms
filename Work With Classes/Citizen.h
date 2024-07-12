//
// Created by Muhammad Biadsy on 29/12/2021.
//

#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <iostream>
#include <string>
#include <memory>

namespace mtm
{
    class Citizen {
    private:
        int id;
        std::string first_name;
        std::string last_name;
        int birth_year;
    public:
        explicit Citizen(const int& id,const std::string& first_name,const std::string& last_name,
                         const int& birth_year);
        Citizen(const Citizen& src) = default;
        virtual ~Citizen() = default;
        virtual Citizen* clone() const = 0;
        int getId() const;
        const std::string& getFirstName() const;
        const std::string& getLastName() const;
        int getBirthYear() const;
        bool operator<(const Citizen& citizen) const;
        bool operator>(const Citizen& citizen) const;
        bool operator==(const Citizen& citizen) const;
        virtual std::ostream& printShort(std::ostream& ostream) const = 0;
        virtual std::ostream& printLong(std::ostream& ostream) const = 0;
    };
    bool operator>=(const Citizen& citizen1, const Citizen& citizen2);
    bool operator<=(const Citizen& citizen1, const Citizen& citizen2);
    bool operator!=(const Citizen& citizen1, const Citizen& citizen2);
}

#endif
