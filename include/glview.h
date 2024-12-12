#pragma once

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>

namespace matplot
{
	namespace backend
	{
	class MatQt;
	}
}

class Shader;


class GLView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{

	Q_OBJECT;


public:
	enum List { TEMP, MAIN, NONE };
	enum VPRMode { AUTO, CUSTOM};

public:
	GLView(QWidget* parent = 0);
	~GLView();

	// Display functions
	void scaleWorldWindow(double _scaleFac);
	void scaleWorldWindow(double _scaleFac, double _pcx, double _pcy);
	void panWorldWindow(double _panFacX, double _panFacY);
	void fitWorldToViewport();
	void setViewportRatioMode(VPRMode _mode);
	void setViewportRatio(double _vpr);

	double worldLeft() const;
	double worldRight() const;
	double worldBottom() const;
	double worldTop() const;
	int worldWidth() const;
	int worldHeight() const;
	int width() const;
	int height() const;

	double worldXCoord(double _x_screen);
	double worldYCoord(double _y_screen);

	void renderBegin();
	void renderEnd();

	void tempBegin();
	void tempEnd();

	void beginWellCollection();
	void beginLineCollection();
	void beginPolylineCollection();
	void endPolylineCollection();
	void cancelPointCollection();
	void cancelPolylineCollection();

	void setBackEnd(matplot::backend::MatQt* _backend);

	void setXAxis(double _min, double _max, const std::vector<double>& _ticks);
	void setYAxis(double _min, double _max, const std::vector<double>& _ticks);

	void drawPath(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color);
	void drawMarkers(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z = {});
	void drawTriangles(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& z = {});
	void drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::array<float, 4>>& color);
	void drawPolygon(const std::vector<double>& x, const std::vector<double>& y, const std::array<float, 4>& color);

public slots:
	// Mouse events slots
	void mouseDoubleClickEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(class QWheelEvent* _event);

signals:
	void currentWorldCoord(double x, double y);

private:
	// Canvas predefined slots
	void initializeGL();
	void resizeGL(int _width, int _height);
	void paintGL();

	void drawXAxis();
	void drawYAxis();

	std::vector<double>& currentLVA();
	std::vector<double>& currentTVA();

	// Viewport properties
	int m_width;                   // width: GL canvas horizontal size
	int m_height;                   // height: GL canvas vertical size

	// Window properties
	GLdouble m_left;           // left limit of object space window
	GLdouble m_right;          // right limit of object space window
	GLdouble m_bottom;         // bottom limit of object space window
	GLdouble m_top;            // top limit of object space window

	// Display lists
	GLuint m_plotId;           // GL list index for temp display
	GLuint m_tempId;           // GL list index for temp display

	// Axis data
	double m_x_min;
	double m_x_max;
	double m_y_min;
	double m_y_max;

	// Distortion ratio
	bool m_vpr_auto;
	double m_vpr;

	std::vector<double> m_x_ticks;
	std::vector<double> m_y_ticks;

	matplot::backend::MatQt* m_backend;

	bool m_is_rendering;
	bool m_has_plot;

	Shader* m_shader;
	Shader* m_aux_shader;
	unsigned int TVAO_main;
	unsigned int LVAO_main;
	unsigned int PVAO_main;
	unsigned int TVBO_main;
	unsigned int LVBO_main;
	unsigned int PVBO_main;
	unsigned int TVAO_temp;
	unsigned int LVAO_temp;
	unsigned int TVBO_temp;
	unsigned int LVBO_temp;

	unsigned int LVAO_border;
	unsigned int LVBO_border;
	unsigned int LVAO_xaxis;
	unsigned int LVBO_xaxis;
	unsigned int LVAO_yaxis;
	unsigned int LVBO_yaxis;

	std::vector<double> tva_main;
	std::vector<double> lva_main;
	std::vector<double> pva_main;
	std::vector<double> tva_temp;
	std::vector<double> lva_temp;
	std::vector<double> tva_null;
	std::vector<double> lva_null;

	List m_current_lst;



};
