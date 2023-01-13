#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<registerwidget.h>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString getUserName();
    int  checkAccount();//检查账户
public  slots:
    void on_pushButton_2_clicked();//退出按钮按下之后触发的事件
    void on_pushButton_clicked();//登录按钮按下之后触发的事件
    void on_pushButton_3_clicked();
signals:
    void loginSuccess();//登录成功成功的信号
private:
    Ui::Login *ui;
    RegisterWidget w;//注册窗口
    QString userName;//账号
    QString passWord;//密码
    QString vefify_Code;//验证码
};

#endif // LOGIN_H
