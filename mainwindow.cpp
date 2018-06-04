#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Crystal's Program");
    ui->myGraphicsView->setRenderHints(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsView* MainWindow::getGraphicsView()
{
    return ui->myGraphicsView;
}

