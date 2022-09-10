#ifndef PATIENTSINFO_H
#define PATIENTSINFO_H

#include <QMainWindow>
#include <QWidget>



#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>


#include <QHeaderView>
#include <QMessageBox>

#include "patientsreception.h"

namespace Ui {
class PatientsInfo;
}

class PatientsInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PatientsInfo(QWidget *parent = nullptr);
    ~PatientsInfo();
       void showInfo(const char *);
    void showQueryFilter(QSqlQuery );

    bool areYouSure();


private slots:
       void on_prijemPacijentaButton_clicked();



       void on_patientsView_clicked(const QModelIndex &index);

       void on_refreshButton_clicked();


       void on_filterButton_clicked();

       void on_deleteButton_clicked();

private:
    Ui::PatientsInfo *ui;
     QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

     QSqlQueryModel  *model1 = new QSqlQueryModel();
        PatientsReception *pPatientsReception = nullptr;

         int rowidx;

         const char  *main_query  = "SELECT idap_pk AS num,CONCAT(patients.f_name,' ',patients.s_name) AS Name,iddr,department,reception_time "
                                "FROM patients "
                                "INNER JOIN daily_patients "
                                "ON patients.idpa_pk = daily_patients.idpa_fk "
                                "INNER JOIN doctors "
                                "ON doctors.iddr = daily_patients.iddr_fk";
};

#endif // PATIENTSINFO_H
