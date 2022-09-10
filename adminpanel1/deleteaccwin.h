#ifndef DELETEACCWIN_H
#define DELETEACCWIN_H

#include <QWidget>



#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDebug>

#include <QMessageBox>
#include  <QCloseEvent>

#include <QMessageBox>

namespace Ui {
class DeleteAccWin;
}

class DeleteAccWin : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteAccWin(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

    ~DeleteAccWin();

private slots:

    void on_deleteButton_clicked();


private:
    Ui::DeleteAccWin *ui;
    QString email;
};

#endif // DELETEACCWIN_H
