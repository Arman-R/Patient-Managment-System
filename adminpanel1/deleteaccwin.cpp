#include "deleteaccwin.h"
#include "ui_deleteaccwin.h"

DeleteAccWin::DeleteAccWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteAccWin)
{
    ui->setupUi(this);
}

DeleteAccWin::~DeleteAccWin()
{
    delete ui;
}

void DeleteAccWin::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;

       msgBox.setWindowTitle("Delete");
       msgBox.setText("Are you sure?");
       msgBox.setIcon(QMessageBox::Icon::Question);
       msgBox.addButton(QMessageBox::Yes);
       msgBox.addButton(QMessageBox::No);

       if (msgBox.exec() == QMessageBox::Yes)
       {

           event->accept();
       }
        else
       {
           event->ignore();
       }
}



void DeleteAccWin::on_deleteButton_clicked()
{
    QSqlQuery query1;
    QSqlQuery query2;
    QSqlQuery query3;


    QSqlQuery query4;

    QString key;


      this->email = ui->email->text();

      query4.prepare("SELECT email FROM dr_accounts WHERE email =  :email");
      query4.bindValue(":email",email);

      if (query4.exec())
      {
    if (query4.size()<=0)
    {
   QMessageBox::warning(this,"Account not deleted","Acoount does not exist");
    }
else {
    query1.prepare("SELECT iddr_fk FROM dr_accounts WHERE email = :email");
    query1.bindValue(":email", email);
      query1.exec();

    while (query1.next()) {
           key = query1.value(0).toString();

      }


  query2.prepare("DELETE FROM dr_accounts WHERE email = :email");
  query2.bindValue(":email",email);


  query3.prepare("DELETE FROM doctors WHERE iddr = :key");
      query3.bindValue(":key",key);

      if (query2.exec() and query3.exec())
         QMessageBox::information(this,"Account deleted","Account has been successfully deleted");
}

      } //query 4 exec
}

