#pragma once
#include <frontend/screen.hpp>
class ResultScreen final : public Screen {
public:
    using Screen::Screen;
    void render(front::Group& root) override;
};
