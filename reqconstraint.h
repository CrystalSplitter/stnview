#ifndef REQCONSTRAINT_H
#define REQCONSTRAINT_H

#include "constraint.h"

class ReqConstraint : public Constraint
{
public:
    ReqConstraint(Node* from, Node* to, double minVal, double maxVal);
    Node* getFrom() const override;
    Node* getTo() const override;
    double reqMin() const;
    double reqMax() const;
    std::string asInequality() const;
    void setMin(double val);
    void setMax(double val);

private:
    double requirementMin_ = 0.0;
    double requirementMax_ = 0.0;
};

#endif // REQCONSTRAINT_H
