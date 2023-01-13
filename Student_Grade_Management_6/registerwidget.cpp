#include "registerwidget.h"
#include "ui_registerwidget.h"
#include<QDebug>
#include<QMessageBox>
#include<QDir>
#include<QFile>


RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

QString RegisterWidget::get_verifyCode()
{
    QString code=QString();
    //随机生成验证码和数字,4位

    for(int i=0;i<4;i++)
    {
        int flag=qrand()%2;
        if(flag)
        {
            //生成随机数
            int c='0'+qrand()%10;
            code+=static_cast<QChar>(c);
        }
        else
        {
            //生成字母
            char ch=(qrand()%2) ?'a':'A';
            code+=static_cast<QChar>(ch+qrand()%26);
        }

    }

    return code;
}

bool RegisterWidget::check_account()
{
    if(ui->user_name->text()=="")
    {
        //用户名为空，则弹出窗口提示
        QMessageBox::warning(this, "错误","用户名不能为空");
    }
    else if(ui->pass_word->text()=="")
    {
        //密码为空
        QMessageBox::warning(this, "错误","密码不能为空");

    }
    else if(ui->re_pass_word->text()=="")
    {
        //再次输入密码为空
        QMessageBox::warning(this, "错误","第二个密码框不能为空");

    }
    else if(ui->mail->text()=="")
    {
         QMessageBox::warning(this, "错误","邮箱不能为空");
    }
    //以上核验是否为空


    //利用正则表达式进行核验
    else if(!QRegExp("^\\d{6,12}$").exactMatch(ui->user_name->text()))
    {
        //账号格式错误
        QMessageBox::warning(this, "错误","账号格式错误");
        ui->user_name->clear();

    }
    else if(isDirExist("Data/"+ui->user_name->text()))
    {
        QMessageBox::warning(this, "错误","该账号已经被注册");
        ui->user_name->clear();
    }
    else if(ui->pass_word->text()!=ui->re_pass_word->text())
    {
        QMessageBox::warning(this, "错误","两次输入的密码不一致");
        ui->pass_word->clear();
        ui->re_pass_word->clear();
    }

    else if(!isMatchRex(ui->pass_word->text()))
    {
            QMessageBox::warning(this, "错误","密码格式错误,需要包含大小写字母，且8-10位，不包含特殊字符");
            ui->pass_word->clear();
            ui->re_pass_word->clear();

    }
    else if(!QRegExp("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+").exactMatch(ui->mail->text()))
    {
        QMessageBox::warning(this, "错误","邮箱格式输入错误");
        ui->mail->clear();

    }
    else
    {
        return 1;
    }

    return 0;
}

bool RegisterWidget::isMatchRex(QString str)
{
    //匹配强密码：必须包含大小写字母和数字的组合，不能使用特殊字符，长度在8-10之间
    //反斜杠需要转义
    QRegExp rex("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,10}$");

    bool ok=rex.exactMatch(str);//返回正则表达式匹配的结果
    return ok;

}

void RegisterWidget::on_backToLogin_clicked()
{

    emit backToLogin();
   // 如果没有点击注册，直接点击返回也会清空
    ui->user_name->clear();
    ui->pass_word->clear();
    ui->re_pass_word->clear();
    ui->mail->clear();


}

void RegisterWidget::on_register_1_clicked()
{
    if(check_account())
     {
        this->saveUser(ui->user_name->text(),ui->pass_word->text(),ui->mail->text());

        QMessageBox::information(this, "提示","您已经注册成功，可以去登录了");

        makeUserFile();

        //注册成功之后清空框里边的内容
           ui->user_name->clear();
           ui->pass_word->clear();
           ui->re_pass_word->clear();
           ui->mail->clear();
    }
}



void RegisterWidget::saveUser(QString name, QString psd, QString phone)
{
        QString filename;
       filename="userData1.txt";


       QFile file(filename);

        if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            qDebug()<<"没有打开文件";
        }
        else
        {
            //能打开文件的前提下通过流的方式输出内容
            QTextStream out(&file);
            out<<name<<'\n'<<psd<<'\n'<<phone<<'\n';
            file.close();
        }
}

void RegisterWidget::makeUserFile()
{

    //注册成功之后为每个用户创建以用户名为名的文件夹，并且在该文件夹下创建“studentData.txt”
    QDir dir;
    if(!dir.exists("Data/"+ui->user_name->text()))
    {
        dir.mkdir("Data/"+ui->user_name->text());
        qDebug()<<"Data/"+ui->user_name->text ()+"创建成功";

        QString filename="Data/"+ui->user_name->text()+"/studentData.txt";
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly|QIODevice::Truncate))
        {
            qDebug()<<"创建sutdentData.txt成功";
            file.close();
        }
        else  qDebug()<<"创建studentData.txt失败";
    }
    else
    {
        qDebug()<<"Data/"+ui->user_name->text ()+"创建失败";
    }
}

bool RegisterWidget::isDirExist(QString fullPath)
{
    QDir dir;
    if(dir.exists(fullPath))
    {
      return true;
    }
    return false;
}

void RegisterWidget::on_register_2_clicked()
{
    if(check_account())
    {
        if(ui->verify_code->text()==verifycode)
        {
            this->saveUser(ui->user_name->text(),ui->pass_word->text(),ui->mail->text());
            QMessageBox::information(this, "提示","您已经注册成功，可以去登录了");

            makeUserFile();

            //注册成功之后清空框里边的内容
               ui->user_name->clear();
                ui->pass_word->clear();
                ui->re_pass_word->clear();
               ui->mail->clear();
        }
        else
        {
            QMessageBox::information(this, "警告","验证码错误");

        }

    }

}

void RegisterWidget::on_sendCode_clicked()
{
    //在邮箱正确的前提才能进行发送
    if(!QRegExp("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+").exactMatch(ui->mail->text()))
    {
        QMessageBox::warning(this, "错误","邮箱格式输入错误");
        ui->mail->clear();

    }
    else
    {
        //发送验证码
        verifycode=get_verifyCode();

        Smtp s;
        s.send(ui->mail->text().toLatin1(),"欢迎注册学生成绩管理系统",("验证码为"+verifycode).toLocal8Bit());

        QMessageBox::information(this, "提示","验证码发送成功");

    }

}
