#include <QApplication>

#include <matplot/matplot.h>
#include <matplot/axes_objects/isocontour.h>
#include <thread>

//#include "matqt_widget.h"
#include "main_window.h"
#include "matqt.h"

using namespace matplot;

int main(int argc, char** argv)
{

 QApplication app(argc, argv);
 MainWindow window;

 std::vector<double> x = linspace(-2*pi, -pi);
 std::vector<double> y = transform(x, [](auto x) { return sin(x); });
 std::vector<double> y2 = transform(x, [](auto x) { return cos(x); });
 std::vector<double> err(y.size(), 0.1);
 std::vector<double> zero(y.size(), 0.00);


 auto b = create_backend<matplot::backend::MatQt>(window.matQt());
 auto f = figure_no_backend(true); f->backend(b);
 auto ax = f->current_axes();
 window.show();
 window.matQt()->canvas()->setViewportRatioMode(GLView::VPRMode::OFF);

 //auto [X, Y, Z] = peaks();

 //for (size_t i = 0; i < X.size(); i++)
 //{
 // for (size_t j = 0; j < X.front().size(); j++)
 // {
 //   X[i][j] *= 1e8;
 //   Y[i][j] *= 1e8;
 //   Z[i][j] *= 1e8;
 // }
 

 //for (size_t i = 0; i < X.size(); i++)
 //{
 // for (size_t j = 0; j < X.front().size(); j++)
 // {
 //  if (X[i][j] * X[i][j] + Y[i][j] * Y[i][j] > 1.0)
 //   Z[i][j] = NaN;
 // }
 //}

 ax->hold(on);
 //ax->errorbar(x, y, err, err, zero, zero);
 //ax->errorbar(x, y, err, error_bar::type::vertical);
 //window.matQt()->canvas()->setGridXEnabled(true);
 //window.matQt()->canvas()->setGridYEnabled(true);

 ax->plot(x, y, "-");
 ax->x_axis().reverse(true);
 //ax->plot(x, y2, "-");

 //ax->legend({ "Sin","Cos" });
	//auto ich = ax->isocontour(X, Y, Z);
	//auto ch = ax->contour(X, Y, Z,"-k");
 //ch->levels(ich->levels());
 //colormap(ax, palette::jet());
 //title(ax, "Title");
 //xlabel(ax, "X");
 //ylabel(ax, "Y");
 //ax->cblim({ -6,6 });
 // 
  //Start rendering
 f->draw();

 //ax->x_axis().tick_spacing(0.5);
 //ax->y_axis().tick_spacing(0.25);

 return app.exec();
}