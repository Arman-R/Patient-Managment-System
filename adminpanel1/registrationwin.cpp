#include "registrationwin.h"
#include "ui_registrationwin.h"
#include <QDebug>

RegistrationWin::RegistrationWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWin)
{
    ui->setupUi(this);

    db.setHostName(" "); //mysql host
       db.setUserName(" "); //username for mysql account
       db.setPassword(" "); //password for mysql account
       db.setDatabaseName(" "); //database name

if (db.open())
{
    qDebug()<<"It's opened";
}

}

RegistrationWin::~RegistrationWin()
{
    delete ui;

}



void RegistrationWin::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;

       msgBox.setWindowTitle("Exit");
       msgBox.setText("Are you sure? ");
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


bool RegistrationWin::checkName(const QString &name)
{

    bool ok = true;
    for (int i=0;i<name.size();i++)
        {
        if (name[i].isDigit() || name[i].isSymbol() || name[i].isPunct())
        {
            ok = false;
            break;
        }

    }

    if (ok and name.size()>=3)
        return ok;

     return false;
}



void RegistrationWin::on_NameLineEdit_textChanged(const QString &name)
{
    QPalette palette = ui->Namelabel->palette();

    if (name.isEmpty())
    {
        palette.setColor(QPalette::WindowText,Qt::black);
        ui->Namelabel->setPalette(palette);
    }


   else if (!checkName(name))
    {

            palette.setColor(QPalette::WindowText,Qt::red);
             ui->Namelabel->setPalette(palette);
     }
    else
    {
        palette.setColor(QPalette::WindowText,Qt::green);
         ui->Namelabel->setPalette(palette);
    }

}


void RegistrationWin::on_SecondNameLineEdit_textChanged(const QString &s_name)
{
    QPalette palette = ui->Namelabel->palette();

    if (s_name.isEmpty())
    {
        palette.setColor(QPalette::WindowText,Qt::black);
        ui->Namelabel_2->setPalette(palette);
    }


    if (!checkName(s_name))
    {

            palette.setColor(QPalette::WindowText,Qt::red);
             ui->Namelabel_2->setPalette(palette);
     }
    else if (s_name.isEmpty())
    {
        palette.setColor(QPalette::WindowText,Qt::black);
        ui->Namelabel_2->setPalette(palette);
    }
    else
    {
        palette.setColor(QPalette::WindowText,Qt::green);
         ui->Namelabel_2->setPalette(palette);

    }

}




QString RegistrationWin::checkPasswdStrength(const QString &passwd)
{


    bool has_lower = false;
   bool has_upper  =false;
   bool has_digit = false;
   bool special_char = false;

  int s_size = passwd.size();

    for (int i=0;i<s_size;i++)
    {

        if (passwd[i].isLower())
                has_lower = true;

        if (passwd[i].isUpper())
                has_upper = true;


        if (passwd[i].isPunct())
                special_char = true;

        if (passwd[i].isDigit())
            has_digit = true;

    }


    if (has_lower and has_upper and special_char and has_digit and (s_size>=8))
        {

            return "Strong";
    }
    else if ((has_lower || has_upper) and special_char and (s_size>=6))
    {
        //strength_level = "Moderate";
            return "Moderate";
    }
    else
    {
        return "Weak";//strength_level;
    }

}




void RegistrationWin::on_PasswordEdit_textChanged(const QString &passwd)
{


    QPalette palette = ui->PswdStrength->palette();

    QString level = checkPasswdStrength(passwd);



    ui->PswdStrength->setVisible(true);


    if (level == "Strong")
    {

        palette.setColor(QPalette::WindowText,Qt::green);
         ui->PswdStrength->setPalette(palette);
         ui->PswdStrength->setText(level);

    }
    else if (level =="Moderate")
    {
        palette.setColor(QPalette::WindowText,Qt::blue);
         ui->PswdStrength->setPalette(palette);
         ui->PswdStrength->setText(level);

    }
    else if (level =="Weak")
    {
        palette.setColor(QPalette::WindowText,Qt::red);
         ui->PswdStrength->setPalette(palette);
         ui->PswdStrength->setText(level);
    }


}

bool RegistrationWin::checkMail(const QString &mail)
{
    QRegularExpression re("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");

    if (re.match(mail.toUpper()).hasMatch())
        return true;

       return false;

}

void RegistrationWin::on_EmailLineEdit_textChanged(const QString &mail_input)
{

      QPalette palette = ui->Emaillabel->palette();


    if (checkMail(mail_input))
    {
        palette.setColor(QPalette::WindowText,Qt::green);
         ui->Emaillabel->setPalette(palette);
    }
    else
    {
        palette.setColor(QPalette::WindowText,Qt::red);
         ui->Emaillabel->setPalette(palette);
    }

}
void RegistrationWin::on_RegisterButton_clicked()
{


        this->f_name = ui->NameLineEdit->text();
        this->s_name = ui->SecondNameLineEdit->text();
        this->department = ui->DepartmentEdit->text();
        this->iddr = ui->IDDocEdit->text();
        this-> mail = ui->EmailLineEdit->text();

        this->gender='M';
    this->reg_time = ui->timeEdit->text();

    this->reg_date = ui->dateEdit->text();

        if (ui->FradioButton->isChecked())
        {
            gender = 'F';
        }




        QSqlQuery query1;

        query1.prepare("SELECT email FROM dr_accounts WHERE email = :email");
        query1.bindValue(":email",mail);


bool query2_status = false;
bool query3_status = false;

if (query1.exec())
{

if (query1.size()==0)
{


    QSqlQuery query2;

    query2.prepare("INSERT INTO doctors VALUES(:iddr,:f_name,:s_name,:gender,:department)"),
   query2.bindValue(":iddr",iddr);
    query2.bindValue(":f_name",f_name);
    query2.bindValue(":s_name",s_name);
    query2.bindValue(":gender",gender);
    query2.bindValue(":department",department);

if (query2.exec())
{


    query2_status = true;

     passw = ui->PasswordEdit->text();

    QSqlQuery query3;
    query3.prepare("INSERT INTO dr_accounts VALUES(:email,AES_ENCRYPT(:passw,'secret'),:create_date, :create_time,:iddr_fk)");


    query3.bindValue(":email",mail);
    query3.bindValue(":passw",passw);
    query3.bindValue(":create_date",reg_date);

    query3.bindValue(":create_time",reg_time);
    query3.bindValue(":iddr_fk",iddr);

    if (query3.exec())
    {
        query3_status = true;
     }

} //query2 exec

if (checkMail(mail) and checkName(f_name)  and checkName(s_name) and query2_status and query3_status )
    {

    QMessageBox::information(this,"Register info","User has been registered succesfully");
}

} //query1 size  --check if mail exist
} //query1 exec status --check if mail exist


} //on register button
