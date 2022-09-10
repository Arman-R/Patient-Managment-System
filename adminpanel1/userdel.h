#ifndef USERDEL_H
#define USERDEL_H

#include <QDialog>
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
class UserDel;
}

class UserDel : public QDialog
{
    Q_OBJECT

public:
    explicit UserDel(QWidget *parent = nullptr);
    ~UserDel();

private slots:
    void on_buttonBox_accepted();

    void on_Delete_clicked();

private:
    Ui::UserDel *ui;
    QString email;
};

#endif // USERDEL_H
