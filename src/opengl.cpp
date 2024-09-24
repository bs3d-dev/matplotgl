//
// Created by Alan Freitas on 26/08/20.
//

#include "opengl.h"
//#include <matplot/core/figure_type.h>
//#include <matplot/util/common.h>

#include "glview.h"
#include "main_window.h"

namespace matplot::backend {
     
    opengl::opengl(GLView* _view, MainWindow* _window) : opengl_embed(_view,_window) {
    }

    opengl::~opengl() {
    }

    bool opengl::new_frame() {
        if (should_close()) {
            return false;
        }
        return opengl_embed::new_frame();
        return true;
    }

    bool opengl::render_data() {
        bool r = opengl_embed::render_data();
        return r;
    }

    bool opengl::should_close() {
     return false;
    }

    void opengl::show(class matplot::figure_type *f) {
        //while (!this->should_close()) {
        //    f->draw();
        //}
    }

    void opengl::window_title(const std::string& title) {
     return;
    }

    std::string opengl::window_title() {
     return "Test";
    }

} // namespace matplot::backend