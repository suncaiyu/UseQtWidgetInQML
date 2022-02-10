#include "WidgetOSRItem.h"
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QWindow>
#include <QQuickWindow>

WidgetOSRItem::WidgetOSRItem()
    :mOSRWidget(0)
{
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemIsFocusScope, true);
    setFlag(ItemHasContents, true);
}

void WidgetOSRItem::setOSRWidget(QVariant w)
{
    mOSRWidget = w.value<QWidget*>();
    if(mOSRWidget)
    {
        mOSRWidget->createWinId();
        mOSRWidget->installEventFilter(this);
		
		QWindow* pw = (QWindow*)(window());
		pw->installEventFilter(this);

        this->update();
    }
}

bool WidgetOSRItem::sendEventToOSRWidget(QEvent *e)
{
    QWindow* wHandle = mOSRWidget->windowHandle();
    bool res = false;
    if(wHandle)
    {
        res = qApp->sendEvent(wHandle, e);
    }

    return res;
}

void WidgetOSRItem::paint(QPainter *painter)
{
    painter->save();
    if(mOSRWidget == NULL)
    {
        painter->drawText(this->boundingRect(), Qt::AlignCenter, "painted item");
    }
    else
    {
        mOSRWidget->render(painter);
    }

    painter->restore();
}

bool WidgetOSRItem::eventFilter(QObject *obj, QEvent *e)
{
    QWindow* pw = (QWindow*)(window());
    bool res = QQuickPaintedItem::eventFilter(obj, e);
    if(obj == mOSRWidget)
    {
        switch(e->type())
        {
        case QEvent::Paint: //当OsrWidget paint的时候也触发自己paint
        {
            QPaintEvent* pe = (QPaintEvent*)e;
            this->update(pe->rect());
        }
            break;
        }
    }
    else if(obj == pw)
    {

        //* 如果是鼠标等（有鼠标坐标信息的事件。）的话我们得计算一下偏移量并修正一下，这里就只处理QMouseEvent和QWheelEvent作为示例
        //* 如果有其他类似的也需要修正，不然可能坐标偏移
        switch(e->type())
        {
        case QEvent::MouseButtonDblClick  :
        case QEvent::MouseButtonPress	  :
        case QEvent::MouseButtonRelease	  :
        case QEvent::MouseMove	          :
        case QEvent::MouseTrackingChange  :
        case QEvent::Move	              :
        {
            QMouseEvent *me = (QMouseEvent*)e;
            QEvent::Type type = me->type();
            QPointF localPosF = me->localPos();
            Qt::MouseButton mouseButton = me->button();
            Qt::MouseButtons mouseButtons = me->buttons();
            Qt::KeyboardModifiers modifiers = me->modifiers();

            //修正一下localpos
            QPointF offsetF = mapToScene(QPoint(0,0));
            QPointF diffPosF = localPosF - offsetF;

            QMouseEvent tme(type, diffPosF, mouseButton, mouseButtons, modifiers);
            sendEventToOSRWidget(&tme);
        }
            break;
        case QEvent::Wheel:
        {
            QWheelEvent *we = (QWheelEvent*)e;
            QPointF localPosF = we->posF();
            QPointF gloabalPosF = we->globalPosF();
            QPoint  pixelDelta = we->pixelDelta();
            QPoint  angleDelta = we->angleDelta();
            int qt4Delta = we->delta();
            Qt::Orientation orientation = we->orientation();
            Qt::MouseButtons mouseButtons = we->buttons();
            Qt::KeyboardModifiers modifiers = we->modifiers();

            //修正一下localpos
            QPointF offsetF = mapToScene(QPoint(0,0));
            QPointF diffPosF = localPosF - offsetF;

            QWheelEvent twe(diffPosF, gloabalPosF, pixelDelta, angleDelta, qt4Delta, orientation, mouseButtons, modifiers);
            sendEventToOSRWidget(&twe);
        }
            break;
        default:
        {
            sendEventToOSRWidget(e);
        }
            break;
        }
    }

    return res;
}

void WidgetOSRItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);

    if(mOSRWidget)
    {
        mOSRWidget->setGeometry(newGeometry.toRect());
    }
}


bool WidgetOSRItem::event(QEvent *e)
{
    return QQuickPaintedItem::event(e);;
}
