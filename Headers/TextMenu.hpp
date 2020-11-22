#ifndef TEXT_MENU_HPP
#define TEXT_MENU_HPP

#include <string>

namespace UI
{
struct Color
{
  short r, g, b;
};

struct TextData
{
  std::string text;
  Color color = {255, 255, 255};
  bool bold = false, italics = false, underlined = false;
  std::string font_name = "";
};

struct Position
{
  int x, y;
};

class TextMenu
{
public:
  virtual void drawTextAt(const TextData&, Position) = 0;
  virtual void clear() = 0;
};
}  // namespace UI

#endif
