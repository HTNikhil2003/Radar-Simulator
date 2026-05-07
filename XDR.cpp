#include "XDR.h"
#include "ui_XDR.h"
#include "QDebug"
#include "mainwindow.h"

XDR::XDR(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::XDR)
{
    ui->setupUi(this);

    timer = new QTimer (this);
    connect(timer,&QTimer::timeout,this, &XDR::on_XDR_confirm_clicked);
    timer->setInterval(1000);
}

XDR::~XDR()
{
    delete ui;
}

void XDR::on_XDR_confirm_clicked()
{
    QString type = ui->cb_TranType->currentText();
    double val = ui->sp_TranMeasurement->value();
    QString id = ui->cb_Tid->currentText();
    QString unit;
    if(type == "C") unit = "C";
    else if (type == "P") unit = "B";
    else if (type == "H") unit = "P";
    else if (type == "F") unit = "H";
    else if (type == "A") unit = "D";
    else if (type == "D") unit = "M";
    else if (type == "R") unit = "l";
    else if (type == "I") unit = "A";
    else if (type == "U") unit = "V";


    QString answer = QString("WIXDR,%1,%2,%3,%4")
                         .arg(type)
                         .arg(val,0,'f',1)
                         .arg(unit)
                         .arg(id);

    QString checksum = MainWindow::calculateChecksum(answer);
    QString finalNMEA = "$" + answer + "*" + checksum;
    qDebug()<< "XDR data" << finalNMEA;
}

void XDR::on_cb_Unit_currentTextChanged(const QString &selection)
{
    if(selection == "Air Temp"){
        ui->cb_TranType->setCurrentText("C");
        ui->cb_Tid->setCurrentText("1");
    }

    else if(selection == "Relative Humidity"){
        ui->cb_TranType->setCurrentText("H");
        ui->cb_Tid->setCurrentText("2");
    }

    else if(selection == "Visibility"){
        ui->cb_TranType->setCurrentText("D");
        ui->cb_Tid->setCurrentText("5");
    }

    else if(selection == "Salinity"){
        ui->cb_TranType->setCurrentText("L");
    }

    else if(selection == "Angular Displacement"){
        ui->cb_TranType->setCurrentText("A");
    }
    else if(selection.trimmed() == "Linear Displacement"){
        ui->cb_TranType->setCurrentText("D");
    }
    else if(selection.trimmed() == "Dew Point"){
        ui->cb_TranType->setCurrentText("C");
        ui->cb_Tid->setCurrentText("4");
    }
    else if(selection == "Frequency"){
        ui->cb_TranType->setCurrentText("F");
    }

    else if(selection == "Air Pressure"){
        ui->cb_TranType->setCurrentText("P");
    }

    else if(selection == "Flow Rate"){
        ui->cb_TranType->setCurrentText("R");
    }

    else if(selection == "Tachometer"){
        ui->cb_TranType->setCurrentText("T");
    }

    else if(selection == "Volume"){
        ui->cb_TranType->setCurrentText("V");
    }

    else if(selection == "Generic"){
        ui->cb_TranType->setCurrentText("G");
    }

    else if(selection.trimmed() == "Current"){
        ui->cb_TranType->setCurrentText("I");
    }

    else if(selection == "Voltage"){
        ui->cb_TranType->setCurrentText("U");
    }

    else if(selection == "Switch / Valve"){
        ui->cb_TranType->setCurrentText("S");
    }
}

void XDR::on_pushButton_clicked()
{
    if(!timer->isActive())
        timer->start();
    qDebug()<<"ON PRESSED - Start Timer";
}

void XDR::on_pushButton_3_clicked()
{
    if(timer->isActive())
        timer->stop();
    qDebug()<<"ON PRESSED - Stop Timer";
}
