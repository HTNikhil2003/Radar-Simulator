#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "TacticalScene.h"
#include <QMainWindow>
#include <TacticalScene.h>
#include <TacticalView.h>
#include <QtNetwork/QUdpSocket>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    TacticalScene *objTacticalScene;
    TacticalView *objTacticalView;
    QGraphicsScene *Scene;
    QUdpSocket *udpSocket;
    //QGraphicsPixmapItem *targetItem;

    QPushButton *btnShowRMC;
    QTextEdit *txtRMC;

    QPushButton *btnShowLOG;
    QTextEdit *txtLOG;

    QPushButton *btnShowECHO;
    QTextEdit *txtECHO;

    QPushButton *btnShowAIS;
    QTextEdit *txtAIS;

    QPushButton *btnShowGYRO;
    QTextEdit *txtGYRO;

    QTextEdit *txtBearing;   // NEW

    QTextEdit *txtCoords;   // NEW

   QTextEdit *txtRange;

    void parseRMC(const QString &rmc);
    void updateRadar(double lat, double lon);

    QGraphicsItem *radarItem;
    void updateAircraft(double lat, double lon);
    double convertToDecimal(QString val, QString dir);

    QPushButton *btnCloseRMC;
    QPushButton *btnCloseLOG;
    QPushButton *btnCloseECHO;
    QPushButton *btnCloseAIS;
    QPushButton *btnCloseGYRO;

    QPushButton *btnShowIBS;
    QPushButton *btnCloseIBS;
    QTextEdit *txtIBS;

    void updateObjectInfo();

    TacticalScene *scene;

private slots:
    void readData();
    //void updateTarget(double range, double bearing);
    void onShowRMCClicked();
    void onShowLOGClicked();
    void onShowECHOClicked();
    void onShowAISClicked();
    void onShowIBSClicked();
    void onShowGYROClicked();

        void onCloseGYRO();
        void onCloseRMC();
        void onCloseLOG();
        void onCloseECHO();
        void onCloseAIS();
        void onCloseIBS();
        void updateMouseBearing(double bearing);

        //void updateAircraftPosition(int bearing);

};
#endif // MAINWINDOW_H
