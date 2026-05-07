#include "AIS.h"
#include "ui_AIS.h"
#include "GPS/AIS.h"
#include <QDebug>

AIS::AIS(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AIS)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &AIS::on_Confirm_AIS_clicked);
    timer->setInterval(1000);

    udpSocket = new QUdpSocket(this);
}

AIS::~AIS()
{
    delete ui;
}

void AIS::on_AIS_customContextMenuRequested(const QPoint &pos)
{}

void AIS::on_pushButton_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void AIS::on_pushButton_2_clicked()
{
    if(timer->isActive())
        timer->stop();

    qDebug() << "ON PRESSED - Timer Stoped";
}

void AIS::on_Confirm_AIS_clicked()
{
    // Read values from UI
    int totalMsg   = ui->Message_SB->value();
    int sentenceNo = ui->Number_SB->value();
    int identifier = ui->Identifier_SB->value();
    QString channel = ui->comboBox->currentText();
    int fillBits   = ui->Bits_SB->value();

    // Create AIS string
    QString aisData = QString("$__AIS,%1,%2,%3,%4,%5")
            .arg(totalMsg)
            .arg(sentenceNo)
            .arg(identifier)
            .arg(channel)
            .arg(fillBits);

    qDebug() << "" << aisData;

    udpSocket->writeDatagram(aisData.toUtf8(),
        QHostAddress::LocalHost,45454
    );
}

QString AIS::calculateChecksum(const QString &sentence)
{
    int checksum = 0;

    for (int i = 1; i < sentence.length(); i++)
    {
        checksum ^= sentence[i].toLatin1();
    }

    return QString("*%1").arg(checksum, 2, 16, QLatin1Char('0')).toUpper();
}
