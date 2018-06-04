
#include "constraint.h"

Constraint::Constraint(Node* from, Node* to)
{
    to_ = to;
    from_ = from;
}

Node* Constraint::getFrom() const
{
    return to_;
}

Node* Constraint::getTo() const
{
    return from_;
}
