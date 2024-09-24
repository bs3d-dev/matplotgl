#pragma once

#include "ui_main_window.h"
#include <QImage>

class QLabel;

class MainWindow : public QMainWindow
{

	Q_OBJECT;

public:
	MainWindow(QWidget* _parent = nullptr);
	~MainWindow();

	GLView* view() const;
	void setXLimits(double x_min, double x_max);
	void setYLimits(double y_min, double y_max);

private:
	Ui::MainWindow ui;

};



