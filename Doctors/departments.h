#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H


#include <QWidget>

#include "patientsinfo.h"

namespace Ui {
class Departments;
}

class Departments : public QWidget
{
    Q_OBJECT

public:
    explicit Departments(QWidget *parent = nullptr);
    ~Departments();

private slots:
    void on_urgentnaPushButton_clicked();

private:
    Ui::Departments *ui;
    PatientsInfo *pPatientsInfo = nullptr;

};

#endif // DEPARTMENTS_H
