#include <cstdlib>
#include <QPointF>
#include <math.h>

#include "stngraphics.h"

StnGraphics::StnGraphics(SimpTempNet* stn, QWidget* parent) :
    QObject(parent),
    stn_(stn),
    nodeToCircleMap_(std::map<Node*, NodeGraphics*>{}),
    edgeGraphics_(std::map<Constraint*, EdgeGraphics*>{})
{
    // Initialise pseudo random number generator.
    srand(static_cast <unsigned> (time(0)));
    // Initialise the map
}

StnGraphics::StnGraphics(QWidget* parent) :
    QObject(parent),
    stn_(nullptr),
    nodeToCircleMap_(std::map<Node*, NodeGraphics*>{}),
    edgeGraphics_(std::map<Constraint*, EdgeGraphics*>{})
{
    // Initialise pseudo random number generator.
    srand(static_cast <unsigned> (time(0)));
    // Initialise the map
}

StnGraphics::~StnGraphics()
{
    // Nothing to do here.
}

void StnGraphics::assignStn(SimpTempNet* stn)
{
    stn_ = stn;
}

void StnGraphics::paintNodes(QGraphicsScene* scene)
{
    if (stn_ == nullptr) {
        throw "StnGraphics cannot paint because no STN assigned.";
    }

    size_t numNodes = stn_->getNodes().size();
    QPointF centre{scene->width()*0.5, scene->height()*0.5};
    std::vector<QPointF> nodePosVector{circularPositions(centre, 200, numNodes)};
    // Assign all the node positions.
    for (size_t i = 0; i < numNodes; i++) {
        Node* node = stn_->getNodes().at(i);
        /*
        float randX = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        randX = randX * scene->width()*0.8f + scene->height()*0.1f;
        float randY = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
        randY = randY * scene->height()*0.8f + scene->height()*0.1f;
        */
        NodeGraphics* nG{new NodeGraphics()};
        //nG->setPos(QPointF(randX, randY));
        nG->setPos(nodePosVector.at(i));
        nG->setLabel(QString("t") + QString::number(i));
        scene->addItem(nG);
        nodeToCircleMap_.insert(std::make_pair(node, nG));
    }
}

void StnGraphics::paintEdges(QGraphicsScene* scene)
{
    if (stn_ == nullptr) {
        throw "StnGraphics cannot paint because no STN assigned.";
    }

    for (auto const& cons: stn_->getConstraints()) {
        Node* from = cons->getFrom();
        Node* to = cons->getTo();

        // Retrieve the circle positions.
        QPointF fromPos{nodeToCircleMap_[from]->getPos()};
        QPointF toPos{nodeToCircleMap_[to]->getPos()};

        EdgeGraphics* edge{new EdgeGraphics(fromPos, toPos, retrieveEdgeLabel(cons))};

        // Make the edge on a layer behind the nodes.
        edge->setZValue(-1.0f);
        scene->addItem(edge);
        edgeGraphics_[cons] = edge;
    }
}

void StnGraphics::updateEdges()
{
    for (auto const& item: edgeGraphics_) {
        Constraint* cons{item.first};
        EdgeGraphics* eG{item.second};
        Node* from{cons->getFrom()};
        Node* to{cons->getTo()};

        QPointF startPoint{nodeToCircleMap_.at(from)->getPos()};
        QPointF endPoint{nodeToCircleMap_.at(to)->getPos()};

        eG->setStartPoint(startPoint);
        eG->setEndPoint(endPoint);
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

std::vector<QPointF> StnGraphics::circularPositions(QPointF centre, double radius,
                                                    size_t nodeCount)
{
    std::vector<QPointF> points{};
    for (size_t i = 0; i < nodeCount; ++i) {
        double xOffset = radius*cos(i/((double) nodeCount)*2.0*M_PI + M_PI*0.5);
        double yOffset = -radius*sin(i/((double) nodeCount)*2.0*M_PI + M_PI*0.5);
        QPointF offset{xOffset, yOffset};
        QPointF nodePos{offset + centre};
        points.push_back(nodePos);
    }
    return points;
}
