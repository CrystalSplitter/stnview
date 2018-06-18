#include <cstdlib>
#include <QPointF>
#include "stngraphics.h"

StnGraphics::StnGraphics(SimpTempNet& stn) :
    stn_(stn),
    nodeToCircleMap_(std::map<Node*, NodeGraphics*>{})
{
    // Initialise pseudo random number generator.
    srand(static_cast <unsigned> (time(0)));
    // Initialise the map
}

void StnGraphics::paintNodes(QGraphicsScene* scene)
{
    for (size_t i = 0; i < stn_.getNodes().size(); i++) {
        Node* node = stn_.getNodes().at(i);
        float randX = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        randX = randX * scene->width()*0.5f + scene->height()*0.25f;
        float randY = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        randY = randY * scene->height()*0.5f + scene->height()*0.25f;

        NodeGraphics* nG{new NodeGraphics()};
        nG->setPos(QPointF(randX, randY));
        nG->setLabel(QString("t") + QString::number(i));
        scene->addItem(nG);
        nodeToCircleMap_.insert(std::make_pair(node, nG));
    }
}

void StnGraphics::paintEdges(QGraphicsScene* scene)
{
    for (auto& cons: stn_.getConstraints()) {
        Node* from = cons->getFrom();
        Node* to = cons->getTo();

        // Retrieve the circle positions.
        QPointF fromPos{nodeToCircleMap_[from]->getPos()};
        QPointF toPos{nodeToCircleMap_[to]->getPos()};

        EdgeGraphics* edge{new EdgeGraphics(fromPos, toPos, retrieveEdgeLabel(cons))};

        // Make the edge on a layer behind the nodes.
        edge->setZValue(-1.0f);
        scene->addItem(edge);
    }
}

QString StnGraphics::retrieveEdgeLabel(Constraint* edge)
{
    ReqConstraint* reqCons{dynamic_cast<ReqConstraint*>(edge)};
    ContConstraint* contCons{dynamic_cast<ContConstraint*>(edge)};

    if (reqCons != nullptr) {
        return QString("[") + QString::number(reqCons->reqMin()) + QString(",")
                + QString::number(reqCons->reqMax()) + QString("]");
    } else if (contCons != nullptr) {
        return QString("N(X,X)");
    } else {
        qDebug() << "retrieveEdgeLabel was unable to cast correctly." << endl;
        return QString("[ERROR]");
    }
}

std::vector<QPointF> StnGraphics::rowStartPoints()
{
    // Do nothing here.
}
