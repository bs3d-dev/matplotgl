#include "matqt_widget.h"

MatQtWidget::MatQtWidget(QWidget* _parent)
	: QMainWindow(_parent)
{
	ui.setupUi(this);
}

MatQtWidget::~MatQtWidget()
{
}

void MatQtWidget::setAxis(double x_min, double x_max, double y_min, double y_max, const std::vector<double>& x_ticks, const std::vector<double>& y_ticks, const std::vector<double>& x_pos, const std::vector<double>& y_pos)
{


	ui.xAxisWidget->setLimits(x_min, x_max);
	ui.xAxisWidget->setTicks(x_ticks);
	ui.xAxisWidget->update();

	ui.yAxisWidget->setLimits(y_min, y_max);
	ui.yAxisWidget->setTicks(y_ticks);
	ui.yAxisWidget->update();

	ui.canvas->setXAxis(x_min, x_max, x_ticks);
	ui.canvas->setYAxis(y_min, y_max, y_ticks);

}

void MatQtWidget::setColorbar(double contour_min, double contour_max, const std::vector<double>& contour_levels)
{
	ui.colorbar->setContourLevels(contour_min, contour_max, contour_levels);
}

void MatQtWidget::setXLabel(const std::string& _x_label)
{
	ui.xAxisWidget->setLabel(_x_label);
}

void MatQtWidget::setYLabel(const std::string& _y_label)
{
	ui.yAxisWidget->setLabel(_y_label);
}

void MatQtWidget::setTitle(const std::string& _title)
{
	ui.titleWidget->setTitle(_title);
}

GLView* MatQtWidget::canvas()
{
	return ui.canvas;
}
