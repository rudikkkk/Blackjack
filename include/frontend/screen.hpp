#pragma once
#include <front/front.hpp>
#include <functional>
#include <memory>
#include <string>

class App;

class Screen {
public:
    explicit Screen(App& app) : app_(app) {}
    virtual ~Screen() = default;
    virtual void render(front::Group& root) = 0;
protected:
    App& app_;
    front::Label& label(front::Group& parent, std::string text,
                        int x, int y, int w, int h, int font = 18);
    front::Button& button(front::Group& parent, std::string text,
                          int x, int y, int w, int h,
                          std::function<void()> callback);
    front::Group& panel(front::Group& parent, int x, int y, int w, int h);
};
