#include "LOG.h"
#include "ui_LOG.h"
#include "QDebug"

LOG::LOG(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LOG)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &LOG::on_LOG_confirmn_clicked);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);
}

LOG::~LOG()
{
    delete ui;
}

void LOG::on_LOG_confirmn_clicked()
{
        // WATER SPEED
        double waterLong = ui->Water_Longitude->value();
        double waterTrans = ui->Water_Transverse->value();
        QString waterStatus = ui->rb_Water_Valid->isChecked() ? "A" : "V";

        // GROUND SPEED
        double groundLong = ui->Ground_Longitude->value();
        double groundTrans = ui->Ground_Transverse->value();
        QString groundStatus = ui->rb_Ground_Valid->isChecked() ? "A" : "V";




        emit sigToUpdateSpeed(groundLong);



        // CREATE LOG STRING
        QString logMsg = QString("$__LOG,%1,%2,%3,%4,%5,%6")
                            .arg(waterLong)
                            .arg(waterTrans)
                            .arg(waterStatus)
                            .arg(groundLong)
                            .arg(groundTrans)
                            .arg(groundStatus);

        qDebug() << "" << logMsg;

        udpSocket->writeDatagram(logMsg.toUtf8(), QHostAddress::LocalHost, 45454);
}

void LOG::GroundSpd(double)
{
    //double groundLong = ui->Ground_Longitude->value();
}

void LOG::on_pushButton_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void LOG::on_pushButton_2_clicked()
{
    if(timer->isActive())
        timer->stop();

   // ui->Ground_Longitude->setValue(0);

    qDebug() << "ON PRESSED - Timer Stoped";
}

void LOG::on_Ground_Longitude_valueChanged(double arg1)
{
   // emit sigToUpdateSpeed(arg1);

    //ui->Ground_Longitude->update();
}

void LOG::on_LOG_cancel_clicked()
{

        // Stop timer if running
        if (timer->isActive())
            timer->stop();

        // Reset WATER SPEED
        ui->Water_Longitude->setValue(0);
        ui->Water_Transverse->setValue(0);
        ui->rb_Water_Valid->setChecked(false);
        ui->rb_Water_Invalid->setChecked(false);

        // Reset GROUND SPEED
        ui->Ground_Longitude->setValue(0);
        ui->Ground_Transverse->setValue(0);
        ui->rb_Ground_Valid->setChecked(false);
        ui->rb_Ground_Invalid->setChecked(false);

        qDebug() << "LOG Cancelled";

}

