#include "userdel.h"
#include "ui_userdel.h"

UserDel::UserDel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDel)
{
    ui->setupUi(this);
}

UserDel::~UserDel()
{
    delete ui;
}




