#include "main_widget.h"

#include <qpainter.h>
#include <qmargins.h>

MainWidget::MainWidget(QWidget* _parent)
	: QWidget(_parent)
{
}

MainWidget::~MainWidget()
{
}

void MainWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect rect = this->rect() - QMargins(10.0, 10.0, 10.0, 10.0);
	painter.drawRect(rect);
}
