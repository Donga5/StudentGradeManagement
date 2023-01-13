#include "adddialog.h"
#include "ui_adddialog.h"

#include<QMessageBox>
AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_clicked()//当ok点击之后
{
    QString name=ui->addName->text();
    QString id=ui->addId->text();
    QString _Class=ui->addClass->text();
    QString sex=ui->addSex->text();
    QString math=ui->addMath->text();
    QString English=ui->addEnglish->text();
    QString C_language=ui->addC_launguage->text();
    if(!name.isEmpty()&&!id.isEmpty()&&!sex.isEmpty()&&!_Class.isEmpty()&&
       !math.isEmpty()&&!English.isEmpty()&&!C_language.isEmpty())
    {

        Student *student=new Student(name,id ,sex, _Class,math, English,C_language);
        //必须是new出来的对象，这样在传递的过程中在不会被释放掉
        emit myUpdate(student);
        this->close();//添加完成之后关闭对话窗口

    }
    else
    {
        QMessageBox::information(this,"提示","请将信息填写完整");
    }

}

void AddDialog::on_exit_clicked()
{

    this->close();//将当前的窗口关闭


}
