#include "ECHO.h"
#include "ui_ECHO.h"
#include "QDebug"
#include <mainwindow.h>

ECHO::ECHO(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ECHO)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &ECHO::on_LOG_confirmn_clicked);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);
}

ECHO::~ECHO()
{
    delete ui;
}
void ECHO::on_LOG_confirmn_clicked()
{

    double depth = ui->Depth_spin->value();
    QString unit = ui->Depth_combo->currentText();

    QString channel;

    if (ui->radioButton_19->isChecked())
        channel = "OFF";
    else if (ui->radioButton_20->isChecked())
        channel = "GARBLE1";
    else if (ui->radioButton_21->isChecked())
        channel = "GARBLE2";

    // Create message
    QString echoMsg = QString("$__ECHO,%1,%2,%3")
                        .arg(depth)
                        .arg(unit)
                        .arg(channel);

    qDebug()<<echoMsg;

    udpSocket->writeDatagram(echoMsg.toUtf8(), QHostAddress::LocalHost, 45454);
}
void ECHO::on_pushButton_clicked()
{
    if(!timer->isActive())
        timer->start();
    qDebug()<<"ON PRESSED - Start Timer";
}
void ECHO::on_pushButton_2_clicked()
{
    if(timer->isActive())
        timer->stop();
    qDebug()<<"ON PRESSED - Stop Timer";
}
