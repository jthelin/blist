// Contents ----------------------------------------------------------------
//
//      TextBox::TextBox
//      TextBox::~TextBox
//     operator <<
//               main function for testing class implementation
//
// Description
//
//          Contains the implementation for the TextBox class
//
// End ---------------------------------------------------------------------

#include "TextBox.h"

#include <iomanip>

TextBox::TextBox(const std::string& text_line, BoxStyle box_type, char box_char) :
    TextBox(std::vector<std::string>{text_line}, box_type, box_char)
{
}

TextBox::TextBox(std::vector<std::string> text_lines, const BoxStyle box_type, const char box_char) :
    _text(std::move(text_lines)), _box_type(box_type), _box_char(box_char)
{
  if (!isprint(_box_char)) {
    // Specified box character is unprintable,
    // so override with a printable default.
    _box_char = '*';
  }
}

void TextBox::PrintTo(std::ostream& s) const
{
  size_t text_len = 0;
  size_t border_width;
  size_t hgap_width;
  size_t vgap_width;

  static constexpr char EOL   = '\n';
  static constexpr char SPACE = ' ';

  // Decide border and gap widths
  if (_box_type == TextBox::DOUBLE) {
    border_width = 2;
    hgap_width   = 2;
    vgap_width   = 1;
  }
  else if (_box_type == TextBox::BASIC) {
    border_width = 1;
    hgap_width   = 1;
    vgap_width   = 0;
  }
  else {
    border_width = 1;
    hgap_width   = 1;
    vgap_width   = 1;
  }

  // Decide on the length of the longest line in the text box.
  for (auto& line : _text)
  {
    text_len = std::max(text_len, line.size());
  }

  // Top border
  for (size_t j = 1; j <= border_width; j++) {
    for (size_t i = 1; i <= (text_len + 2 * border_width + 2 * hgap_width); i++) {
      s << _box_char;
    }
    s << EOL;
  }
  // Top gap
  for (size_t j = 1; j <= vgap_width; j++) {
    for (size_t i = 1; i <= border_width; i++) {
      s << _box_char;
    }
    for (size_t i = 1; i <= text_len + 2 * hgap_width; i++) {
      s << SPACE;
    }
    for (size_t i = 1; i <= border_width; i++) {
      s << _box_char;
    }
    s << EOL;
  }

  // Output each line of the text message
  for (auto& line : _text)
  {
    for (size_t i = 1; i <= border_width; i++) {
      s << _box_char;
    }
    for (size_t i = 1; i <= hgap_width; i++) {
      s << SPACE;
    }

    // Output this line of the text left justified in a field
    // big enough to take the longest line in the TextBox.
    s << std::setw(static_cast<int>(text_len)) << std::setiosflags(std::ios::left) << line;

    for (size_t i = 1; i <= hgap_width; i++) {
      s << SPACE;
    }
    for (size_t i = 1; i <= border_width; i++) {
      s << _box_char;
    }
    s << EOL;
  }

  // Bottom gap
  for (size_t j = 1; j <= vgap_width; j++) {
    for (size_t i = 1; i <= border_width; i++) {
      s << _box_char;
    }
    for (size_t i = 1; i <= text_len + 2 * hgap_width; i++) {
      s << SPACE;
    }
    for (size_t i = 1; i <= border_width; i++) {
      s << _box_char;
    }
    s << EOL;
  }
  // Bottom border
  for (size_t j = 1; j <= border_width; j++) {
    for (size_t i = 1; i <= (text_len + 2 * border_width + 2 * hgap_width); i++) {
      s << _box_char;
    }
    s << EOL;
  }
}

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
09-Feb-91       NJT     v1.0 - Initial MS-DOS version.
25-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
07-May-96       NJT     v1.2 - Moved box_style into class TextBox.
******************************************************************************/
