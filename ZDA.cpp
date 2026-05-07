#include "ZDA.h"
#include "ui_ZDA.h"
#include <QMessageBox>
#include <QDebug>

ZDA::ZDA(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ZDA)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &ZDA::on_pushButton_clicked);
    timer->setInterval(1000);
}

ZDA::~ZDA()
{
    delete ui;
}
void ZDA::on_pushButton_clicked()
{

  QString aa = QString("%1").arg(ui->spinBox->value(), 2, 10, QChar('0'));
  QString bb = QString("%1").arg(ui->spinBox_2->value(), 2, 10, QChar('0'));
  QString cc = QString("%1").arg(ui->spinBox_3->value(), 2, 10, QChar('0'));
  QString dd = ui->spinBox_5->text();
  QString ee = ui->spinBox_4->text();

  QDate date = ui->dateEdit->date();
  QString dateStr = date.toString("dd,MM,yyyy");

 QString zda = "$__ZDA," +aa+bb+cc+","+dateStr+","+dd+","+ee+"*66";
 qDebug()<<zda ;
}

void ZDA::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Canceled","");
}

void ZDA::on_pushButton_3_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void ZDA::on_pushButton_4_clicked()
{
    if(timer->isActive())
    timer->stop();
    qDebug() << "OFF PRESSED - Timer Stopped";
}

