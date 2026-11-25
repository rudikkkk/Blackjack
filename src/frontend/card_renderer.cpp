#include <frontend/card_renderer.hpp>

#include <algorithm>
#include <string>

namespace {
char suit_code(backend::Suit suit) {
    switch (suit) {
    case backend::Suit::Clubs: return 'C';
    case backend::Suit::Diamonds: return 'D';
    case backend::Suit::Hearts: return 'H';
    case backend::Suit::Spades: return 'S';
    }
    return 'C';
}

std::string rank_code(backend::Rank rank) {
    switch (rank) {
    case backend::Rank::Two: return "2";
    case backend::Rank::Three: return "3";
    case backend::Rank::Four: return "4";
    case backend::Rank::Five: return "5";
    case backend::Rank::Six: return "6";
    case backend::Rank::Seven: return "7";
    case backend::Rank::Eight: return "8";
    case backend::Rank::Nine: return "9";
    case backend::Rank::Ten: return "10";
    case backend::Rank::Jack: return "J";
    case backend::Rank::Queen: return "Q";
    case backend::Rank::King: return "K";
    case backend::Rank::Ace: return "A";
    }
    return "2";
}
}

void CardRenderer::render(front::Group& parent, const backend::HandData& hand,
                          int x, int y, int available_width,
                          int card_width, int card_height) {
    if (hand.cards_.empty())
        return;

    const int count = static_cast<int>(hand.cards_.size());
    const int gap = count > 1
        ? std::max(2, std::min(12, (available_width - card_width) / (count - 1) - card_width))
        : 0;
    const int step = count > 1
        ? std::min(card_width + 8, std::max(20, (available_width - card_width) / (count - 1)))
        : 0;
    (void)gap;

    for (int i = 0; i < count; ++i) {
        const auto& card = hand.cards_[static_cast<std::size_t>(i)];
        auto& image = parent.create<front::Image>(front::Size{card_width, card_height});
        image.set_position({x + i * step, y});
        image.set_size({card_width, card_height});
        image.set_fit(front::ImageFit::contain);

        std::string path = "cards/";
        path += card.is_face_down_ ? "back.png" : rank_code(card.rank_) + suit_code(card.suit_) + ".png";
        if (!image.load(path)) {
            // A missing asset is visible as a neutral placeholder instead of text cards.
            // All standard deck images are shipped in include/assets/cards.
        }
    }
}
