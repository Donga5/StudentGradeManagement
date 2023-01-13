#ifndef STUDENT_H
#define STUDENT_H

#include<QString>
class Student
{
public:
    Student();
    void setId(QString id);
    void setName(QString name);
    void setSex(QString sex);
    void setClass(QString _Class);
    void setMath(QString _Math);
    void setEnglish(QString _English);
    void setC_language(QString _C_language);
    QString getId()const;//不能通过该函数修改变量的值
    QString getName()const;
    QString getSex()const;
    QString getClass()const;
    QString getMath()const;
    QString getEnglish()const;
    QString getC_language()const;
    Student(QString id,QString name, QString sex, QString _Class, QString _Math, QString _English, QString _C_language);
private:
    QString Id;
    QString Name;
    QString Sex;
    QString Class;
    QString Math;
    QString English;
    QString C_language;

};

#endif // STUDENT_H
