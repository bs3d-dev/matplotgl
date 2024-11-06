//
// Created by Alan Freitas on 26/08/20.
//

#ifndef MATPLOTPLUSPLUS_OPENGL_EMBED_H
#define MATPLOTPLUSPLUS_OPENGL_EMBED_H

#include <matplot/detail/config.h>

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages on
	* Apple */
	/* What the hell is Apple thinking? */
#define GL_SILENCE_DEPRECATION
#endif

#include <matplot/backend/backend_interface.h>

#include <QMouseEvent>

class MatQtWidget;

namespace matplot::backend {
	class MATPLOT_EXPORTS MatQt : public backend_interface {

	public:
		MatQt(MatQtWidget* _widget);
		~MatQt();

	public:

		bool is_interactive() override;
		const std::string& output() override;
		const std::string& output_format() override;
		bool output(const std::string& filename) override;
		bool output(const std::string& filename,
			const std::string& file_format) override;
		unsigned int width() override;
		unsigned int height() override;
		void width(unsigned int new_width) override;
		void height(unsigned int new_height) override;
		unsigned int position_x() override;
		unsigned int position_y() override;
		void position_x(unsigned int new_position_x) override;
		void position_y(unsigned int new_position_y) override;
		bool new_frame() override;
		// This is only a demonstration that is blocking the main thread.
		// Because glfw does not work well with multiple threads,
		// the challenge is to run the rendering loop in another thread
		// while we see this function only to update what should be rendered.
		bool render_data() override;
		void show(matplot::figure_type*) override;
		bool supports_fonts() override;
		bool should_close() override;
		void window_title(const std::string& title) override;
		std::string window_title() override;

	public:
		void draw_background(const std::array<float, 4>& color) override;
		void draw_rectangle(const double x1, const double x2,
			const double y1, const double y2,
			const std::array<float, 4>& color) override;
		void draw_path(const std::vector<double>& x,
			const std::vector<double>& y,
			const std::array<float, 4>& color) override;
		void draw_markers(const std::vector<double>& x,
			const std::vector<double>& y,
			const std::vector<double>& z = {}) override;
		void draw_text(const std::vector<double>& x,
			const std::vector<double>& y,
			const std::vector<double>& z = {}) override;
		void
			draw_image(const std::vector<std::vector<double>>& x,
				const std::vector<std::vector<double>>& y,
				const std::vector<std::vector<double>>& z = {}) override;
		void draw_triangle(const std::vector<double>& x,
			const std::vector<double>& y,
			const std::vector<double>& z = {}) override;
		virtual void draw_polygon(const std::vector<double>& x,
			const std::vector<double>& y,
			const std::vector<std::array<float, 4>>& node_colors);

		virtual void draw_polygon(const std::vector<double>& x,
			const std::vector<double>& y,
			const std::array<float, 4>& color) override;

		void draw_axis(double x_min, double x_max, double y_min, double y_max, bool x_reverse, bool y_reverse) override;

		void draw_colorbar(double contour_min, double contour_max) override;
		void draw_labels(const std::string& x_label, const std::string& y_label) override;
		void draw_title(const std::string& _title) override;
		void	draw_legends(const std::vector<std::string>& labels, const std::vector<line_spec>& line_specs);

		void begin_point_collection();
		void begin_line_collection();

		// Mouse events slots
		void mouseDoubleClickEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		void wheelEvent(class QWheelEvent* _event);

	//protected:
		void updateAxis();

	private:
		MatQtWidget* m_widget;

		// Axes in world coordinates
		double m_xmin;
		double m_xmax;
		double m_ymin;
		double m_ymax;

		// Axes directions
		bool m_x_reverse;
		bool m_y_reverse;

		// Curve collection directions
		bool m_is_collecting_point;
		bool m_is_collecting_line;		
		bool m_is_first_pt;		

		// QPoint is a Qt class that defines a point in a plane
		// i.e. the position of the mouse on the canvas.
		QPoint m_pt0;             // mouse position at button press event
		QPoint m_pt1;             // current mouse position
		QPoint m_pt2;             // previous mouse position
		int m_mouseMoveTol;       // tolerance for mouse move

		double m_pt_x;
		double m_pt_y;
		double m_line_x0;
		double m_line_x1;
		double m_line_y0;
		double m_line_y1;
		double m_line_xtemp;
		double m_line_ytemp;
	};



} // namespace matplot::backend

#endif // MATPLOTPLUSPLUS_OPENGL_EMBED_H
