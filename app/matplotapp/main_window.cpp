#include "main_window.h"


MainWindow::MainWindow(QWidget* _parent)
	: QWidget(_parent)
	, m_mqt_widget(new MatQtWidget(this))
{
	ui.setupUi(this);

	ui.gridLayout->addWidget(m_mqt_widget);

	connect(ui.xSlider, SIGNAL(valueChanged(int)),this,SLOT(setXRatio(int)));
	connect(ui.ySlider, SIGNAL(valueChanged(int)),this,SLOT(setYRatio(int)));
}

MainWindow::~MainWindow()
{

}

MatQtWidget* MainWindow::matQt()
{
	return m_mqt_widget;
}

void MainWindow::setXRatio(int _value)
{

	m_mqt_widget->canvas()->setViewportRatioMode(GLView::VPRMode::CUSTOM);

	double x_ratio = (double)_value / (double)ui.xSlider->maximum() * 10;
	double y_ratio = (double)ui.ySlider->value() / (double)ui.ySlider->maximum() * 10;
	
	m_mqt_widget->canvas()->setViewportRatio(y_ratio / x_ratio);

}

void MainWindow::setYRatio(int _value)
{
	m_mqt_widget->canvas()->setViewportRatioMode(GLView::VPRMode::CUSTOM);

	double x_ratio = (double)ui.xSlider->value() / (double)ui.xSlider->maximum() * 10;
	double y_ratio = (double)_value / (double)ui.ySlider->maximum() * 10;

	m_mqt_widget->canvas()->setViewportRatio(y_ratio / x_ratio);
}
