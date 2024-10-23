#include "legend_box.h"

#include <qpen.h>
#include <qpainter.h>
#include <qstatictext.h>

#include "matplot/core/line_spec.h"

LegendBox::LegendBox(QWidget* _parent)
	:QWidget(_parent)
{
	
}

LegendBox::~LegendBox()
{
}

QSize LegendBox::minimumSizeHint() const
{
	return QSize(150, 200);
}

QSize LegendBox::sizeHint() const
{
	return QSize(300, 600);
}

void LegendBox::setLabels(const std::vector<std::string>& labels)
{
	m_labels = labels;
}

void LegendBox::setLineSpecs(const std::vector<matplot::line_spec>& line_specs)
{
	m_line_specs = line_specs;
}

void LegendBox::paintEvent(QPaintEvent* event)
{
	QPen pen = QPen(Qt::black, 0.00, Qt::PenStyle::SolidLine, Qt::PenCapStyle::FlatCap, Qt::PenJoinStyle::BevelJoin);
	QPainter painter(this);
	painter.setPen(pen);
	QFontMetricsF font_metrics = painter.fontMetrics();

	QRectF legend_rect = rect() - QMargins(10.00, 30.00, 10.00, 10.00); 

	QRectF curr_row = legend_rect;
	curr_row.setHeight(15.0);

	// Line length
	double line_length = 20.0;

	// Max horizontal length
	double max_h_length = 0.00;

	for (size_t i = 0; i < m_labels.size(); i++)
	{

		// Draw line 
		double x1 = curr_row.left();
		double x2 = x1 + line_length;
		double y1 = (curr_row.top() + curr_row.bottom()) / 2.0;
		double y2 = y1;

		// Set color
		matplot::color_array spec_color = m_line_specs[i].color();
		QColor qspec_color;
		qspec_color.setRedF(spec_color[1]);
		qspec_color.setGreenF(spec_color[2]);
		qspec_color.setBlueF(spec_color[3]);
		pen.setColor(qspec_color);
		painter.setPen(pen);

		painter.drawLine(QLineF(x1, y1, x2, y2));

		// Draw text
		pen.setColor(Qt::black);
		painter.setPen(pen);
		curr_row.translate(line_length + 5.0, 0);
		painter.drawText(curr_row, Qt::AlignVCenter | Qt::AlignLeft, QString::fromStdString(m_labels[i]));
		curr_row.translate(-line_length - 5.0, 15);

		// Get max length
		max_h_length = std::max(max_h_length, font_metrics.horizontalAdvance(QString::fromStdString(m_labels[i])))	;
	}

	QPointF legend_br(legend_rect.left() + line_length + max_h_length + 5.0, curr_row.bottom() - 15);
	legend_rect.setBottomRight(legend_br);

	pen.setColor(Qt::black);
	painter.setPen(pen);
	painter.drawRect(legend_rect);

}
