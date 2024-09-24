#include <QApplication>

#include <matplot/matplot.h>
#include <matplot/axes_objects/isocontour.h>
#include <thread>

#include "matqt_widget.h"
#include "matqt.h"

using namespace matplot;

int main(int argc, char** argv)
{
 using namespace matplot;

 QApplication app(argc, argv);
 MatQtWidget window;
 window.show();

 std::vector<double> x = linspace(0, 2 * pi);
 std::vector<double> y = transform(x, [](auto x) { return sin(x); });

 auto b = create_backend<matplot::backend::MatQt>(&window);
 auto f = figure_no_backend(true); f->backend(b);
 auto ax = f->current_axes();

 auto [X, Y, Z] = peaks();

 for (size_t i = 0; i < X.size(); i++)
 {
  for (size_t j = 0; j < X.front().size(); j++)
  {
   if (X[i][j] * X[i][j] + Y[i][j] * Y[i][j] > 1.0)
    Z[i][j] = NaN;
  }
 }

 //vector_2d mask(Z.size());
 //for (size_t i = 0; i < Z.size(); i++)
 //{
 // mask[i].resize(Z[i].size());
 // for (size_t j = 0; j < Z[i].size(); j++)
 // {
 //  mask[i][j] = isnan(Z[i][j]);
 // }
 //}

 //ax->plot(x, y, "-");
 ax->hold(on);
	auto ich = ax->isocontour(X, Y, Z);
	auto ch = ax->contour(X, Y, Z,"-k");
 ch->levels(ich->levels());
 //ax->patch(X, Y, mask);
 colormap(ax, palette::jet());
 title(ax, "Title");
 xlabel(ax, "X");
 ylabel(ax, "Y");
 //ax->cblim({ -6,6 });
 
  //Start rendering
 f->draw();

 return app.exec();
}