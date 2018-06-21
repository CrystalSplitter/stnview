#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "simptempnet.h"
#include "stngraphics.h"

const QSize DEFAULT_WINDOW_SIZE{500, 500};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Crystal's Program");
    ui->myGraphicsView->setRenderHints(QPainter::Antialiasing);

    // Resize this window to a default size.
    resize(DEFAULT_WINDOW_SIZE);

    QGraphicsView* gViewPtr = ui->myGraphicsView;
    gViewPtr->setMinimumSize(500, 500);
    // Create the scene and assign it to the graphics view
    QGraphicsScene* scenePtr = createScene(gViewPtr);
    gViewPtr->setScene(scenePtr);
    gViewPtr->setCacheMode(QGraphicsView::CacheBackground);
    gViewPtr->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsView* MainWindow::getGraphicsView()
{
    return ui->myGraphicsView;
}

QGraphicsScene* MainWindow::createScene(QGraphicsView* gViewPtr)
{
    // Make a new graphics scene in this window.
    QGraphicsScene* scene{new QGraphicsScene(this)};
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    // Set the scene rectangle to the same as the graphics view rectangle.
    scene->setSceneRect(gViewPtr->rect());
    qDebug() << scene->sceneRect();

    SimpTempNet stn{};
    size_t nodeA{stn.addNode()};
    size_t nodeB{stn.addNode()};
    size_t nodeC{stn.addNode()};
    size_t nodeD{stn.addNode()};
    size_t nodeE{stn.addNode()};
    stn.addReqConstraint(nodeA, nodeB, 10.0, 10.0);
    stn.addReqConstraint(nodeB, nodeC, 20.0, 20.0);
    stn.addReqConstraint(nodeD, nodeE, 3.0, 7.0);
    stn.addContConstraint(nodeE, nodeB);

    stn.addReqConstraint(nodeA, nodeB, 5.0, 5.0);

    StnGraphics stnGraphics{stn};
    stnGraphics.paintNodes(scene);
    stnGraphics.paintEdges(scene);

    return scene;
}
