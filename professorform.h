#ifndef PROFESSORFORM_H
#define PROFESSORFORM_H

#include <QDialog>
#include "dbmanager.h"
#include <QMessageBox>
namespace Ui {
class ProfessorForm;
}

class ProfessorForm : public QDialog
{
    Q_OBJECT

public:
    explicit ProfessorForm(QWidget *parent = nullptr, DbManager *db = nullptr);
    ~ProfessorForm();
    int currentID;
    QString currentPassword;

    int getCurrentID() const;

    void setCurrentID(int value);

    void setCurrentPassword(const QString &value);

private slots:
    void on_bttnAddButton_clicked();

    void on_bttnShowAllStudent_clicked();

    void showEvent( QShowEvent* event );

    void on_pushButton_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButtonMarksUpdate_clicked();

private:
    Ui::ProfessorForm *ui;
    DbManager *db_m;
    QString studentIDSelectedFromTable;
};

#endif // PROFESSORFORM_H
