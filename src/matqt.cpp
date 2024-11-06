#include "matqt.h"

#include "matqt_widget.h"
#include "util.h"

#include <future>
#include <iostream>
#include <matplot/core/figure_registry.h>
#include <matplot/util/common.h>
#include <thread>
#include <QMouseEvent>

namespace matplot::backend {

	MatQt::MatQt(MatQtWidget* _widget)
		: m_widget(_widget)
		, m_x_reverse(false)
		, m_y_reverse(false)
		, m_mouseMoveTol(10)
		, m_is_collecting_line(false)
		, m_is_collecting_point(false)
		, m_is_first_pt(false)
	{
		m_widget->canvas()->setBackEnd(this);
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
		return m_widget->canvas()->worldWidth();
	}

	unsigned int MatQt::height() {
		return m_widget->canvas()->worldHeight();
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
		m_widget->reset();
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

	void MatQt::draw_axis(double x_min, double x_max, double y_min, double y_max, bool x_reverse, bool y_reverse)
	{
		// Store limits
		m_xmin = x_min;
		m_xmax = x_max;
		m_ymin = y_min;
		m_ymax = y_max;

		// Store directions
		m_x_reverse = x_reverse;
		m_y_reverse = y_reverse;

		updateAxis();
	}

	void MatQt::draw_colorbar(double contour_min, double contour_max)
	{

		if (isnan(contour_min) || isnan(contour_max))
		{
			m_widget->setColorbar(contour_min, contour_max, {}, {}, 0);
			return;
		}			

		if (contour_min == contour_max)
		{
			if (contour_min < 0)
				contour_max = 0.99 * contour_min;
			else
				contour_max = 1.01 * contour_min;
		}

		matplot::ticks_results cticks_results = matplot::calcticks(contour_min, contour_max);

		m_widget->setColorbar(contour_min, contour_max,cticks_results.ticks,cticks_results.tickLabels,cticks_results.expDec);
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

	void MatQt::draw_legends(const std::vector<std::string>& labels, const std::vector<line_spec>& line_specs)
	{
		m_widget->setLegends(labels, line_specs);
	}

	void MatQt::begin_point_collection()
	{
		m_is_collecting_point = true;		
		m_is_collecting_line = false;
		m_widget->setCursor(Qt::CrossCursor);
	}

	void MatQt::begin_line_collection()
	{
		m_is_collecting_line = true;
		m_is_first_pt = true;
		m_is_collecting_point = false;
		m_widget->setCursor(Qt::CrossCursor);
	}

	void MatQt::mouseDoubleClickEvent(QMouseEvent* event)
	{
		Qt::MouseButton mouseButton = event->button();
		if (mouseButton == Qt::MiddleButton)
		{
			// Fit canvas
			m_widget->canvas()->fitWorldToViewport();
		}
	}

	void MatQt::mousePressEvent(QMouseEvent* event)
	{
		m_pt0 = event->pos();
		Qt::MouseButton mouseButton = event->button();
	}

	void MatQt::mouseReleaseEvent(QMouseEvent* event)
	{
		// Get current mouse position
		m_pt1 = event->pos();

		Qt::MouseButton mouseButton = event->button();
		if (mouseButton == Qt::LeftButton)
		{
			if (m_is_collecting_line)
			{
				// Only consider current point if left mouse point was used and
				// if it is on the same location of button press point.
				if ((abs(m_pt0.x() - m_pt1.x()) <= m_mouseMoveTol) &&
					(abs(m_pt0.y() - m_pt1.y()) <= m_mouseMoveTol))
				{
					if (m_is_first_pt)
					{
						m_line_x0 = m_widget->canvas()->worldXCoord(m_pt1.x());
						m_line_y0 = m_widget->canvas()->worldYCoord(m_pt1.y());
						m_is_first_pt = false;
					}						
					else
					{
						m_line_x1 = m_widget->canvas()->worldXCoord(m_pt1.x());
						m_line_y1 = m_widget->canvas()->worldYCoord(m_pt1.y());
						m_widget->canvas()->tempBegin();
						m_widget->canvas()->tempEnd();
						m_widget->canvas()->update();
						m_is_collecting_line = false;
						m_is_first_pt = true;
						m_widget->lineCollected(m_line_x0, m_line_y0, m_line_x1, m_line_y1);
						m_widget->setCursor(Qt::ArrowCursor);
					}
				}					
			}			
			else if (m_is_collecting_point)
			{
				// Only consider current point if left mouse point was used and
				// if it is on the same location of button press point.
				if ((abs(m_pt0.x() - m_pt1.x()) <= m_mouseMoveTol) &&
					(abs(m_pt0.y() - m_pt1.y()) <= m_mouseMoveTol))
				{
						m_pt_x = m_widget->canvas()->worldXCoord(m_pt1.x());
						m_pt_y = m_widget->canvas()->worldYCoord(m_pt1.y());
						m_is_collecting_point = false;
						m_widget->pointCollected(m_pt_x, m_pt_y);
						m_widget->setCursor(Qt::ArrowCursor);
				}
			}
		}
	}

	void MatQt::mouseMoveEvent(QMouseEvent* event)
	{
		
		// Get current mouse position
		m_pt1 = event->pos();
		Qt::MouseButtons mouseButton = event->buttons();
		if (mouseButton & Qt::MiddleButton)
		{
			// Pan canvas
			QPoint delta = (m_pt1 - m_pt0);
			double x = -(double)delta.x() / (double)m_widget->canvas()->width();
			double y = (double)delta.y() / (double)m_widget->canvas()->height();
			m_widget->canvas()->panWorldWindow(x, y);

			// Store last point
			m_pt0 = m_pt1;
		}
		else/* if (mouseButton & Qt::NoButton)*/
		{
			// Only consider current point if left mouse button was used,
			// if not button pressed, and if current point is not at the
			// same location of button press point.
			if ((abs(m_pt0.x() - m_pt1.x()) > m_mouseMoveTol) ||
				(abs(m_pt0.y() - m_pt1.y()) > m_mouseMoveTol))
			{
				if (m_is_collecting_line && !m_is_first_pt)
				{
					// Convert current mouse position point to world coordinates
					m_line_xtemp = m_widget->canvas()->worldXCoord(m_pt1.x());
					m_line_ytemp = m_widget->canvas()->worldYCoord(m_pt1.y());
					// Render temp line
					m_widget->canvas()->tempBegin();
					draw_path({ m_line_x0,m_line_xtemp }, { m_line_y0,m_line_ytemp }, { 0, 0, 0, 0 });
					m_widget->canvas()->tempEnd();
					m_widget->canvas()->update();
				}
			}
		}
	}

	void MatQt::wheelEvent(QWheelEvent* _event)
	{

		// Zoom in/out
		double delta = 1 - (double)_event->angleDelta().y() / 1200.0;
		int w = m_widget->canvas()->width();
		int h = m_widget->canvas()->height();
		m_widget->canvas()->scaleWorldWindow(delta, (double)_event->position().x() / (double)w, 1.0 - (double)_event->position().y() / (double)h);
	}

	void MatQt::updateAxis()
	{

		// Adjust axis
		double cleft = m_widget->canvas()->worldLeft();
		double cright = m_widget->canvas()->worldRight();
		double cbottom = m_widget->canvas()->worldBottom();
		double ctop = m_widget->canvas()->worldTop();

		double ymin;
		double ymax;
		if (m_y_reverse)
		{
			ymax = interp1(m_ymax, m_ymin, cbottom);
			ymin = interp1(m_ymax, m_ymin, ctop);
		}
		else
		{
			ymin = interp1(m_ymin, m_ymax, cbottom);
			ymax = interp1(m_ymin, m_ymax, ctop);
		}

		double xmin;
		double xmax;
		if (m_x_reverse)
		{
			xmax = interp1(m_xmax, m_xmin, cleft);
			xmin = interp1(m_xmax, m_xmin, cright);
		}
		else
		{
			xmin = interp1(m_xmin, m_xmax, cleft);
			xmax = interp1(m_xmin, m_xmax, cright);
		}
		
		// Evaluate nice ticks
		matplot::ticks_results results_x = matplot::calcticks(xmin, xmax, true, 0.02*(xmax-xmin));
		matplot::ticks_results results_y = matplot::calcticks(ymin, ymax);

		if (m_x_reverse)
		{
			for (double& x : results_x.ticks)
				x = xmin + xmax - x;
		}

		if (m_y_reverse)
		{
			for (double& y : results_y.ticks)
				y = ymin + ymax - y;
		}

		// Update axis
		m_widget->setXAxis(xmin, xmax, results_x.ticks, results_x.tickLabels, results_x.expDec);
		m_widget->setYAxis(ymin, ymax, results_y.ticks, results_y.tickLabels, results_y.expDec);
	}

} // namespace matplot::backend