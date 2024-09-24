#pragma once

#include <qwidget.h>

class MainWidget : public QWidget
{

public:
	MainWidget(QWidget* _parent = nullptr);
	~MainWidget();

protected:
	virtual void paintEvent(QPaintEvent* event);



};
