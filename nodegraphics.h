#ifndef NODEGRAPHICS_H
#define NODEGRAPHICS_H

#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

class NodeGraphics : public QGraphicsItem
{
public:
    NodeGraphics();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void move(QPointF targetPos);

    // Getters and setters.

    float getRadius() const;

    QPointF getPos() const;

    bool getTrack() const;

    void setPos(QPointF pos);
    void setRadius(float radius);
    void setTrack(bool val);
    void setColor(QColor col);
    void setLabel(QString label);

private:
    QString label_;
    QPointF centre_;
    QColor color_;
    float radius_;
    bool trackCursor_;
    bool drawText_;

    //QGraphicsView* graphicsView_;

protected:
    void advance(int phase) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};

#endif // NODEGRAPHICS_H
