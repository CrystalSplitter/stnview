#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

#include "stngraphics.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsView* getGraphicsView();
    StnGraphics* getStnGraphics();

private:
    Ui::MainWindow* ui;
    StnGraphics* stnGraphics_;
    SimpTempNet* stn_;

    QGraphicsScene* createScene(QGraphicsView* gViewPtr);

};

#endif // MAINWINDOW_H
