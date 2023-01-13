#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"login.h"
#include<control.h>

#include<adddialog.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_onIistWidget(int row);//将某一行的信息显示到右侧表中
    void showItem(Student *stu);//把一个学生的信息显示到表格中
    void showList();//将整个链表中学生的信息显示到表格上
    void closeEvent(QCloseEvent *event);//重写基类的窗口关闭事件
public slots:
    void on_backToLogin_clicked();//返回到注册界面
    void on_addButton_clicked();//添加按钮点击之后
    void onMyUpdate(Student *);//发送添加学生成功的信号
    void sortWidgetColumn(int column);//将表格内容进行排序
    void on_saveButton_clicked();//保存模块
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void on_searchButton_clicked();//查找按钮被点击
    void on_deleteButton_clicked();//点击删除按钮
    void on_tableWidget_cellChanged(int row, int column);
    void on_pushButton_clicked();//刷新按钮
    void on_pushButton_2_clicked();//导入按钮
    void on_pushButton_3_clicked();//导出按钮
private:
    Ui::MainWindow *ui;
    Login w1;//登录窗口
    Control *ctrl;//只有一个控制对象
    AddDialog *addDialog;//添加信息的窗口对象
    bool item4_UpAndDown=0;//记录第五列的排序信息
    bool item5_UpAndDown=0;//记录第六列排序信息
    bool item6_UpAndDown=0;//记录第七列排序信息
};
#endif // MAINWINDOW_H
