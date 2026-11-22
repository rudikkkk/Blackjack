#include <front/widget/widget.hpp>
#include "../backend/fltk/native.hpp"
namespace front {
struct Widget::Impl { void* native{}; int x{},y{},w{},h{}; bool visible{true},enabled{true}; };
Widget::Widget(void* n):impl_(std::make_unique<Impl>()){impl_->native=n;}
Widget::~Widget()=default;
void* Widget::native_handle()const noexcept{return impl_->native;}
void Widget::attach_native(void* n){impl_->native=n;apply_geometry();if(!impl_->visible&&n)detail::widget(n)->hide();if(!impl_->enabled&&n)detail::widget(n)->deactivate();}
void Widget::apply_geometry(){if(impl_->native)detail::widget(impl_->native)->resize(impl_->x,impl_->y,impl_->w,impl_->h);}
void Widget::set_position(Point p){impl_->x=p.x;impl_->y=p.y;apply_geometry();}
void Widget::set_size(Size s){impl_->w=s.width<0?0:s.width;impl_->h=s.height<0?0:s.height;apply_geometry();}
Point Widget::position()const noexcept{return{impl_->x,impl_->y};} Size Widget::size()const noexcept{return{impl_->w,impl_->h};} Rect Widget::bounds()const noexcept{return{impl_->x,impl_->y,impl_->w,impl_->h};}
void Widget::show(){impl_->visible=true;if(impl_->native)detail::widget(impl_->native)->show();}void Widget::hide(){impl_->visible=false;if(impl_->native)detail::widget(impl_->native)->hide();}
void Widget::set_visible(bool v){v?show():hide();}bool Widget::visible()const noexcept{return impl_->visible;}
void Widget::set_enabled(bool e){impl_->enabled=e;if(impl_->native){if(e)detail::widget(impl_->native)->activate();else detail::widget(impl_->native)->deactivate();}}bool Widget::enabled()const noexcept{return impl_->enabled;}
void Widget::redraw(){if(impl_->native)detail::widget(impl_->native)->redraw();}
}
