#include "hintboxdrawer.h"
#include "canvasopengl.h"

// ==================================================================================================
#define BOX_HEIGHT 20
#define ANIM_DURATION 800

// ==================================================================================================
HintBoxDrawer::HintBoxDrawer(CanvasOpenGL* canvas) : Drawer(canvas) {
    animation = nullptr;
    Show();
}

// ==================================================================================================
HintBoxDrawer::~HintBoxDrawer() {
     if (animation != nullptr) { animation->stop(); }
}

// ==================================================================================================
void HintBoxDrawer::Draw(QColor pointsColor) {
    QPainter painter(canvas);

    QBrush brush(pointsColor, Qt::SolidPattern);
    QPen pen(pointsColor);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(rect);

    pen.setColor(QColor(0, 0, 0));
    painter.setPen(pen);
    painter.drawText(rect, Qt::AlignCenter, Text, nullptr);
}


// ==================================================================================================
QRect HintBoxDrawer::Rect() const {
    return rect;
}

// ==================================================================================================
void HintBoxDrawer::setRect(const QRect &rect) {
    this->rect = rect;
    canvas->update();
}

// ==================================================================================================
void HintBoxDrawer::Show() {
    if (animation != nullptr) { animation->stop(); }

    animation = new QPropertyAnimation(this, "rect");
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setDuration(ANIM_DURATION);
    animation->setStartValue(QRect(0, 0, canvas->width(), 0));
    animation->setEndValue(QRect(0, 0, canvas->width(), BOX_HEIGHT));

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// ==================================================================================================
void HintBoxDrawer::Dismiss() {
    if (animation != nullptr) { animation->stop(); }

    animation = new QPropertyAnimation(this, "rect");
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->setDuration(ANIM_DURATION);
    animation->setStartValue(QRect(0, 0, canvas->width(), BOX_HEIGHT));
    animation->setEndValue(QRect(0, 0, canvas->width(), 0));

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
