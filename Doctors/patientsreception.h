#ifndef PATIENTSRECEPTION_H
#define PATIENTSRECEPTION_H

#include <QWidget>



#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QHeaderView>

namespace Ui {
class PatientsReception;
}

class PatientsReception : public QWidget
{
    Q_OBJECT

public:
    explicit PatientsReception(QWidget *parent = nullptr);

    void fillComboBox();

    ~PatientsReception();

private slots:

    void on_patientView_clicked(const QModelIndex &index);

    void on_searchButton_clicked();
    void on_submitButton_clicked();

private:
    Ui::PatientsReception *ui;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QSqlQueryModel  *model1 = new QSqlQueryModel();
     QString name_surname;
     QString time;
     QString doctor;

    int rowidx;
};

#endif // PATIENTSRECEPTION_H

