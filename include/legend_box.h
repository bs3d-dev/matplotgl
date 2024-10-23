#pragma once

#include <QWidget>

namespace matplot
{
	class line_spec;
}

class LegendBox : public QWidget
{

public:
	LegendBox(QWidget* _parent = nullptr);
	~LegendBox();


	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void setLabels(const std::vector<std::string>& labels);
	void setLineSpecs(const std::vector<matplot::line_spec>& line_specs);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	std::vector<std::string> m_labels;
	std::vector<matplot::line_spec> m_line_specs;
};
