#include <stdio.h>
#include <iostream>

#include "reqconstraint.h"

ReqConstraint::ReqConstraint(Node* from, Node* to , double minVal, double maxVal) :
    Constraint(from, to),
    requirementMin_(minVal),
    requirementMax_(maxVal)

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

double ReqConstraint::reqMin() const
{
    return requirementMin_;
}

double ReqConstraint::reqMax() const
{
    return requirementMax_;
}

std::string ReqConstraint::asInequality() const
{
    std::string msg{"t" + std::to_string(to_->nodeId()) + " - "
            + "t" + std::to_string(from_->nodeId())  + " < "
            + std::to_string(requirementMax_) + " ; "

            + "t" + std::to_string(from_->nodeId()) + " - "
            + "t" + std::to_string(to_->nodeId()) + " < "
            + std::to_string(requirementMin_)};
    return msg;
}

void ReqConstraint::setMin(double val)
{
    requirementMin_ = val;
}

void ReqConstraint::setMax(double val)
{
    requirementMax_ = val;
}
