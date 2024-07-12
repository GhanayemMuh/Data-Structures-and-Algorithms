//
// Created by Muhammad Biadsy on 28/12/2021.
//

#ifndef SKILL_H_
#define SKILL_H_
#include <iostream>
#include <string>
#include <memory>

namespace mtm
{
    class Skill {
    private:
        int id;
        std::string name;
        int required_points;
    public:
        explicit Skill(const int& id,const std::string& name,const int& required_points);
        Skill(const Skill& src) = default;
        ~Skill() = default;
        int getId() const;
        const std::string& getName() const;
        int getRequiredPoints() const;
        friend std::ostream& operator<<(std::ostream& ostream, const Skill& skill);
        bool operator<(const Skill& skill) const;
        bool operator>(const Skill& skill) const;
        bool operator==(const Skill& skill) const;
        Skill operator++(int);
        Skill& operator+=(const int& points);
    };
    std::ostream& operator<<(std::ostream& ostream, const Skill& skill);
    bool operator>=(const Skill& skill1, const Skill& skill2);
    bool operator<=(const Skill& skill1, const Skill& skill2);
    bool operator!=(const Skill& skill1, const Skill& skill2);
    Skill operator+(const Skill& skill, const int& points);
    Skill operator+(const int& points, const Skill& skill);
}
#endif
