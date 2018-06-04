#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPointF>

class Utilities
{
public:
    static QPointF linearInterpolate(QPointF start, QPointF target,
            double interpolation);
};

#endif // UTILITIES_H
