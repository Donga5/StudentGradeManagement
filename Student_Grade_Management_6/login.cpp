#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include<registerwidget.h>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QTextCodec>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //开始的时候就隐藏注册界面
    w.hide();

    connect(&w,&RegisterWidget::backToLogin,[=](){
        w.close();
        this->show();//注册窗口收到返回登录界面的信号之后，关闭注册窗口

    });//connect函数里边的指针不能是空指针，否则会导致程序异常结束

  }

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_2_clicked()
{
    exit(0);
}


void Login::on_pushButton_clicked()
{
    //查找是否有该账户
    //如果有，就切换到主界面
    //没有就返回到登录界面

    if(this->checkAccount()==1)
    {

        emit loginSuccess();

    }
    else if(this->checkAccount()==2)
    {
        QMessageBox::information(this, "提示","警告","数据库为空，请先注册");

    }
    else
    {
        QMessageBox::information(this, "提示","找不到该用户，请重新输入或者注册");
        //输入错误之后，清空账号和密码两栏

    }

    this->ui->username->clear();
    this->ui->password->clear();



}
QString Login::getUserName()
{

    return userName;

}
int Login::checkAccount()
{
    //打开文件，进行读取，然后核验账号和密码是否输入正确，正确则进入系统，错误则清空账号和密码
    this->userName=ui->username->text();
    this->passWord=ui->password->text();

    QString filename="D:\\Code\\qt\\Student_Grade_Management\\userData.txt";
    filename="userData1.txt";
    //在工作目录下，与exe文件同在一个目录下面
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    if(file.atEnd())
    {
        return 2;
    }

    QString str_1="";
    QString str_2="";
    QString str_3="";
    while(!file.atEnd())
    {
        str_1=file.readLine();
        str_2=file.readLine();
        str_3=file.readLine();
        //去掉读入的换行符
        str_1=str_1.trimmed();
        str_2=str_2.trimmed();
       if(str_1==userName&&str_2==passWord)
        {

           userName=str_1;//将当前的用户信息保存
            return 1;
        }

    }

    return 0;


}

void Login::on_pushButton_3_clicked()
{
    w.show();//不能给注册窗口制定父对象，注册窗口应该是一个顶层窗口
    this->hide();

}


