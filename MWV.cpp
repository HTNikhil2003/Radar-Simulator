#include "MWV.h"
#include "ui_MWV.h"
#include "QDebug"
#include "mainwindow.h"

MWV::MWV(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MWV)
{
    ui->setupUi(this);

    timer = new QTimer (this);
    connect(timer, &QTimer::timeout,this,&MWV::on_MWV_confirm_clicked);
    timer->setInterval(1000);
}

MWV::~MWV()
{
    delete ui;
}

QString MWV::conditionStr(double water_Angle, QString reference, double water_Speed, QString unit, QString status)
{
    QString answer = QString("WIMWV,%1,%2,%3,%4,%5")
        .arg(water_Angle, 3, 'f', 1)
        .arg(reference)
        .arg(water_Speed, 0, 'f', 1)
        .arg(unit)
        .arg(status);

    QString checksum = MainWindow::calculateChecksum(answer);
    return "$" + answer + "*" +checksum ;
}

void MWV::on_MWV_confirm_clicked()
{
    double water_Angle = ui->waterAngle->value();
    double water_Speed = ui->waterSpeed->value();

    QString unit = "Kn";
    if(ui->rb_kmph->isChecked()) unit = "Km";
    else if(ui->rb_mps->isChecked()) unit = "M";

    QString status = "A";
    if(ui->status_Invalid->isChecked()){
        status = "V";
    }

    if (ui->wind_RefRelative->isChecked())
    {
        QString packet = conditionStr(water_Angle,"R",water_Speed,unit,status);
        qDebug() << "MWV Relative" << packet;
    }
    else
    {
        QString packetTrue = conditionStr(water_Angle,"T",water_Speed,unit,status);
        qDebug()<< "MWV True:" << packetTrue;
        QString packetRel = conditionStr(water_Angle,"R",water_Speed,unit,status);
        qDebug()<<"MWV Relative: "<< packetRel;
    }
}

void MWV::on_pushButton_clicked()
{
    if(!timer->isActive())
        timer->start();
    qDebug()<<"ON TIMER - Start Timer";
}

void MWV::on_pushButton_3_clicked()
{
    if(timer->isActive())
        timer->stop();
    qDebug()<<"OFF TIMER - Stop Timer";
}
