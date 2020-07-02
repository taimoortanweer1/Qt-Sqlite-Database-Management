#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QDialog>
#include "dbmanager.h"
#include <QMessageBox>

namespace Ui {
class studentForm;
}

class studentForm : public QDialog
{
    Q_OBJECT

public:
    explicit studentForm(QWidget *parent = nullptr, DbManager *db = nullptr);
    ~studentForm();
    int currentId;
    QString currentpass;

    void setCurrentId(int value);

    void setCurrentpass(const QString &value);
    void showEvent( QShowEvent* event ) ;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::studentForm *ui;
    DbManager *db_m;
};

#endif // STUDENTFORM_H
