#include <QtWidgets>
#include <QGraphicsView>
#include <QDebug>

#include "nodegraphics.h"
#include "mainwindow.h"
#include "simptempnet.h"
#include "stngraphics.h"
#include "argparser.h"

QGraphicsScene* createScene(MainWindow* mainWin, QGraphicsView* gViewPtr);
SimpTempNet stnFromJson(char* filepath);

const size_t GRAPHICS_FPS = 60;

int main(int argc, char** argv)
{
    ArgParser argParser{};
    argParser.parse(argc, argv);

    QApplication app{argc, argv};

    MainWindow mainWin;

    QGraphicsView* gViewPtr = mainWin.getGraphicsView();
    QGraphicsScene* scenePtr = createScene(&mainWin, gViewPtr);
    gViewPtr->setScene(scenePtr);
    gViewPtr->setCacheMode(QGraphicsView::CacheBackground);
    gViewPtr->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    mainWin.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), scenePtr, SLOT(advance()));
    timer.start(1000/GRAPHICS_FPS);

    return app.exec();
}

QGraphicsScene* createScene(MainWindow* mainWin, QGraphicsView* gViewPtr)
{
    QGraphicsScene* scene{new QGraphicsScene(mainWin)};
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    // Set the scene rectangle to the same as the graphics view rectangle.
    scene->setSceneRect(gViewPtr->rect());

    SimpTempNet stn{};
    size_t nodeA{stn.addNode()};
    size_t nodeB{stn.addNode()};
    size_t nodeC{stn.addNode()};
    size_t nodeD{stn.addNode()};
    size_t nodeE{stn.addNode()};
    stn.addReqConstraint(nodeA, nodeB, 10.0, 10.0);
    stn.addReqConstraint(nodeB, nodeC, 20.0, 20.0);
    stn.addReqConstraint(nodeD, nodeE, 3.0, 7.0);
    stn.addReqConstraint(nodeE, nodeB, 0.0, 100.0);

    qDebug() << dynamic_cast<ReqConstraint*>(stn.getConstraintBetween(nodeA, nodeB))->reqMin()
             << endl;
    stn.addReqConstraint(nodeA, nodeB, 5.0, 5.0);
    qDebug() << dynamic_cast<ReqConstraint*>(stn.getConstraintBetween(nodeA, nodeB))->reqMin()
             << endl;

    StnGraphics stnGraphics{stn};
    stnGraphics.paintNodes(scene);
    stnGraphics.paintEdges(scene);

    return scene;
}
