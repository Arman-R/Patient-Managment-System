#include "patientsinfo.h"
#include "ui_patientsinfo.h"

PatientsInfo::PatientsInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientsInfo)
{
    ui->setupUi(this);


    db.setHostName(" ");//hostname
       db.setUserName(" "); //database's account username
       db.setPassword(" "); //database's account password
       db.setDatabaseName(" ");

      qDebug()<<db.lastError().text();

if (db.open())
{
    ui->patientsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

 ui->patientsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    showInfo(this->main_query);
}

}

PatientsInfo::~PatientsInfo()
{
    delete ui;
}



void PatientsInfo::showInfo(const char *query__)
{

    model1->setQuery(query__);

    ui->patientsView->setModel(model1);
}

void PatientsInfo::on_refreshButton_clicked()
{
    showInfo(this->main_query);
}



void PatientsInfo::on_prijemPacijentaButton_clicked()
{
    pPatientsReception = new PatientsReception();
    pPatientsReception->setWindowTitle("Recption");
    pPatientsReception->show();



}


void PatientsInfo::on_patientsView_clicked(const QModelIndex &index)
{
      QString data;
    if (index.isValid())
         data = index.data().toString();

    qDebug()<<"\nDATA:" <<data;



    this-> rowidx = ui->patientsView->selectionModel()->currentIndex().row();


    for (int i=0;i<4;i++)
    {

        qDebug()<<ui->patientsView->model()->data(ui->patientsView->model()->index(rowidx,i)).toString()<<" ";
    }

}




void PatientsInfo::showQueryFilter(QSqlQuery query)
{
query.exec();
    model1->setQuery(std::move (query));
    ui->patientsView->setModel(model1);


}
void PatientsInfo::on_filterButton_clicked()
{


               QString f_name_filter =ui->nameEdit->text();
                  QString s_name_filter = ui->s_nameEdit->text();
                  QString doctor_filter = ui->doctorEdit->text();

            QSqlQuery query1;




      if (f_name_filter.isEmpty() and  s_name_filter.isEmpty() and !doctor_filter.isEmpty())
      {

          query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                         "FROM patients pat "
                         "INNER JOIN daily_patients dp "
                         "ON pat.idpa_pk = dp.idpa_fk "
                         "INNER JOIN doctors "
                         "ON doctors.iddr = dp.iddr_fk "
                         "WHERE dp.iddr_fk LIKE :iddr OR dp.iddr_fk = :iddr");


qDebug()<<query1.lastError().text();
query1.bindValue(":iddr", (doctor_filter+"%"));

    showQueryFilter(std::move(query1));

}



                  else if (f_name_filter.isEmpty() and  !s_name_filter.isEmpty() and doctor_filter.isEmpty())
                {
          query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                         "FROM patients pat "
                         "INNER JOIN daily_patients dp "
                         "ON pat.idpa_pk = dp.idpa_fk "
                         "INNER JOIN doctors "
                         "ON doctors.iddr = dp.iddr_fk "
                         "WHERE pat.s_name LIKE :name OR pat.s_name = :name");



          query1.bindValue(":name",(s_name_filter+"%"));

       this->showQueryFilter(std::move(query1));
                  }
                  else if (f_name_filter.isEmpty() and  !s_name_filter.isEmpty() and !doctor_filter.isEmpty())
                  {

                        query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                                       "FROM patients pat "
                                       "INNER JOIN daily_patients dp "
                                       "ON pat.idpa_pk = dp.idpa_fk "
                                       "INNER JOIN doctors "
                                       "ON doctors.iddr = dp.iddr_fk "
                                       "WHERE pat.s_name LIKE :name AND dp.iddr_fk LIKE :iddr "
                                       "OR pat.s_name = :name AND dp.iddr_fk = :iddr"
                                       );


                                  query1.bindValue(":name",(s_name_filter+"%"));
                                  query1.bindValue(":iddr", (doctor_filter+"%"));


                        showQueryFilter(std::move(query1));
                  }

                  else if (!f_name_filter.isEmpty() and  s_name_filter.isEmpty() and doctor_filter.isEmpty())
                  {
          query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                         "FROM patients pat "
                         "INNER JOIN daily_patients dp "
                         "ON pat.idpa_pk = dp.idpa_fk "
                         "INNER JOIN doctors "
                         "ON doctors.iddr = dp.iddr_fk "
                         "WHERE pat.f_name LIKE :name OR pat.f_name = :name");


                    query1.bindValue(":name",(f_name_filter+"%"));

                    showQueryFilter(std::move(query1));
                  }
                  else if (!f_name_filter.isEmpty() and  s_name_filter.isEmpty() and !doctor_filter.isEmpty())
                  {

          query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                         "FROM patients pat "
                         "INNER JOIN daily_patients dp "
                         "ON pat.idpa_pk = dp.idpa_fk "
                         "INNER JOIN doctors "
                         "ON doctors.iddr = dp.iddr_fk "
                         "WHERE pat.f_name LIKE :name AND doctors.iddr LIKE :iddr "
                         "OR pat.f_name = :name AND doctors.iddr = :iddr");


                    query1.bindValue(":name",(f_name_filter+"%"));
                     query1.bindValue(":iddr", (doctor_filter+"%"));

                      showQueryFilter(std::move(query1));


                  }
                  else if (!f_name_filter.isEmpty() and  !s_name_filter.isEmpty() and doctor_filter.isEmpty())
                  {
          query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                         "FROM patients pat "
                         "INNER JOIN daily_patients dp "
                         "ON pat.idpa_pk = dp.idpa_fk "
                         "INNER JOIN doctors "
                         "ON doctors.iddr = dp.iddr_fk "
                         "WHERE pat.f_name LIKE :f_name AND pat.s_name LIKE :s_name "
                         "OR pat.f_name = :f_name AND pat.s_name = :s_name");

           query1.bindValue(":f_name",(f_name_filter+"%"));
query1.bindValue(":s_name",(s_name_filter+"%"));

 showQueryFilter(std::move(query1));
                  }

      else if (!f_name_filter.isEmpty() and !s_name_filter.isEmpty() and !doctor_filter.isEmpty())
      {
          query1.prepare("SELECT idap_pk AS num,CONCAT(pat.f_name,' ',pat.s_name) AS Name,iddr,department,reception_time "
                         "FROM patients pat "
                         "INNER JOIN daily_patients dp "
                         "ON pat.idpa_pk = dp.idpa_fk "
                         "INNER JOIN doctors "
                         "ON doctors.iddr = dp.iddr_fk "
                         "WHERE pat.f_name LIKE :f_name AND pat.s_name LIKE :s_name AND doctors.iddr LIKE :iddr "
                         "OR pat.f_name = :f_name AND pat.s_name = :s_name  AND doctors.iddr = :iddr" );

           query1.bindValue(":f_name",(f_name_filter+"%"));
query1.bindValue(":s_name",(s_name_filter+"%"));
query1.bindValue(":iddr",(doctor_filter+"%"));
 showQueryFilter(std::move(query1));
      }
}





bool PatientsInfo::areYouSure()
{

    QMessageBox msgBox;

       msgBox.setWindowTitle("Delete Patient");
       msgBox.setText("Are you sure?");
       msgBox.setIcon(QMessageBox::Icon::Question);
       msgBox.addButton(QMessageBox::Yes);
       msgBox.addButton(QMessageBox::No);

       if (msgBox.exec()==QMessageBox::Yes)
       {
           return true;
       }

       return false;

}
void PatientsInfo::on_deleteButton_clicked()
{



    QSqlQuery query;

    query.prepare("DELETE FROM daily_patients "
                   "WHERE daily_patients.idap_pk = :rowidx");

    int key =ui->patientsView->model()->data(ui->patientsView->model()->index(rowidx,0)).toInt();
   query.bindValue(":rowidx",key);

   if (areYouSure())
   {
      query.exec();
   }


}

