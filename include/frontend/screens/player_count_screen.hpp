#pragma once
#include <frontend/screen.hpp>
class PlayerCountScreen final : public Screen {
public:
    using Screen::Screen;
    void render(front::Group& root) override;
};
