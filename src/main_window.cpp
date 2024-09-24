#include "main_window.h"
#include "qfiledialog.h"
//#include <matplot/matplot.h>
//#include <thread>
#include "util.h"

#include <qlabel.h>
#include <qimagereader.h>
#include <qmessagebox.h>
#include <QColorSpace>


MainWindow::MainWindow(QWidget* _parent)
: QMainWindow(_parent)
{
	ui.setupUi(this);

	//ui.openGLWidget->makeDisplayModel();
}

MainWindow::~MainWindow()
{
}

GLView* MainWindow::view() const
{
	return ui.openGLWidget;
}

void MainWindow::setXLimits(double x_min, double x_max)
{
	ui.xminLabel->setText(QString::number(x_min));
	ui.xmaxLabel->setText(QString::number(x_max));
}

void MainWindow::setYLimits(double y_min, double y_max)
{
	ui.yminLabel->setText(QString::number(y_min));
	ui.ymaxLabel->setText(QString::number(y_max));
}
