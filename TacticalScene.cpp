#include "TacticalScene.h"
#include <QtDebug>
#include <QtMath>
#include <QTimer>

TacticalScene::TacticalScene(QObject *parent)
          : QGraphicsScene (parent)
{
  setSceneRect(450,50,2000,2000);

  drawRadar();
  QPixmap targetPix(":/new/prefix1/os4.png");
  targetItem = new QGraphicsPixmapItem(targetPix);
  targetItem->setPos(1400,1000);
  addItem(targetItem);

  QPixmap aircraftPix(":/new/prefix2/RadioButtonChecked.png");
  aircraftItem = new QGraphicsPixmapItem(aircraftPix);
  addItem(aircraftItem);
  aircraftItem->setPos(10000,10000);
  aircraftItem->hide();

  angle = 0;

  QPointF center = sceneRect().center();

  sweepLine = addLine(center.x(), center.y(),center.x() + 800, center.y(),QPen(Qt::red, 2));

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TacticalScene::updateSweep);
  timer->start(50);

  moveAngle = 0;
  moveRadius = 600;

  moveTimer = new QTimer(this);
  connect(moveTimer, &QTimer::timeout, this, &TacticalScene::moveAircraftAuto);
//  moveTimer->start(1000);

}

void TacticalScene::moveAircraft(int step)
{
    if(!aircraftItem || !targetItem)
        return;

    QPointF aircraftPos = aircraftItem->pos();
    QPointF targetPos = targetItem->pos();

    double dx = targetPos.x() - aircraftPos.x();
    double dy = targetPos.y() - aircraftPos.y();

    double length = qSqrt(dx*dx + dy*dy);
    if(length == 0 )
        return;

    dx /= length;
    dy /= length;

    aircraftItem->setPos( aircraftPos.x() + dx * step, aircraftPos.y() + dy * step);
}

void TacticalScene::moveAircraftTo(double angle, double distance)
{
    if (!aircraftItem)
        return;

    QPointF center = sceneRect().center();

    double x = distance * cos(qDegreesToRadians(angle));
    double y = distance * sin(qDegreesToRadians(angle));

    aircraftItem->setPos(center.x() + x,center.y() - y);
}

void TacticalScene::drawRadar()
{
    int radius = 800;

    QPointF center = sceneRect().center();   // ✅ dynamic center

    addEllipse(center.x() - radius,center.y() - radius,radius * 2,radius * 2, QPen(Qt::green, 2));

    QFont font;
    font.setPointSize(14);
    font.setBold(true);

    auto top = addText("0°", font);
    top->setDefaultTextColor(Qt::green);
    top->setPos(center.x() - 20, center.y() - radius - 40);

    auto right = addText("90°", font);
    right->setDefaultTextColor(Qt::green);
    right->setPos(center.x() + radius + 10, center.y() - 10);

    auto bottom = addText("180°", font);
    bottom->setDefaultTextColor(Qt::green);
    bottom->setPos(center.x() - 30, center.y() + radius + 10);

    auto left = addText("270°", font);
    left->setDefaultTextColor(Qt::green);
    left->setPos(center.x() - radius - 60, center.y() - 10);

    QList<int> angles = {45, 135, 225, 315};

    for (int angle : angles)
    {
        double rad = qDegreesToRadians((double)angle - 90.0);

        double x = center.x() + radius * cos(rad);
        double y = center.y() + radius * sin(rad);

        auto text = addText(QString::number(angle) + "°", font);
        text->setDefaultTextColor(Qt::green);

        text->setPos(x - 20, y - 20);
    }
}

void TacticalScene::updateTarget(double lat, double lon)
{
    QPointF center = sceneRect().center();

    double scale = 2000;

    double x = lon * scale;
    double y = lat * scale;

    targetItem->setPos(center.x() + x,center.y() - y);
}

void TacticalScene::updateAircraftPosition(double x, double y)
{
    if (aircraftItem)
            aircraftItem->setPos(x, y);
}

void TacticalScene::updateSweep()
{
    angle += 2;  // rotation speed

    if (angle >= 360) angle = 0;

    QPointF center = sceneRect().center();

    double radius = 800;

    double x = center.x() + radius * cos(qDegreesToRadians(angle));
    double y = center.y() + radius * sin(qDegreesToRadians(angle));

    sweepLine->setLine(center.x(), center.y(), x, y);
}

QPointF TacticalScene::getAircraftPosition() const
{
    return aircraftItem->pos();
}

void TacticalScene::moveAircraftAuto()
{
    if (!aircraftItem || !aircraftItem->isVisible())
        return;

    QPointF center = sceneRect().center();

    moveAngle += 1;

    if (moveAngle >= 360)
        moveAngle = 0;

    double rad = qDegreesToRadians(moveAngle);

    double x = center.x() + moveRadius * cos(rad);
    double y = center.y() + moveRadius * sin(rad);

    aircraftItem->setPos(x, y);
}

void TacticalScene::showAircraft()
{
    if (aircraftItem)
    {
        aircraftItem->setPos(sceneRect().center()); // start from center
        aircraftItem->show();
    }
}

