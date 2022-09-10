#ifndef VALIDATIONWIN_H
#define VALIDATIONWIN_H

#include <QMainWindow>
#include <QWidget>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QString>

#include <QDebug>
#include <QMessageBox>
#include "patientsinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ValidationWin; }
QT_END_NAMESPACE

class ValidationWin : public QMainWindow
{
    Q_OBJECT

public:
    ValidationWin(QWidget *parent = nullptr);
    ~ValidationWin();
    bool checkLogin();

private slots:
    void on_Login_clicked();

private:
    Ui::ValidationWin *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString email;
    QString passw;
     QSqlQuery query;
    PatientsInfo *pPatientsInfo;



};
#endif // VALIDATIONWIN_H
