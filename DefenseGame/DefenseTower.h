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
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPoint dragStartPosition;
    QPoint moveDelta;
    QPixmap towerPixmap;


};

#endif // DEFENSETOWER_H
