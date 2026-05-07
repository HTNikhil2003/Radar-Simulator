#ifndef ZDA_H
#define ZDA_H

#include <QFrame>
#include <QTimer>

namespace Ui {
class ZDA;
}

class ZDA : public QFrame
{
    Q_OBJECT

public:
    explicit ZDA(QWidget *parent = nullptr);
    ~ZDA();

public:
    int getHH();
    int getMM();
    int getSS();

private:
    QTimer *timer;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ZDA *ui;
};

#endif // ZDA_H
