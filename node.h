#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>

class Node
{
public:
    Node();
    Node(size_t id);
    size_t nodeId() const;

private:
    size_t nodeId_;
};

#endif // NODE_H
