//
// Created by Alan Freitas on 26/08/20.
//

#include "main_window.h"
#include "opengl_view.h"
#include <future>
#include <iostream>
#include <matplot/core/figure_registry.h>
#include <matplot/core/figure_type.h>
#include <matplot/util/common.h>
#include <thread>

namespace matplot::backend {

	opengl_embed::opengl_embed(GLView* _view, MainWindow* _window)
		: m_view(_view)
		, m_window(_window)
	{
	}

	opengl_embed::~opengl_embed() {

	}

	bool opengl_embed::is_interactive() { return false; }

	const std::string& opengl_embed::output() {
		throw std::logic_error("output not implemented yet");
	}

	const std::string& opengl_embed::output_format() {
		throw std::logic_error("output_format not implemented yet");
	}

	bool opengl_embed::output(const std::string& filename) {
		throw std::logic_error("output not implemented yet");
	}

	bool opengl_embed::output(const std::string& filename,
		const std::string& file_format) {
		throw std::logic_error("output not implemented yet");
	}

	unsigned int opengl_embed::width() {
		return m_view->width();
	}

	unsigned int opengl_embed::height() {
		return m_view->height();
	}

	void opengl_embed::width(unsigned int new_width) {
		throw std::logic_error("width not implemented yet");
	}

	void opengl_embed::height(unsigned int new_height) {
		throw std::logic_error("height not implemented yet");
	}

	unsigned int opengl_embed::position_x() {
		throw std::logic_error("position_x not implemented yet");
	}

	unsigned int opengl_embed::position_y() {
		throw std::logic_error("position_y not implemented yet");
	}

	void opengl_embed::position_x(unsigned int new_position_x) {
		throw std::logic_error("position_x not implemented yet");
	}

	void opengl_embed::position_y(unsigned int new_position_y) {
		throw std::logic_error("position_y not implemented yet");
	}

	bool opengl_embed::new_frame() { 
		m_view->renderBegin();
		return true; 
	}

	bool opengl_embed::render_data() 
	{
		m_view->renderEnd();
		return true;
	}

	void opengl_embed::draw_rectangle(const double x1, const double x2,
		const double y1, const double y2,
		const std::array<float, 4>& color)
	{

		//glColor3f(color[0],color[1],color[2]); 
		//glBegin(GL_QUADS);
		//glVertex2f(x1, y1); // vertex 1
		//glVertex2f(x2, y1); // vertex 2
		//glVertex2f(x2, y2); // vertex 3
		//glVertex2f(x1, y2); // vertex 4
		//glEnd();

	}

	void opengl_embed::draw_background(const std::array<float, 4>& color) {
		//glClearColor(color[1], color[2], color[3], 1.f - color[0]);
		//glClear(GL_COLOR_BUFFER_BIT);
	}

	void opengl_embed::show(class matplot::figure_type* f) {
		//backend_interface::show(f);
	}

	bool opengl_embed::supports_fonts() { return false; }

	void opengl_embed::draw_path(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::array<float, 4>& color) 
	{
	}

	void opengl_embed::draw_markers(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::vector<double>& z) {
	}

	void opengl_embed::draw_text(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::vector<double>& z) {
		throw std::logic_error("draw_text not implemented yet");
	}

	void opengl_embed::draw_image(const std::vector<std::vector<double>>& x,
		const std::vector<std::vector<double>>& y,
		const std::vector<std::vector<double>>& z) {
		throw std::logic_error("draw_image not implemented yet");
	}

	void opengl_embed::draw_triangle(const std::vector<double>& x,
		const std::vector<double>& y,
		const std::vector<double>& z) {
	}

	void opengl_embed::draw_axis(double x_min, double x_max, double y_min, double y_max, const std::vector<double>& x_ticks, const std::vector<double>& y_ticks, const std::vector<double>& x_pos, const std::vector<double>& y_pos)
	{
		m_window->setXLimits(x_min,x_max);
		m_window->setYLimits(y_min,y_max);
	}

	void opengl_embed::draw_colorbar(double x_min, double x_max, double y_min, double y_max, const std::vector<double>& x_ticks, const std::vector<double>& y_ticks, const std::vector<double>& x_pos, const std::vector<double>& y_pos)
	{

	}

} // namespace matplot::backend