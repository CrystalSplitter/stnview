#ifndef STNGRAPHICS_H
#define STNGRAPHICS_H

#include <QGraphicsScene>
#include <map>
#include "simptempnet.h"
#include "nodegraphics.h"
#include "node.h"
#include "constraint.h"
#include "edgegraphics.h"

class StnGraphics
{
public:
    StnGraphics(SimpTempNet& stn);
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

    // Private functions
private:
    std::vector<QPointF> rowStartPoints();

    // Data members.
private:
    QString retrieveEdgeLabel(Constraint* edge);

    SimpTempNet& stn_;
    std::map<Node*, NodeGraphics*> nodeToCircleMap_;
};

#endif // STNGRAPHICS_H
