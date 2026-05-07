#ifndef IBS_H
#define IBS_H

#include <QFrame>
#include <QTimer>
#include <QUdpSocket>
#include <qmath.h>
namespace Ui {
class IBS;
}

class IBS : public QFrame
{
    Q_OBJECT

public:
    explicit IBS(QWidget *parent = nullptr);
    ~IBS();

public slots:
    void slotToSetOwnPosition(double latitude, double longitude);
private:
    QTimer *timer;

     QPointF ownPos;
     QPointF IBStrackPos;

private slots:
    void on_radioButton_clicked();
//    void on_radioButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_Confirm_PB_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_16_clicked();

    void on_radioButton_17_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_spinBox_9_valueChanged(const QString &arg1);

//    void updateTargetPosition();
    void updateTrackPos();




    void on_spinBox_12_valueChanged(int value);


    void on_comboBox_4_currentTextChanged(const QString &unit);


private:
    Ui::IBS *ui;
    QUdpSocket *udpSocket;
    double trackrange;


    double convertToNautical(double value, QString unit);
};

#endif // IBS_H
