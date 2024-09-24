#pragma once

#include <qwidget.h>
#include <qpen.h>
#include <qbrush.h>

class Colorbar : public QWidget
{
public:
	Colorbar(QWidget* parent = nullptr);
	~Colorbar();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void setContourLevels(double contour_min, double contour_max, const std::vector<double>& contour_levels);

protected:
	void paintEvent(QPaintEvent* event) override;

private:

	double m_cmin;
	double m_cmax;
	std::vector<double> m_levels;

	QPen pen;
	QBrush brush;
	int m_top_margin;
	int m_bottom_margin;
	int m_left_margin;
	int m_right_margin;

};