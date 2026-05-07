#ifndef ECHO_H
#define ECHO_H

#include <QFrame>
#include <QTimer>
#include <QUdpSocket>

namespace Ui {
class ECHO;
}

class ECHO : public QFrame
{
    Q_OBJECT

public:
    explicit ECHO(QWidget *parent = nullptr);
    ~ECHO();

private slots:
    void on_LOG_confirmn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ECHO *ui;
    QTimer *timer;

    QUdpSocket *udpSocket;
};

#endif // ECHO_H
