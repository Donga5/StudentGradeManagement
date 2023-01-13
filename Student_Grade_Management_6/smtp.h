#ifndef SMTP_H
#define SMTP_H

#include<QByteArray>
#include<QString>
#include<QTcpSocket>
#include<QMessageBox>
class Smtp
{
public:
    Smtp();
    //发送邮件的函数
    void send(QByteArray address,QByteArray subject, QByteArray content);
    void output_receiveData();//将接收到的数据进行输出
private:
    QByteArray username;//发送邮箱的账户
    QByteArray password;//授权码
    QTcpSocket *clientSocket;
};

#endif // SMTP_H
