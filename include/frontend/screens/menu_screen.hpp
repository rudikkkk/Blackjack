#pragma once
#include <frontend/screen.hpp>
class MenuScreen final : public Screen {
public:
    using Screen::Screen;
    void render(front::Group& root) override;
};
