#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>
#include "dbmanager.h"
#include "professorform.h"
#include "studentform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);        
    ~MainWindow();
    DbManager *db;
    QString dbPath;


private slots:
    void on_bttnLoginStudent_clicked();

    void on_pushButton_clicked();

    void on_bttnLoginProfessor_clicked();

    void on_bttnResetProfessor_clicked();

    void on_bttnResetStudent_clicked();

    void on_pushButtonSetDatabasePath_clicked();

private:
    Ui::MainWindow *ui;
    ProfessorForm *pi;
    studentForm *si;
};
#endif // MAINWINDOW_H
