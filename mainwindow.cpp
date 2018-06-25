#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "simptempnet.h"
#include "stngraphics.h"

const QSize DEFAULT_WINDOW_SIZE{500, 500};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    stnGraphics_{new StnGraphics{}}
{
    ui->setupUi(this);
    setWindowTitle("Crystal's Program");
    ui->myGraphicsView->setRenderHints(QPainter::Antialiasing);

    // Create the STN
    stn_ = new SimpTempNet{};

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
    delete stn_;
    delete ui;
    delete stnGraphics_;
}

QGraphicsView* MainWindow::getGraphicsView()
{
    return ui->myGraphicsView;
}

StnGraphics* MainWindow::getStnGraphics()
{
    return stnGraphics_;
}

QGraphicsScene* MainWindow::createScene(QGraphicsView* gViewPtr)
{
    // Make a new graphics scene in this window.
    QGraphicsScene* scene{new QGraphicsScene(this)};
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    // Set the scene rectangle to the same as the graphics view rectangle.
    scene->setSceneRect(gViewPtr->rect());

    size_t nodeF{stn_->addNode()};

    size_t nodeA{stn_->addNode()};
    size_t nodeB{stn_->addNode()};
    size_t nodeC{stn_->addNode()};
    size_t nodeD{stn_->addNode()};
    size_t nodeE{stn_->addNode()};
    stn_->addReqConstraint(nodeA, nodeB, 10.0, 10.0);
    stn_->addReqConstraint(nodeB, nodeC, 20.0, 20.0);
    stn_->addReqConstraint(nodeD, nodeE, 3.0, 7.0);
    stn_->addContConstraint(nodeE, nodeB);
    stn_->addReqConstraint(nodeF, nodeC, -5.0, 10.0);
    stn_->assignMakespan(nodeA, 0.0, 50.0);

    stn_->addReqConstraint(nodeA, nodeB, 5.0, 5.0);

    stnGraphics_->assignStn(stn_);
    stnGraphics_->paintNodes(scene);
    stnGraphics_->paintEdges(scene);

    return scene;
}
