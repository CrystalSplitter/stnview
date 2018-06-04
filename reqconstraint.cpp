#include <stdio.h>

#include "reqconstraint.h"

ReqConstraint::ReqConstraint(Node* from, Node* to , double val) :
    Constraint(from, to),
    requirementValue_(val)

{
    // Nothing to do.
}

Node* ReqConstraint::getFrom() const
{
    return from_;
}

Node* ReqConstraint::getTo() const
{
    return to_;
}

double ReqConstraint::requirement() const
{
    return requirementValue_;
}

std::string ReqConstraint::asInequality() const
{
    std::string msg{"t" + std::to_string(to_->nodeId()) + " - "
            + "t" + std::to_string(from_->nodeId())  + " < "
            + std::to_string(requirementValue_)};
    return msg;
}
