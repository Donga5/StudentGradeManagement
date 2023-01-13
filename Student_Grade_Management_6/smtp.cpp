#include "smtp.h"
#include<QDebug>

Smtp::Smtp()
{
    //在构造参数中固定了账号和密码
    username="zhaoguodong23@163.com";
    password="PQVSWDYQBQUHFFQZ";

}

void Smtp::send(QByteArray address, QByteArray subject, QByteArray content)
{
    clientSocket=new QTcpSocket();

    // 命令行中回车是\r\n
    //跟服务器链接
    clientSocket->connectToHost("smtp.163.com",25);
    clientSocket->waitForConnected(1000);
    output_receiveData();

    //打招呼
    clientSocket->write("HELO smtp.163.com\r\n");
    output_receiveData();

    //登录指令
    clientSocket->write("AUTH LOGIN\r\n");
    output_receiveData();

    //输入base64转码之后的账户
    clientSocket->write(username.toBase64().append("\r\n"));
    output_receiveData();

    //输入密码
    clientSocket->write(password.toBase64().append("\r\n"));
    output_receiveData();

    //输入信号发送端
    clientSocket->write("mail from:<"+username+">\r\n");
    output_receiveData();

    //输入接收端
    clientSocket->write("rcpt to:<"+address+">\r\n");
    output_receiveData();

    //开始输入数据
    clientSocket->write("data\r\n");
    output_receiveData();

    //输入主题
    clientSocket->write("Subject:"+subject+"\r\n");
    clientSocket->write("\r\n");

    //输入内容
    clientSocket->write(content.append("\r\n"));
    clientSocket->write(".\r\n");
    output_receiveData();


    //退出
    clientSocket->write("quit\r\n");
    output_receiveData();

    clientSocket->disconnect();




}

void Smtp::output_receiveData()
{
    clientSocket->waitForReadyRead(1000);
    qDebug()<<(clientSocket->readAll());
}
