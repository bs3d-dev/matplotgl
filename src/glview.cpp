#include "glview.h"

#include "matqt.h"
#include <array>
#include "util.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLView::GLView(QWidget* parent)
	: QOpenGLWidget(parent)
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

	// Initialize GL functions
	initializeOpenGLFunctions();

	// Initialize shaders
	m_shader = Shader::defaultColorShader();
	m_aux_shader = Shader::defaultShader();

	// Init buffers
	glGenVertexArrays(1, &TVAO_main);
	glGenBuffers(1, &TVBO_main);
	glGenVertexArrays(1, &LVAO_main);
	glGenBuffers(1, &LVBO_main);
	glGenVertexArrays(1, &PVAO_main);
	glGenBuffers(1, &PVBO_main);
	glGenVertexArrays(1, &TVAO_temp);
	glGenBuffers(1, &TVBO_temp);
	glGenVertexArrays(1, &LVAO_temp);
	glGenBuffers(1, &LVBO_temp);
	glGenVertexArrays(1, &LVAO_border);
	glGenBuffers(1, &LVBO_border);
	glGenVertexArrays(1, &LVAO_xaxis);
	glGenBuffers(1, &LVBO_xaxis);
	glGenVertexArrays(1, &LVAO_yaxis);
	glGenBuffers(1, &LVBO_yaxis);

	// Initialize border
	std::array<double,8> border = { -0.9999,-0.9999,
																																	 1.0,-0.9999, 
																																	 1.0, 1.0, 
																																	-0.9999, 1.0 };
	glBindVertexArray(LVAO_border);
	glBindBuffer(GL_ARRAY_BUFFER, LVBO_border);
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * 8, &border[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	// Set white as background color and clear window
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(5.0f);
}

void GLView::resizeGL(int _width, int _height)
{

	if (m_is_rendering)
		return;

	// Avoid division by zero
	if (_width == 0) _width = 1;

	// Store GL canvas sizes in object properties
	m_width = _width;
	m_height = _height;

	// Setup world space window limits based on model bounding box
	m_left = 0.0;
	m_right = 1.0;
	m_bottom = 0.0;
	m_top = 1.0;

	scaleWorldWindow(1.10);

	// Setup the viewport to canvas dimensions
	glViewport(0, 0, (GLint)m_width, (GLint)m_height);

	// Establish the clipping volume by setting up an
	// orthographic projection
	glm::mat4 trans = glm::ortho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
	unsigned int transformLoc = glGetUniformLocation(m_shader->id(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void GLView::paintGL()
{
	if (m_is_rendering)
		return;

	//Clear the buffer with the current clear color
	glClear(GL_COLOR_BUFFER_BIT);

	m_aux_shader->use();
	glBindVertexArray(LVAO_border);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(LVAO_xaxis);
	glDrawArrays(GL_LINES, 0, m_x_ticks.size()*2);
	glBindVertexArray(LVAO_yaxis);
	glDrawArrays(GL_LINES, 0, m_y_ticks.size()*2);

	m_shader->use();
	// Draw main data
	if (!tva_main.empty())
	{
		glBindVertexArray(TVAO_main);
		glDrawArrays(GL_TRIANGLES, 0, tva_main.size() / 5);
	}
	if (!lva_main.empty())
	{
		glBindVertexArray(LVAO_main);
		glDrawArrays(GL_LINES, 0, lva_main.size() / 5);
	}

	if (!tva_temp.empty())
	{
		glBindVertexArray(TVAO_temp);
		glDrawArrays(GL_TRIANGLES, 0, tva_temp.size() / 5);
	}
	if (!lva_temp.empty())
	{
		glBindVertexArray(LVAO_temp);
		glDrawArrays(GL_LINES, 0, lva_temp.size() / 5);
	}
	if (!pva_main.empty())
	{
		glBindVertexArray(PVAO_main);
		glDrawArrays(GL_POINTS, 0, pva_main.size()/5);
	}

}

void GLView::drawXAxis()
{

	// Evaluate parametric values
	std::vector<double> tick_vertexes;
	for (int i = 0; i < m_x_ticks.size(); i++)
	{
		double uc_tick = (2 * m_x_ticks[i] - (m_x_min + m_x_max)) / (m_x_max - m_x_min);
		tick_vertexes.push_back(uc_tick);
		tick_vertexes.push_back(-1.0);
		tick_vertexes.push_back(uc_tick);
		tick_vertexes.push_back(-1.0 + 0.015);
	}

	this->makeCurrent();
	glBindVertexArray(LVAO_xaxis);
	glBindBuffer(GL_ARRAY_BUFFER, LVBO_xaxis);
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * tick_vertexes.size(), &tick_vertexes[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	this->doneCurrent();
}

void GLView::drawYAxis()
{

	// Evaluate parametric values
	std::vector<double> tick_vertexes;
	for (int i = 0; i < m_y_ticks.size(); i++)
	{
		double uc_tick = (2 * m_y_ticks[i] - (m_y_min + m_y_max)) / (m_y_max - m_y_min);
		tick_vertexes.push_back(-1.0);
		tick_vertexes.push_back(uc_tick);
		tick_vertexes.push_back(-1.0 + 0.015);
		tick_vertexes.push_back(uc_tick);
	}

	this->makeCurrent();
	glBindVertexArray(LVAO_yaxis);
	glBindBuffer(GL_ARRAY_BUFFER, LVBO_yaxis);
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * tick_vertexes.size(), &tick_vertexes[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	this->doneCurrent();
}

std::vector<double>& GLView::currentLVA()
{
	switch (m_current_lst)
	{
	case MAIN:
		return lva_main;
	case TEMP:
		return lva_temp;
	default:
		return lva_null;
	}
}

std::vector<double>& GLView::currentTVA()
{
	switch (m_current_lst)
	{
	case MAIN:
		return tva_main;
	case TEMP:
		return tva_temp;
	default:
		return tva_null;
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
	sizex = (m_right - m_left);
	sizey = (m_top - m_bottom);

	// Get current window center.
	cx = m_left + sizex * 0.5;
	cy = m_bottom + sizey * 0.5;

	// Adjust window to keep the same aspect ratio of the viewport.
	double wr = sizey / sizex;
	if (wr < vpr) sizey = sizex * vpr;
	else  sizex = sizey / vpr;
	m_left = cx - sizex * 0.5 * _scaleFac;
	m_right = cx + sizex * 0.5 * _scaleFac;
	m_bottom = cy - sizey * 0.5 * _scaleFac;
	m_top = cy + sizey * 0.5 * _scaleFac;

	// Establish the clipping volume by setting up an
	// orthographic projection
	this->makeCurrent();
	glm::mat4 trans = glm::ortho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
	unsigned int transformLoc = glGetUniformLocation(m_shader->id(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	this->doneCurrent();

	// Update
	m_backend->updateAxis();
	update();
}

void GLView::scaleWorldWindow(double _scaleFac, double _pcx, double _pcy)
{
	double vpr;          // viewport distortion ratio
	double cx, cy;       // window center
	double sizex, sizey; // window sizes

	// Set new window sizes based on scaling factor.
	sizex = (m_right - m_left);
	sizey = (m_top - m_bottom);

	//Compute canvas viewport ratio.
	vpr = (double)m_height / (double)m_width;

	// Get current window center.
	cx = m_left + sizex * _pcx;
	cy = m_bottom + sizey * _pcy;

	// Adjust window 
	double wr = sizey / sizex;
	if (wr < vpr) sizey = sizex * vpr;
	else  sizex = sizey / vpr;
	double szLeft = sizex * _pcx;
	double szBottom = sizey * _pcy;
	m_left = cx - szLeft * _scaleFac;
	m_right = cx + (sizex - szLeft) * _scaleFac;
	m_bottom = cy - szBottom * _scaleFac;
	m_top = cy + (sizey - szBottom) * _scaleFac;

	// Establish the clipping volume by setting up an
	// orthographic projection
	this->makeCurrent();
	glm::mat4 trans = glm::ortho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
	unsigned int transformLoc = glGetUniformLocation(m_shader->id(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	this->doneCurrent();

	m_backend->updateAxis();
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
	this->makeCurrent();
	glm::mat4 trans = glm::ortho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
	unsigned int transformLoc = glGetUniformLocation(m_shader->id(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	this->doneCurrent();

	// Update
	m_backend->updateAxis();
	update();
}

void GLView::fitWorldToViewport()
{

	// Setup world space window limits based on model bounding box
	m_left = 0.0;
	m_right = 1.0;
	m_bottom = 0.0;
	m_top = 1.0;

	// Scale to 1.10 times bounding box
	scaleWorldWindow(1.10);

	// Establish the clipping volume by setting up an
	// orthographic projection
	this->makeCurrent();
	glm::mat4 trans = glm::ortho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
	unsigned int transformLoc = glGetUniformLocation(m_shader->id(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	this->doneCurrent();

	// Update
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
	this->hide();
	tva_main.clear();
	lva_main.clear();
	pva_main.clear();
	m_is_rendering = true;
	m_has_plot = false;
	m_current_lst = MAIN;
}

void GLView::renderEnd()
{
	this->makeCurrent();
	m_is_rendering = false;
	m_has_plot = true;

	if (!tva_main.empty())
	{
		glBindVertexArray(TVAO_main);
		glBindBuffer(GL_ARRAY_BUFFER, TVBO_main);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * tva_main.size(), &tva_main[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2 * sizeof(double)));
		glEnableVertexAttribArray(1);
	}

	if (!lva_main.empty())
	{
		glBindVertexArray(LVAO_main);
		glBindBuffer(GL_ARRAY_BUFFER, LVBO_main);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * lva_main.size(), &lva_main[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2 * sizeof(double)));
		glEnableVertexAttribArray(1);
	}

	if (!pva_main.empty())
	{
		glBindVertexArray(PVAO_main);
		glBindBuffer(GL_ARRAY_BUFFER, PVBO_main);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * pva_main.size(), &pva_main[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2 * sizeof(double)));
		glEnableVertexAttribArray(1);
	}

	this->doneCurrent();

	m_current_lst = NONE;
	this->show();
}

void GLView::tempBegin()
{
	tva_temp.clear();
	lva_temp.clear();
	m_is_rendering = true;
	m_current_lst = TEMP;
}

void GLView::tempEnd()
{
	m_is_rendering = false;

	this->makeCurrent();
	if (!tva_temp.empty())
	{
		glBindVertexArray(TVAO_temp);
		glBindBuffer(GL_ARRAY_BUFFER, TVBO_temp);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * tva_temp.size(), &tva_temp[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2 * sizeof(double)));
		glEnableVertexAttribArray(1);
	}

	if (!lva_temp.empty())
	{
		glBindVertexArray(LVAO_temp);
		glBindBuffer(GL_ARRAY_BUFFER, LVBO_temp);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * lva_temp.size(), &lva_temp[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2 * sizeof(double)));
		glEnableVertexAttribArray(1);
	}
	this->doneCurrent();

	m_current_lst = NONE;
}

void GLView::beginWellCollection()
{
	m_backend->begin_point_collection();
}

void GLView::beginLineCollection()
{
	m_backend->begin_line_collection();
}

void GLView::beginPolylineCollection()
{
	m_backend->begin_polyline_collection();
}

void GLView::endPolylineCollection()
{
	m_backend->end_polyline_collection();
}

void GLView::cancelPointCollection()
{
	m_backend->cancel_point_collection();
}

void GLView::cancelPolylineCollection()
{
	m_backend->cancel_polyline_collection();
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

	drawXAxis();
}

void GLView::setYAxis(double _min, double _max, const std::vector<double>& _ticks)
{
	m_y_min = _min;
	m_y_max = _max;
	m_y_ticks = _ticks;

	drawYAxis();
}

void GLView::drawPath(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color)
{

	std::vector<double>& lva = currentLVA();

	// Store segments' vertexes
	size_t npts = x.size();
	for (size_t i = 1; i < npts; i++)
	{
		lva.push_back(x[i - 1]); lva.push_back(y[i - 1]); lva.push_back(color[1]);  lva.push_back(color[2]);  lva.push_back(color[3]);
		lva.push_back(x[i]); lva.push_back(y[i]); lva.push_back(color[1]);  lva.push_back(color[2]);  lva.push_back(color[3]);
	}
}

void GLView::drawMarkers(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z)
{

	const std::array<float, 4> color = { 1.0f,0.0f,0.0f,0.0f };
	size_t npts = x.size();
	for (size_t i = 0; i < x.size(); i++)
	{
		pva_main.push_back(x[i]); pva_main.push_back(y[i]);
		pva_main.push_back(color[1]);  pva_main.push_back(color[2]);  pva_main.push_back(color[3]);
	}

}

void GLView::drawTriangles(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z)
{
}

void GLView::drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::array<float, 4>>& color)
{

	std::vector<double>& tva = currentTVA();

	size_t nvtx = x.size();
	size_t cvtx = 2;
	while (cvtx < nvtx)
	{
		tva.push_back(x[0]); tva.push_back(y[0]);
		tva.push_back(color[0][1]); tva.push_back(color[0][2]); tva.push_back(color[0][3]);
		tva.push_back(x[cvtx - 1]); tva.push_back(y[cvtx - 1]);
		tva.push_back(color[cvtx - 1][1]); tva.push_back(color[cvtx - 1][2]); tva.push_back(color[cvtx - 1][3]);
		tva.push_back(x[cvtx]); tva.push_back(y[cvtx]);
		tva.push_back(color[cvtx][1]); tva.push_back(color[cvtx][2]); tva.push_back(color[cvtx][3]);
		cvtx++;
	}
}

void GLView::drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color)
{

	std::vector<double>& tva = currentTVA();

	size_t nvtx = x.size();
	size_t cvtx = 2;
	while (cvtx < nvtx)
	{
		tva.push_back(x[0]); tva.push_back(y[0]);
		tva.push_back(color[1]); tva.push_back(color[2]); tva.push_back(color[3]);
		tva.push_back(x[cvtx - 1]); tva.push_back(y[cvtx - 1]);
		tva.push_back(color[1]); tva.push_back(color[2]); tva.push_back(color[3]);
		tva.push_back(x[cvtx]); tva.push_back(y[cvtx]);
		tva.push_back(color[1]); tva.push_back(color[2]); tva.push_back(color[3]);
		cvtx++;
	}
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

void GLView::mouseReleaseEvent(QMouseEvent* _event)
{
	m_backend->mouseReleaseEvent(_event);

	Qt::MouseButton mouseButton = _event->button();
	if (mouseButton == Qt::MiddleButton)
		setCursor(Qt::ArrowCursor);
}

void GLView::mouseMoveEvent(QMouseEvent* _event)
{

	m_backend->mouseMoveEvent(_event);
	update();

	if (!m_has_plot)
		return;

	QPoint pt = _event->pos();
	double xi = worldXCoord(pt.x()); double eps = worldYCoord(pt.y());
	emit currentWorldCoord(xi, eps);		
}

void GLView::wheelEvent(QWheelEvent* _event)
{
	m_backend->wheelEvent(_event);
}