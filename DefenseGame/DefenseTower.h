#ifndef DEFENSETOWER_H
#define DEFENSETOWER_H

#include <QWidget>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>

class DefenseTower : public QWidget
{
    Q_OBJECT

public:
    explicit DefenseTower(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
private:
    QPoint dragStartPosition;
    QPoint moveDelta;
    QPixmap towerPixmap;
    QPixmap scaledPixmap;

private:
    void removeGreenColor();


};

#endif // DEFENSETOWER_H
