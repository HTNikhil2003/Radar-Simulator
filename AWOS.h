#ifndef AWOS_H
#define AWOS_H

#include <QFrame>

namespace Ui {
class AWOS;
}

class AWOS : public QFrame
{
    Q_OBJECT

public:
    explicit AWOS(QWidget *parent = nullptr);
    ~AWOS();

private:
    Ui::AWOS *ui;
};

#endif // AWOS_H
