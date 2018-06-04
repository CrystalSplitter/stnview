#include "nodegraphics.h"
#include <QPainter>
#include <QWidget>
#include "utilities.h"

const QColor DEFAULT_COLOUR(200, 200, 200);
const float DEFAULT_RADIUS(20.0f);

NodeGraphics::NodeGraphics() :
    label_(QString()),
    centre_(QPointF(0.0f, 0.0f)),
    color_(DEFAULT_COLOUR),
    radius_(DEFAULT_RADIUS),
    trackCursor_(false),
    drawText_(true)
{
    //graphicsView_ = gView;
}

QRectF NodeGraphics::boundingRect() const
{
    QPointF topLeft(centre_.x() - radius_, centre_.y() - radius_);
    QPointF botRight(centre_.x() + radius_, centre_.y() + radius_);
    QRectF rect(topLeft, botRight);
    return rect;
}

void NodeGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    painter->setBrush(color_);
    painter->drawEllipse(centre_, getRadius(), getRadius());
    if (drawText_) {
        painter->setFont(QFont("URW Bookman L", 16));
        painter->drawText(boundingRect(), Qt::AlignCenter, label_);
    }
}

void NodeGraphics::move(QPointF targetPos)
{
    setPos(targetPos);
}

void NodeGraphics::advance(int phase)
{
    if (!phase) {
        return;
    }
    if (trackCursor_) {
        prepareGeometryChange();
        // Removed because I don't want to deal with sharing QGraphicsView
        /*
        QPoint gvPoint = graphicsView_->mapFromGlobal(QCursor::pos());
        QPointF scenePoint = graphicsView_->mapToScene(gvPoint);
        // Interpolate the point.
        QPointF interPoint = Utilities::linearInterpolate(
                    getPos(), scenePoint, 0.7);
        centre_ = interPoint;
        */
    }
}

// GETTERS & SETTERS

float NodeGraphics::getRadius() const { return radius_; }

QPointF NodeGraphics::getPos() const { return centre_; }

void NodeGraphics::setRadius(float radius) { radius_ = radius; }

bool NodeGraphics::getTrack() const { return trackCursor_; }

void NodeGraphics::setPos(QPointF pos) { centre_ = pos; }

void NodeGraphics::setTrack(bool val) { trackCursor_ = val; }

void NodeGraphics::setColor(QColor col) { color_ = col; }

void NodeGraphics::setLabel(QString label) { label_ = label; }
