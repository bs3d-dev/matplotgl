#pragma once

#include "ui_matqt_widget.h"

namespace matplot
{
	class line_spec;
}


class MatQtWidget : public QWidget
{


	Q_OBJECT;


public:
	MatQtWidget(QWidget* _parent = nullptr);
	~MatQtWidget();

	void setXAxis(double x_min, double x_max, const std::vector<double>& x_ticks, const std::vector<std::string>& x_labels, int _exp);
	void setYAxis(double y_min, double y_max, const std::vector<double>& y_ticks, const std::vector<std::string>& y_labels, int _exp);
	void setColorbar(double contour_min, double contour_max, const std::vector<double>& contour_levels, const std::vector<std::string>& contour_labels, int _exp);
	void setXLabel(const std::string& _x_label);
	void setYLabel(const std::string& _y_label);
	void setTitle(const std::string& _title);
	void setLegends(const std::vector<std::string>& labels, const std::vector<matplot::line_spec>& line_specs);
	void pointCollected(double x, double y);
	void lineCollected(double x0, double y0, double x1, double y1);
	void polylineCollected(std::vector<double> x, std::vector<double> y);

	void reset();

	GLView* canvas();

public slots:
	void openConfigurations();


private:
	Ui::MatQtWidget ui;

public:
	class Observer
	{
	public:
		virtual void polylineCollected(std::vector<double> x, std::vector<double> y) = 0;
		virtual void lineCollected(double x0, double y0, double x1, double y1) = 0;
		virtual void pointCollected(double x, double y) = 0;
	};

public:
	void attachObserver(Observer* _entry) { m_observers.push_back(_entry); };
	void clearObservers() { m_observers.clear(); };

private:
	std::list<Observer*> m_observers;

};



