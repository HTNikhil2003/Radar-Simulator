#include "TacticalView.h"
#include "mainwindow.h"
#include "TacticalScene.h"
#include "qdebug.h"
#include <QMouseEvent>
#include <QtMath>


TacticalView::TacticalView(QWidget *parent) : QGraphicsView (parent)
{
    qDebug()<<"entered to view class";
    setSceneRect(0,0,20000,20000);
    setGeometry(0,60,1200,820);
    scale(0.82,0.82);

    setMouseTracking(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TacticalView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF scenePos = mapToScene(event->pos());

    QPointF center = scene()->sceneRect().center();

    double dx = scenePos.x() - center.x();

    double dy = center.y() - scenePos.y();

    double angleRad = atan2(dx, dy);

    double angleDeg = qRadiansToDegrees(angleRad);

    if (angleDeg < 0)
        angleDeg += 360;

    emit mouseBearingChanged(angleDeg);

    QGraphicsView::mouseMoveEvent(event);
}
