#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include<smtp.h>

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();
    QString get_verifyCode();//获取验证码
    bool check_account();//检查输入的是否有错误
    bool isMatchRex(QString str);//检验是否为强密码
     //注册成功之后将用户信息进行保存
    void saveUser(QString name, QString psd, QString phone);
    void makeUserFile();//为每个用户创建相应的文件夹
    bool isDirExist(QString fullPath);//判断文件夹是否存在
signals:
    void backToLogin();//返回登录界面的信号
private slots:
    void on_backToLogin_clicked();//返回按钮点击
    void on_register_1_clicked();//离线注册按钮点击
    void on_register_2_clicked();//注册按钮点击
    void on_sendCode_clicked();//发送验证码点击
private:
    Ui::RegisterWidget *ui;
    QString verifycode;//验证码
};

#endif // REGISTERWIDGET_H
