#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSpinBox>
#include <QHostAddress>
#include <QByteArray>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QUdpSocket>
#include <QPushButton>
#include <QTextEdit>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objTacticalScene = new TacticalScene();
    objTacticalView = new TacticalView(this);

    objTacticalView->setScene(objTacticalScene);
    objTacticalView->setBackgroundBrush(Qt::black);

    btnShowRMC = new QPushButton("GPS", this);
    btnShowRMC->setFixedSize(120, 30);

    txtRMC = new QTextEdit(this);
    txtRMC->setReadOnly(true);
    txtRMC->setFixedSize(200, 70);
    txtRMC->hide();

    btnCloseRMC = new QPushButton("x", this);
    btnCloseRMC->setFixedSize(25, 25);
    btnCloseRMC->hide();

    btnShowLOG = new QPushButton("LOG", this);
    btnShowLOG->setFixedSize(120, 30);

    txtLOG = new QTextEdit(this);
    txtLOG->setReadOnly(true);
    txtLOG->setFixedSize(200, 70);
    txtLOG->hide();

    btnCloseLOG = new QPushButton("x", this);
    btnCloseLOG->setFixedSize(25, 25);
    btnCloseLOG->hide();

    btnShowECHO = new QPushButton("ECHO", this);
    btnShowECHO->setFixedSize(120, 30);

    txtECHO = new QTextEdit(this);
    txtECHO->setReadOnly(true);
    txtECHO->setFixedSize(200, 70);
    txtECHO->hide();

    btnCloseECHO = new QPushButton("x", this);
    btnCloseECHO->setFixedSize(25, 25);
    btnCloseECHO->hide();

    btnShowAIS = new QPushButton("AIS", this);
    btnShowAIS->setFixedSize(120, 30);

    txtAIS = new QTextEdit(this);
    txtAIS->setReadOnly(true);
    txtAIS->setFixedSize(200, 70);
    txtAIS->hide();

    btnCloseAIS = new QPushButton("x", this);
    btnCloseAIS->setFixedSize(25, 25);
    btnCloseAIS->hide();

    btnShowIBS = new QPushButton("IBS", this);
    btnShowIBS->setFixedSize(120, 30);

    txtIBS = new QTextEdit(this);
    txtIBS->setReadOnly(true);
    txtIBS->setFixedSize(200, 70);
    txtIBS->hide();

    btnCloseIBS = new QPushButton("x", this);
    btnCloseIBS->setFixedSize(25, 25);
    btnCloseIBS->hide();

    btnShowGYRO = new QPushButton ("GYRO", this);
    btnShowGYRO->setFixedSize(120,30);

    txtGYRO = new QTextEdit (this);
    txtGYRO->setReadOnly(true);
    txtGYRO->setFixedSize(200, 70);
    txtGYRO->hide();

    btnCloseGYRO = new QPushButton("x", this);
    btnCloseGYRO->setFixedSize(25, 25);
    btnCloseGYRO->hide();


    txtRange = new QTextEdit(this);
    txtRange->setReadOnly(true);
    txtRange->setFixedSize(200, 50);
    txtRange->setText("Range: 0");

    txtBearing = new QTextEdit(this);
    txtBearing->setReadOnly(true);
    txtBearing->setFixedSize(200, 50);
    txtBearing->setText("Bearing: 0°");

    txtCoords = new QTextEdit(this);
    txtCoords->setReadOnly(true);
    txtCoords->setFixedSize(250, 50);
    txtCoords->setText("");

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(txtRange);

    topLayout->addStretch();
    topLayout->addWidget(txtCoords);
    topLayout->addStretch();

    topLayout->addWidget(txtBearing);
    mainLayout->addLayout(topLayout);

    mainLayout->addWidget(objTacticalView);

    QHBoxLayout *rmcLayout = new QHBoxLayout();
    QHBoxLayout *rmcTop = new QHBoxLayout();
    rmcTop->addWidget(btnShowRMC);
    rmcTop->addWidget(btnCloseRMC);
    rmcLayout->addLayout(rmcTop);
    rmcLayout->addWidget(txtRMC);

    QHBoxLayout *logLayout = new QHBoxLayout();
    QHBoxLayout *logTop = new QHBoxLayout();
    logTop->addWidget(btnShowLOG);
    logTop->addWidget(btnCloseLOG);
    logLayout->addLayout(logTop);
    logLayout->addWidget(txtLOG);

    QHBoxLayout *echoLayout = new QHBoxLayout();
    QHBoxLayout *echoTop = new QHBoxLayout();
    echoTop->addWidget(btnShowECHO);
    echoTop->addWidget(btnCloseECHO);
    echoLayout->addLayout(echoTop);
    echoLayout->addWidget(txtECHO);

    QHBoxLayout *aisLayout = new QHBoxLayout();
    QHBoxLayout *aisTop = new QHBoxLayout();
    aisTop->addWidget(btnShowAIS);
    aisTop->addWidget(btnCloseAIS);
    aisLayout->addLayout(aisTop);
    aisLayout->addWidget(txtAIS);

    QHBoxLayout *ibsLayout = new QHBoxLayout();
    QHBoxLayout *ibsTop = new QHBoxLayout();
    ibsLayout->addWidget(btnShowIBS);
    ibsLayout->addWidget(btnCloseIBS);
    ibsLayout->addWidget(txtIBS);

    QHBoxLayout *gyroLayout = new QHBoxLayout();
    QHBoxLayout *gyroTop = new QHBoxLayout();
    gyroLayout->addWidget(btnShowGYRO);
    gyroLayout->addWidget(btnCloseGYRO);
    gyroLayout->addWidget(txtGYRO);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addLayout(rmcLayout);
    bottomLayout->addLayout(logLayout);
    bottomLayout->addLayout(echoLayout);
    bottomLayout->addLayout(aisLayout);
    bottomLayout->addLayout(ibsLayout);
    bottomLayout->addLayout(gyroLayout);

    mainLayout->addLayout(bottomLayout);

    setCentralWidget(central);

    connect(btnShowRMC, &QPushButton::clicked, this, &MainWindow::onShowRMCClicked);
    connect(btnShowLOG, &QPushButton::clicked, this, &MainWindow::onShowLOGClicked);
    connect(btnShowECHO, &QPushButton::clicked, this, &MainWindow::onShowECHOClicked);
    connect(btnShowAIS, &QPushButton::clicked, this, &MainWindow::onShowAISClicked);
    connect(btnShowIBS, &QPushButton::clicked, this, &MainWindow::onShowIBSClicked);
    connect(btnShowGYRO, &QPushButton::clicked,this, &MainWindow::onShowGYROClicked);

    connect(btnCloseRMC, &QPushButton::clicked, this, &MainWindow::onCloseRMC);
    connect(btnCloseLOG, &QPushButton::clicked, this, &MainWindow::onCloseLOG);
    connect(btnCloseECHO, &QPushButton::clicked, this, &MainWindow::onCloseECHO);
    connect(btnCloseAIS, &QPushButton::clicked, this, &MainWindow::onCloseAIS);
    connect(btnCloseIBS, &QPushButton::clicked, this, &MainWindow::onCloseIBS);
    connect(btnCloseGYRO, &QPushButton::clicked, this, &MainWindow::onCloseGYRO);

    connect(objTacticalView, &TacticalView::mouseBearingChanged,
            this, &MainWindow::updateMouseBearing);

    //connect(ui->spinBox_9, SIGNAL(valueChanged(int)),this, SLOT(updateAircraftPosition(int)));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 45454);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onShowRMCClicked()
{
    txtRMC->show();
//    txtRMC->show();
    btnCloseRMC->show();
//    txtRMC->append("");
}

void MainWindow::onShowLOGClicked()
{
    txtLOG->show();
    btnCloseLOG->show();
    //txtLOG->append("");
}

void MainWindow::onShowECHOClicked()
{
    txtECHO->show();
    btnCloseECHO->show();
   // txtECHO->append("");
}

void MainWindow::onShowAISClicked()
{
    txtAIS->show();
    btnCloseAIS->show();
    //txtAIS->append("");
}

void MainWindow::onShowIBSClicked()
{
    txtIBS->show();
    btnCloseIBS->show();
    objTacticalScene->showAircraft();
}

void MainWindow::onShowGYROClicked()
{
  txtGYRO->show();
  btnCloseGYRO->show();
}


void MainWindow::onCloseRMC()
{
    txtRMC->hide();
    btnCloseRMC->hide();
}

void MainWindow::onCloseLOG()
{
    txtLOG->hide();
    btnCloseLOG->hide();
}

void MainWindow::onCloseECHO()
{
    txtECHO->hide();
    btnCloseECHO->hide();
}

void MainWindow::onCloseAIS()
{
    txtAIS->hide();
    btnCloseAIS->hide();
}

void MainWindow::onCloseIBS()
{
    txtIBS->hide();
    btnCloseIBS->hide();
}

void MainWindow::onCloseGYRO()
{
    txtGYRO->hide();
    btnCloseGYRO->hide();
}

void MainWindow::readData()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        QString data = QString(datagram).trimmed();

        //qDebug() << "Received:" << data;

        if (data.startsWith("$GPRMC"))
                {
                    txtRMC->show();
                    txtRMC->setText(data);

                    QStringList parts = data.split(",");

                    if (parts.size() < 3)return;

                    double range = parts[1].toDouble();

                    QString bearingStr = parts[2];
                    bearingStr.remove(QRegularExpression("[^0-9.]"));

                    double bearing = bearingStr.toDouble();

                    //updateAircraft(range, bearing);
                }

        else if (data.startsWith("$__LOG"))
        {
            QStringList parts = data.split(",");

            if (parts.size() >= 7)
            {
                QString display =
                    "Water Speed:\n"
                    " Longitudinal: " + parts[1] +"\n Transverse: " + parts[2] +"\n Status: " + parts[3] +

                    "\n\nGround Speed:\n"
                    " Longitudinal: " + parts[4] + "\n Transverse: " + parts[5] +"\n Status: " + parts[6];

                txtLOG->setText(display);
            }
        }

        else if (data.startsWith("$__ECHO"))
        {
            QStringList parts = data.split(",");

            if (parts.size() >= 4)
            {
                QString display =
                    "Echo Data:\n"
                    " Depth: " + parts[1] + " " + parts[2] +
                    "\n Channel: " + parts[3];

                txtECHO->setText(display);
            }
        }
        else if (data.startsWith("$__AIS"))
        {
            QStringList parts = data.split(",");

            if (parts.size() >= 6)
            {
                QString display =
                    "AIS Data:\n"
                    " Total Messages: " + parts[1] +"\n Sentence Number: " + parts[2] +"\n Identifier: " + parts[3] +
                    "\n Channel: " + parts[4] +"\n Fill Bits: " + parts[5];

                txtAIS->setText(display);
            }
        }

        else if (data.startsWith("$__TTM"))
        {
            QStringList p = data.split(",");

            if (p.size() >= 17)
            {

                QString display =
                    "TTM (IBS Data):\n"
                    " Target No: " + p[1] +"\n Range: " + p[2] +"\n Bearing Type: " + p[3] +
                    "\n Ship Bearing: " + p[4] + "\n\n Speed: " + p[5] + "\n Course: " + p[6] +"\n Bearing Type: " + p[7] +

                    "\n\n CPA Dist: " + p[8] +"\n CPA Time: " + p[9] +"\n Units: " + p[10] +

                    "\n\n Name: " + p[11] +"\n Status: " + p[12] +

                    "\n\n Time: " + p[13] + ":" + p[14] + ":" + p[15] + "\n Type: " + p[16];

                txtIBS->setText(display);

                double range = p[2].toDouble();
                double bearing = p[4].toDouble();
qDebug()<<"bearing"<<bearing;
                updateAircraft(range, bearing);
            }
        }

        else if (data.startsWith("$GYRO"))
        {
            QStringList parts = data.split(",");

            if (parts.size() >= 2)
            {
                QString heading = parts[1];

                QString display =
                    "GYRO Data:\n"
                    " Heading: " + heading;

                txtGYRO->setText(display);

                double bearing = heading.toDouble();

               }
        }

        else if (data.startsWith("$GPGGA"))
        {
            QStringList parts = data.split(",");

            if (parts.size() < 10) return;

            txtRMC->show();
            txtRMC->setText(data);

            QString time = parts[1];

            QString latStr = parts[2];
            QString latDir = parts[3];

            QString lonStr = parts[4];
            QString lonDir = parts[5];

            QString fixQuality = parts[6];
            QString satellites = parts[7];
            QString altitude = parts[9];

            double lat = 0.0, lon = 0.0;

            if (!latStr.isEmpty())
            {
                double latVal = latStr.toDouble();
                int deg = int(latVal / 100);
                double min = latVal - (deg * 100);
                lat = deg + (min / 60.0);

                if (latDir == "S") lat = -lat;
            }

            if (!lonStr.isEmpty())
            {
                double lonVal = lonStr.toDouble();
                int deg = int(lonVal / 100);
                double min = lonVal - (deg * 100);
                lon = deg + (min / 60.0);

                if (lonDir == "W") lon = -lon;
            }

            QString display =
                "GGA Data:\n"
                " Time: " + time +
                "\n Latitude: " + QString::number(lat, 'f', 6) +
                "\n Longitude: " + QString::number(lon, 'f', 6) +
                "\n Fix: " + fixQuality +
                "\n Satellites: " + satellites +
                "\n Altitude: " + altitude + " m";

            txtRMC->setText(display);

        }

    }
}

void MainWindow::parseRMC(const QString &nmea)
{
    QStringList fields = nmea.split(",");

        if (fields.size() < 7)
            return;

        QString latStr = fields[3];
        QString lonStr = fields[5];

        double lat = latStr.toDouble();
        double lon = lonStr.toDouble();

        updateAircraft(lat, lon);
    }

    void MainWindow::updateAircraft(double range, double bearing)
    {
          double rad = qDegreesToRadians(bearing - 90);

        double scale = 0.5;

        double dx = range * scale * cos(rad);
        double dy = range * scale * sin(rad);

        QPointF center = objTacticalScene->sceneRect().center();

        double newX = center.x() + dx;
        double newY = center.y() + dy;

        objTacticalScene->updateAircraftPosition(newX, newY);

        updateObjectInfo();
    }

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (objTacticalView && objTacticalScene)
    {
        objTacticalView->fitInView(objTacticalScene->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::updateRadar(double lat, double lon)
{
    double x = lon * 5;
    double y = lat * 5;

    radarItem->setPos(x, y);
}

double MainWindow::convertToDecimal(QString val, QString dir)
{
    if (val.isEmpty()) return 0;

    double d = val.toDouble();
    int degrees = int(d / 100);
    double minutes = d - (degrees * 100);

    double result = degrees + (minutes / 60.0);

    if (dir == "S" || dir == "W")
        result = -result;

    return result;
}

void MainWindow::updateMouseBearing(double bearing)
{
    txtBearing->setText(QString("Mouse Tracking: %1°").arg(bearing, 0, 'f', 1));
}

void MainWindow::updateObjectInfo()
{
    if (!objTacticalScene) return;

    QPointF center = objTacticalScene->sceneRect().center();
    QPointF pos = objTacticalScene->getAircraftPosition();

    double dx = pos.x() - center.x();
    double dy = center.y() - pos.y();

    double range = sqrt(dx * dx + dy * dy);

    double angleRad = atan2(dx, dy);
    double bearing = qRadiansToDegrees(angleRad);

    if (bearing < 0)
        bearing += 360;

    double scale = 0.01;
    double latitude = dy * scale;
    double longitude = dx * scale;


    QString text = QString("Range: %1\nBearing: %2°\nLat: %3\nLon: %4")
                       .arg(range, 0, 'f', 2)
                       .arg(bearing, 0, 'f', 2)
                       .arg(latitude, 0, 'f', 4)
                       .arg(longitude, 0, 'f', 4);

    txtRange->setText(text);
}





