#include <front/animation/animation.hpp>
#include <FL/Fl.H>
#include <algorithm>
#include <chrono>
#include <cmath>
namespace front {
Animation::Animation(float d,Callback cb,bool repeat):duration_(std::max(0.0001f,d)),callback_(std::move(cb)),repeat_(repeat){}
void Animation::start(){elapsed_=0;running_=true;if(callback_)callback_(0.f);}void Animation::stop(){running_=false;}bool Animation::running()const noexcept{return running_;}
void Animation::tick(float dt){if(!running_)return;elapsed_+=dt;float t=std::clamp(elapsed_/duration_,0.f,1.f);if(callback_)callback_(t);if(elapsed_>=duration_){if(repeat_)elapsed_=std::fmod(elapsed_,duration_);else running_=false;}}
struct AnimationManager::Impl {std::vector<std::shared_ptr<Animation>> animations;bool timer_active{};std::chrono::steady_clock::time_point last{};};
AnimationManager::AnimationManager():impl_(std::make_unique<Impl>()){}AnimationManager::~AnimationManager(){stop();}
AnimationManager& AnimationManager::instance(){static AnimationManager manager;return manager;}
void AnimationManager::add(const std::shared_ptr<Animation>& a){if(a)impl_->animations.push_back(a);}
void AnimationManager::start(){if(impl_->timer_active)return;impl_->timer_active=true;impl_->last=std::chrono::steady_clock::now();Fl::add_timeout(1.0/60.0,timer_cb,this);}
void AnimationManager::stop(){impl_->timer_active=false;Fl::remove_timeout(timer_cb,this);}
void AnimationManager::timer_cb(void* p){static_cast<AnimationManager*>(p)->tick_manager();}
void AnimationManager::tick_manager(){auto now=std::chrono::steady_clock::now();float dt=std::chrono::duration<float>(now-impl_->last).count();impl_->last=now;for(auto& a:impl_->animations)a->tick(dt);impl_->animations.erase(std::remove_if(impl_->animations.begin(),impl_->animations.end(),[](const auto& a){return !a->running();}),impl_->animations.end());if(impl_->animations.empty()){impl_->timer_active=false;return;}Fl::repeat_timeout(1.0/60.0,timer_cb,this);}
}
