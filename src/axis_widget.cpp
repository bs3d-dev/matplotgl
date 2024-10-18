#include "axis_widget.h"

#include <qpainter.h>
#include <qstatictext.h>
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

void AxisWidget::setTicks(const std::vector<double>& _ticks,const std::vector<std::string>& _ticks_labels)
{
	m_ticks = _ticks;
	m_ticks_labels = _ticks_labels;
}

void AxisWidget::setLabel(const std::string& _label)
{
	m_label = _label;
}

void AxisWidget::setExp(int _exp)
{
	m_exp = _exp;
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
	QRectF text_rect = ticks_rect;
	for (int i = 0; i < m_ticks.size(); i++)
	{
		text_rect.moveCenter(QPointF(ticks_x[i], text_rect.center().y()));
		painter.drawText(text_rect, Qt::AlignTop | Qt::AlignHCenter, QString::fromStdString(m_ticks_labels[i]));
	}

	//Draw exponential
	if (m_exp != 0)
	{

		QFont exp_font = painter.font();
		exp_font.setPointSizeF(exp_font.pointSize() / 1.25);
		QFontMetrics exp_metrics(exp_font);

		QRectF dec_exp_rect = ticks_rect;
		QRectF dec_rect = font_metrics.boundingRect("x 10");
		QRectF exp_rect = exp_metrics.boundingRect(QString::number(m_exp));

		dec_exp_rect.setLeft(dec_exp_rect.right() - dec_rect.width() - exp_rect.width()*2);
		dec_exp_rect.setTop(dec_exp_rect.top() + font_max_height);
		dec_exp_rect.setHeight(dec_rect.height() + exp_rect.height());

		painter.drawText(dec_exp_rect, Qt::AlignBottom | Qt::AlignLeft, QString("x 10"));

		dec_exp_rect.setBottomLeft(dec_exp_rect.bottomLeft() + dec_rect.topRight());

		painter.save();
		painter.setFont(exp_font);
		dec_exp_rect.translate(exp_rect.width() / 2, exp_rect.height() / 2);
		painter.drawText(dec_exp_rect, Qt::AlignBottom | Qt::AlignLeft, QString::number(m_exp));
		painter.restore();
	}

	// Draw label
	QRectF label_rect(ticks_rect.topLeft(), rect().bottomRight());
	painter.drawText(label_rect, Qt::AlignCenter, QString::fromLatin1(m_label.c_str()));

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
	int font_max_width = font_metrics.horizontalAdvance("0.000000");
	int font_max_height = font_metrics.height();

	QRectF ticks_rect = rect() - QMargins(0.00, 30.00, 0.00, 10.00); /*ticks_rect.setWidth(font_max_width);*/

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
		painter.drawText(text_rect, Qt::AlignVCenter | Qt::AlignRight, QString::fromStdString(m_ticks_labels[i]));
	}
	
	//Draw exponential
	if (m_exp != 0)
	{

		QFont exp_font = painter.font();
		exp_font.setPointSizeF(exp_font.pointSize() / 1.25);
		QFontMetrics exp_metrics(exp_font);

		QRectF dec_exp_rect = rect();
		QRectF dec_rect = font_metrics.boundingRect("x 10");
		QRectF exp_rect = exp_metrics.boundingRect(QString::number(m_exp));

		dec_exp_rect.setLeft(dec_exp_rect.right() - dec_rect.width() - exp_rect.width() * 2);
		dec_exp_rect.setHeight(dec_rect.height() + exp_rect.height());

		painter.drawText(dec_exp_rect, Qt::AlignBottom | Qt::AlignLeft, QString("x 10"));

		dec_exp_rect.setBottomLeft(dec_exp_rect.bottomLeft() + dec_rect.topRight());

		painter.save();
		painter.setFont(exp_font);
		dec_exp_rect.translate(exp_rect.width() / 2, exp_rect.height() / 2);
		painter.drawText(dec_exp_rect, Qt::AlignBottom | Qt::AlignLeft, QString::number(m_exp));
		painter.restore();
	}

	// Draw label
	QRectF label_rect(ticks_rect.topLeft(), QPointF(text_rect.left(), ticks_rect.bottom()));
	painter.translate(label_rect.center());
	painter.rotate(-90);
	painter.drawText(0, 0, QString::fromLatin1(m_label.c_str()));
	painter.rotate(90);

}


QSize XAxisWidget::minimumSizeHint() const
{
	return QSize(500, 75);
}

QSize XAxisWidget::sizeHint() const
{
	return  QSize(500, 75);
}


QSize YAxisWidget::minimumSizeHint() const
{
	return QSize(75, 500);
}

QSize YAxisWidget::sizeHint() const
{
	return  QSize(75, 500);
}