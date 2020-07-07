#include <QtGui>

class Window:public QWindow
{
public:
    Window(QWindow *parent=0)
        :QWindow(parent), m_backingStore(this)
		{
		}
protected:
    bool event(QEvent *evt)
		{
			if (evt->type()==QEvent::Expose || evt->type()==QEvent::Resize) {
				QRect rect(QPoint(), geometry().size());
				m_backingStore.resize(rect.size());
				m_backingStore.beginPaint(rect);

				QPainter p(m_backingStore.paintDevice());
				p.setBrush(Qt::blue);
				p.drawEllipse(rect);

				m_backingStore.endPaint();
				m_backingStore.flush(rect);

			}
			return QWindow::event(evt);
		}
private:
    QBackingStore m_backingStore;
};
