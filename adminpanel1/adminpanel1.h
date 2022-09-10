#ifndef ADMINPANEL1_H
#define ADMINPANEL1_H

#include <QMainWindow>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDebug>

#include "registrationwin.h"

#include "deleteaccwin.h"



QT_BEGIN_NAMESPACE
namespace Ui { class adminpanel1; }
QT_END_NAMESPACE

class adminpanel1 : public QMainWindow
{
    Q_OBJECT

public:
    adminpanel1(QWidget *parent = nullptr);
    ~adminpanel1();
    void openDbConnection();
void startProcess(const QString &);
void refreshTables();
void setPaletteActiveColorGreen();
void setPaletteActiveColorRed();



private slots:


    void on_RegisterAcc_clicked();

    void on_StartMYSQL_clicked();

    void on_StopMYSQL_clicked();


    void on_RestartMYSQL_clicked();

    void on_Refresh_clicked();

    void on_Delete_clicked();


private:
    Ui::adminpanel1 *ui;

    RegistrationWin *pRegisterWin =nullptr;
    DeleteAccWin *pDeleteWin = nullptr;
    QProcess process;

    const  QString bash ="/bin/bash";
    QSqlDatabase  db = QSqlDatabase::addDatabase("QMYSQL");


    QSqlQueryModel  *model1 = new QSqlQueryModel();
      QSqlQueryModel  *model2 = new QSqlQueryModel();




};
#endif // ADMINPANEL1_H
