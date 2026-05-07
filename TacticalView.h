#ifndef TACTICALVIEW_H
#define TACTICALVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class TacticalView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TacticalView(QWidget *parent = nullptr);

signals:
    void mouseBearingChanged(double bearing);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif
