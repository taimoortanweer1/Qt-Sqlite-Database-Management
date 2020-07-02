#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DbManager(ui->lineEditDbPath->text());

    db->createTable();


    pi = new ProfessorForm(nullptr,db);
    si = new studentForm(nullptr,db);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bttnLoginStudent_clicked()
{

    bool ret = db->studentExistsForLogin(ui->spinBoxStudentID->value(),ui->lineStudentLoginPass->text());

    QMessageBox m;
    if(ret)
    {
        si->setCurrentId(ui->spinBoxStudentID->value());
        si->setCurrentpass(ui->lineStudentLoginPass->text());
        si->show();
    }
    else {
        m.setText("Wrong Id or Password");
        m.exec();
    }


}

void MainWindow::on_pushButton_clicked()
{
    bool ret = db->addProfessor(ui->spinBox->value(),ui->nameLineEdit->text(),ui->lastNameLineEdit->text(),ui->passwordLineEdit->text());

    QMessageBox m;

    if(ret)
    {
        m.setText("New ID Created");

    }
    else
    {
        m.setText("Error | Field Missing | Already Registered");

    }

    m.exec();

}

void MainWindow::on_bttnLoginProfessor_clicked()
{
    bool ret = db->professorExistsForLogin(ui->spinBoxProfessorID->value(),ui->lineProfessorLoginPass->text());
    QMessageBox m;
    if(ret)
    {
        pi->setCurrentID(ui->spinBoxProfessorID->value());
        pi->setCurrentPassword(ui->lineProfessorLoginPass->text());

        pi->show();
    }
    else {
        m.setText("Wrong Id or Password");
        m.exec();
    }

}

void MainWindow::on_bttnResetProfessor_clicked()
{
    ui->spinBox->setValue(0);
    ui->lineProfessorLoginPass->setText("");
}

void MainWindow::on_bttnResetStudent_clicked()
{
    ui->spinBoxStudentID->setValue(0);
    ui->lineStudentLoginPass->setText("");
}


void MainWindow::on_pushButtonSetDatabasePath_clicked()
{
    //db->setDatabasePath(ui->lineEditDbPath->text());

    if(db)
        delete  db;

    if(pi)
        delete pi;

    if(si)
        delete si;

    db = new DbManager(ui->lineEditDbPath->text());

    db->createTable();


    pi = new ProfessorForm(nullptr,db);
    si = new studentForm(nullptr,db);

    QMessageBox m;
    m.setText("Database Path Updated");
    m.exec();
}
