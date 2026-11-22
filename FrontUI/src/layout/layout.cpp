#include <front/layout/layout.hpp>
#include <front/widget/group.hpp>
namespace front {

VerticalLayout::VerticalLayout(int s, int p)
    : spacing_(std::max(0, s)), padding_(std::max(0, p)) {}

void VerticalLayout::set_spacing(int s) { spacing_ = std::max(0, s); }

void VerticalLayout::set_padding(int p) { padding_ = std::max(0, p); }

void VerticalLayout::arrange(Group &g, Rect a) {
    auto &c = g.children();
    int n = int(c.size());
    if (!n)
        return;
    int innerw = std::max(0, a.width - 2 * padding_),
        innerh = std::max(0, a.height - 2 * padding_ - spacing_ * (n - 1)),
        each = innerh / n, y = a.y + padding_;
    for (int i = 0; i < n; ++i) {
        int h = i == n - 1 ? a.y + a.height - padding_ - y : each;
        c[i]->set_position({a.x + padding_, y});
        c[i]->set_size({innerw, h});
        y += h + spacing_;
    }
}

HorizontalLayout::HorizontalLayout(int s, int p)
    : spacing_(std::max(0, s)), padding_(std::max(0, p)) {}

void HorizontalLayout::set_spacing(int s) { spacing_ = std::max(0, s); }

void HorizontalLayout::set_padding(int p) { padding_ = std::max(0, p); }

void HorizontalLayout::arrange(Group &g, Rect a) {
    auto &c = g.children();
    int n = int(c.size());
    if (!n)
        return;
    int innerh = std::max(0, a.height - 2 * padding_),
        innerw = std::max(0, a.width - 2 * padding_ - spacing_ * (n - 1)),
        each = innerw / n, x = a.x + padding_;
    for (int i = 0; i < n; ++i) {
        int w = i == n - 1 ? a.x + a.width - padding_ - x : each;
        c[i]->set_position({x, a.y + padding_});
        c[i]->set_size({w, innerh});
        x += w + spacing_;
    }
}

GridLayout::GridLayout(int c, int s, int p)
    : columns_(std::max(1, c)), spacing_(std::max(0, s)),
      padding_(std::max(0, p)) {}

void GridLayout::arrange(Group &g, Rect a) {
    auto &c = g.children();
    if (c.empty())
        return;
    int rows = (int(c.size()) + columns_ - 1) / columns_,
        cw = std::max(0, (a.width - 2 * padding_ - spacing_ * (columns_ - 1)) /
                             columns_),
        ch = std::max(0,
                      (a.height - 2 * padding_ - spacing_ * (rows - 1)) / rows);
    for (std::size_t i = 0; i < c.size(); ++i) {
        int col = int(i) % columns_, row = int(i) / columns_;
        c[i]->set_position({a.x + padding_ + col * (cw + spacing_),
                            a.y + padding_ + row * (ch + spacing_)});
        c[i]->set_size({cw, ch});
    }
}

void AbsoluteLayout::arrange(Group &, Rect) {}
} // namespace front
