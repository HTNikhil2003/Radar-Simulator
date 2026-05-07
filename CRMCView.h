#ifndef CRMCVIEW_H
#define CRMCVIEW_H
#include <QFrame>
#include <QtNetwork/QUdpSocket>
#include <QTimer>
#include <QUdpSocket>

namespace Ui {
class CRMCView;
}

class CRMCView : public QFrame
{
    Q_OBJECT

public:
    explicit CRMCView(QWidget *parent = nullptr);
    ~CRMCView();

private:
    QTimer *timer;

    double OwnShipSpeed;

    double OwnShipCourse;

signals:
    void positionChanged(int latDD, double latMM,int lonDD, double lonMM);
    void sigToSetOwnPosition(double,double);

public slots:
//    void m_readyRead();

    void slotToUpdateSpeed(double speed);

    void slotToUpdateCourse(double speed);

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void updateGPRMC();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    // void on_spinBox_5_valueChanged(int value);

private:
    Ui::CRMCView *ui;

    QUdpSocket *udpSocket;
};

#endif // CRMCVIEW_H
