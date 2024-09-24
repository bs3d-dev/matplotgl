#pragma once

#include <qwidget.h>

class TitleWidget : public QWidget
{

public:
	TitleWidget(QWidget* _parent = nullptr);
	TitleWidget();

	void setTitle(const std::string& _label);

protected:
	void paintEvent(QPaintEvent* _event) override;

private:
	std::string m_label;

};
