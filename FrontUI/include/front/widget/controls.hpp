#pragma once
#include "widget.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace front {

class Label : public Widget {
  public:
    explicit Label(std::string text, Size size);
    ~Label() override;
    void set_text(std::string);
    const std::string &text() const noexcept;
    void set_text_color(Color);
    void set_font_size(int px);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

class Button : public Widget {
  public:
    explicit Button(std::string text, Size size);
    ~Button() override;
    void set_text(std::string);
    const std::string &text() const noexcept;
    void set_on_click(std::function<void()>);
    void set_color(Color);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

class ImageData {
  public:
    ImageData();
    ImageData(int width, int height, int channels = 3);
    bool load(const std::string &path);
    int width() const noexcept;
    int height() const noexcept;
    int channels() const noexcept;
    const std::uint8_t *data() const noexcept;
    std::uint8_t *data() noexcept;
    bool empty() const noexcept;

  private:
    int width_{}, height_{}, channels_{3};
    std::vector<std::uint8_t> pixels_;
};

enum class ImageFit { original, contain, cover, stretch };

class Image : public Widget {
  public:
    explicit Image(Size size);
    ~Image() override;
    void set_size(Size) override;
    bool load(const std::string &);
    void set_image(const ImageData &);
    void set_fit(ImageFit);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    void refresh_image();
};

class NumberInput : public Widget {
  public:
    explicit NumberInput(Size size);
    std::string value() const;
    void set_value(const std::string& value);
};

class Spacer : public Widget {
  public:
    explicit Spacer(Size s = {1, 1});
};

} // namespace front
