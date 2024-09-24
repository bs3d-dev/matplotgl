#pragma once

#include <QtOpenGL/QGLWidget>

class GLView : public QGLWidget
{

	Q_OBJECT;

public:
	GLView(QWidget* parent = 0);
	~GLView();

	// Display functions
	void scaleWorldWindow(double _scaleFac);

	int width() const;
	int height() const;

	void renderBegin();
	void renderEnd();

	void setXAxis(double _min, double _max, const std::vector<double>& _ticks);
	void setYAxis(double _min, double _max, const std::vector<double>& _ticks);

	void drawPath(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color);
	void drawMarkers(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z = {});
	void drawTriangles(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& z = {});
	void drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::array<float, 4>>& color);
	void drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color);

private:
	// Canvas predefined slots
	void initializeGL();
	void resizeGL(int _width, int _height);
	void paintGL();

	void drawXAxis();
	void drawYAxis();


	// Viewport properties
	int m_width;                   // width: GL canvas horizontal size
	int m_height;                   // height: GL canvas vertical size

	// Window properties
	GLdouble m_left;           // left limit of object space window
	GLdouble m_right;          // right limit of object space window
	GLdouble m_bottom;         // bottom limit of object space window
	GLdouble m_top;            // top limit of object space window

	// Display lists
	GLuint m_tempId;           // GL list index for temp display

	// Axis data
	double m_x_min;
	double m_x_max;
	double m_y_min;
	double m_y_max;

	std::vector<double> m_x_ticks;
	std::vector<double> m_y_ticks;

};
