#include "GLL.h"
#include "ui_GLL.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include <QSpinBox>
GLL::GLL(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GLL)
{
    ui->setupUi(this);

    init();
    load();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &GLL::on_pushButton_clicked);
    timer->setInterval(1000);
}
GLL::~GLL()
{
    delete ui;
}
void GLL::on_pushButton_clicked()
{

  QString aa = ui->spinBox_4->text();
  QString bb = ui->doubleSpinBox_3->text();
  QString cc = ui->textEdit->toPlainText();
  QString dd = ui->spinBox_11->text();
  QString ee = ui->doubleSpinBox_4->text();
  QString ff = ui->textEdit_2->toPlainText();
  QString AA = QString("%1").arg(ui->spinBox->value(), 2, 10, QChar('0'));
  QString BB = QString("%1").arg(ui->spinBox_2->value(), 2, 10, QChar('0'));
  QString CC = QString("%1").arg(ui->spinBox_3->value(), 2, 10, QChar('0'));
  QString XX = ui->comboBox_2->currentText();
  QString YY = ui->comboBox_3->currentText();
  QString ZZ = ui->comboBox_4->currentText();


  QString gll = "$__GLL," +aa+bb+","+XX+","+dd+ee+","+YY+","+AA+BB+CC+","+ZZ+"*itm";
  qDebug()<<gll;
}

void GLL::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Cleared","");
}

void GLL::on_comboBox_currentIndexChanged(int index)
{
}
void GLL::init()
{
    ui->comboBox->clear();

    for (int i = 0;i < 10;i++) {
     ui->comboBox->addItem("Item number" + QString::number(i));
    }
}

void GLL::load()
{
 QSettings settings;
 QVariant value = settings.value("settings",0);

 bool ok;
 int index = value.toInt(&ok);


 if(index < ui->comboBox->count())
 {

 }
 else
 {
     ui->comboBox->setCurrentIndex(index);
 }
}

void GLL::updatePosition(int latDD, double latMM,
                         int lonDD, double lonMM)
{
    ui->spinBox->setValue(latDD);
    ui->doubleSpinBox_3->setValue(latMM);

    ui->spinBox_2->setValue(lonDD);
    ui->doubleSpinBox_4->setValue(lonMM);
}

void GLL::on_pushButton_3_clicked()
{
    if(!timer->isActive())
        timer->start();

    qDebug() << "ON PRESSED - Timer Started";
}

void GLL::on_pushButton_4_clicked()
{
    if(timer->isActive())
    timer->stop();
    qDebug() << "OFF PRESSED - Timer Stopped";
}
