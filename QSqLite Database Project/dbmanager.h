#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 people.db
 * 2. sqilte> CREATE TABLE people(ids integer primary key, name text);
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);


    //set database path
    void setDatabasePath(QString dbpath);


    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable();

    /**
     * @brief Add person data to db
     * @param name - name of person to add
     * @return true - person added successfully, false - person not added
     */
    bool addProfessor(const int id,const QString& name,const QString& lastname, const QString& password);
    bool addStudent(const int id, const QString& password,const QString& name,const QString& address, const QString& birthday);
    bool addNotes(const int id, const QString& notes,const QString& coe);
    /**
     * @brief Remove person data from db
     * @param name - name of person to remove.
     * @return true - person removed successfully, false - person not removed
     */
    bool removePerson(const QString& name);
    bool removeStudent(const int& id);
    bool removeNotes(const int& id);


    /**
     * @brief Check if person of name "name" exists in db
     * @param name - name of person to check.
     * @return true - person exists, false - person does not exist
     */
    bool personExists(const QString& name) const;
    bool professorExists(const int id);
    bool professorExistsForLogin(const int id, const QString& password);
    bool studentExistsForLogin(const int id, const QString& password);
    bool studentExists(const int id);
    bool notesExists(const int id);

    /**
     * @brief Print names of all persons in db
     */
    void printAllPersons() const;
    QStringList printAllStudents() const;
    QStringList printStudent(int id) const;
    QStringList printProfessor(int id) const;
    QStringList printNote(int id) const;


    bool updateMarks(const int id, const int marks);
    /**
     * @brief Remove all persons from db
     * @return true - all persons removed successfully, false - not removed
     */
    bool removeAllPersons();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
