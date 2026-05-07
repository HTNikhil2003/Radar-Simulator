#include "GYRO.h"
#include "ui_GYRO.h"
#include "QDebug"

GYRO::GYRO(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GYRO)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &GYRO::on_pushButton_clicked);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);

}

GYRO::~GYRO()
{
    delete ui;
}

void GYRO::on_pushButton_clicked()
{
    double heading = ui->doubleSpinBox->value();




    emit sigToUpdateCourse(heading);




    QString gyro = QString("$GYRO,%1,T*F").arg(heading);

    qDebug() << gyro;

    udpSocket->writeDatagram(gyro.toUtf8(), QHostAddress::LocalHost, 45454);
}

void GYRO::on_pushButton_3_clicked()
{
    if(!timer->isActive())
        timer->start();
    qDebug()<<"ON PRESSED - Timer Started";
}

void GYRO::on_pushButton_4_clicked()
{
    if(timer->isActive())
        timer->stop();
    qDebug()<<"ON PRESSED - Timer Stoped";
}

void GYRO::on_doubleSpinBox_valueChanged(double arg1)
{
  //  emit sigToUpdateCourse(arg1);

}
