#include "matqt.h"

#include "matqt_widget.h"

#include <future>
#include <iostream>
#include <matplot/core/figure_registry.h>
#include <matplot/core/figure_type.h>
#include <matplot/util/common.h>
#include <thread>

namespace matplot::backend {

	MatQt::MatQt(MatQtWidget* _widget)
		: m_widget(_widget)
	{
	}

	MatQt::~MatQt() {

	}

	bool MatQt::is_interactive() { return false; }

	const std::string& MatQt::output() {
		throw std::logic_error("output not implemented yet");
	}

	const std::string& MatQt::output_format() {
		throw std::logic_error("output_format not implemented yet");
	}

	bool MatQt::output(const std::string& filename) {
		throw std::logic_error("output not implemented yet");
	}

	bool MatQt::output(const std::string& filename,
		const std::string& file_format) {
		throw std::logic_error("output not implemented yet");
	}

	unsigned int MatQt::width() {
		return m_widget->canvas()->width();
	}

	unsigned int MatQt::height() {
		return m_widget->canvas()->height();
	}

	void MatQt::width(unsigned int new_width) {
		throw std::logic_error("width not implemented yet");
	}

	void MatQt::height(unsigned int new_height) {
		throw std::logic_error("height not implemented yet");
	}

	unsigned int MatQt::position_x() {
		throw std::logic_error("position_x not implemented yet");
	}

	unsigned int MatQt::position_y() {
		throw std::logic_error("position_y not implemented yet");
	}

	void MatQt::position_x(unsigned int new_position_x) {
		throw std::logic_error("position_x not implemented yet");
	}

	void MatQt::position_y(unsigned int new_position_y) {
		throw std::logic_error("position_y not implemented yet");
	}

	bool MatQt::new_frame() {
		m_widget->canvas()->renderBegin();
		return true;
	}

	bool MatQt::render_data()
	{
		m_widget->canvas()->renderEnd();
		return true;
	}

	void MatQt::draw_rectangle(const double x1, const double x2,
		const double y1, const double y2,
		const std::array<float, 4>& color)
	{
	}

	void MatQt::draw_background(const std::array<float, 4>& color) 
	{
	}

	void MatQt::show(class matplot::figure_type* f) 
	{
	}

	bool MatQt::supports_fonts() 
	{ 
		return false; 
	}

	bool MatQt::should_close()
	{
		return false;
	}

	void MatQt::window_title(const std::string& title)
	{
	}

	std::string MatQt::window_title()
	{
		return std::string();
	}

	void MatQt::draw_path(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::array<float, 4>& color)
	{
		m_widget->canvas()->drawPath(x, y, color);
	}

	void MatQt::draw_markers(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::vector<double>& z) 
	{
		m_widget->canvas()->drawMarkers(x, y, z);
	}

	void MatQt::draw_text(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::vector<double>& z) {
		throw std::logic_error("draw_text not implemented yet");
	}

	void MatQt::draw_image(const std::vector<std::vector<double>>& x,
		const std::vector<std::vector<double>>& y,
		const std::vector<std::vector<double>>& z) {
		throw std::logic_error("draw_image not implemented yet");
	}

	void MatQt::draw_triangle(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::vector<double>& z) 
	{
		m_widget->canvas()->drawTriangles(x, y, z);
	}

	void MatQt::draw_polygon(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::array<float, 4>>& node_colors)
	{
		m_widget->canvas()->drawPolygon(x, y, node_colors);
	}

	void MatQt::draw_polygon(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color)
	{
		m_widget->canvas()->drawPolygon(x, y, color);
	}

	void MatQt::draw_axis(double x_min, double x_max, double y_min, double y_max, const std::vector<double>& x_ticks, const std::vector<double>& y_ticks, const std::vector<double>& x_pos, const std::vector<double>& y_pos)
	{
		m_widget->setAxis(x_min, x_max, y_min, y_max,  x_ticks, y_ticks, x_pos, y_pos);
	}

	void MatQt::draw_colorbar(double contour_min, double contour_max, const std::vector<double>& contour_levels)
	{
		m_widget->setColorbar(contour_min, contour_max, contour_levels);
	}

	void MatQt::draw_labels(const std::string& x_label, const std::string& y_label)
	{
		m_widget->setXLabel(x_label);
		m_widget->setYLabel(y_label);
	}

	void MatQt::draw_title(const std::string& _title)
	{
		m_widget->setTitle(_title);
	}

} // namespace matplot::backend