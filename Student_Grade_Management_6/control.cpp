#include "control.h"
#include<QFile>
#include<QTextStream>

#include<QDebug>
#include<QTextCodec>

Control::Control()
{
qDebug()<<"Control类的对象创建成功";
}

Control::Control(Control &ctrl)
{
    qDebug()<<"Control类的对象创建成功";
}

Control::~Control()
{
    auto ite=list.begin();
    while(ite!=list.end())
    {
        delete  *ite;
        ite++;//当控制对象被释放的时候，将对应链表中的数据也进行释放
    }

}



Control *Control::getCtrl()
{
    //通过函数来调用构造函数来创建对象
    if(ctrl==nullptr)
    {
        ctrl=new Control;
    }
    //前一个版本这里是错误的
        return ctrl;

}

QList<Student *> &Control::getList()
{
    return list;
}

Control* Control::ctrl=nullptr;//静态变量在类外进行定义



void Control::addStu(Student *stu)
{

        list.push_back(stu);
}

void Control::deleteStu(QString id)
{
    QList<Student*>::Iterator ite=list.begin();
    //可以使用atuo自动判断ite的类型
    while(ite!=list.end())
    {
        //如果名字和学号有一个匹配，那就删除这个对象
        if((*ite)->getId()==id||(*ite)->getName()==id)
        {
            delete *ite;
            list.erase(ite);
            break;
        }

        ite++;
    }

}


void Control::listToFile()
{
    QFile file("Data/"+username+"/studentData.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"打开文件失败";
    }
    else
    {
        qDebug()<<"成功打开文件";
        //清除后重新写入
        QTextStream out(&file);
        out.setCodec(QTextCodec::codecForName("utf-8"));//按照utf进行写入

        auto ite=list.begin();

        while(ite!=list.end())
        {
            //将信息依次进行输出
            out<<(*ite)->getName()<<" "<<(*ite)->getId()<<" "<<(*ite)->getSex()<<" "<<(*ite)->getClass()
              <<" "<<(*ite)->getMath()<<" "<<(*ite)->getEnglish()<<" "<<(*ite)->getC_language();

            out<<'\n';
            ite++;
        }

       file.close();
    }


}

void Control::fileToList(QString s)
{
    QString filename=s;
   //将文件中链表中进行读入
    if(s.isEmpty())
    {
       filename="Data/"+username+"/studentData.txt";

    }
     QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
           //没有成功打开文件情况下就提示，并且直接结束函数
           qDebug()<<"打开文件失败";
           return ;
    }

    while(!file.atEnd())
    {
        QString line=file.readLine().trimmed();
        QStringList list=line.trimmed().split(' ');

       addStu(new Student(list[0],list[1],list[2],list[3],list[4],list[5],list[6]));
    }

    file.close();//最后一定要记得关闭文件
}

void Control::setUsername(QString str)
{
    username=str;

}

void Control::allClear()
{
    auto ite=list.begin();
    while(ite!=list.end())
    {
        if((*ite)!=nullptr)
       {
            delete (*ite);//释放掉内存空间
            *ite=nullptr;
        }

        ite++;
    }
    //上面只是释放掉了内存空间，并没有清楚元素
    list.clear();//清除元素

}
