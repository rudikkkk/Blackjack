#include <front/widget/controls.hpp>
#include "../backend/fltk/native.hpp"
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_draw.H>
#include <algorithm>
#include <stdexcept>
#include <memory>
namespace front { namespace { Fl_Color fl_color(Color c){return fl_rgb_color(c.r,c.g,c.b);} }
struct Label::Impl { std::string text; };
Label::Label(std::string text,Size s):Widget(new Fl_Box(0,0,s.width,s.height)),impl_(std::make_unique<Impl>()){impl_->text=std::move(text);static_cast<Fl_Box*>(native_handle())->label(impl_->text.c_str());set_size(s);} Label::~Label()=default;
void Label::set_text(std::string t){impl_->text=std::move(t);static_cast<Fl_Box*>(native_handle())->label(impl_->text.c_str());redraw();}const std::string& Label::text()const noexcept{return impl_->text;}
void Label::set_text_color(Color c){static_cast<Fl_Box*>(native_handle())->labelcolor(fl_color(c));redraw();}void Label::set_font_size(int px){static_cast<Fl_Box*>(native_handle())->labelsize(std::max(1,px));redraw();}
struct Button::Impl { std::string text; std::function<void()> callback; };
Button::Button(std::string text,Size s):Widget(new Fl_Button(0,0,s.width,s.height)),impl_(std::make_unique<Impl>()){impl_->text=std::move(text);auto* b=static_cast<Fl_Button*>(native_handle());b->label(impl_->text.c_str());b->callback([](Fl_Widget*,void* p){auto* self=static_cast<Button*>(p);if(self->impl_->callback)self->impl_->callback();},this);set_size(s);} Button::~Button()=default;
void Button::set_text(std::string t){impl_->text=std::move(t);static_cast<Fl_Button*>(native_handle())->label(impl_->text.c_str());redraw();}const std::string& Button::text()const noexcept{return impl_->text;}
void Button::set_on_click(std::function<void()> f){impl_->callback=std::move(f);}void Button::set_color(Color c){static_cast<Fl_Button*>(native_handle())->color(fl_color(c));redraw();}
ImageData::ImageData()=default;ImageData::ImageData(int w,int h,int c):width_(w),height_(h),channels_(c){if(w<=0||h<=0||c<1||c>4)throw std::invalid_argument("Invalid image dimensions/channels");pixels_.resize(static_cast<std::size_t>(w)*static_cast<std::size_t>(h)*c);}
bool ImageData::load(const std::string& path){std::unique_ptr<Fl_Image> im;if(path.ends_with(".png")||path.ends_with(".PNG"))im=std::make_unique<Fl_PNG_Image>(path.c_str());else if(path.ends_with(".jpg")||path.ends_with(".jpeg")||path.ends_with(".JPG"))im=std::make_unique<Fl_JPEG_Image>(path.c_str());else if(path.ends_with(".bmp")||path.ends_with(".BMP"))im=std::make_unique<Fl_BMP_Image>(path.c_str());else return false;if(!im||im->w()<=0||im->h()<=0||!im->data())return false;width_=im->w();height_=im->h();channels_=3;pixels_.resize(static_cast<std::size_t>(width_)*height_*3);const auto* src=im->data()[0];int d=im->d();for(int i=0;i<width_*height_;++i){pixels_[i*3]=src[i*d];pixels_[i*3+1]=d>1?src[i*d+1]:src[i*d];pixels_[i*3+2]=d>2?src[i*d+2]:src[i*d];}return true;}
int ImageData::width()const noexcept{return width_;}int ImageData::height()const noexcept{return height_;}int ImageData::channels()const noexcept{return channels_;}const std::uint8_t* ImageData::data()const noexcept{return pixels_.data();}std::uint8_t* ImageData::data()noexcept{return pixels_.data();}bool ImageData::empty()const noexcept{return pixels_.empty();}
struct Image::Impl { ImageData data; std::unique_ptr<Fl_RGB_Image> image; ImageFit fit{ImageFit::contain}; };
Image::Image(Size s):Widget(new Fl_Box(0,0,s.width,s.height)),impl_(std::make_unique<Impl>()){static_cast<Fl_Box*>(native_handle())->box(FL_NO_BOX);set_size(s);}Image::~Image()=default;
void Image::set_size(Size s){Widget::set_size(s);refresh_image();}bool Image::load(const std::string& p){if(!impl_->data.load(p))return false;refresh_image();return true;}void Image::set_image(const ImageData& d){impl_->data=d;refresh_image();}void Image::set_fit(ImageFit f){impl_->fit=f;refresh_image();}
void Image::refresh_image(){auto* box=static_cast<Fl_Box*>(native_handle());impl_->image.reset();box->image(nullptr);if(impl_->data.empty())return;auto* rgb=new Fl_RGB_Image(impl_->data.data(),impl_->data.width(),impl_->data.height(),impl_->data.channels());if(impl_->fit==ImageFit::contain){int ww=std::max(1,size().width),hh=std::max(1,size().height);float scale=std::min(float(ww)/impl_->data.width(),float(hh)/impl_->data.height());rgb->scale(std::max(1,int(impl_->data.width()*scale)),std::max(1,int(impl_->data.height()*scale)),0,1);}else if(impl_->fit==ImageFit::stretch)rgb->scale(std::max(1,size().width),std::max(1,size().height),0,1);impl_->image.reset(rgb);box->image(impl_->image.get());box->redraw();}
Spacer::Spacer(Size s):Widget(nullptr){set_size(s);}
}
