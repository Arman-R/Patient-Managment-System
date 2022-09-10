#include "patientsreception.h"
#include "ui_patientsreception.h"




PatientsReception::PatientsReception(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientsReception)
{
    ui->setupUi(this);



    db.setHostName(" ");//hostname
       db.setUserName(" "); //database's account username
       db.setPassword(" "); //database's account password
       db.setDatabaseName(" ");

    if (db.open())
    {


  //  ui->patientsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

 ui->patientView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
fillComboBox();
    }

}
void PatientsReception::fillComboBox()
{
QSqlQuery query1;
query1.prepare("SELECT iddr FROM doctors");
query1.exec();
while (query1.next()) {
        ui->comboBox->addItem(query1.value(0).toString());
        }
}
void PatientsReception::on_patientView_clicked(const QModelIndex &index)
{
    QString data;
  if (index.isValid())
       data = index.data().toString();

  qDebug()<<"\nDATA:" <<data;


//  QItemSelectionModel *select = ui->patientsView->selectionModel();

  this->rowidx = ui->patientView->selectionModel()->currentIndex().row();


  for (int i=1;i<3;i++)
  {

      name_surname = name_surname + " "+ ui->patientView->model()->data(ui->patientView->model()->index(rowidx,i)).toString();

      qDebug()<<"\nIMe:"<<ui->patientView->model()->data(ui->patientView->model()->index(rowidx,i)).toString();


  }

  ui->full_nameLabel->setText(name_surname);

}


void PatientsReception::on_searchButton_clicked()
{


    QSqlQuery query;

    bool f_name_empty = ui->fnameEdit->text().isEmpty();
    bool s_name_empty = ui->snameEdit->text().isEmpty();
    bool ssn_empty = ui->ssnEdit->text().isEmpty();
    bool date_empty = ui->dateEdit->text().isEmpty();

    QString edit_values[4];


    edit_values[0] = ui->fnameEdit->text();
    edit_values[1] = ui->snameEdit->text();
    edit_values[2] = ui->ssnEdit->text();
    edit_values[3] = ui->dateEdit->text();

    if (f_name_empty and s_name_empty and ssn_empty) //all empty
    {
        if (!date_empty)
        {

            query.prepare("SELECT * FROM patients WHERE b_day=:date OR b_day LIKE(:date)");

            query.bindValue(":date",(edit_values[3]+"%"));
if(query.exec())

            model1->setQuery(std::move (query));

            ui->patientView->setModel(model1);


        }
    }

    else if (f_name_empty and s_name_empty and !ssn_empty)
    {

        if (!date_empty)
        {
            query.prepare("SELECT * FROM patients WHERE b_day =:date AND ssn=:ssn OR b_day LIKE :date AND ssn LIKE :ssn");
             query.bindValue(":ssn",(edit_values[2]+"%"));

             query.bindValue(":date",(edit_values[3]+"%"));
                    query.exec();

        }

        else
        {

            query.prepare("SELECT * FROM patients WHERE ssn=:ssn OR ssn LIKE :ssn");
               query.bindValue(":ssn",(edit_values[2]+"%"));
            query.exec();


        }

        model1->setQuery(std::move (query));

        ui->patientView->setModel(model1);
    }

    else if (f_name_empty and !s_name_empty and ssn_empty)
    {


            if(!date_empty)
            {
                query.prepare("SELECT * FROM patients WHERE b_day =:date AND s_name=:s_name OR b_day LIKE :date AND s_name LIKE :s_name");
                 query.bindValue(":s_name",(edit_values[1]+"%"));

                 query.bindValue(":date",(edit_values[3]+"%"));
                        query.exec();
            }

            else
            {
                query.prepare("SELECT * FROM patients WHERE s_name = :s_name OR s_name LIKE :s_name");
                query.bindValue(":s_name",(edit_values[1]+"%"));
                query.exec();
            }
            model1->setQuery(std::move (query));
            ui->patientView->setModel(model1);


    }
    else if (f_name_empty and !s_name_empty and !ssn_empty)
    {

        if (!date_empty)
        {
        query.prepare("SELECT * FROM patients WHERE b_day=:date AND s_name =:s_name AND ssn=:ssn OR b_day LIKE :date AND s_name LIKE :s_name AND ssn LIKE :ssn" );

        query.bindValue(":date",(edit_values[3]+"%"));

        query.bindValue(":s_name",(edit_values[1]+"%"));

        query.bindValue(":ssn",( edit_values[2]+"%"));

        query.exec();
        }
        else
        {
            query.prepare("SELECT * FROM patients WHERE s_name =:s_name AND ssn=:ssn OR s_name LIKE :s_name AND ssn LIKE :ssn");

            query.bindValue(":ssn",(edit_values[2]+"%"));
            query.bindValue(":s_name",(edit_values[1]+"%"));
            query.exec();
        }
        model1->setQuery(std::move (query));
        ui->patientView->setModel(model1);


 }
    else if (!f_name_empty and s_name_empty and ssn_empty)
    {

        if(!date_empty)
        {
            query.prepare("SELECT * FROM patients WHERE b_day=:date AND f_name =:name OR b_day LIKE :date AND f_name LIKE :name" );

               query.bindValue(":name",(edit_values[0]+"%"));
            query.bindValue(":date",(edit_values[3]+"%"));

            query.exec();

        }
        else
        {
            query.prepare("SELECT * FROM patients WHERE f_name = :name OR f_name LIKE :name");
            query.bindValue(":name",(edit_values[0]+"%"));
            query.exec();

    }

        model1->setQuery(std::move (query));
        ui->patientView->setModel(model1);

    }
    else if (!f_name_empty and s_name_empty and !ssn_empty)
    {

        if(!date_empty)
        {
            query.prepare("SELECT * FROM patients WHERE b_day = :date AND f_name = :name AND ssn =:ssn OR b_day LIKE :date AND f_name LIKE :name AND ssn LIKE :ssn");

            query.bindValue(":name",(edit_values[0]+"%"));
            query.bindValue(":ssn",(edit_values[2]+"%"));
             query.bindValue(":date",(edit_values[3]+"%"));
            query.exec();
        }

        else
        {

            query.prepare("SELECT * FROM patients WHERE f_name = :name AND ssn = :ssn OR f_name LIKE :name AND ssn LIKE :ssn");

            query.bindValue(":name",(edit_values[0]+"%"));
            query.bindValue(":ssn",(edit_values[2]+"%"));
            query.exec();

        }
        model1->setQuery(std::move (query));
        ui->patientView->setModel(model1);

    }
    else if (!f_name_empty and !s_name_empty and ssn_empty)
    {

        if (!date_empty)
        {
            query.prepare("SELECT * FROM patients WHERE b_day = :date AND f_name = :name AND s_name =:s_name OR b_day LIKE :date AND f_name LIKE :name AND s_name LIKE :s_name");

            query.bindValue(":name",(edit_values[0]+"%"));
            query.bindValue(":s_name",(edit_values[1]+"%"));
             query.bindValue(":date",(edit_values[3]+"%"));
            query.exec();

        }
        else

        {
            query.prepare("SELECT * FROM patients WHERE f_name = :name AND s_name =:s_name OR f_name LIKE :name AND s_name LIKE :s_name");

            query.bindValue(":name",(edit_values[0]+"%"));
            query.bindValue(":s_name",(edit_values[1]+"%"));

            query.exec();
        }

        model1->setQuery(std::move (query));
        ui->patientView->setModel(model1);
    }
    else if (!f_name_empty and !s_name_empty and !ssn_empty) //not empty
    {
        if(!date_empty)
        {

  query.prepare("SELECT * FROM patients "

                "WHERE b_day = :date AND f_name = :f_name AND s_name = :s_name AND ssn =:ssn "
                "OR b_day LIKE :date AND f_name LIKE :f_name AND s_name LIKE :s_name  AND ssn LIKE :ssn");


  query.bindValue(":f_name",(edit_values[0]+"%"));
  query.bindValue(":s_name",(edit_values[1]+"%"));
  query.bindValue(":ssn",(edit_values[2]+"%"));
  query.bindValue(":date",(edit_values[3]+"%"));

        query.exec();


        }

        else
         {
            query.prepare("SELECT * FROM patients "
                          "WHERE f_name = :f_name AND s_name = :s_name AND ssn =:ssn "
                          "OR f_name LIKE :f_name AND s_name LIKE :s_name  AND ssn LIKE :ssn"


                          );

            query.bindValue(":f_name",(edit_values[0]+"%"));
            query.bindValue(":s_name",(edit_values[1]+"%"));
            query.bindValue(":ssn",(edit_values[2]+"%"));
            query.exec();
        }
        model1->setQuery(std::move (query));
        ui->patientView->setModel(model1);

    }




}



void PatientsReception::on_submitButton_clicked()
{
    QString p_key = ui->patientView->model()->data(ui->patientView->model()->index(rowidx,0)).toString();


    if (!ui->full_nameLabel->text().isEmpty())
    {
        QSqlQuery query;

        this->doctor = ui->comboBox->currentText();
    this->time  = ui->timeEdit->text();
query.prepare("INSERT INTO daily_patients (reception_time, iddr_fk,idpa_fk) "
              "VALUES(:time, :doctor,:idpa_fk)");


query.bindValue(":time",time);
query.bindValue(":doctor",doctor);
query.bindValue(":idpa_fk",p_key);

query.exec();

            qDebug()<<"P KEY: "<<p_key;
       // query.prepare("")
    }
}
PatientsReception::~PatientsReception()
{
    delete ui;
    db.close();
}




