#include <front/window/window.hpp>
#include "../backend/fltk/native.hpp"
namespace front {
struct Window::Impl { void* native{}; };
Window::Window(int w,int h,std::string t):impl_(std::make_unique<Impl>()),root_({w,h}){impl_->native=new Fl_Window(w,h,t.c_str());auto* win=detail::window(impl_->native);win->begin();win->add(detail::widget(root_.native_handle()));win->end();win->resizable(win);}
Window::~Window(){if(impl_->native){auto* win=detail::window(impl_->native);win->remove(detail::widget(root_.native_handle()));delete win;impl_->native=nullptr;}}
Group& Window::root()noexcept{return root_;}void Window::set_title(const std::string& t){detail::window(impl_->native)->label(t.c_str());}
void Window::set_size(Size s){auto* w=detail::window(impl_->native);w->resize(w->x(),w->y(),s.width,s.height);root_.set_size(s);root_.update_layout();}
void Window::set_resizable(bool r){auto* w=detail::window(impl_->native);if(r)w->resizable(w);else w->resizable(nullptr);}void Window::show(){detail::window(impl_->native)->show();}void Window::hide(){detail::window(impl_->native)->hide();}void Window::redraw(){detail::window(impl_->native)->redraw();}void Window::run(){Fl::run();}void Window::close(){hide();}
}
