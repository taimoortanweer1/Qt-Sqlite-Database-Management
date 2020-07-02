#include "professorform.h"
#include "ui_professorform.h"

ProfessorForm::ProfessorForm(QWidget *parent, DbManager *db) :
    QDialog(parent),
    ui(new Ui::ProfessorForm)
{
    ui->setupUi(this);

    this->db_m = db;
    QStringList headerStrings;
    headerStrings << "ID" << "NAME" << "ADDRESS" << "BIRTHDAY" << "MARKS";

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->horizontalHeader()->setStyleSheet("color: #FFFF00");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setStyleSheet("color: #FFFF00");
    ui->tableWidget->setHorizontalHeaderLabels(headerStrings);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setStyleSheet("border: none; background-color: rgb(36, 35, 36);selection-background-color: #999; color: #FFFFFF"); //for demo purposes



}

ProfessorForm::~ProfessorForm()
{
    delete ui;
}

void ProfessorForm::setCurrentPassword(const QString &value)
{
    currentPassword = value;
}

void ProfessorForm::setCurrentID(int value)
{
    currentID = value;
}

int ProfessorForm::getCurrentID() const
{
    return currentID;
}

void ProfessorForm::on_bttnAddButton_clicked()
{
    bool ret = db_m->addStudent(ui->spinBoxIDAddDelete->value(),ui->passwordLineEdit->text(),ui->nameLineEdit->text(),ui->addressLineEdit->text(),ui->birthdayLineEdit->text());

    QMessageBox m;

    if(ret)
        m.setText("Student Added !!");
    else
        m.setText("Some Error Ocurred");


    m.exec();

    on_bttnShowAllStudent_clicked();
}

void ProfessorForm::on_bttnShowAllStudent_clicked()
{
    QStringList d = db_m->printAllStudents();

    ui->tableWidget->clearContents();


    int j  = 0;
    for ( int i = 0 ; i < d.size();)
    {

        int k = 0;
        ui->tableWidget->setItem(j,k,new QTableWidgetItem(d[i++]));
        k++;

        ui->tableWidget->setItem(j,k,new QTableWidgetItem(d[i++]));
        k++;

        ui->tableWidget->setItem(j,k,new QTableWidgetItem(d[i++]));
        k++;

        ui->tableWidget->setItem(j,k,new QTableWidgetItem(d[i++]));
        k++;

        ui->tableWidget->setItem(j,k,new QTableWidgetItem(d[i++]));
        k++;
        j++;
    }

    ui->plainTextEditNotesStudent->setPlainText("");

}


void ProfessorForm::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
    QStringList list = db_m->printProfessor(currentID);

    ui->iDLineEdit->setText(list[0]);
    ui->nameLineEdit_2->setText(list[1]);
    ui->lastNameLineEdit->setText(list[2]);

    on_bttnShowAllStudent_clicked();


}

void ProfessorForm::on_pushButton_2_clicked()
{
    bool ret = db_m->removeStudent(ui->spinBoxIDAddDelete->value());

    QMessageBox m;

    if(ret)
    {
        bool ret1 = db_m->removeNotes(ui->spinBoxIDAddDelete->value());

        if(ret1)
            m.setText("Student Deleted and Notes Deleted!!");
        else
            m.setText("Student Notes does not exist!!");
    }
    else
        m.setText("Error Ocurred | Student Doesnt Exist");


    m.exec();

    on_bttnShowAllStudent_clicked();
}

void ProfessorForm::on_tableWidget_cellClicked(int row, int column)
{

    //only if ID is clicked
    if(column == 0)
    {
        QTableWidgetItem item = *ui->tableWidget->item(row,column);
        studentIDSelectedFromTable= item.text();

        QStringList list = db_m->printNote(studentIDSelectedFromTable.toInt());
        ui->plainTextEditNotesStudent->setPlainText("");

        if(list.size() > 0)
        {
            ui->plainTextEditNotesStudent->setPlainText(list[0]);
        }
        else
        {
            QMessageBox m;
            m.setText("No Notes Exist of this Student ID");
            m.exec();
        }
    }


}

void ProfessorForm::on_pushButtonMarksUpdate_clicked()
{
    //update marks by professor

    if(db_m->notesExists(studentIDSelectedFromTable.toInt()))
    {
        bool ret = db_m->updateMarks(studentIDSelectedFromTable.toInt(),ui->spinBoxMarks->value());

        QMessageBox m;
        if(ret)
            m.setText("Marks Updated");
        else
            m.setText("Marks Update Error");

        m.exec();
    }
    else
    {
        QMessageBox m;
        m.setText("Cannot Update Marks | No Notes Exists");
        m.exec();
    }

    on_bttnShowAllStudent_clicked();
}
