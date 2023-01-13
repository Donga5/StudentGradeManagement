#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QWidget>
#include<student.h>
namespace Ui {
class AddDialog;
}

class AddDialog : public QWidget
{
    Q_OBJECT
public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
private slots:
    void on_pushButton_clicked();
    void on_exit_clicked();
signals:
    void  myUpdate(Student*);
private:
    Ui::AddDialog *ui;
};
#endif // ADDDIALOG_H
