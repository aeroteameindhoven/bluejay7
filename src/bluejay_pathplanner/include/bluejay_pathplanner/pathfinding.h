#ifndef PATHFINDING_H
#define PATHFINDING_H

class pathfinding{
public:
    virtual ~pathfinding(){}
    virtual bool calculatepath() = 0;
};
#endif // PATHFINDING_H
