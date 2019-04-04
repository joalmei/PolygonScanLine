#include "hintboxdrawer.h"
#include "canvasopengl.h"


HintBoxDrawer::~HintBoxDrawer() { }

void HintBoxDrawer::Draw(CanvasOpenGL* canvas, QColor pointsColor) {
    QPainter painter(canvas);

    QPen pen(1); // 1 px
    pen.setColor(pointsColor);
    QBrush brush;
    brush.setColor(pointsColor);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    QRect rect(0,0, canvas->width(), 20);
    painter.drawRect(rect);

    pen.setColor(QColor(0, 0, 0));
    painter.setPen(pen);
    painter.drawText(rect, Qt::AlignCenter, Text, nullptr);
}
