//
// Created by Muhammad Ghanayem on 30/12/2021.
//

#ifndef FACULTY_H_
#define FACULTY_H_
#include "exceptions.h"
#include "Skill.h"
#include "Employee.h"

namespace mtm
{
    class Condition {
    public:
        virtual bool operator()(Employee* employee) = 0;
    };

    template<class FunctionObject>
    class Faculty {
    private:
        int id;
        FunctionObject* condition;
        Skill skill;
        int added_points;
    public:
        explicit Faculty(const int& id, const Skill& skill, const int& added_points,FunctionObject* functionObject);
        Faculty(const Faculty<FunctionObject>& src) = default;
        ~Faculty() = default;
        int getId() const;
        const Skill& getSkill() const;
        int getAddedPoints() const;
        void teach(Employee* employee);
    };

    template<class FunctionObject>
    mtm::Faculty<FunctionObject>::Faculty(const int &id, const Skill &skill, const int &added_points,
                                          FunctionObject* functionObject):
    id(id),condition(functionObject),skill(skill),added_points(added_points){}

    template<class FunctionObject>
    int mtm::Faculty<FunctionObject>::getId() const
    {
        return this->id;
    }

    template<class FunctionObject>
    const Skill& mtm::Faculty<FunctionObject>::getSkill() const
    {
        return this->skill;
    }

    template<class FunctionObject>
    int mtm::Faculty<FunctionObject>::getAddedPoints() const
    {
        return this->added_points;
    }

    template<class FunctionObject>
    void mtm::Faculty<FunctionObject>::teach(Employee *employee)
    {
        if (!condition->operator()(employee))
        {
            throw EmployeeNotAccepted();
        }
        employee->setScore(added_points);
        employee->learnSkill(skill);
    }
}

#endif
