#ifndef GGA_H
#define GGA_H

#include <QFrame>
#include <QTimer>
#include <QUdpSocket>

namespace Ui {
class GGA;
}

class GGA : public QFrame
{
    Q_OBJECT

public:
    explicit GGA(QWidget *parent = nullptr);
    ~GGA();

public slots:
    void updatePosition(int latDD, double latMM,int lonDD, double lonMM);

private:
    QTimer *timer;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

     void updateGPGGA();

     void sendGGA();

     void on_pushButton_3_clicked();

     void on_pushButton_4_clicked();

private:
    QUdpSocket *udpSocket;

     //void saveOutputGGA(const QString &sentence);

signals:
    void sendSentence(QString sentence);

private:
    Ui::GGA *ui;
};

#endif // GGA_H
