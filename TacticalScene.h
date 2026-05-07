#ifndef TACTICALSCENE_H
#define TACTICALSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsLineItem>

class TacticalScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit TacticalScene(QObject *parent = nullptr);

    void moveAircraft(int step);

    void moveAircraft(double angle, double distance);

    void moveAircraftTo(double angle, double distance);

    void drawRadar();

    void updateTarget(double range, double bearing);

    void updateAircraftPosition(double x, double y);

    QPointF getAircraftPosition() const;

    void moveAircraftAuto();

    void showAircraft();

    //void updateAircraftPosition(double range, double bearing);

private:
    QGraphicsPixmapItem *aircraftItem;
    QGraphicsPixmapItem *targetItem;

    QGraphicsLineItem *sweepLine;
        QTimer *timer;
        double angle;

        QTimer *moveTimer;
        double moveAngle;
        double moveRadius;

private slots:
    void updateSweep();

};

#endif
