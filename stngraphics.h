#ifndef STNGRAPHICS_H
#define STNGRAPHICS_H

#include <QGraphicsScene>
#include <map>
#include "simptempnet.h"
#include "nodegraphics.h"
#include "node.h"
#include "constraint.h"
#include "edgegraphics.h"

class StnGraphics: public QObject
{
    Q_OBJECT
public:
    explicit StnGraphics(SimpTempNet* stn, QWidget* parent=nullptr);
    explicit StnGraphics(QWidget* parent=nullptr);
    ~StnGraphics();
    /**
     * @brief paintNodes Paints the modes of the STN onto the provided scene.
     * @param scene Scene to draw on.
     */
    void paintNodes(QGraphicsScene* scene);
    /**
     * @brief paintEdges Paints the edges of the STN onto the provided scene.
     * @param scene Scene to draw on.
     */
    void paintEdges(QGraphicsScene* scene);

    void assignStn(SimpTempNet* stn);

public slots:
    void updateEdges();

    // Private functions
private:
    /**
     * @brief circularPositions Computes a set of points that are equidistant along a circle.
     * @param centre Position of the circle centre in the GraphicsScene.
     * @param radius Radius of the circle.
     * @return Returns a vector of QPointFs of each position.
     */
    std::vector<QPointF> circularPositions(QPointF centre, double radius, size_t nodeCount);

    // Data members.
private:
    SimpTempNet* stn_;
    std::map<Node*, NodeGraphics*> nodeToCircleMap_;
    std::map<Constraint*, EdgeGraphics*> edgeGraphics_;

    QString retrieveEdgeLabel(Constraint* edge);
};

#endif // STNGRAPHICS_H
