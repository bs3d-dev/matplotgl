#include "glview.h"

#include "matqt.h"
#include <array>
#include "util.h"

GLView::GLView(QWidget* parent)
	: QGLWidget(parent)
	, m_is_rendering(false)
	, m_has_plot(false)
	, m_backend(nullptr)
	, m_left(0)
	, m_right(1)
	, m_bottom(0)
	, m_top(1)
{
	// Set mouse tracking
	setMouseTracking(true);
}

GLView::~GLView()
{
}

void GLView::initializeGL()
{
	// Set white as background color and clear window
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	m_tempId = glGenLists(1);
}

void GLView::resizeGL(int _width, int _height)
{
	// Avoid division by zero
	if (_width == 0) _width = 1;

	// Store GL canvas sizes in object properties
	m_width = _width;
	m_height = _height;

	// Setup the viewport to canvas dimensions
	glViewport(0, 0, (GLint)m_width, (GLint)m_height);

	// Reset the coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish the clipping volume by setting up an
	// orthographic projection
	glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);

	// Setup display in model coordinates
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLView::paintGL()
{
	if (m_is_rendering)
		return;

	//Clear the buffer with the current clear color
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw model's data
	glCallList(m_tempId);

	// Draw border
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_left, m_top);
	glVertex2f(m_left, m_bottom);
	glVertex2f(m_right, m_bottom);
	glVertex2f(m_right, m_top);
	glEnd();

	drawXAxis();
	drawYAxis();

}

void GLView::drawXAxis()
{
	// Evaluate parametric values
	std::vector<double> ticks(m_x_ticks.size());
	for (int i = 0; i < m_x_ticks.size(); i++)
		ticks[i] = (m_x_ticks[i] - m_x_min) / (m_x_max - m_x_min);

	// Get world coordinates
	ticks = interp1(m_left, m_right, ticks);

	// Draw ticks
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	for (int i = 0; i < ticks.size(); i++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2d(ticks[i], m_bottom);
		glVertex2d(ticks[i], m_bottom + 0.015*(m_top - m_bottom));
		glEnd();
	}	
}

void GLView::drawYAxis()
{
	// Evaluate parametric values
	std::vector<double> ticks(m_y_ticks.size());
	for (int i = 0; i < m_y_ticks.size(); i++)
		ticks[i] = (m_y_ticks[i] - m_y_min) / (m_y_max - m_y_min);

	// Get world coordinates
	ticks = interp1(m_bottom, m_top, ticks);

	// Draw ticks
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	for (int i = 0; i < ticks.size(); i++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2d(m_left, ticks[i]);
		glVertex2d(m_left + 0.015*(m_right - m_left),ticks[i]);
		glEnd();
	}
}

void GLView::scaleWorldWindow(double _scaleFac)
{
	double vpr;          // viewport distortion ratio
	double cx, cy;       // window center
	double sizex, sizey; // window sizes

	//Compute canvas viewport ratio.
	vpr = (double)m_height / (double)m_width;

	// Set new window sizes based on scaling factor.
	/*** COMPLETE HERE - GLCANVAS: 02 ***/
	sizex = (m_right - m_left);
	sizey = (m_top - m_bottom);
	/*** COMPLETE HERE - GLCANVAS: 02 ***/

	// Get current window center.
	/*** COMPLETE HERE - GLCANVAS: 01 ***/
	cx = m_left + sizex * 0.5;
	cy = m_bottom + sizey * 0.5;
	/*** COMPLETE HERE - GLCANVAS: 01 ***/

	// Adjust window to keep the same aspect ratio of the viewport.
	/*** COMPLETE HERE - GLCANVAS: 03 ***/
	double wr = sizey / sizex;
	if (wr < vpr) sizey = sizex * vpr;
	else  sizex = sizey / vpr;
	m_left = cx - sizex * 0.5 * _scaleFac;
	m_right = cx + sizex * 0.5 * _scaleFac;
	m_bottom = cy - sizey * 0.5 * _scaleFac;
	m_top = cy + sizey * 0.5 * _scaleFac;
	/*** COMPLETE HERE - GLCANVAS: 03 ***/

	// Establish the clipping volume by setting up an
	// orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);

	//drawAttributes();
	update();
}

void GLView::scaleWorldWindow(double _scaleFac, double _pcx, double _pcy)
{
	double cx, cy;       // window center
	double sizex, sizey; // window sizes

	// Set new window sizes based on scaling factor.
	sizex = (m_right - m_left);
	sizey = (m_top - m_bottom);

	// Get current window center.
	cx = m_left + sizex * _pcx;
	cy = m_bottom + sizey * _pcy;

	// Adjust window 
	double szLeft = sizex * _pcx;
	double szBottom = sizey * _pcy;
	m_left = cx - szLeft * _scaleFac;
	m_right = cx + (sizex - szLeft) * _scaleFac;
	m_bottom = cy - szBottom * _scaleFac;
	m_top = cy + (sizey - szBottom) * _scaleFac;

	// Establish the clipping volume by setting up an
	// orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);

	update();
}

void GLView::panWorldWindow(double _panFacX, double _panFacY)
{
	// Compute pan distances in horizontal and vertical directions.
	double panX = (m_right - m_left) * _panFacX;
	double panY = (m_top - m_bottom) * _panFacY;

	// Shift current window.
	m_right += panX;
	m_left += panX;
	m_top += panY;
	m_bottom += panY;

	// Establish the clipping volume by setting up an
	// orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);

	update();
}

void GLView::fitWorldToViewport()
{
	m_left = 0.0;
	m_right = 1.0;
	m_bottom = 0.0;
	m_top = 1.0;

	// Establish the clipping volume by setting up an
	// orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);

	update();
}

double GLView::worldLeft() const
{
	return m_left;
}

double GLView::worldRight() const
{
	return m_right;
}

double GLView::worldBottom() const
{
	return m_bottom;
}

double GLView::worldTop() const
{
	return m_top;
}

int GLView::worldWidth() const
{
	return 1.0;
}

int GLView::worldHeight() const
{
	return 1.0;
}

int GLView::width() const
{
	return m_width;
}

int GLView::height() const
{
	return m_height;
}

double GLView::worldXCoord(double _x_screen)
{
	double sizex = (m_right - m_left);
	return m_left + sizex * _x_screen/m_width;
}

double GLView::worldYCoord(double _y_screen)
{
	double sizey = (m_top - m_bottom);
	return m_top - sizey * _y_screen/m_height;
}

void GLView::renderBegin()
{
	glNewList(m_tempId, GL_COMPILE);
	m_is_rendering = true;
	m_has_plot = false;
}

void GLView::renderEnd()
{
	glEndList();
	m_is_rendering = false;
	m_has_plot = true;
}

void GLView::setBackEnd(matplot::backend::MatQt* _backend)
{
	m_backend = _backend;
}

void GLView::setXAxis(double _min, double _max, const std::vector<double>& _ticks)
{
	m_x_min = _min;
	m_x_max = _max;
	m_x_ticks = _ticks;
}

void GLView::setYAxis(double _min, double _max, const std::vector<double>& _ticks)
{
	m_y_min = _min;
	m_y_max = _max;
	m_y_ticks = _ticks;
}

void GLView::drawPath(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color)
{
	// Set line color
	glColor3d(color[1], color[2], color[3]);

	// Set line width
	glLineWidth(1.0);

	// Draw lines
	glBegin(GL_LINE_STRIP);
	for (int j = 0; j < x.size(); j++)
		glVertex2d(x[j], y[j]);
	glEnd();
}

void GLView::drawMarkers(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z)
{

	// Set point size
	glPointSize(5.0);

	// Set color
	glColor3d(1.0, 0.0, 0.0);

 // Draw markers
	glBegin(GL_POINTS);
	for (int n = 0; n < x.size(); n++)
		glVertex2d(x[n], y[n]);
	glEnd();
}

void GLView::drawTriangles(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z)
{

	// Set color
	glColor3d(1.0, 0.0, 0.0);

	// Draw triangles
	for (int j = 0; j < x.size(); j++) 
	{
		glBegin(GL_TRIANGLES);
		glVertex2d(x[0], y[0]);
		glVertex2d(x[1], y[1]);
		glVertex2d(x[2], y[2]);
		glEnd();
	}

}

void GLView::drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::array<float, 4>>& color)
{
	glBegin(GL_POLYGON);
	// Draw polygon
	for (int j = 0; j < x.size(); j++)
	{
		glColor3d(color[j][1], color[j][2], color[j][3]);
		glVertex2d(x[j], y[j]);
	}
	glEnd();
}

void GLView::drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color)
{
	glBegin(GL_POLYGON);
	// Draw polygon
	glColor3d(color[1], color[2], color[3]);
	for (int j = 0; j < x.size(); j++)
	{
		glVertex2d(x[j], y[j]);
	}
	glEnd();
}

void GLView::mouseDoubleClickEvent(QMouseEvent* _event)
{
	m_backend->mouseDoubleClickEvent(_event);
}

void GLView::mousePressEvent(QMouseEvent* _event)
{
	m_backend->mousePressEvent(_event);

	Qt::MouseButton mouseButton = _event->button();
	if (mouseButton == Qt::MiddleButton)
		setCursor(Qt::ClosedHandCursor);
}

void GLView::mouseMoveEvent(QMouseEvent* _event)
{

	if (!m_has_plot)
		return;

	QPoint pt = _event->pos();
	double xi = worldXCoord(pt.x()); double eps = worldYCoord(pt.y());
	double x = m_x_min + (m_x_max - m_x_min) * xi;
	double y = m_y_min + (m_y_max - m_y_min) * eps;
	emit currentWorldCoord(x, y);		

	m_backend->mouseMoveEvent(_event);
	update();	
}

void GLView::wheelEvent(QWheelEvent* _event)
{
	m_backend->wheelEvent(_event);
}
