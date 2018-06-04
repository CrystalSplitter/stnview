#include <iostream>
#include "simptempnet.h"

SimpTempNet::SimpTempNet() :
    nodes_(std::vector<Node*>{}),
    constraints_(std::vector<Constraint*>{})
{
    // Nothing to do here
}

SimpTempNet::~SimpTempNet()
{
    for (auto const& constraint: constraints_) {
        delete constraint;
    }

    for (auto const& node: nodes_) {
        delete node;
    }
}

Node* SimpTempNet::addNode()
{
    size_t nodeCount{nodes_.size()};
    Node* addedNode{new Node(nodeCount)};
    nodes_.push_back(addedNode);
    return addedNode;
}

ReqConstraint* SimpTempNet::addReqConstraint(Node* from, Node* to, double value)
{
    ReqConstraint* addedConstraint{new ReqConstraint(from, to, value)};
    constraints_.push_back(addedConstraint);
    std::cout << addedConstraint->asInequality() << std::endl;
    return addedConstraint;
}

ContConstraint* SimpTempNet::addContConstraint(Node* from, Node* to)
{
    ContConstraint* addedConstraint{new ContConstraint(from, to)};
    constraints_.push_back(addedConstraint);
    return addedConstraint;
}

std::vector<Node*> SimpTempNet::getNodes()
{
    return nodes_;
}

std::vector<Constraint*> SimpTempNet::getConstraints()
{
    return constraints_;
}
