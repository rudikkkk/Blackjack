#include <frontend/screens/rules_screen.hpp>
#include <frontend/app.hpp>
void RulesScreen::render(front::Group& root) {
    label(root, "ПРАВИЛА BLACKJACK", 250, 55, 600, 55, 30).set_text_color(front::colors::blue);
    const char* rules[] = {
        "Цель: набрать больше очков, чем дилер, не превышая 21.",
        "Карты 2–10 дают значение своего номинала.",
        "Валет, дама и король дают 10 очков.",
        "Туз считается за 1 или 11 очков — выбирается выгодное значение.",
        "Blackjack — 21 очко на первых двух картах.",
        "В свой ход можно взять карту (Hit) или остановиться (Stand).",
        "Если сумма очков больше 21, игрок проигрывает.",
        "Дилер открывает закрытую карту и добирает до установленного порога."
    };
    int y = 155;
    for (const char* rule : rules) {
        label(root, rule, 105, y, 890, 42, 17);
        y += 57;
    }
    button(root, "Назад в меню", 400, 680, 300, 58, [this] { app_.show_menu(); });
}
