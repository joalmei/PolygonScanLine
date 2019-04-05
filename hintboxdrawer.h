#ifndef HINTBOXDRAWER_H
#define HINTBOXDRAWER_H

#include "drawer.h"
#include <QObject>
#include <QRect>
#include <QPropertyAnimation>
#include <QPointer>

class HintBoxDrawer: public Drawer {
    Q_OBJECT
    Q_PROPERTY(QRect rect READ Rect WRITE setRect)

public:
    QString Text;

private:
    QRect rect;
    QPointer<QPropertyAnimation> animation; // a smart pointer is used because an animation autodestructs
                                            // when finished (only way to check if object was destroyed)

public:
    HintBoxDrawer(CanvasOpenGL*);
    virtual ~HintBoxDrawer();

    virtual void Draw(QColor pointsColor);

    // ACCESSORS
    QRect Rect() const;
    void setRect(const QRect &rect);

    // ANIMATION METHODS
    void Show();
    void Dismiss();
};

#endif // HINTBOXDRAWER_H
