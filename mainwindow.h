#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsView* getGraphicsView();

private:
    Ui::MainWindow* ui;

    QGraphicsScene* createScene(QGraphicsView* gViewPtr);

};

#endif // MAINWINDOW_H
