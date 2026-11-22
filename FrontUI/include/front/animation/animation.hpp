#pragma once
#include <functional>
#include <memory>
#include <vector>

namespace front {

class Animation {
  public:
    using Callback = std::function<void(float)>;
    Animation(float duration, Callback, bool repeat = false);
    void start();
    void stop();
    bool running() const noexcept;
    void tick(float dt);

  private:
    float duration_, elapsed_{};
    Callback callback_;
    bool repeat_, running_{};
};

class AnimationManager {
  public:
    static AnimationManager &instance();
    void add(const std::shared_ptr<Animation> &);
    void start();
    void stop();

  private:
    AnimationManager();
    ~AnimationManager();
    AnimationManager(const AnimationManager &) = delete;
    AnimationManager &operator=(const AnimationManager &) = delete;
    struct Impl;
    std::unique_ptr<Impl> impl_;
    void tick_manager();
    static void timer_cb(void *);
};

} // namespace front
