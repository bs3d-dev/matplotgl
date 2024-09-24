#include "axis_widget.h"

#include <qpainter.h>
#include "util.h"

AxisWidget::AxisWidget(QWidget* _parent)
	: QWidget(_parent)
	, m_max(0.00)
	, m_min(0.00)
	, m_canvas_margin(10.0)
{
	pen = QPen(Qt::black, 0.00, Qt::PenStyle::SolidLine, Qt::PenCapStyle::FlatCap, Qt::PenJoinStyle::BevelJoin);
}

AxisWidget::~AxisWidget()
{
}

void AxisWidget::setLimits(double _min, double _max)
{
	m_min = _min;
	m_max = _max;
}

void AxisWidget::setTicks(const std::vector<double>& _ticks)
{
	m_ticks = _ticks;
}

void AxisWidget::setLabel(const std::string& _label)
{
	m_label = _label;
}

XAxisWidget::XAxisWidget(QWidget* _parent)
	: AxisWidget(_parent)
{
}

XAxisWidget::~XAxisWidget()
{
}

void XAxisWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(pen);

	QFontMetrics font_metrics = painter.fontMetrics();
	int font_max_width = font_metrics.maxWidth();
	int font_max_height = font_metrics.height();

	QRectF ticks_rect = rect() - QMargins(10.00, 0.00, 10.00, 0.00); ticks_rect.setHeight(font_max_height);

	// Draw ticks

		// Evaluate parametric values
	std::vector<double> ticks(m_ticks.size());
	for (int i = 0; i < m_ticks.size(); i++)
		ticks[i] = (m_ticks[i] - m_min) / (m_max - m_min);

	// Transform to pixel values
	std::vector<double> ticks_x(m_ticks.size());
	auto x2px = Param2Px{ ticks_rect.left(),ticks_rect.top(),ticks_rect.right(),ticks_rect.bottom() };
	for (int i = 0; i < m_ticks.size(); i++)
		ticks_x[i] = x2px.x(ticks[i]);

	//Draw tick labels
	QRectF text_rect(ticks_rect.topRight(), QSizeF(font_max_width, font_max_height));
	//text_rect.translate(0.00, 5.00);
	for (int i = 0; i < m_ticks.size(); i++)
	{
		text_rect.moveLeft(ticks_x[i] - font_max_width / 2.00);
		painter.drawText(text_rect, Qt::AlignTop | Qt::AlignHCenter, QString::number(m_ticks[i]));
	}

	// Draw label
	QRectF label_rect(ticks_rect.topLeft(), rect().bottomRight());
	painter.drawText(label_rect, Qt::AlignCenter, QString::fromStdString(m_label));

}

YAxisWidget::YAxisWidget(QWidget* _parent)
	: AxisWidget(_parent)
{
}

YAxisWidget::~YAxisWidget()
{
}

void YAxisWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(pen);

	QFontMetrics font_metrics = painter.fontMetrics();
	int font_max_width = font_metrics.maxWidth();
	int font_max_height = font_metrics.height();

	QRectF ticks_rect = rect() - QMargins(0.00, 10.00, 0.00, 10.00); /*ticks_rect.setWidth(font_max_width);*/

	// Draw ticks

		// Evaluate parametric values
	std::vector<double> ticks(m_ticks.size());
	for (int i = 0; i < m_ticks.size(); i++)
		ticks[i] = (m_ticks[i] - m_min) / (m_max - m_min);

	// Transform to pixel values
	std::vector<double> ticks_x(m_ticks.size());
	auto x2px = Param2Px{ ticks_rect.left(),ticks_rect.top(),ticks_rect.right(),ticks_rect.bottom() };
	for (int i = 0; i < m_ticks.size(); i++)
		ticks_x[i] = x2px.y(ticks[i]);

	//Draw tick labels
	QRectF text_rect(ticks_rect.topRight(), QSizeF(font_max_width, font_max_height));
	text_rect.translate(-font_max_width, 0.00);
	for (int i = 0; i < m_ticks.size(); i++)
	{
		text_rect.moveTop(ticks_x[i] - font_max_height/2.0);
		painter.drawText(text_rect, Qt::AlignVCenter | Qt::AlignRight, QString::number(m_ticks[i]));
	}

	// Draw label
	QRectF label_rect(ticks_rect.topLeft(), QPointF(text_rect.left(), ticks_rect.bottom()));
	painter.translate(label_rect.center());
	painter.rotate(-90);
	painter.drawText(0, 0, QString::fromStdString(m_label));
	painter.rotate(90);

}


QSize XAxisWidget::minimumSizeHint() const
{
	return QSize(500, 50);
}

QSize XAxisWidget::sizeHint() const
{
	return  QSize(500, 50);
}


QSize YAxisWidget::minimumSizeHint() const
{
	return QSize(50, 500);
}

QSize YAxisWidget::sizeHint() const
{
	return  QSize(50, 500);
}