#include "student.h"
#include<QDebug>
Student::Student()
{

}

void Student::setId(QString id)
{
    Id=id;
}

void Student::setName(QString name)
{
    Name=name;
}

void Student::setSex(QString sex)
{
   Sex=sex;
}

void Student::setClass(QString _Class)
{
    Class=_Class;

}

void Student::setMath(QString _Math)
{
    Math=_Math;
}

void Student::setEnglish(QString _English)
{
    English=_English;
}

void Student::setC_language(QString _C_language)
{
    C_language=_C_language;
}

QString Student::getId() const
{
    return Id;
}

QString Student::getName() const
{
    return Name;
}

QString Student::getSex() const
{
    return Sex;
}

QString Student::getClass() const
{
    return Class;
}

QString Student::getMath() const
{
    return Math;
}

QString Student::getEnglish() const
{
    return English;
}

QString Student::getC_language() const
{
    return C_language;
}

Student::Student(QString name, QString id, QString sex, QString _Class, QString _Math, QString _English, QString _C_language)
    :Id(id),Name(name),Sex(sex),Class(_Class),Math(_Math),English(_English),C_language(_C_language)
{


}
