#ifndef LOG_H
#define LOG_H

#include <QFrame>
#include <QTimer>
#include <QUdpSocket>

namespace Ui {
class LOG;
}

class LOG : public QFrame
{
    Q_OBJECT

public:
    explicit LOG(QWidget *parent = nullptr);
    ~LOG();

private slots:
    void on_LOG_confirmn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void GroundSpd(double);

    void on_Ground_Longitude_valueChanged(double arg1);

    void on_LOG_cancel_clicked();


private:
    Ui::LOG *ui;
    QTimer *timer;

    QUdpSocket *udpSocket;



signals:
    void sigToUpdateSpeed(double speed);


};

#endif // LOG_H
