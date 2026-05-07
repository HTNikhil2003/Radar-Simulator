#include "IBS.h"
#include "ui_IBS.h"
#include "QDebug"
#include "QString"
#include <GPS/IBS.h>
#include <QUdpSocket>

IBS::IBS(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::IBS)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &IBS::updateTrackPos);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);

    ownPos.setX(77);
    ownPos.setY(12);
}

IBS::~IBS()
{
    delete ui;
}
void IBS::on_radioButton_clicked()
{
    ui->radioButton->setText("OFF");
}

void IBS::on_pushButton_clicked()
{
    ui->groupBox->isChecked();
}
void IBS::on_pushButton_2_clicked()
{}

void IBS::on_Confirm_PB_clicked()
{

    double lat0 = qDegreesToRadians(ownPos.y()); // latitude
    double lon0 = qDegreesToRadians(ownPos.x()); // longitude

    double bearing = qDegreesToRadians(ui->doubleSpinBox_9->value());
    double d = ui->spinBox_8->value(); // meters

    double R = 6371000.0; // Earth radius

    double lat = asin( sin(lat0)*cos(d/R) +
                       cos(lat0)*sin(d/R)*cos(bearing) );

    double lon = lon0 + atan2( sin(bearing)*sin(d/R)*cos(lat0),
                               cos(d/R) - sin(lat0)*sin(lat) );

    // convert back to degrees
    double newLat = qRadiansToDegrees(lat);
    double newLon = qRadiansToDegrees(lon);

    IBStrackPos.setY(newLat); // latitude
    IBStrackPos.setX(newLon); // longitude

    qDebug()<<"newPos"<<IBStrackPos.x()<<IBStrackPos.y();

}

void IBS::on_radioButton_14_clicked()
{
    ui->radioButton_14->text();
}

void IBS::on_radioButton_15_clicked()
{
    ui->radioButton_15->text();
}

void IBS::on_radioButton_16_clicked()
{
    ui->radioButton_16->text();
}

void IBS::on_radioButton_17_clicked()
{
    ui->radioButton_17->text();
}

void IBS::on_pushButton_4_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void IBS::on_pushButton_6_clicked()
{
    if(timer->isActive())
    timer->stop();
    qDebug() << "OFF PRESSED - Timer Stopped";
}

void IBS::on_pushButton_5_clicked()
{

}

void IBS::on_spinBox_9_valueChanged(const QString &arg1)
{

}

void IBS::updateTrackPos()
{
    double lat0 = qDegreesToRadians(IBStrackPos.y());
    double lon0 = qDegreesToRadians(IBStrackPos.x());

    double bearing = qDegreesToRadians(static_cast<double>(ui->spinBox_11->value()));

    double speed = ui->spinBox_10->value();
    double dt = 1.0;
    double d = speed * dt;

    double R = 6371000.0;

    double lat = asin( sin(lat0)*cos(d/R) +
                       cos(lat0)*sin(d/R)*cos(bearing) );

    double lon = lon0 + atan2( sin(bearing)*sin(d/R)*cos(lat0), cos(d/R) - sin(lat0)*sin(lat) );

//    if (lon > M_PI) lon -= 2*M_PI;
//    if (lon < -M_PI) lon += 2*M_PI;

    IBStrackPos.setY(qRadiansToDegrees(lat));
    IBStrackPos.setX(qRadiansToDegrees(lon));

    double latOwn = qDegreesToRadians(ownPos.y());
    double lonOwn = qDegreesToRadians(ownPos.x());

    double dLat = lat - latOwn;
    double dLon = lon - lonOwn;

    double a = sin(dLat/2)*sin(dLat/2) +
               cos(latOwn)*cos(lat) *
               sin(dLon/2)*sin(dLon/2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    trackrange = R * c;

    double y = sin(lon - lonOwn) * cos(lat);
    double x = cos(latOwn)*sin(lat) - sin(latOwn)*cos(lat)*cos(lon - lonOwn);

    double bearingFromOwn = atan2(y, x);

    double bearingDeg = qRadiansToDegrees(bearingFromOwn);

    if (bearingDeg < 0)
        bearingDeg += 360.0;

        QString ttm = QString("$__TTM,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17")
            .arg(ui->spinBox_7->value())
            .arg(trackrange)
            .arg(ui->comboBox_6->currentText())
            .arg(bearingDeg)
            .arg(ui->spinBox_10->value())
            .arg(ui->spinBox_11->value())
            .arg(ui->comboBox_5->currentText())
            .arg(ui->spinBox_12->value())
            .arg(ui->spinBox_13->value())
            .arg(ui->comboBox_4->currentText())
            .arg(ui->comboBox->currentText())
            .arg(ui->comboBox_2->currentText())
            .arg(ui->spinBox_15->value())
            .arg(ui->spinBox_16->value())
            .arg(ui->spinBox_14->value())
            .arg(ui->comboBox_3->currentText())
            .arg("A");

        qDebug()<< "ownposss"<<ownPos.x()<<ownPos.y();

        qDebug()<<ttm;

        udpSocket->writeDatagram(ttm.toUtf8(), QHostAddress::LocalHost, 45454);

}

void IBS::slotToSetOwnPosition(double latitude, double longitude)
{

   // qDebug()<< "ownposss123"<<ownPos.x()<<ownPos.y();

    ownPos.setX(longitude);
    ownPos.setY(latitude);
}



double IBS::convertToNautical(double value, QString unit)
{
    if(unit == "N")
        return value / 1.852;
    else if(unit == "K")
        return value * 3.6;
    else if(unit == "S")
        return value * 2.2369;

    return value;
}


void IBS::on_spinBox_12_valueChanged(int value)
{
    QString unit = ui->comboBox_4->currentText();

    double convertedNM = convertToNautical(value, unit);

}


void IBS::on_comboBox_4_currentTextChanged(const QString &unit)
{
    int value = ui->spinBox_12->value();

    double convertedNM = convertToNautical(value, unit);

}
