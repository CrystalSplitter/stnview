#ifndef EDGEGRAPHICS_H
#define EDGEGRAPHICS_H

#include <QGraphicsItem>

class EdgeGraphics : public QGraphicsItem
{
public:
    EdgeGraphics(QPointF start, QPointF end, QString label);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

    QPointF getMidpoint() const;
    QSizeF getLineSize() const;
    void setReverseBend(bool val);
    void setLabel(QString label);

private:
    QPointF start_;
    QPointF end_;
    // Label text for the edge.
    QString label_;
    QColor color_;

    bool reverseBend_ = false;
    double arrowSize_ = 10.0;
    double arrowPercent_ = 0.7;

    QPointF getControlPoint(double bendAmount, bool bendToScale) const;
    QPolygonF createArrow(QPointF position, double size, double angle, bool reverse) const;
    bool shouldReverseArrow(QPainterPath& path) const;
};

#endif // EDGEGRAPHICS_H
