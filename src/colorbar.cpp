#include "colorbar.h"

#include "colormap.h"
#include "util.h"
#include <qpainter.h>

Colorbar::Colorbar(QWidget* parent)
	: m_right_margin(0.00)
	, m_left_margin(0.00)
	, m_top_margin(30.00)
	, m_bottom_margin(10.00)
{
	pen = QPen(Qt::black, 0.00, Qt::PenStyle::SolidLine, Qt::PenCapStyle::FlatCap, Qt::PenJoinStyle::BevelJoin);
}

Colorbar::~Colorbar()
{
}

QSize Colorbar::minimumSizeHint() const
{
	return QSize(50,500);
}

QSize Colorbar::sizeHint() const
{
	return QSize(50,500);
}

void Colorbar::setContourLevels(double contour_min, double contour_max, const std::vector<double>& contour_levels, const std::vector<std::string>& contour_labels, int _exp)
{
	m_cmin = contour_min;
	m_cmax = contour_max;
	m_levels = contour_levels;
	m_levels_labels = contour_labels;
	m_exp = _exp;

	update();
}

void Colorbar::paintEvent(QPaintEvent* event)
{

	Colormap::Jet colormap;

	QLinearGradient linearGradient(0, 0, 0, this->height());
	int n_colors = colormap.length();
	for (double i = 0; i < n_colors; i++)
	{
		double t = i / (n_colors - 1);
		linearGradient.setColorAt(1-t, colormap.color(t));
	}
	brush = linearGradient;

	QPainter painter(this);
	painter.setPen(pen);
	painter.setBrush(brush);

	QFontMetrics font_metrics = painter.fontMetrics();
	int font_max_width = font_metrics.maxWidth();
	int font_max_height = font_metrics.height();

	// Draw colorbar
	QRectF canvas_rect = rect() - QMargins(m_left_margin, m_top_margin, m_right_margin, m_bottom_margin);
	canvas_rect.setWidth(30);
	painter.drawRect(canvas_rect);

	// Draw ticks

		// Evaluate parametric values
	std::vector<double> ticks(m_levels.size());
	for (int i = 0; i < m_levels.size(); i++)
		ticks[i] = (m_levels[i] - m_cmin) / (m_cmax - m_cmin); 

		// Transform to pixel values
	std::vector<double> ticks_y(m_levels.size());
	auto y2px = Param2Px{ canvas_rect.left(),canvas_rect.top(),canvas_rect.right(),canvas_rect.bottom() };
	for (int i = 0; i < m_levels.size(); i++)
		ticks_y[i] = y2px.y(ticks[i]);

		// Draw lines
	int tick_width = canvas_rect.width() / 3;
	int tick_x1 = canvas_rect.width();
	int tick_x2 = tick_x1 - tick_width;
	for (int i = 0; i < m_levels.size(); i++)
		painter.drawLine(QLineF(tick_x1, ticks_y[i], tick_x2, ticks_y[i]));

	 //Draw tick labels
	QRectF text_rect(canvas_rect.topRight(), QSizeF(font_max_width, font_max_height));
	text_rect.translate(5.00, 0.00);
	for (int i = 0; i < m_levels.size(); i++)
	{
		text_rect.moveTop(ticks_y[i] - font_max_height / 2.00);
		painter.drawText(text_rect, Qt::AlignBottom | Qt::AlignLeft, QString::fromStdString(m_levels_labels[i]));
	}

	//Draw exponential
	if (m_exp != 0)
	{

		QFont exp_font = painter.font();
		exp_font.setPointSizeF(exp_font.pointSize() / 1.25);
		QFontMetrics exp_metrics(exp_font);

		QRectF dec_exp_rect = rect();
		dec_exp_rect.setLeft(text_rect.left());
		QRectF dec_rect = font_metrics.boundingRect("x 10");
		QRectF exp_rect = exp_metrics.boundingRect(QString::number(m_exp));

		//dec_exp_rect.setLeft(dec_exp_rect.right() - dec_rect.width() - exp_rect.width() * 2);
		dec_exp_rect.setHeight(dec_rect.height() + exp_rect.height());

		painter.drawText(dec_exp_rect, Qt::AlignBottom | Qt::AlignLeft, QString("x 10"));

		dec_exp_rect.setBottomLeft(dec_exp_rect.bottomLeft() + dec_rect.topRight());

		painter.save();
		painter.setFont(exp_font);
		dec_exp_rect.translate(exp_rect.width() / 2, exp_rect.height() / 2);
		painter.drawText(dec_exp_rect, Qt::AlignBottom | Qt::AlignLeft, QString::number(m_exp));
		painter.restore();
	}

}
