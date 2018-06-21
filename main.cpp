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
    mainWin.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), mainWin.getGraphicsView()->scene(),
                     SLOT(advance()));
    timer.start(1000/GRAPHICS_FPS);

    return app.exec();
}
