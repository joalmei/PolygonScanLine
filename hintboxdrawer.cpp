#include "hintboxdrawer.h"
#include "canvasopengl.h"

HintBoxDrawer::HintBoxDrawer(CanvasOpenGL* canvas) : Drawer(canvas) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "rect");
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setDuration(800);
    animation->setStartValue(QRect(0, 0, canvas->width(), 0));
    animation->setEndValue(QRect(0, 0, canvas->width(), 20));

    animation->start();
}

HintBoxDrawer::~HintBoxDrawer() { }

void HintBoxDrawer::Draw(QColor pointsColor) {
    QPainter painter(canvas);

    QPen pen(1); // 1 px
    pen.setColor(pointsColor);
    QBrush brush;
    brush.setColor(pointsColor);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawRect(rect);

    pen.setColor(QColor(0, 0, 0));
    painter.setPen(pen);
    painter.drawText(rect, Qt::AlignCenter, Text, nullptr);
}


QRect HintBoxDrawer::Rect() const {
    return rect;
}
void HintBoxDrawer::setRect(const QRect &rect) {
    this->rect = rect;
    canvas->update();
}
