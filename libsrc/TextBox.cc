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

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <vector>

// Summary -----------------------------------------------------------------
//
// Constructor for TextBox object
//	Initialise the object data & stores the text message on the heap.
//
// End ---------------------------------------------------------------------
TextBox::TextBox(const std::string& text, box_style box_type, char box_char)
{
  // Store the text message on the heap

  char* s = static_cast<char*>(malloc(strlen(text.c_str()) + 1));

  assert(s != nullptr);

  if (s) {
    strcpy(s, text.c_str());
  }

  // Initialise object data
  this->text      = s;
  this->num_lines = 1;

  if (isprint(box_char)) {
    this->box_char = box_char;
  }
  else {
    // Specified box character is unprintable,
    // so override with a printable default.
    this->box_char = '*';
  }

  this->box_type = box_type;
}
// End TextBox constructor //

// Summary -----------------------------------------------------------------
//
// Constructor for TextBox object
//	Initialise the object data & stores the multi-line text message on
//	 the heap.
//
// End ---------------------------------------------------------------------
TextBox::TextBox(const std::vector<std::string>& text_lines, const box_style box_type, const char box_char)
{
  // Store the text message on the heap

  size_t line_count = 0;
  size_t area_size  = 0;

  for (const auto& text_line : text_lines) {
    area_size += strlen(text_line.c_str()) + 1; // count /0 string terminator
    line_count++;
  }

  assert(line_count >= 0);

  char* s = static_cast<char*>(malloc(area_size + 1)); // allow for final /0

  assert(s != nullptr);

  // Copy lines onto heap
  char* p = s;
  for (size_t i = 0; i < line_count; i++) {
    strcpy(p, text_lines[i].c_str());
    p += strlen(text_lines[i].c_str()) + 1;
  }
  *p = '\0'; // Add final terminator

  // Initialise object data
  this->text      = s;
  this->num_lines = line_count;

  if (isprint(box_char)) {
    this->box_char = box_char;
  }
  else {
    // Specified box character is unprintable,
    // so override with a printable default.
    this->box_char = '*';
  }

  this->box_type = box_type;
}
// End TextBox constructor //

// Summary -----------------------------------------------------------------
//
// Destructor for TextBox object
//	Frees up the heap memory used to store the message string.
//
// End ---------------------------------------------------------------------
TextBox::~TextBox()
{
  if (!this->text) {
    free(this->text);
  }
}
// End TextBox Destructor //

// Summary -----------------------------------------------------------------
//
// Stream output Function operator <<
//	Outputs the specified TextBox object to the specified output stream.
//
// End ---------------------------------------------------------------------
std::ostream& operator<<(std::ostream& s, const TextBox& tb)
{
  size_t text_len = 0;
  size_t l;
  size_t border_width;
  size_t hgap_width;
  size_t vgap_width;

  static const char EOL   = '\n';
  static const char SPACE = ' ';

  // Decide border and gap widths
  if (tb.box_type == TextBox::DOUBLE) {
    border_width = 2;
    hgap_width   = 2;
    vgap_width   = 1;
  }
  else if (tb.box_type == TextBox::BASIC) {
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
  char* p;
  for (l = 0, p = tb.text; l < tb.num_lines; l++, p += strlen(p) + 1) {
    if (text_len < strlen(p)) {
      text_len = strlen(p);
    }
  }

  // Top border
  for (size_t j = 1; j <= border_width; j++) {
    for (size_t i = 1; i <= (text_len + 2 * border_width + 2 * hgap_width); i++) {
      s << tb.box_char;
    }
    s << EOL;
  }
  // Top gap
  for (size_t j = 1; j <= vgap_width; j++) {
    for (size_t i = 1; i <= border_width; i++) {
      s << tb.box_char;
    }
    for (size_t i = 1; i <= text_len + 2 * hgap_width; i++) {
      s << SPACE;
    }
    for (size_t i = 1; i <= border_width; i++) {
      s << tb.box_char;
    }
    s << EOL;
  }

  // Output each line of the text message
  for (l = 0, p = tb.text; l < tb.num_lines; l++, p += strlen(p) + 1) {
    for (size_t i = 1; i <= border_width; i++) {
      s << tb.box_char;
    }
    for (size_t i = 1; i <= hgap_width; i++) {
      s << SPACE;
    }

    // Output this line of the text left justified in a field
    // big enough to take the longest line in the TextBox.
    s << std::setw(static_cast<int>(text_len)) << std::setiosflags(std::ios::left) << p;

    for (size_t i = 1; i <= hgap_width; i++) {
      s << SPACE;
    }
    for (size_t i = 1; i <= border_width; i++) {
      s << tb.box_char;
    }
    s << EOL;
  }

  // Bottom gap
  for (size_t j = 1; j <= vgap_width; j++) {
    for (size_t i = 1; i <= border_width; i++) {
      s << tb.box_char;
    }
    for (size_t i = 1; i <= text_len + 2 * hgap_width; i++) {
      s << SPACE;
    }
    for (size_t i = 1; i <= border_width; i++) {
      s << tb.box_char;
    }
    s << EOL;
  }
  // Bottom border
  for (size_t j = 1; j <= border_width; j++) {
    for (size_t i = 1; i <= (text_len + 2 * border_width + 2 * hgap_width); i++) {
      s << tb.box_char;
    }
    s << EOL;
  }

  return s;
}
// End Stream output Function operator << //

/* Original RCS change records from DOS version: */
/*****************************************************************************
 * $Log$
 * Revision 1.1  1996/05/07 14:29:38  njt
 * Initial revision
 *
 * Revision 1.1  91/02/09  17:46:43  njt
 * Initial revision
 *
 *****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
25-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
07-May-96       NJT     v1.2 - Moved box_style into class TextBox.
******************************************************************************/
