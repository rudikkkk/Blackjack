#include <front/widget/group.hpp>
#include "../backend/fltk/native.hpp"
#include <algorithm>
#include <stdexcept>
namespace front {
struct Group::Impl { void* native{}; std::vector<std::unique_ptr<Widget>> children; std::unique_ptr<Layout> layout; };
Group::Group(Size s):Widget(nullptr),impl_(std::make_unique<Impl>()){impl_->native=new Fl_Group(0,0,s.width,s.height);detail::group(impl_->native)->box(FL_NO_BOX);detail::group(impl_->native)->begin();detail::group(impl_->native)->end();attach_native(impl_->native);set_size(s);}
Group::~Group(){clear();if(impl_->native){auto* g=detail::group(impl_->native);if(g->parent())g->parent()->remove(g);delete g;impl_->native=nullptr;}}
void* Group::native_group()const noexcept{return impl_->native;}
Widget& Group::add(std::unique_ptr<Widget> c){if(!c)throw std::invalid_argument("null child");if(c->native_handle())detail::group(impl_->native)->add(detail::widget(c->native_handle()));impl_->children.push_back(std::move(c));update_layout();return *impl_->children.back();}
void Group::remove(Widget& c){auto it=std::find_if(impl_->children.begin(),impl_->children.end(),[&](auto& p){return p.get()==&c;});if(it==impl_->children.end())return;if(c.native_handle()){auto* n=detail::widget(c.native_handle());detail::group(impl_->native)->remove(n);if(dynamic_cast<Group*>(&c)==nullptr){delete n;c.attach_native(nullptr);}}impl_->children.erase(it);update_layout();}
void Group::clear(){for(auto& c:impl_->children)if(c->native_handle()){auto* n=detail::widget(c->native_handle());detail::group(impl_->native)->remove(n);if(dynamic_cast<Group*>(c.get())==nullptr){delete n;c->attach_native(nullptr);}}impl_->children.clear();update_layout();}
void Group::set_layout(std::unique_ptr<Layout> l){impl_->layout=std::move(l);update_layout();}void Group::update_layout(){if(impl_->layout){auto s=size();impl_->layout->arrange(*this,{0,0,s.width,s.height});}}const std::vector<std::unique_ptr<Widget>>& Group::children()const noexcept{return impl_->children;}
}
