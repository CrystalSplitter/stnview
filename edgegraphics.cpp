#include <math.h>
#include <QPainter>
#include <QWidget>
#include <QDebug>

#include "edgegraphics.h"

const QColor DEFAULT_LINE_COLOUR(30, 30, 30);
const size_t DEFAULT_LINE_WIDTH(2);

EdgeGraphics::EdgeGraphics(QPointF start, QPointF end) :
    start_(start),
    end_(end),
    color_(DEFAULT_LINE_COLOUR)
{
    // Nothing to do here.
}

QRectF EdgeGraphics::boundingRect() const
{
    QSizeF size{getLineSize()};
    QPointF topLeft{getMidpoint().x() + size.width()*0.5, getMidpoint().y() + size.height()*0.5};
    return QRectF{topLeft, size};
}

void EdgeGraphics::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                         QWidget* widget)
{
    QPainterPath edgePath(start_);

    // check to see if we should reverse the bend on this edge.
    int revBend = reverseBend_ ? -1 : 1;

    edgePath.quadTo(getControlPoint(50 * revBend, false), end_);
    painter->setPen(QPen(DEFAULT_LINE_COLOUR, DEFAULT_LINE_WIDTH));
    painter->drawPath(edgePath);

    painter->setBrush(QBrush(QColor()));
    double arrowAngle = atan(edgePath.slopeAtPercent(arrowPercent_)) * 180/M_PI;
    QPainterPath arrowPath;
    QPolygonF polygon = createArrow(edgePath.pointAtPercent(arrowPercent_),
            arrowSize_,
            arrowAngle,
            shouldReverseArrow(edgePath));

    arrowPath.addPolygon(polygon);
    painter->drawPath(arrowPath);
}

QPointF EdgeGraphics::getMidpoint() const
{
    qreal centreX{(end_.x() + start_.x())/2.0f};
    qreal centreY{(end_.y() + start_.y())/2.0f};
    return QPointF(centreX, centreY);
}

QSizeF EdgeGraphics::getLineSize() const
{
    return QSizeF{fabs(end_.x() - start_.x()), fabs(end_.y() - start_.y())};
}

void EdgeGraphics::setReverseBend(bool val) { reverseBend_ = val; }

QPointF EdgeGraphics::getControlPoint(double bendAmount, bool bendToScale) const
{
    double diffX = end_.x() - start_.x();
    double diffY = end_.y() - start_.y();
    double mag = pow(diffX*diffX + diffY*diffY, 0.5);
    double dirX = (end_.x() - start_.x())/mag;
    double dirY = (end_.y() - start_.y())/mag;
    double perpX = -dirY;
    double perpY = dirX;

    if (bendToScale) {
        return getMidpoint() + bendAmount * mag * QPointF(perpX, perpY);
    }
    return getMidpoint() + bendAmount * QPointF(perpX, perpY);
}

QPolygonF EdgeGraphics::createArrow(QPointF position, double size,
                                    double angle, bool reverse) const
{
    if (reverse) {
        angle += 180.0;
    }

    QVector<QPointF> points{QPointF(size*0.5, 0.0f),
                            QPointF(-size*0.5, size * 0.75),
                            QPointF(-size*0.5, -size * 0.75),
                            QPointF(size*0.5, 0.0f)};
    QPolygonF arrow(points);
    arrow = QTransform()
            .translate(position.x(), position.y())
            .rotate(angle)
            .map(arrow);
    return arrow;
}

bool EdgeGraphics::shouldReverseArrow(QPainterPath& path) const
{
    QPointF p1(path.pointAtPercent(0.49));
    QPointF p2(path.pointAtPercent(0.51));
    return p2.x() < p1.x();
}
