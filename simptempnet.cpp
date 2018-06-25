#include <iostream>
#include "simptempnet.h"

const bool DEBUG = true;

SimpTempNet::SimpTempNet() :
    nodes_(std::vector<Node*>{}),
    constraints_(std::map<std::pair<size_t, size_t>, Constraint*>{})
{
    // Nothing to do here
}


SimpTempNet::~SimpTempNet()
{
    for (auto const& item: constraints_) {
        delete item.second;
    }

    for (auto const& node: nodes_) {
        if (node != nullptr) {
            delete node;
        }
    }
}


size_t SimpTempNet::addNode()
{
    size_t nodeCount{nodes_.size()};
    Node* addedNode{new Node(nodeCount)};
    nodes_.push_back(addedNode);
    return addedNode->nodeId();
}


ReqConstraint* SimpTempNet::addReqConstraint(size_t from,
                                             size_t to,
                                             double minValue,
                                             double maxValue)
{
    return addReqConstraint(from, to, minValue, maxValue, false);
}


ReqConstraint* SimpTempNet::addReqConstraint(size_t from,
                                             size_t to,
                                             double minValue,
                                             double maxValue,
                                             bool onlyTighten)
{
    const auto constraintThere = constraints_.find(std::make_pair(from, to));

    ReqConstraint* reqThere;
    if (constraintThere == constraints_.end()) {
        reqThere = nullptr;
    } else {
        // Try to cast Constraints to a requirement Edge.
        try {
            reqThere = dynamic_cast<ReqConstraint*>(constraintThere->second);
        } catch (std::bad_cast) {
            reqThere = nullptr;
        }
    }

    // Check if we don't have this constraint.
    if (constraintThere == constraints_.end() || reqThere == nullptr) {
        ReqConstraint* addedConstraint{new ReqConstraint(nodes_.at(from),
                                                         nodes_.at(to),
                                                         minValue,
                                                         maxValue)
                                      };
        constraints_[std::make_pair(from, to)] = addedConstraint;
        std::cout << addedConstraint->asInequality() << std::endl;
        return addedConstraint;
    }

    // Only gets run if there is no constraint present since we exited early.
    if (onlyTighten) {
        if (reqThere->reqMin() < minValue) {
            reqThere->setMin(minValue);
        }
        if (reqThere->reqMax() > maxValue) {
            reqThere->setMax(maxValue);
        }
    } else if (!onlyTighten) {
        reqThere->setMin(minValue);
        reqThere->setMax(maxValue);
    }
    return reqThere;
}


ContConstraint* SimpTempNet::addContConstraint(size_t from, size_t to)
{
    ContConstraint* addedConstraint{new ContConstraint(nodes_.at(from), nodes_.at(to))};
    constraints_[std::make_pair(from, to)] = addedConstraint;
    return addedConstraint;
}

void SimpTempNet::assignMakespan(size_t referenceNodeId, double minVal, double maxVal)
{
    for (size_t i = 0; i < nodes_.size(); ++i) {
        if (i == referenceNodeId) {
            continue;
        }
        addReqConstraint(referenceNodeId, i, minVal, maxVal);
    }
}

std::vector<Node*> SimpTempNet::getNodes()
{
    return nodes_;
}


std::vector<Constraint*> SimpTempNet::getConstraints()
{
    std::vector<Constraint*> vect(constraints_.size());
    size_t count = 0;
    for (auto const& i: constraints_) {
        vect[count] = i.second;
        count++;
    }
    return vect;
}


Node* SimpTempNet::getNodeAt(size_t ind) const
{
    return nodes_.at(ind);
}

Constraint* SimpTempNet::getConstraintBetween(size_t from, size_t to) const
{
    // Check if the constraint exists first.
    if (constraints_.find(std::make_pair(from, to)) != constraints_.end()) {
        return constraints_.at(std::make_pair(from, to));
    } else {
        return nullptr;
    }
}

ReqConstraint* SimpTempNet::getReqBetween(size_t from, size_t to) const
{
    try {
        Constraint* con{getConstraintBetween(from, to)};
        if (con == nullptr) {
            return nullptr;
        }
        return dynamic_cast<ReqConstraint*>(con);
    } catch (std::bad_cast) {
        if (DEBUG) {
            std::cout << "BAD CAST CAUGHT." << std::endl;
        }
        return nullptr;
    }
}
