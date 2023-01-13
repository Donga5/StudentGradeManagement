#ifndef CONTROL_H
#define CONTROL_H

#include<student.h>
#include<QObject>
//只允许有一个控制类
class Control//对存储的链表信息进行一些操作
{
private:
    //单例模式，只有一个实例对象，类外无法在创建的新的对象
    static Control * ctrl;//指向该类类型的静态函数指针
    QList<Student*> list;
private:
    Control();
    Control(Control &ctrl);
    QString username;
    //将构造函数设置为私有的，设置一个公有的静态函数来创建一个对象
public:
    ~Control();
    static Control *getCtrl();
    //在类外通过这个函数得到唯一的对象
    QList<Student*> &getList(); //返回链表
    void addStu(Student *stu);
    void deleteStu(QString id);
    void listToFile();//由链表向文件中写入数据
    void fileToList(QString s="");//将数据从文件读到链表中
    void setUsername(QString str);
    void allClear();
};

#endif // CONTROL_H
