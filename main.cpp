#include <QtWidgets>
#include <QGraphicsView>
#include <QDebug>

#include "nodegraphics.h"
#include "mainwindow.h"
#include "simptempnet.h"
#include "stngraphics.h"

QGraphicsScene* createScene(MainWindow* mainWin, QGraphicsView* gViewPtr);
SimpTempNet stnFromJson(char* filepath);

const size_t GRAPHICS_FPS = 60;

int main(int argc, char** argv)
{
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
    Node* nodeA{stn.addNode()};
    Node* nodeB{stn.addNode()};
    Node* nodeC{stn.addNode()};
    stn.addReqConstraint(nodeA, nodeB, 10.0);
    stn.addReqConstraint(nodeB, nodeA, 10.0);
    stn.addReqConstraint(nodeB, nodeC, 20.0);
    stn.addReqConstraint(nodeC, nodeB, 20.0);

    StnGraphics stnGraphics{stn};
    stnGraphics.paintNodes(scene);
    stnGraphics.paintEdges(scene);

    return scene;
}
