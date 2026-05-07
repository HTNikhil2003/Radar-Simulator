#ifndef GLL_H
#define GLL_H

#include <QFrame>
#include <QTimer>

namespace Ui {
class GLL;
}

class GLL : public QFrame
{
    Q_OBJECT

public:
    explicit GLL(QWidget *parent = nullptr);
    ~GLL();

public slots:
    void updatePosition(int latDD, double latMM, int lonDD, double lonMM);

private:
    QTimer *timer;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::GLL *ui;

    void init();
    void load();
};

#endif // GLL_H
