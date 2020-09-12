#pragma once

#include <iostream>
#include <string>
#include <vector>

/*!
 * TextBox - A message to be output surrounded by a box of text characters,
 * using a specified box character, and using a variety of box styles.
 */
class TextBox {
public:
  enum BoxStyle { BASIC, STANDARD, DOUBLE };

protected:
  std::vector<std::string> _text;
  char                     _box_char;
  BoxStyle                 _box_type;

public:
  /*!
   * Constructor for TextBox object with a single-line text message.
   * @param text_line - The line of test to be included in this TextBox.
   * @param box_type - The style of box outline and padding to use.
   * @param box_char - The box outline character to use.
   */
  explicit TextBox(const std::string& text_line, BoxStyle box_type = STANDARD, char box_char = '*');

  /*!
   * Constructor for TextBox object with a multi-line text message.
   * @param text_lines - The lines of test to be included in this TextBox.
   * @param box_type - The style of box outline and padding to use.
   * @param box_char - The box outline character to use.
   */
  explicit TextBox(std::vector<std::string> text_lines, BoxStyle box_type = STANDARD, char box_char = '*');

  // Copy constructors.
  TextBox(const TextBox&) = default;
  TextBox& operator=(const TextBox&) = default;
  // Move constructors.
  TextBox(TextBox&&) = default;
  TextBox& operator=(TextBox&&) = default;

  ~TextBox() = default;

  // PrintTo - Outputs this TextBox object to the specified output stream.
  void PrintTo(std::ostream& s) const;

  // Stream output Function operator <<
  friend std::ostream& operator<<(std::ostream& s, const TextBox& tb)
  {
    tb.PrintTo(s);
    return s;
  }
};

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
09-Feb-91       NJT     v1.0 - Initial MS-DOS version.
25-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
07-May-96       NJT     v1.2 - Moved box_style enum into class TextBox.
******************************************************************************/
