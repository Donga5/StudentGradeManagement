#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"login.h"
#include<QDebug>
#include<QModelIndex>
#include<QDebug>
#include<student.h>
#include<QMessageBox>
#include<QScrollBar>
#include<QAxObject>
#include<QFileDialog>
#include<QDesktopServices>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //对于表格的一些设置


    //在设置好有多少列的基础上设置表头才能显示
    ui->tableWidget->setColumnCount(7);
    QStringList headers;
    headers<<"姓名"<<"学号"<<"性别"<<"班级"<<"高数"<<"英语"<<"C语言";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStyleSheet(
                "QHeaderView::section{background-color:rgb(189,255,253);"
                                                       "font:12pt;color: black;};");

    ui->tableWidget->resizeRowsToContents();//表格所有行自动适应文本大小
    ui->tableWidget->setShowGrid(1);//默认显示表格线
    ui->tableWidget->setFont(QFont("黑体",10));
    //设定选择的行为,按照行进行选择
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:rgb(255,209,128)");


    //垂直滚动条样式
    ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 12px;}"
             "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
             "QScrollBar::handle:hover{background:gray;}"
             "QScrollBar::sub-line{background:transparent;}"
             "QScrollBar::add-line{background:transparent;}");
    ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:12px;}"
             "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
             "QScrollBar::handle:hover{background:gray;}"
             "QScrollBar::sub-line{background:transparent;}"
             "QScrollBar::add-line{background:transparent;}");



    //ui表格的显示进行设计

     ui->tableWidget->horizontalHeader()->setSortIndicator(4,Qt::DescendingOrder);
    ui->tableWidget->horizontalHeader()->setSortIndicator(5,Qt::DescendingOrder);
     ui->tableWidget->horizontalHeader()->setSortIndicator(6,Qt::DescendingOrder);
     ui->tableWidget->horizontalHeader()->setSortIndicatorShown(1);//设置三角显示器进行显示


        connect(ui->tableWidget->horizontalHeader(),&QHeaderView::sectionClicked,this, &MainWindow::sortWidgetColumn);


    addDialog=nullptr;


    this->setFixedSize(1300,800);

    qDebug()<<"11111111111";
    w1.show();//首先显示登录界面

    //收到登录成功的信号之后，打开主界面，并且关闭登录界面
    connect(&w1,&Login::loginSuccess,this,
            [=](){
             this->show();
             w1.close();
             //登录成功之后，在登录界面显示用户名,不能写到外面，因为这是在登录之后才保存。

             ctrl=Control::getCtrl();//获取控制类对象的指针

             ui->username_->setText("欢迎您,"+w1.getUserName());

             ctrl->setUsername(w1.getUserName());
             //获取到登录信息之后才能决定打开哪个用户对应的txt文件
             ctrl->fileToList();

             showList();//链表中的信息显示到表格上面


      });
    //接收到学生信息填写成功的情况下，添加学生信息链表


    //在打开程序的时候检查是否存在data目录，不存在则创建
    QDir dir;
    if(!dir.exists("Data"))
    {
          if(dir.mkpath("Data"))qDebug()<<"目录创建成功";
    }
    else {
        qDebug()<<"data目录已存在";
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_onIistWidget(int row)//将某一行的信息显示到右侧表中
{
    if(ui->listWidget->count()!=0)
    {
        ui->listWidget->item(0)->setText("姓名:"+ui->tableWidget->item(row,0)->text());
        ui->listWidget->item(1)->setText("学号:"+ui->tableWidget->item(row,1)->text());
        ui->listWidget->item(2)->setText("性别:"+ui->tableWidget->item(row,2)->text());
        ui->listWidget->item(3)->setText("班级:"+ui->tableWidget->item(row,3)->text());
        ui->listWidget->item(4)->setText("高数:"+ui->tableWidget->item(row,4)->text()+"分");
        ui->listWidget->item(5)->setText("英语:"+ui->tableWidget->item(row,5)->text()+"分");
        ui->listWidget->item(6)->setText("C语言:"+ui->tableWidget->item(row,6)->text()+"分");

    }
    else
    {
        ui->listWidget->addItem("姓名:"+ui->tableWidget->item(row,0)->text());
        ui->listWidget->addItem("学号:"+ui->tableWidget->item(row,1)->text());
        ui->listWidget->addItem("性别:"+ui->tableWidget->item(row,2)->text());
        ui->listWidget->addItem("班级:"+ui->tableWidget->item(row,3)->text());
        ui->listWidget->addItem("高数:"+ui->tableWidget->item(row,4)->text());
        ui->listWidget->addItem("英语:"+ui->tableWidget->item(row,5)->text());
        ui->listWidget->addItem("C语言:"+ui->tableWidget->item(row,6)->text());
    }



}

void MainWindow::showItem(Student *stu)
{

    //在修改下面的表格内容的之前断开信号和槽的连接
    disconnect(ui->tableWidget,&QTableWidget::cellChanged,nullptr, nullptr);

    int row=ui->tableWidget->rowCount();

    int Math=(int)stu->getMath().toDouble();
    int English=stu->getEnglish().toDouble();

    int C_language=stu->getC_language().toDouble();
    int Id=(int)stu->getId().toDouble();


    QTableWidgetItem *item0=new QTableWidgetItem(stu->getName());
    item0->setTextAlignment(Qt::AlignCenter);//设置表格内容居中对齐

    QTableWidgetItem *item1=new QTableWidgetItem;
    item1->setData(Qt::DisplayRole,Id);
    item1->setText(QString::number(Id));
    item1->setTextAlignment(Qt::AlignCenter);//设置表格内容居中对齐


    QTableWidgetItem *item2=new QTableWidgetItem(stu->getSex());
    item2->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *item3=new QTableWidgetItem(stu->getClass());
    item3->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *item4=new QTableWidgetItem;
    item4->setData(Qt::DisplayRole,Math);
    item4->setText(QString::number(Math));
    item4->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *item5=new QTableWidgetItem;
    item5->setData(Qt::DisplayRole,English);
    item5->setText(QString::number(English));
    item5->setTextAlignment(Qt::AlignCenter);



    QTableWidgetItem *item6=new QTableWidgetItem;
    item6->setData(Qt::DisplayRole,C_language);
    item6->setText(QString::number(C_language));
    item6->setTextAlignment(Qt::AlignCenter);
    //必须设置有多少行和列，否则默认是0行0列，无法显示
    ui->tableWidget->setRowCount(row+1);

    ui->tableWidget->setItem(row,0,item0);
    ui->tableWidget->setItem(row,1,item1);
    ui->tableWidget->setItem(row,2,item2);
    ui->tableWidget->setItem(row,3,item3);
    ui->tableWidget->setItem(row,4,item4);
    ui->tableWidget->setItem(row,5,item5);
    ui->tableWidget->setItem(row,6,item6);



    connect(ui->tableWidget,&QTableWidget::cellChanged,this,&MainWindow::on_tableWidget_cellChanged);
}
void MainWindow::sortWidgetColumn(int column)
{
    if(column==4)
    {
        if(item4_UpAndDown)
        {
            ui->tableWidget->sortItems(column);//默认是降序
            item4_UpAndDown=false;
        }
        else
        {
            ui->tableWidget->sortItems(column,Qt::DescendingOrder);
            item4_UpAndDown=true;
        }

    }
    else if(column==5)
     {

        if(item5_UpAndDown)
        {
            ui->tableWidget->sortItems(column);//默认是降序
            item5_UpAndDown=false;
        }
        else
        {
            ui->tableWidget->sortItems(column,Qt::DescendingOrder);
            item5_UpAndDown=true;
        }

    }
    else if(column==6)
    {
        if(item6_UpAndDown)
        {
            ui->tableWidget->sortItems(column);//默认是降序
            item6_UpAndDown=false;
        }
        else
        {
            ui->tableWidget->sortItems(column,Qt::DescendingOrder);
            item6_UpAndDown=true;
        }
    }
}



void MainWindow::showList()
{
    auto ite=ctrl->getList().begin();

    while(ite!=ctrl->getList().end())
    {
        showItem(*ite);

        ite++;
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"提示","当前修改没有保存，是否要进行保存")==QMessageBox::StandardButton::Yes)
    {
        ctrl->listToFile();

    }

}


void MainWindow::on_backToLogin_clicked()
{
  this->hide();

   //退出之后将表格中的信息清空
   ui->tableWidget->clearContents();
   ui->tableWidget->setRowCount(0);
   ui->tableWidget->verticalScrollBar()->setSliderPosition(0);
   ctrl->listToFile();//保存
   ctrl->allClear();//清楚链表中的所有元素并且释放内存
  w1.show();
}

void MainWindow::on_addButton_clicked()
{

    addDialog= new AddDialog();//创建新的对话窗口


    //connect里边的指针不能是空指针，空指针会导致程序异常退出
    connect(addDialog,&AddDialog::myUpdate,this, &MainWindow::onMyUpdate);
    addDialog->setWindowTitle("添加学生信息");

    addDialog->show();
    //将窗口显示出来

}

void MainWindow::onMyUpdate(Student * stu)
{
    //将当前获取到的学生信息添加到链表中
  //首先要进行检查是否该学生已经存在

    auto ite=ctrl->getList().begin();
    while(ite!=ctrl->getList().end())
    {
        if(stu->getId()==(*ite)->getId())
        {
            //查找到相同的就进行提示添加失败
            QMessageBox::warning(this, "提示","学号不能重复添加失败，请重新添加");
            return ;

        }
        ite++;

    }

    ctrl->addStu(stu);
    showItem(stu);
    QMessageBox::information(this, "提示","添加成功");

}

void MainWindow::on_saveButton_clicked()
{
    ctrl->listToFile();

    on_pushButton_clicked();//刷新表格信息

    QMessageBox::information(this,"提示","保存成功");
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    show_onIistWidget(row);
}

void MainWindow::on_searchButton_clicked()
{
    //基于表格里边的信息去查找,可以根据学号和姓名进行查找
    QString infor=ui->lineEdit->text();
    int row=ui->tableWidget->rowCount();

    for(int i=0;i<row;++i)
    {
        QString name=ui->tableWidget->item(i,0)->text();
        QString id=ui->tableWidget->item(i,1)->text();
        if(name==infor||infor==id)
        {
            show_onIistWidget(i);
            ui->tableWidget->selectRow(i);

            if(i>8)
            {
                ui->tableWidget->verticalScrollBar()->setSliderPosition(i-8);//数字代表滑动多少行
            }//使其一直保持在页面的中央

            return ;
        }

    }
    QMessageBox::warning(this,"提示","没有找到该学生信息，请重新输入");
    ui->lineEdit->clear();

}


void MainWindow::on_deleteButton_clicked()
{
  //QTablewidgeItem存储一个单元格的信息，row返回的是单元格所在的行
  ui->listWidget->clear();//删除相关信息

  //基本思路：通过保存选中单元格的信息，然后依次遍历，当前一个和后一个单元格不在同一行时，删除前一行
  QList<QTableWidgetItem*>qlist=ui->tableWidget->selectedItems();
  auto ite=qlist.begin();
  while(ite!=qlist.end())
  {
      int row_1=(*ite)->row();
      ite++;
      int row_2=-1;//下一个单元格所在的行
      if(ite!=qlist.end())
      {
          row_2=(*ite)->row();
      }
      if(row_1!=row_2)
      {
          QString str=ui->tableWidget->item(row_1,1)->text();
          ui->tableWidget->removeRow(row_1);
          ctrl->deleteStu(str);
      }

  }
  on_pushButton_clicked();//刷新
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{

    //单元格内容被修改之后做出反应

    QString str=ui->tableWidget->item(row, column)->text();
    //获取被修改单元格的内容
    QMessageBox::StandardButton button=QMessageBox::StandardButton::No;//默认赋值为不保存

    if(column==1)
    {
        QMessageBox::warning(this, "警告","学号不允许修改");
    }
    else
    {

        button=QMessageBox::question(this,"提示","是否保存对学号为"+ui->tableWidget->item(row,1)->text()+"学生信息的修改");

    }

    //根据button的值分两种情况，一种是保存修改，另一种是放弃修改，并且将修改还原到以前的值


    //先找到链表中与被修改单元格学号相同元素的位置
    auto ite=ctrl->getList().begin();
    while(ite!=ctrl->getList().end())
    {
        if(ui->tableWidget->item(row,1)->text()==(*ite)->getId())
            break;

        ite++;
    }

    qDebug()<<"2222222222";

    if(button==QMessageBox::StandardButton::Yes)
    {
        switch(column)
        {
            case 0:(*ite)->setName(str);break;
            case 2:(*ite)->setSex(str);break;
            case 3:(*ite)->setClass(str);break;
            case 4:(*ite)->setMath(str);break;
            case 5:(*ite)->setEnglish(str);break;
            case 6:(*ite)->setC_language(str);break;
        }
        qDebug()<<"1111111111111";
        show_onIistWidget(row);//将当前行更新后的信息显示到旁边的列表上面
    }
    else
    {
        //修改表格内容之前断开连接，不然有可能会死循环
        disconnect(ui->tableWidget,&QTableWidget::cellChanged,nullptr, nullptr);
        //分两种情况，第一种是修改了学号,第二种是其他
        switch (column) {
         case 1:
            {
              //有关这一行的信息已经显示到了旁边的表中，从表中可以直接获取当前的学号，因为学号是不可以修改，所以学号还是原来正确的学号
            QStringList lst=ui->listWidget->item(1)->text().split(':');
            //将得到的第二行信息进行分割，分割后得到的第二个字符串就是学号
            ui->tableWidget->item(row, column)->setText(lst[1]);
            }
            break;
         case 0:
            ui->tableWidget->item(row, column)->setText((*ite)->getName());
            break;
        case 2:
           ui->tableWidget->item(row, column)->setText((*ite)->getSex());
           break;
        case 3:
           ui->tableWidget->item(row, column)->setText((*ite)->getClass());
           break;
        case 4:
           ui->tableWidget->item(row, column)->setText((*ite)->getMath());
           break;
        case 5:
           ui->tableWidget->item(row, column)->setText((*ite)->getEnglish());
           break;
        case 6:
           ui->tableWidget->item(row, column)->setText((*ite)->getC_language());
           break;
        }

        connect(ui->tableWidget,&QTableWidget::cellChanged,this,&MainWindow::on_tableWidget_cellChanged);
    }


}

void MainWindow::on_pushButton_clicked()
{

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->verticalScrollBar()->setSliderPosition(0);

    showList();
}

void MainWindow::on_pushButton_3_clicked()
{
    //获取保存路径
    QString filepath=QFileDialog::getSaveFileName(this,"Save","./", "表格文件(*.xlsx)");//默认打开的是当前编译路径


    if(!filepath.isEmpty()){
        QAxObject *excel = new QAxObject(this);
        //连接Excel控件
        excel->setControl("Excel.Application");
        //不显示窗体
        excel->dynamicCall("SetVisible (bool Visible)","false");
        //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        excel->setProperty("DisplayAlerts", false);
        //获取工作簿集合

        QAxObject *workbooks = excel->querySubObject("WorkBooks");
        //新建一个工作簿
        workbooks->dynamicCall("Add");
        //获取当前工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
        //获取工作表集合
        QAxObject *worksheets = workbook->querySubObject("Sheets");
        //获取工作表集合的工作表1，即sheet1
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);



          //设置水平表头值,设置某行某列
        for(int i=1;i<ui->tableWidget->columnCount()+1;i++)
        {

            QAxObject *Range = worksheet->querySubObject("Cells(int,int)", 1, i);
            Range->dynamicCall("SetValue(const QString &)",ui->tableWidget->horizontalHeaderItem(i-1)->text());
        }


        //设置表格数据
        for(int i = 1;i<ui->tableWidget->rowCount()+1;i++)
        {
            for(int j = 1;j<ui->tableWidget->columnCount()+1;j++)
            {
                QAxObject *Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)",ui->tableWidget->item(i-1,j-1)->data(Qt::DisplayRole).toString());
            }
        }
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        QMessageBox::information(this,"提示","已经成功导出");
    }


}


void MainWindow::on_pushButton_2_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, "打开文件","./","文本文件(*.txt)");

    if(!filename.isEmpty())
    {
    ctrl->fileToList(filename);//将新的文本读到链表中

    on_pushButton_clicked();//刷新表格内容
    QMessageBox::information(this, "提示","导入成功");

    }
    else
    {
        QMessageBox::information(this, "提示","导入失败");
    }


}
