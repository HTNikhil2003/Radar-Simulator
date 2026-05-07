#include "GGA.h"
#include "ui_GGA.h"
#include <QMessageBox>
#include <QDebug>
#include <qdatetime.h>
#include <QFile>
#include <QTextStream>

GGA::GGA(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GGA)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &GGA::updateGPGGA);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);
}

GGA::~GGA()
{
    delete ui;
}

void GGA::on_pushButton_clicked()
{
 QString aa = ui->spinBox_10->text();
 QString bb = ui->doubleSpinBox_3->text();
 QString cc = ui->textEdit->toPlainText();
 QString dd = ui->spinBox_11->text();
 QString ee = ui->doubleSpinBox_4->text();
 QString ff = ui->textEdit_2->toPlainText();
 QString AA = QString("%1").arg(ui->spinBox->value(), 2, 10, QChar('0'));
 QString BB = QString("%1").arg(ui->spinBox_2->value(), 2, 10, QChar('0'));
 QString CC = QString("%1").arg(ui->spinBox_3->value(), 2, 10, QChar('0'));
 QString DD = ui->spinBox_4->text();
 QString EE = ui->spinBox_5->text();
 QString FF = ui->spinBox_6->text();
 QString GG = ui->spinBox_7->text();
 QString HH = ui->spinBox_8->text();
 QString II = ui->spinBox_9->text();
 QString XX = ui->comboBox_2->currentText();
 QString YY = ui->comboBox_3->currentText();
 QString ZZ = ui->comboBox->currentText();
 QString gga = "$__GGA," +AA+BB+CC+","+aa+bb+","+XX+","+dd+ee+","+YY+","+ZZ+","+HH+","+DD+","+EE+FF+",M,"+GG+","+II+"*7f"+ZZ;

  qDebug()<< gga;
}

void GGA::updateGPGGA()
{
  QString gpgga = "$GPGGA,"+QString("%1%2%3")
         .arg(ui->spinBox->value(),2,10,QChar('0'))
          .arg(ui->spinBox_2->value(),2,10,QChar('0'))
          .arg(ui->spinBox_3->value(),2,10,QChar('0'))+
          ","+
          QString::number(ui->spinBox_10->value()) +
          QString::number(ui->doubleSpinBox_3->value(),'f',2) +","+
          ui->textEdit->toPlainText()+","+
          QString::number(ui->spinBox_11->value()) +
          QString::number(ui->doubleSpinBox_4->value(),'f',2)+","+
         ui->textEdit_2->toPlainText()+","+
          QString::number(ui->spinBox_4->value())+
          QString::number(ui->spinBox_5->value())+
          ",M,"+
          QString::number(ui->spinBox_6->value())+
          QString::number(ui->spinBox_7->value())+
          ",M,"+
          QString::number(ui->spinBox_8->value())+
          QString::number(ui->spinBox_9->value())+"*7f";

          qDebug() << gpgga;
}

void GGA::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Canceled","");
}
void GGA::sendGGA(){
    QString sentence="$GPGGA,"+QString("%1%2%3")
            .arg(ui->spinBox->value(),2,10,QChar('0'))
            .arg(ui->spinBox_2->value(),2,10,QChar('0'))
            .arg(ui->spinBox_3->value(),2,10,QChar('0'))+
            ","+
            QString::number(ui->spinBox_10->value()) +
            QString::number(ui->doubleSpinBox_3->value(),'f',2) +","+
            ui->textEdit->toPlainText()+","+
            QString::number(ui->spinBox_11->value()) +
            QString::number(ui->doubleSpinBox_4->value(),'f',2)+","+
            ui->textEdit_2->toPlainText()+","+
            QString::number(ui->spinBox_4->value())+
            QString::number(ui->spinBox_5->value())+
            ",M,"+
            QString::number(ui->spinBox_6->value())+
            QString::number(ui->spinBox_7->value())+
            ",M,"+
            QString::number(ui->spinBox_8->value())+
            QString::number(ui->spinBox_9->value())+"*7f";



    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 4000);

    qDebug() << sentence;
    emit sendSentence(sentence);

    QByteArray data = sentence.toUtf8();

    udpSocket->writeDatagram(sentence.toUtf8(),
                             QHostAddress("127.0.0.1"),
                             45454);
}

void GGA::updatePosition(int latDD, double latMM,
                         int lonDD, double lonMM)
{
    ui->spinBox->setValue(latDD);
    ui->doubleSpinBox_3->setValue(latMM);

    ui->spinBox_2->setValue(lonDD);
    ui->doubleSpinBox_4->setValue(lonMM);
}

void GGA::on_pushButton_3_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void GGA::on_pushButton_4_clicked()
{
      if(timer->isActive())
      timer->stop();
      qDebug() << "OFF PRESSED - Timer Stopped";
}


