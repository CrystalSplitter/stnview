#ifndef SIMPTEMPNET_H
#define SIMPTEMPNET_H

#include <vector>
#include <map>

#include "node.h"
#include "constraint.h"
#include "contconstraint.h"
#include "reqconstraint.h"

class SimpTempNet
{
public:
    SimpTempNet();
    ~SimpTempNet();

    size_t addNode();

    /**
     * @brief addReqConstraint Overload for addReqConstraint(from, to, value, onlyTighten),
     *        where onlyTighten is set to false.
     * @param from Index of the node to connect from.
     * @param to Index of the node to connect to.
     * @param value Requirement Constraint temporal value.
     * @return Returns a pointer to the made or updated constraint.
     */
    ReqConstraint* addReqConstraint(size_t from,
                                    size_t to,
                                    double minValue,
                                    double maxValue);

    /**
     * @brief addReqConstraint Creates or updates a constraint between two nodes.
     * @note If a constraint is already present, then this function updates the existing
     *       constraint, unless onlyTighten is present.
     * @param from Index of the node to connect from.
     * @param to Index of the node to connect to.
     * @param value Requirement Constraint temporal value.
     * @return Returns a pointer to the made or updated constraint.
     */
    ReqConstraint* addReqConstraint(size_t from,
            size_t to,
            double minValue, double maxValue,
            bool onlyTighten
    );

    ContConstraint* addContConstraint(
            size_t from,
            size_t to
    );

    /**
     * @brief assignMakespan Place makespan constraints on all nodes using a provided reference
     *                       node.
     * @param referenceNodeId node id of the reference.
     * @param minVal Minimum makespan time.
     * @param maxVal Maximum makespan time.
     */
    void assignMakespan(size_t referenceNodeId, double minVal, double maxVal);

    std::vector<Node*> getNodes();
    std::vector<Constraint*> getConstraints();
    /**
     * @brief getNodeAt Get the node at a given Index.
     * @param id ID/Index of the Node to look up.
     * @return Returns a pointer to the Node.
     */
    Node* getNodeAt(size_t ind) const;
    /**
     * @brief getConstraintBetween
     * @param from Index of node
     * @param to Index of node
     * @return Returns a pointer to a constraint between the two nodes.
     */
    Constraint* getConstraintBetween(size_t from, size_t to) const;

    ReqConstraint* getReqBetween(size_t from, size_t to) const;

private:
    size_t agentCount = 0;
    std::vector<Node*> nodes_;
    std::map<std::pair<size_t, size_t>, Constraint*> constraints_;
    //std::vector<Constraint*> constraints_;
};

#endif // SIMPTEMPNET_H
