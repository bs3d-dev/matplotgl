#pragma once

#include "qwidget.h"

#include <vector>
#include <string>
#include <qpen.h>

class AxisWidget : public QWidget
{

public:
	AxisWidget(QWidget* _parent = nullptr);
	~AxisWidget();

	virtual QSize minimumSizeHint() const = 0;
	virtual QSize sizeHint() const = 0;

	void setLimits(double _min, double _max);
	void setTicks(const std::vector<double>& _ticks, const std::vector<std::string>& _ticks_labels);
	void setLabel(const std::string& _label);
	void setExp(int _exp);

protected:
	virtual void paintEvent(QPaintEvent* event) = 0;

protected:
	double m_min;
	double m_max;
	std::vector<double> m_ticks;
	std::vector<std::string> m_ticks_labels;
	int m_exp;
	std::string m_label;
	QPen pen;
	int m_canvas_margin;
	//QBrush brush;

};

class XAxisWidget : public AxisWidget
{

public:
	XAxisWidget(QWidget* _parent = nullptr);
	~XAxisWidget();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent* event) override;
};

class YAxisWidget : public AxisWidget
{

public:
	YAxisWidget(QWidget* _parent = nullptr);
	~YAxisWidget();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent* event) override;
};

