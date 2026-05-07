#include "AWOS.h"
#include "ui_AWOS.h"

AWOS::AWOS(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AWOS)
{
    ui->setupUi(this);
}

AWOS::~AWOS()
{
    delete ui;
}
