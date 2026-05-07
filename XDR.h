#ifndef XDR_H
#define XDR_H

#include <QFrame>
#include <QTimer>

namespace Ui {
class XDR;
}

class XDR : public QFrame
{
    Q_OBJECT

public:
    explicit XDR(QWidget *parent = nullptr);
    ~XDR();

private slots:
    void on_XDR_confirm_clicked();

    void on_cb_Unit_currentTextChanged(const QString &selection);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::XDR *ui;
    QTimer *timer;
};

#endif // XDR_H
