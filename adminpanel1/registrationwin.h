#ifndef REGISTRATIONWIN_H
#define REGISTRATIONWIN_H

#include <QWidget>

#include <QCloseEvent>
#include <QMessageBox>
#include <QColor>
#include <QPalette>

#include <QString>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


#include <QRegularExpression>
#include <QProcess>

namespace Ui {
class RegistrationWin;
}

class RegistrationWin : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWin(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

    bool checkName(const QString &);
    bool checkMail(const QString &);

     QString checkPasswdStrength(const QString &);

    ~RegistrationWin();

private slots:

    void on_NameLineEdit_textChanged(const QString &arg1);



    void on_SecondNameLineEdit_textChanged(const QString &arg1);

    void on_PasswordEdit_textChanged( const QString &arg1);

    void on_RegisterButton_clicked();

    void on_EmailLineEdit_textChanged(const QString &);

private:
    Ui::RegistrationWin *ui;

    QString f_name;
    QString s_name;
    QString department;
    QString iddr;
    QString mail;
    QString passw;
    QString gender;
    QString reg_date;
    QString reg_time;

      QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

};

#endif // REGISTRATIONWIN_H
