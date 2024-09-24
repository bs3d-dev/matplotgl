#include "title_widget.h"

#include <qpainter.h>

TitleWidget::TitleWidget(QWidget* _parent)
	: QWidget(_parent)
{
}

TitleWidget::TitleWidget()
{
}

void TitleWidget::setTitle(const std::string& _label)
{
	m_label = _label;
}

void TitleWidget::paintEvent(QPaintEvent* _event)
{
	QPainter painter(this);
	painter.drawText(rect(), Qt::AlignCenter, QString::fromStdString(m_label));
}
