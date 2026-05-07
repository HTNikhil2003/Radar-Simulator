#include "CRMCView.h"
#include "ui_CRMCView.h"
#include <QMessageBox>
#include <qradiobutton.h>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include "qspinbox.h"
#include <QtNetwork/QUdpSocket>
#include "qdatetime.h"
#include "QtMath"

CRMCView::CRMCView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CRMCView)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &CRMCView::updateGPRMC);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);
}
CRMCView::~CRMCView()
{
    delete ui;
}

void CRMCView::on_radioButton_clicked()
    {
        if(ui->radioButton->isChecked()) {}
    }
void CRMCView::on_radioButton_2_clicked()
{
    if(ui->radioButton_2->isChecked()){}
}
void CRMCView::on_radioButton_3_clicked()
{
    if(ui->radioButton_3->isChecked()){}
}
void CRMCView::on_radioButton_4_clicked()
{
    if(ui->radioButton_4->isChecked()){}
}
void CRMCView::on_pushButton_clicked()
{
    QString hh = ui->spinBox->text();
    QString mm = ui->spinBox_2->text();
    QString ss = ui->doubleSpinBox_3->text();
    QString SS = ui->doubleSpinBox_4->text();
    QString HH = QString("%1").arg(ui->spinBox_3->value(), 2, 10, QChar('0'));
    QString MM = QString("%1").arg(ui->spinBox_4->value(), 2, 10, QChar('0'));
    QString sec = QString("%1").arg(ui->spinBox_8->value(), 2, 10, QChar('0'));
    QString Knots = ui->spinBox_5->text();
    QString deg = ui->spinBox_6->text();
    QString Deg = ui->spinBox_7->text();
    //QString sec = ui->spinBox_8->text();
    QString NN = ui->textEdit->toPlainText();
    QString EE = ui->textEdit_2->toPlainText();
    QString XX = ui->comboBox->currentText();
    QString YY = ui->comboBox_2->currentText();
    QString AA = ui->comboBox_3->currentText();
    QString BB = ui->comboBox_4->currentText();

    QDate date = ui->dateEdit->date();
    QString dateStr = date.toString("ddMMyy");
    QString time = "$GPRMC,"+ HH + MM + sec + ","+BB+","+hh + ss +","+ XX +"," +mm +SS +
            +","+YY+"," + Knots +","+ deg + "," +dateStr + "," + Deg + ","+AA+","+"A*1e";
    qDebug()<<time;

    int latDD = ui->spinBox->value();
        double latMM = ui->doubleSpinBox_3->value();
        QString latDir = ui->comboBox->currentText();

        int lonDD = ui->spinBox_2->value();
        double lonMM = ui->doubleSpinBox_4->value();
        QString lonDir = ui->comboBox_2->currentText();

        QString lat = QString("%1%2").arg(latDD, 2, 10, QChar('0')).arg(latMM, 0, 'f', 2);

        QString lon = QString("%1%2").arg(lonDD, 3, 10, QChar('0')).arg(lonMM, 0, 'f', 2);

        QString rmc = QString("$__RMC,LAT:%1,%2,LON:%3,%4")
                        .arg(lat)
                        .arg(latDir)
                        .arg(lon)
                        .arg(lonDir);

}

void CRMCView::updateGPRMC()
{
    double latDeg = ui->spinBox->value();
    double latMin = ui->doubleSpinBox_3->value();

    double lonDeg = ui->spinBox_2->value();
    double lonMin = ui->doubleSpinBox_4->value();


    double lat = latDeg + (latMin / 60);
    double lon = lonDeg + (lonMin / 60);

    if (ui->comboBox->currentText() == "S")lat = -lat;

    if (ui->comboBox_2->currentText() == "W")lon = -lon;


    double speed = OwnShipSpeed;   // knots
    double course = OwnShipCourse; // degrees

    double dt = 1.0; // seconds

    // Convert
    double bearing = qDegreesToRadians(course);
    double latRad = qDegreesToRadians(lat);
    double lonRad = qDegreesToRadians(lon);

    // Convert speed to meters/sec
    double speed_mps = speed * 1852.0 / 3600.0;

    // Distance traveled
    double d = speed_mps * dt;

    // Earth radius
    double R = 6371000.0;

    // New latitude
    double newLat = asin( sin(latRad) * cos(d / R) +
                          cos(latRad) * sin(d / R) * cos(bearing) );

    // New longitude
    double newLon = lonRad + atan2( sin(bearing) * sin(d / R) * cos(latRad),
                                   cos(d / R) - sin(latRad) * sin(newLat) );

    // Convert back to degrees
    lat = qRadiansToDegrees(newLat);
    lon = qRadiansToDegrees(newLon);





    int newLatDeg = static_cast<int>(lat);
    double newLatMin = (lat - newLatDeg) * 60.0;

    int newLonDeg = static_cast<int>(lon);
    double newLonMin = (lon - newLonDeg) * 60.0;

    ui->spinBox->setValue(newLatDeg);
    ui->doubleSpinBox_3->setValue(newLatMin);

    ui->spinBox_2->setValue(newLonDeg);
    ui->doubleSpinBox_4->setValue(newLonMin);

    QString gprmc = "$GPRMC," + QString::number(0)+ "\n" +
            "LAT : "+QString::number(lat, 'f', 6)  + "\n" +
            "LON: "+QString::number(lon, 'f', 6) ;

    qDebug() << gprmc;

    emit sigToSetOwnPosition(lat,lon);

    udpSocket->writeDatagram(gprmc.toUtf8(), QHostAddress::LocalHost, 45454);
}

void CRMCView::on_pushButton_2_clicked()
{
}
void CRMCView::on_pushButton_3_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void CRMCView::on_pushButton_4_clicked()
{
    if(timer->isActive())
    timer->stop();
    qDebug() << "OFF PRESSED - Timer Stopped";
}

void CRMCView::slotToUpdateSpeed(double speed)
{
    qDebug() << "speedddd"<<speed;

    OwnShipSpeed=speed;

}

void CRMCView::slotToUpdateCourse(double course)
{
    OwnShipCourse=course;

    qDebug() << "course"<<course;
}

