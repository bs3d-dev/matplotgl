#include "matqt_widget.h"

MatQtWidget::MatQtWidget(QWidget* _parent)
	: QWidget(_parent)
{
	ui.setupUi(this);
	reset();
}

MatQtWidget::~MatQtWidget()
{
}

void MatQtWidget::setXAxis(double x_min, double x_max, const std::vector<double>& x_ticks, const std::vector<std::string>& x_labels, int _exp)
{

	ui.xAxisWidget->setLimits(x_min, x_max);
	ui.xAxisWidget->setTicks(x_ticks, x_labels);
	ui.xAxisWidget->setExp(_exp);
	ui.xAxisWidget->update();

	ui.canvas->setXAxis(x_min, x_max, x_ticks);
}

void MatQtWidget::setYAxis(double y_min, double y_max, const std::vector<double>& y_ticks, const std::vector<std::string>& y_labels, int _exp)
{

	ui.yAxisWidget->setLimits(y_min, y_max);
	ui.yAxisWidget->setTicks(y_ticks, y_labels);
	ui.yAxisWidget->setExp(_exp);
	ui.yAxisWidget->update();

	ui.canvas->setYAxis(y_min, y_max, y_ticks);

	ui.canvas->update();
}

void MatQtWidget::setColorbar(double contour_min, double contour_max, const std::vector<double>& contour_levels, const std::vector<std::string>& contour_labels, int _exp)
{
	ui.colorbar->setContourLevels(contour_min, contour_max, contour_levels, contour_labels, _exp);
	ui.colorbar->update();
}

void MatQtWidget::setXLabel(const std::string& _x_label)
{
	ui.xAxisWidget->setLabel(_x_label);
}

void MatQtWidget::setYLabel(const std::string& _y_label)
{
	ui.yAxisWidget->setLabel(_y_label);
}

void MatQtWidget::setCBLabel(const std::string& _cb_label)
{
	ui.colorbar->setLabel(_cb_label);
}

void MatQtWidget::setTitle(const std::string& _title)
{
	ui.titleWidget->setTitle(_title);
	ui.titleWidget->update();
}

void MatQtWidget::setLegends(const std::vector<std::string>& labels, const std::vector<matplot::line_spec>& line_specs)
{
	ui.legendBoxWidget->setLabels(labels);
	ui.legendBoxWidget->setLineSpecs(line_specs);
	ui.legendBoxWidget->update();
	ui.legendBoxWidget->setVisible(true);
}

void MatQtWidget::pointCollected(double x, double y)
{
	for (auto observer : m_observers )
	{
		observer->pointCollected(x, y);
	}
}

void MatQtWidget::lineCollected(double x0, double y0, double x1, double y1)
{
	for (auto observer : m_observers )
	{
		observer->lineCollected(x0, y0, x1, y1);
	}
}

void MatQtWidget::polylineCollected(std::vector<double> x, std::vector<double> y)
{
	for (auto observer : m_observers)
	{
		observer->polylineCollected(x,y);
	}
}

void MatQtWidget::setXAxisVisible(bool _switch)
{
	ui.xAxisWidget->setVisible(_switch);
}

void MatQtWidget::setYAxisVisible(bool _switch)
{
	ui.yAxisWidget->setVisible(_switch);
}

void MatQtWidget::setTitleVisible(bool _switch)
{
	ui.titleWidget->setVisible(_switch);
}

void MatQtWidget::setColorbarVisible(bool _switch)
{
	ui.colorbar->setVisible(_switch);
}

void MatQtWidget::setLegendsVisible(bool _switch)
{
	ui.legendBoxWidget->setVisible(_switch);
}

void MatQtWidget::reset()
{
	ui.colorbar->hide();
	ui.legendBoxWidget->hide();
}

GLView* MatQtWidget::canvas()
{
	return ui.canvas;
}