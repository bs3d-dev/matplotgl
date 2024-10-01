#pragma once

#include "ui_matqt_widget.h"

class MatQtWidget : public QWidget
{


	//Q_OBJECT;


public:
	MatQtWidget(QWidget* _parent = nullptr);
	~MatQtWidget();

	void setXAxis(double x_min, double x_max, const std::vector<double>& x_ticks, const std::vector<std::string>& x_labels, int _exp);
	void setYAxis(double y_min, double y_max, const std::vector<double>& y_ticks, const std::vector<std::string>& y_labels, int _exp);
	void setColorbar(double contour_min, double contour_max, const std::vector<double>& contour_levels, const std::vector<std::string>& contour_labels, int _exp);
	void setXLabel(const std::string& _x_label);
	void setYLabel(const std::string& _y_label);
	void setTitle(const std::string& _title);

	GLView* canvas();


private:
	Ui::MatQtWidget ui;

};



