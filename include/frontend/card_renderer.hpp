#pragma once

#include <backend/GameData.hpp>
#include <front/front.hpp>

class CardRenderer {
public:
    static void render(front::Group& parent, const backend::HandData& hand,
                       int x, int y, int available_width,
                       int card_width = 54, int card_height = 76);
};
