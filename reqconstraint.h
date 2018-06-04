#ifndef REQCONSTRAINT_H
#define REQCONSTRAINT_H

#include "constraint.h"

class ReqConstraint : public Constraint
{
public:
    ReqConstraint(Node* from, Node* to, double val);
    Node* getFrom() const override;
    Node* getTo() const override;
    double requirement() const;
    std::string asInequality() const;

private:
    double requirementValue_ = 0.0;
};

#endif // REQCONSTRAINT_H
