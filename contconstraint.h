#ifndef CONTCONSTRAINT_H
#define CONTCONSTRAINT_H

#include "constraint.h"

class ContConstraint : public Constraint
{
public:
    ContConstraint(Node* from, Node* to);
    Node* getFrom() const override;
    Node* getTo() const override;
};

#endif // CONTCONSTRAINT_H
