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

class GLView;
class MainWindow;

namespace matplot::backend {
    class MATPLOT_EXPORTS opengl_embed : public backend_interface {
      public:
        opengl_embed(GLView* _view, MainWindow* _window);
        ~opengl_embed();

      public:
        bool is_interactive() override;
        const std::string &output() override;
        const std::string &output_format() override;
        bool output(const std::string &filename) override;
        bool output(const std::string &filename,
                    const std::string &file_format) override;
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
        void show(matplot::figure_type *) override;
        bool supports_fonts() override;

      public:
        void draw_background(const std::array<float, 4> &color) override;
        void draw_rectangle(const double x1, const double x2,
                                      const double y1, const double y2,
                                      const std::array<float, 4> &color) override;
        void draw_path(const std::vector<double> &x,
                       const std::vector<double> &y,
                       const std::array<float, 4> &color) override;
        void draw_markers(const std::vector<double> &x,
                          const std::vector<double> &y,
                          const std::vector<double> &z = {}) override;
        void draw_text(const std::vector<double> &x,
                       const std::vector<double> &y,
                       const std::vector<double> &z = {}) override;
        void
        draw_image(const std::vector<std::vector<double>> &x,
                   const std::vector<std::vector<double>> &y,
                   const std::vector<std::vector<double>> &z = {}) override;
        void draw_triangle(const std::vector<double> &x,
                           const std::vector<double> &y,
                           const std::vector<double> &z = {}) override;

        void draw_axis(double x_min, double x_max, double y_min, double y_max,
         const std::vector<double>& x_ticks, const std::vector<double>& y_ticks,
         const std::vector<double>& x_pos,
         const std::vector<double>& y_pos);

        void draw_colorbar(double x_min, double x_max, double y_min, double y_max,
                           const std::vector<double>& x_ticks, const std::vector<double>& y_ticks,
                           const std::vector<double>& x_pos,
                           const std::vector<double>& y_pos);

    private:
     MainWindow* m_window;
     GLView* m_view;
    };
} // namespace matplot::backend

#endif // MATPLOTPLUSPLUS_OPENGL_EMBED_H
