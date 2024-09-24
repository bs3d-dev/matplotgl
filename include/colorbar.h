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

	void setContourLevels(double contour_min, double contour_max, const std::vector<double>& contour_levels, const std::vector<std::string>& contour_labels, int _exp);

protected:
	void paintEvent(QPaintEvent* event) override;

private:

	double m_cmin;
	double m_cmax;
	std::vector<double> m_levels;
	std::vector<std::string> m_levels_labels;
	int m_exp;

	QPen pen;
	QBrush brush;
	int m_top_margin;
	int m_bottom_margin;
	int m_left_margin;
	int m_right_margin;

};