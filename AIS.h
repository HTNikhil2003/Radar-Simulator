#ifndef AIS_H
#define AIS_H

#include <QFrame>
#include <QTimer>
#include <QUdpSocket>

namespace Ui {
class AIS;
}

class AIS : public QFrame
{
    Q_OBJECT

public:
    explicit AIS(QWidget *parent = nullptr);
    ~AIS();

private:
    QTimer *timer;

    QString calculateChecksum(const QString &sentence);

private slots:
    void on_AIS_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Confirm_AIS_clicked();

private:
    Ui::AIS *ui;

    QUdpSocket *udpSocket;
};

#endif // AIS_H
