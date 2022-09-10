#include "departments.h"
#include "ui_departments.h"

Departments::Departments(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Departments)
{
    ui->setupUi(this);
}

Departments::~Departments()
{
    delete ui;
}

void Departments::on_urgentnaPushButton_clicked()
{
    try {
        this->pPatientsInfo = new PatientsInfo();
    pPatientsInfo->show();
    pPatientsInfo->setWindowTitle("Patients ");
    this->close();



    } catch (std::exception &e) {
        qDebug()<<e.what();
    }
}

