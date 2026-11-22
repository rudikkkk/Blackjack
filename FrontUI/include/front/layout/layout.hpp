#pragma once
#include "../core/types.hpp"
#include <algorithm>
namespace front {

class Group;

class Layout {
  public:
    virtual ~Layout() = default;
    virtual void arrange(Group &, Rect) = 0;
};

class VerticalLayout : public Layout {
  public:
    explicit VerticalLayout(int spacing = 0, int padding = 0);
    void set_spacing(int);
    void set_padding(int);
    void arrange(Group &, Rect) override;

  private:
    int spacing_, padding_;
};

class HorizontalLayout : public Layout {
  public:
    explicit HorizontalLayout(int spacing = 0, int padding = 0);
    void set_spacing(int);
    void set_padding(int);
    void arrange(Group &, Rect) override;

  private:
    int spacing_, padding_;
};

class GridLayout : public Layout {
  public:
    GridLayout(int columns, int spacing = 0, int padding = 0);
    void arrange(Group &, Rect) override;

  private:
    int columns_, spacing_, padding_;
};

class AbsoluteLayout : public Layout {
  public:
    void arrange(Group &, Rect) override;
};

} // namespace front
