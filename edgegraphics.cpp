#include <math.h>
#include <QPainter>
#include <QWidget>
#include <QDebug>

#include "edgegraphics.h"

const QColor DEFAULT_LINE_COLOUR{30, 30, 30};
const size_t DEFAULT_LINE_WIDTH{2};
const QPointF DEFAULT_LABEL_OFFSET{10, -10};

EdgeGraphics::EdgeGraphics(QPointF start, QPointF end, QString label) :
    start_(start),
    end_(end),
    label_(label),
    color_(DEFAULT_LINE_COLOUR),
    labelOffset_(DEFAULT_LABEL_OFFSET)
{
    // Nothing to do here.
}

QRectF EdgeGraphics::boundingRect() const
{
    QSizeF size{getLineSize()};
    QPointF topLeft{getMidpoint().x() - size.width()*0.5, getMidpoint().y() - size.height()*0.5};
    return QRectF{topLeft, size};
}

void EdgeGraphics::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                         QWidget* widget)
{
    // We don't use these parameters. Silence the warnings.
    (void) option;
    (void) widget;

    QPainterPath edgePath(start_);

    // check to see if we should reverse the bend on this edge.
    int revBend = reverseBend_ ? -1 : 1;

    edgePath.quadTo(getControlPoint(bendAmount_ * revBend, false), end_);
    painter->setPen(QPen(DEFAULT_LINE_COLOUR, DEFAULT_LINE_WIDTH));
    painter->drawPath(edgePath);

    // Draw the arrow
    painter->setBrush(QBrush(QColor()));
    double arrowAngle = atan(edgePath.slopeAtPercent(arrowPercent_)) * 180/M_PI;
    QPainterPath arrowPath;
    QPolygonF polygon = createArrow(edgePath.pointAtPercent(arrowPercent_),
            arrowSize_,
            arrowAngle,
            shouldReverseArrow(edgePath));


    arrowPath.addPolygon(polygon);
    painter->drawPath(arrowPath);

    // Draw the Text.
    painter->drawText(edgePath.pointAtPercent(0.5) + labelOffset_, label_);
}

void EdgeGraphics::advance(int phase)
{
    if (!phase) {
        return;
    }

    prepareGeometryChange();
}

QPointF EdgeGraphics::getMidpoint() const
{
    qreal centreX{(end_.x() + start_.x())/2.0f};
    qreal centreY{(end_.y() + start_.y())/2.0f};
    return QPointF(centreX, centreY);
}

QSizeF EdgeGraphics::getLineSize() const
{
    return QSizeF{fabs(end_.x() - start_.x()) + bendAmount_ + arrowSize_ + labelOffset_.x(),
                fabs(end_.y() - start_.y()) + bendAmount_ + arrowSize_ + labelOffset_.y()};
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

void EdgeGraphics::setLabel(QString label)
{
    label_ = label;
}

void EdgeGraphics::setStartPoint(const QPointF& pos)
{
    start_ = pos;
}

void EdgeGraphics::setEndPoint(const QPointF& pos)
{
    end_ = pos;
}
