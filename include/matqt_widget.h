#pragma once

#include "ui_matqt_widget.h"

class MatQtWidget : public QMainWindow
{


	//Q_OBJECT;


public:
	MatQtWidget(QWidget* _parent = nullptr);
	~MatQtWidget();

	void setAxis(double x_min, double x_max, double y_min, double y_max, const std::vector<double>& x_ticks, const std::vector<double>& y_ticks, const std::vector<double>& x_pos, const std::vector<double>& y_pos);
	void setColorbar(double contour_min, double contour_max, const std::vector<double>& contour_levels);
	void setXLabel(const std::string& _x_label);
	void setYLabel(const std::string& _y_label);
	void setTitle(const std::string& _title);

	GLView* canvas();


private:
	Ui::MatQtWidget ui;

};



