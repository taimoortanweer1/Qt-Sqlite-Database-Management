#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

void DbManager::setDatabasePath(QString dbpath)
{
    m_db.setDatabaseName(dbpath);
}
bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;


    query.prepare("CREATE TABLE student(id INTEGER PRIMARY KEY, password TEXT ,name TEXT, address TEXT, birthday TEXT, marks INTEGER);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'student': one might already exist.";
        success = false;
    }

    query.prepare("CREATE TABLE internship(id INTEGER PRIMARY KEY, notes TEXT, coe text);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'internship': one might already exist.";
        success = false;
    }

    query.prepare("CREATE TABLE professor(id INTEGER PRIMARY KEY, password TEXT, name TEXT, lastname text);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'professor': one might already exist.";
        success = false;
    }

    return success;
}


bool DbManager::addProfessor(const int id,const QString& name,const QString& lastname, const QString& password)
{
    bool success = false;

    if (!name.isEmpty() &&  id>-1 && !lastname.isEmpty() && !password.isEmpty() )
    {

        QSqlQuery testQuery;
        testQuery.prepare("INSERT INTO professor(id,password,name,lastname) VALUES(:id,:password,:name,:lastname)");



        testQuery.bindValue(":id", id);
        testQuery.bindValue(":password", password);
        testQuery.bindValue(":name", name);
        testQuery.bindValue(":lastname", lastname);


        if(testQuery.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add professor failed: " << testQuery.lastError();
        }
    }
    else
    {
        qDebug() << "add professor failed: name cannot be empty";
    }

    return success;
}

bool DbManager::addStudent(const int id, const QString& password,const QString& name,const QString& address, const QString& birthday)
{
    bool success = false;

    if (!name.isEmpty() &&  id>-1 && !address.isEmpty() && !birthday.isEmpty() )
    {

        QSqlQuery testQuery;
        testQuery.prepare("INSERT INTO student(id,password,name,address,birthday,marks) VALUES(:id,:password,:name,:address,:birthday,:marks)");

        testQuery.bindValue(":id", id);
        testQuery.bindValue(":password", password);
        testQuery.bindValue(":name", name);
        testQuery.bindValue(":address", address);
        testQuery.bindValue(":birthday", birthday);
        testQuery.bindValue(":marks", 0);
        if(testQuery.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add student failed: " << testQuery.lastError();
        }
    }
    else
    {
        qDebug() << "add student failed: name cannot be empty";
    }

    return success;
}

bool DbManager::addNotes(const int id, const QString& notes,const QString& coe)
{
    bool success = false;

    if (id>-1 && !notes.isEmpty() && !coe.isEmpty() )
    {

        QSqlQuery testQuery;
        testQuery.prepare("INSERT INTO internship(id,notes,coe) VALUES(:id,:notes,:coe)");

        testQuery.bindValue(":id", id);
        testQuery.bindValue(":notes", notes);
        testQuery.bindValue(":coe", coe);


        if(testQuery.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add notes failed: " << testQuery.lastError();
        }
    }
    else
    {
        qDebug() << "add notes failed: name cannot be empty";
    }

    return success;
}

bool DbManager::removeStudent(const int& id)
{
    bool success = false;

    if (studentExists(id))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM student WHERE id = (:id)");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove student failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove person failed: person doesnt exist";
    }

    return success;
}

bool DbManager::removeNotes(const int& id)
{
    bool success = false;

    if (notesExists(id))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM internship WHERE id = (:id)");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove notes failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove notes failed: notes with this ID doesnt exist";
    }

    return success;
}


bool DbManager::updateMarks(const int id, const int marks)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("UPDATE student set marks=(:marks) WHERE id = (:id)");
    checkQuery.bindValue(":id", id);
    checkQuery.bindValue(":marks", marks);

    if (checkQuery.exec())
    {
            exists = true;
    }
    else
    {
        qDebug() << "marks update failed exists failed: " << checkQuery.lastError();
    }

    return exists;
}

QStringList DbManager::printAllStudents() const
{
    QStringList List;
    qDebug() << "Students in db:";
    QSqlQuery query("SELECT * FROM student");
    int idCur = query.record().indexOf("id");
    int passCur = query.record().indexOf("password");
    int nameCur = query.record().indexOf("name");
    int addressCur = query.record().indexOf("address");
    int birthdayCur = query.record().indexOf("birthday");
    int marksCur = query.record().indexOf("marks");

    while (query.next())
    {
        QString id = query.value(idCur).toString();
        QString password = query.value(passCur).toString();
        QString name = query.value(nameCur).toString();
        QString address = query.value(addressCur).toString();
        QString birthday = query.value(birthdayCur).toString();
        QString marks = query.value(marksCur).toString();

        List << id <<  name << address << birthday << marks;

        //qDebug() <<id << "===" << password << "===" << name << "===" << address << "===" << birthday << "---" << marks;
    }

    return List;
}


QStringList DbManager::printNote(int id) const
{
    QStringList d;
    qDebug() << "Note in db:";
    QSqlQuery query("SELECT * FROM internship");
    int idCur = query.record().indexOf("id");
    int noteCur = query.record().indexOf("notes");
    int coeCur = query.record().indexOf("coe");


    while (query.next())
    {
        QString id_need = query.value(idCur).toString();
        QString note = query.value(noteCur).toString();
        QString coe = query.value(coeCur).toString();

        if(QVariant(id_need).toInt() == id)
        {
            d << note << id_need << coe;
            break;
        }
    }

    return d;
}

QStringList DbManager::printStudent(int id) const
{
    QStringList d;
    qDebug() << "Student in db:";
    QSqlQuery query("SELECT * FROM student");
    int idCur = query.record().indexOf("id");
    int passCur = query.record().indexOf("password");
    int nameCur = query.record().indexOf("name");
    int addressCur = query.record().indexOf("address");
    int birthdayCur = query.record().indexOf("birthday");
    int marksCur = query.record().indexOf("marks");

    while (query.next())
    {
        QString id_need = query.value(idCur).toString();
        QString password = query.value(passCur).toString();
        QString name = query.value(nameCur).toString();
        QString address = query.value(addressCur).toString();
        QString birthday = query.value(birthdayCur).toString();
        QString marks = query.value(marksCur).toString();

        if(QVariant(id_need).toInt() == id)
        {
            d << id_need << name << address << birthday << marks;
            break;
        }
    }

    return d;
}

QStringList DbManager::printProfessor(int id) const
{
    QStringList d;
    qDebug() << "Professor in db:";
    QSqlQuery query("SELECT * FROM professor");
    int idCur = query.record().indexOf("id");
    int nameCur = query.record().indexOf("name");
    int lastnameCur = query.record().indexOf("lastname");

    while (query.next())
    {
        QString id_need = query.value(idCur).toString();
        QString name = query.value(nameCur).toString();
        QString lastname = query.value(lastnameCur).toString();

        if(QVariant(id_need).toInt() == id)
        {
            d << id_need << name << lastname;
            break;
        }
    }

    return d;
}

bool DbManager::professorExistsForLogin(const int id, const QString& password)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT  * FROM professor WHERE id = (:id) AND password = (:password)");
    checkQuery.bindValue(":id", id);
    checkQuery.bindValue(":password", password);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "professor exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::studentExistsForLogin(const int id, const QString& password)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM student WHERE id = (:id) AND password = (:password)");
    checkQuery.bindValue(":id", id);
    checkQuery.bindValue(":password", password);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "student exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::professorExists(const int id)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM professor WHERE id = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "professor exists failed: " << checkQuery.lastError();
    }

    return exists;
}


bool DbManager::studentExists(const int id)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT  * FROM student WHERE id = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "student exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::notesExists(const int id)
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT  * FROM internship WHERE id = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "notes exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllPersons()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM people");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all persons failed: " << removeQuery.lastError();
    }

    return success;
}
