#ifndef GYRO_H
#define GYRO_H

#include <QFrame>
#include <QTimer>
#include <QUdpSocket>

namespace Ui {
class GYRO;
}

class GYRO : public QFrame
{
    Q_OBJECT

public:
    explicit GYRO(QWidget *parent = nullptr);
    ~GYRO();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();



    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::GYRO *ui;
    QTimer *timer;

    QUdpSocket *udpSocket;


signals:
    void sigToUpdateCourse(double speed);
};

#endif // GYRO_H
