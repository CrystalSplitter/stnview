#include "utilities.h"
#include <math.h>

QPointF Utilities::linearInterpolate(QPointF start, QPointF target,
        double interpolation)
{
    double difX = target.x() - start.x();
    double difY = target.y() - start.y();
    double newX = difX*interpolation + start.x();
    double newY = difY*interpolation + start.y();

    return QPointF(newX, newY);
}
