#pragma once
#include <backend/GameData.hpp>
#include <front/front.hpp>
#include <cstddef>

class PlayerPanel {
public:
    static void render(front::Group& parent, const backend::PlayerData& player,
                       std::size_t index, bool active, int x, int y, int width, int height);
};
