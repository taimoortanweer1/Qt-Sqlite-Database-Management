#include "studentform.h"
#include "ui_studentform.h"

studentForm::studentForm(QWidget *parent, DbManager *db) :
    QDialog(parent),
    ui(new Ui::studentForm)
{
    ui->setupUi(this);
    this->db_m = db;



}

studentForm::~studentForm()
{
    delete ui;
}

void studentForm::setCurrentpass(const QString &value)
{
    currentpass = value;
}

void studentForm::setCurrentId(int value)
{
    currentId = value;
}



void studentForm::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
    QStringList list = db_m->printStudent(currentId);

    ui->nameLineEdit->setText(list[1]);
    ui->iDLineEdit->setText(list[0]);
    ui->addressLineEdit->setText(list[2]);
    ui->birthdayLineEdit->setText(list[3]);
    ui->marksLineEdit->setText(list[4]);

    QStringList list1 = db_m->printNote(currentId);
    if(list1.size()!=0)
        ui->textEdit->setText(list1[0]);

}

void studentForm::on_pushButton_clicked()
{
    bool ret = db_m->addNotes(currentId,ui->textEdit->toPlainText(),"idk");

    QMessageBox m;

    if(ret)
        m.setText("Notes Added For evaluation");
    else
        m.setText("Error | Notes Already Added");


    m.exec();

    //ui->textEdit->setText("");
}

void studentForm::on_pushButton_2_clicked()
{
    bool ret = db_m->removeNotes(currentId);

    QMessageBox m;

    if(ret)
        m.setText("Notes Deleted");
    else
        m.setText("Error | Notes Doesnot Exist");


    m.exec();
}
