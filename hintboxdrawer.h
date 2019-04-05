#ifndef HINTBOXDRAWER_H
#define HINTBOXDRAWER_H

#include "drawer.h"
#include <QObject>
#include <QRect>
#include <QPropertyAnimation>

class HintBoxDrawer: public Drawer {
    Q_OBJECT
    Q_PROPERTY(QRect rect READ Rect WRITE setRect)

public:
    QString Text;

private:
    QRect rect;
    QPropertyAnimation* animation;

public:
    HintBoxDrawer(CanvasOpenGL*);
    virtual ~HintBoxDrawer();
    virtual void Draw(QColor pointsColor);

    QRect Rect() const;
    void setRect(const QRect &rect);
};

#endif // HINTBOXDRAWER_H
