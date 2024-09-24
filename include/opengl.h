//
// Created by Alan Freitas on 26/08/20.
//

#ifndef MATPLOTPLUSPLUS_OPENGL_H
#define MATPLOTPLUSPLUS_OPENGL_H

#include <matplot/detail/config.h>

#include "opengl_view.h"

class GLView;
class MainWindow;

namespace matplot::backend {
    class MATPLOT_EXPORTS opengl : public opengl_embed {
      public:
        opengl(GLView* _view, MainWindow* _window);
        ~opengl();

      public:
        bool new_frame() override;
        bool render_data() override;
        void show(matplot::figure_type *) override;
        bool should_close() override;
        void window_title(const std::string& title) override;
        std::string window_title() override;

    };
} // namespace matplot::backend

#endif // MATPLOTPLUSPLUS_OPENGL_H
