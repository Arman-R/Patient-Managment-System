#include "adminpanel1.h"
#include "ui_adminpanel1.h"




adminpanel1::adminpanel1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::adminpanel1)
{


    db.setHostName(" ");//hostname
       db.setUserName(" "); //database's account username
       db.setPassword(" "); //database's account password
       db.setDatabaseName(" ");


    ui->setupUi(this);

   ui->dr_accounts_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->doctors_view->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->dr_accounts_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->doctors_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

     if (!db.open())
     {


         setPaletteActiveColorRed();
     }
     setPaletteActiveColorGreen();
         refreshTables();


}
void adminpanel1::refreshTables()
{


    model1 -> setQuery("SELECT email,create_date, create_time, iddr_fk FROM dr_accounts;");
    ui -> dr_accounts_view-> setModel(model1);


    model2 -> setQuery("SELECT iddr, f_name AS 'Name', s_name AS 'Second name', gender, department  FROM doctors;");
    ui->doctors_view->setModel(model2);
}

adminpanel1::~adminpanel1()
{
    delete ui;
    delete model1;
    delete model2;
}

void adminpanel1::on_Refresh_clicked()
{


        refreshTables();

qDebug()<<db.open();


}


void adminpanel1::on_RegisterAcc_clicked()
{

    try {

        pRegisterWin = new RegistrationWin();
        pRegisterWin->show();
        pRegisterWin->setWindowTitle("Register Account");
    } catch (std::exception &e)
    {
        qDebug()<<e.what();
        }


}

void adminpanel1::startProcess(const QString &path__)
{

    try {


    process.start(path__);
     process.waitForFinished();
    QString output = process.readAllStandardOutput();
    qDebug() << output;
    QString err = process.readAllStandardError();
    qDebug() << err;
    }
    catch(std::invalid_argument e)
    {
        qDebug()<<e.what();
    }




}

void adminpanel1::setPaletteActiveColorGreen()
{
    QPalette palette = ui->ActiveLabel->palette();
    palette.setColor(QPalette::WindowText,Qt::green);
    ui->ActiveLabel->setPalette(palette);

}

void adminpanel1::setPaletteActiveColorRed()
{
    QPalette palette = ui->ActiveLabel->palette();
    palette.setColor(QPalette::WindowText,Qt::red);
    ui->ActiveLabel->setPalette(palette);
}
void adminpanel1::on_StartMYSQL_clicked()
{


   const QString path = " "; //path for bash file for starting mysql

    startProcess(path);


    if (db.open())
            setPaletteActiveColorGreen();

}


void adminpanel1::on_StopMYSQL_clicked()
{
 const QString path = " "; //path for bash file for stopping mysql


    startProcess(path);
    if (!db.open())
    {
       setPaletteActiveColorRed();
    }
}


void adminpanel1::on_RestartMYSQL_clicked()
{
    const QString path = " "; //path for bash file for restarting mysql

    startProcess(path);


}



void adminpanel1::on_Delete_clicked()
{

    try {

        pDeleteWin = new DeleteAccWin();
        pDeleteWin->setWindowTitle("Delete Account");
        pDeleteWin->show();
    } catch (std::exception &e)
    {
        qDebug()<<e.what();
        }


}

