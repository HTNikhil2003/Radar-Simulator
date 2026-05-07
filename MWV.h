#ifndef MWV_H
#define MWV_H

#include <QFrame>
#include <QTimer>

namespace Ui {
class MWV;
}

class MWV : public QFrame
{
    Q_OBJECT

public:
    explicit MWV(QWidget *parent = nullptr);
    ~MWV();

private slots:
    void on_MWV_confirm_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MWV *ui;
    QString conditionStr(double angle, QString ref, double speed, QString unit, QString status);
    QTimer *timer;

};

#endif // MWV_H
