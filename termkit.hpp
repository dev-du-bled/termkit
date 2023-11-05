/**
 * This file is part of the Luna distribution (https://github.com/0x454d505459).
 * Copyright (c) 2023 Luna OGER--MASSICOT.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <string>

namespace termkit
{
  /**
   * Escape sequence to reset the terminal styling (Removes colors and text
   * effects)
   */
  extern const char DEFAULT_TERM_STYLE[5];

  class Term_size
  {
  public:
    unsigned width, height;
  };

  std::string rgb_impl(unsigned r, unsigned g, unsigned b, bool color_background);

  /**
   * @brief Generates a color escape sequence.
   * Colors the foreground with the given color
   *
   * @param [in] r Intensity of the red channel (ranges from 0-255)
   * @param [in] g Intensity of the green channel (ranges from 0-255)
   * @param [in] b Intensity of the blue channel (ranges from 0-255)
   * @param [in] add_padding whether or not to automatically pad the string to account for the color escape sequence; Default is false
   *
   * @return color ANSI Escape sequence (string) representing a color
   */
  extern std::string rgb_fg(std::string text, unsigned r, unsigned g, unsigned b, bool add_padding = false);

  /**
   * @brief Generates a color escape sequence.
   * Colors the background with the given color
   *
   * @param [in] r Intensity of the red channel (ranges from 0-255)
   * @param [in] g Intensity of the green channel (ranges from 0-255)
   * @param [in] b Intensity of the blue channel (ranges from 0-255)
   * @param [in] add_padding whether or not to automatically pad the string to account for the color escape sequence; Default is false
   *
   * @return color ANSI Escape sequence (string) representing a color
   */
  extern std::string rgb_bg(std::string text, unsigned r, unsigned g, unsigned b, bool add_padding = false);

  /**
   * @brief Generates a movement escape sequence.
   * Moves the cursor up a certain amount of times
   *
   * @param [in] shift How many times to go up
   *
   * @return movement ANSI Escape sequence (string) representing a movement
   */
  extern void move_cursor_up(unsigned shift);

  /**
   * @brief Generates a movement escape sequence.
   * Moves the cursor left a certain amount of times
   *
   * @param [in] shift How many times to go left
   *
   * @return movement ANSI Escape sequence (string) representing a movement
   */
  extern void move_cursor_left(unsigned shift);

  /**
   * @brief Generates a movement escape sequence.
   * Moves the cursor right a certain amount of times
   *
   * @param [in] shift How many times to go right
   *
   * @return movement ANSI Escape sequence (string) representing a movement
   */
  extern void move_cursor_right(unsigned shift);

  /**
   * @brief Generates a movement escape sequence.
   * Moves the cursor down a certain amount of times
   *
   * @param [in] shift How many times to go down
   *
   * @return movement ANSI Escape sequence (string) representing a movement
   */
  extern void move_cursor_down(unsigned shift);

  /**
   * @brief Clears the line.
   * Moves the cursor at the end of the line.
   *
   * @return movement ANSI Escape sequence (string) representing a movement
   */
  extern void clear_line();

  /**
   * @brief Sets the terminal's window title
   *
   * @param [in] title The new window title
   *
   * @return void
   */
  extern void set_term_title(std::string title);

  /**
   * @brief Makes the text look THICK
   *
   * @param [in] text Text to be bolded
   * @param [in] add_padding whether or not add spacing before the string to accomodate for escape sequences
   *
   * @return bolded text
   */
  extern std::string bold_text(std::string text, bool add_padding = false);

  /**
   * @brief Draws a line under the text
   *
   * @param [in] text Text to underline
   *
   * @return underlined text
   */
  extern std::string underline_text(std::string text);

  /**
   * @brief Tells the terminal to save the cursor position for later
   *
   * @return void
   */
  extern void save_cursor_pos();

  /**
   * @brief Tells the terminal to put the cursor back at the saved position (if any)
   *
   * @return void
   */
  extern void restore_cursor_pos();

  /**
   * @brief Puts the cursor at coordinate (X,Y)
   * 1,1 is the top left corner
   *
   * @param [in] line Position on the Y axis
   * @param [in] column Position on the X axis
   *
   * @return void
   */
  extern void set_cursor_pos(unsigned line, unsigned column);

  /**
   * @brief Clears the terminal screen and history
   *
   * @return void
   */
  extern void clear();

  /**
   * @brief Gets a single char from the user.
   * Does not echo and does not process keys
   *
   * @return char
   */
  extern char getch();

  /**
   * @brief Gets the size of the terminal in rows and columns
   *
   * @return Term_size
   */
  extern Term_size get_term_size();

  /**
   * @brief Hide the cursor
   *
   * @return void
   */
  extern void hide_cursor();

  /**
   * @brief Show the cursor
   *
   * @return void
   */
  extern void show_cursor();

  /**
   * @brief Centers a single line horizontally
   * Adds space chars for padding
   *
   * @param [in] line String of text to center
   * @param [in] visual_witdh Overwrite the automatic width detection, usefull when the string contains non-printable characters
   *
   * @return a string padded-left with space chars
   */
  extern std::string center_line(std::string line, unsigned visual_width = 0);

  /**
   * @brief Centers a paragraph line by line horizontally
   * Calls termkit::center_line en every lines
   *
   * @param [in] text String of text to center
   * @param [in] visual_witdh Overwrite the automatic width detection, usefull when the string contains non-printable characters
   *
   * @return a string with every line padded-left using space chars
   */
  extern std::string center_text(std::string text, unsigned visual_width = 0);

  /**
   * @brief Centers a paragraph horizontally
   *
   * @param [in] text String of text to center
   * @param [in] visual_witdh Overwrite the automatic width detection, usefull when the string contains non-printable characters
   *
   * @return a string with every line padded-left using space chars
   */
  extern std::string center_text_block(std::string text, unsigned visual_width = 0);

 
  /**
   * @brief Resets the terminal, not meant to be used by anything other than the signal handler
   *
   * @param [in] signal_id The id of the received signal, unused by the function
   *
   */
  void reset_terminal_and_exit(int signal_id);

  /**
   * @brief Handles program interuptions, like ^C and everything sending a sigINT signal
   */
  extern void handle_SIGINT();
  
} // namespace termkit
