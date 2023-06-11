#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->plainTextEdit->setEnabled(false);
}

Dialog::~Dialog()
{
    delete ui;
}
