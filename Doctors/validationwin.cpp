#include "validationwin.h"
#include "ui_validationwin.h"

ValidationWin::ValidationWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ValidationWin)
{
    ui->setupUi(this);

    db.setHostName(" ");//hostname
       db.setUserName(" "); //database's account username
       db.setPassword(" "); //database's account password
       db.setDatabaseName(" ");


    ui->WrongInputLabel->setVisible(false);

}

bool ValidationWin::checkLogin()
{
    if (db.open())
    {
      this->email = ui->emailEdit->text();
       this-> passw = ui->passwEdit->text();



        query.prepare("SELECT email,passw FROM dr_accounts WHERE email = :email AND AES_DECRYPT(passw,'secret') = :passw");

        query.bindValue(":email", email);
        query.bindValue(":passw", passw);


        if (query.exec())
        {
                if (query.size()>0)
                {

                    qDebug()<<"Ima";
                    return true;
                }

    }
    } //db open ?
    return false;
}



void ValidationWin::on_Login_clicked()
{
    if (checkLogin())
    {
        try {

            pPatientsInfo = new PatientsInfo();
           pPatientsInfo->show();
            pPatientsInfo->setWindowTitle("Patients");

         this->close();

        } catch (std::exception &e)
        {
            qDebug()<<e.what();
            }
    }
    QPalette palette = ui->WrongInputLabel->palette();
     palette.setColor(QPalette::WindowText,Qt::red);
     ui->WrongInputLabel->setVisible(true);
     ui->WrongInputLabel->setPalette(palette);

}


ValidationWin::~ValidationWin()
{
    delete ui;
    db.close();


}
