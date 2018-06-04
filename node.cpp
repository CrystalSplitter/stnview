#include "node.h"

Node::Node() : nodeId_(0)
{
    // Nothing to do here.
}

Node::Node(size_t  id) : nodeId_(id)
{
    // Nothing to do here.
}

size_t Node::nodeId() const
{
    return nodeId_;
}
