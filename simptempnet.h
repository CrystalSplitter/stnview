#ifndef SIMPTEMPNET_H
#define SIMPTEMPNET_H

#include <memory>
#include <vector>

#include "node.h"
#include "constraint.h"
#include "contconstraint.h"
#include "reqconstraint.h"

class SimpTempNet
{
public:
    SimpTempNet();
    ~SimpTempNet();

    Node* addNode();

    ReqConstraint* addReqConstraint(
            Node* from,
            Node* to,
            double value
    );

    ContConstraint* addContConstraint(
            Node* from,
            Node* to
    );

    std::vector<Node*> getNodes();
    std::vector<Constraint*> getConstraints();

private:
    size_t agentCount = 0;
    std::vector<Node*> nodes_;
    std::vector<Constraint*> constraints_;
};

#endif // SIMPTEMPNET_H
