#pragma once

#include "ui_main_window.h"

#include "matqt_widget.h"

class MainWindow : public QWidget
{

	Q_OBJECT;

public:
	MainWindow(QWidget* _parent = nullptr);
	~MainWindow();

	MatQtWidget* matQt();

public slots:
	//void foo();
	void setXRatio(int _pos);
	void setYRatio(int _pos);

private:
	Ui::Form ui;
	MatQtWidget* m_mqt_widget;
	double m_vpr;

};

