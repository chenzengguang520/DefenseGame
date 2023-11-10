#include "defensetower.h"

DefenseTower::DefenseTower(QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(50, 50);  // 设置防御塔的大小
    setAcceptDrops(true);  // 启用放置功能

    // 加载防御塔的图片
    towerPixmap.load("./images/Fortress/small1.BMP.");  // 替换为你的图片路径
}

void DefenseTower::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
        moveDelta = QPoint(0, 0);

        // 创建拖拽对象
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData;
        drag->setMimeData(mimeData);

        // 检查 towerPixmap 是否为空，如果为空，则不执行拖拽
        if (!towerPixmap.isNull()) {

    
            // 设置拖拽的图标
            drag->setPixmap(towerPixmap.scaled(size()));  // 可能需要调整缩放大小
            // 启动拖拽操作
            drag->exec(Qt::MoveAction);
        }
    }

    QWidget::mousePressEvent(event);
}


void DefenseTower::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - dragStartPosition;
        moveDelta = delta;
    }

    QWidget::mouseMoveEvent(event);
}

void DefenseTower::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // 处理防御塔放下的逻辑
        // ...


        moveDelta = QPoint(0, 0);  // 重置移动距离
    }

    QWidget::mouseReleaseEvent(event);
}

void DefenseTower::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void DefenseTower::dropEvent(QDropEvent* event)
{
    // 处理拖放事件
    // ...

    event->acceptProposedAction();
}

void DefenseTower::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), towerPixmap);
}


