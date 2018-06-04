#include "contconstraint.h"

ContConstraint::ContConstraint(Node* from, Node* to) : Constraint(from, to)
{
    // Nothing to do here.
}

Node* ContConstraint::getFrom() const
{
    return from_;
}

Node* ContConstraint::getTo() const
{
    return to_;
}
