#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <memory>
#include "node.h"

class Constraint
{
public:
    virtual Node* getFrom() const;
    virtual Node* getTo() const;

protected:
    Constraint(Node* from, Node* to);
    Node* from_;
    Node* to_;
};

#endif // CONSTRAINT_H
