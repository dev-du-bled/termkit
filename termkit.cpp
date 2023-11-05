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

#include "termkit.hpp"
#include <iostream>
#include <string>
#if defined(unix) || defined(__APPLE__)
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#elif defined(_WIN32)
#include <conio.h>
#include <windows.h>
#endif
/* https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 */
/* https://www.xfree86.org/current/ctlseqs.html */

namespace termkit
{
  extern const char DEFAULT_TERM_STYLE[5] = "\x1b[0m";

  std::string rgb_impl(std::string text, unsigned r, unsigned g, unsigned b, bool color_background, bool do_pad)
  {

    std::string result;

    std::string red = std::to_string(r);
    std::string green = std::to_string(g);
    std::string blue = std::to_string(b);

    // Color codes are made like this, as they consist of characters they mess up our spacing functions, as a workaround we
    // add a left padding to the string with an equal amount of space characters.
    // 12+3 is a magic number that magically make everything work
    // \x1b[38;2;red;green;bluem
    // result = std::string(' ', red.length() + green.length() +blue.length() + 13 + 8);
    if (do_pad)
    {
      for (unsigned long i = 0; i < 12 + 3 + red.length() + green.length() + blue.length(); i++)
      {
        result += " ";
      }
    }

    // creating the color code
    result += "\x1b[" + std::to_string(3 + color_background) + "8;2;" + red + ";" + green + ";" + blue + "m";
    result += text;
    // reset styling to avoid messing with the upcoming text
    result += "\x1b[" + std::to_string(3 + color_background) + "9m";
    return result;
  }

  extern std::string rgb_fg(std::string text, unsigned r, unsigned g,
                            unsigned b, bool add_padding)
  {
    return rgb_impl(text, r, g, b, false, add_padding);
  }

  extern std::string rgb_bg(std::string text, unsigned r, unsigned g,
                            unsigned b, bool add_padding)
  {
    return rgb_impl(text, r, g, b, true, add_padding);
  }

  extern void move_cursor_up(unsigned shift) { printf("\x1b[%iA", shift); }

  extern void move_cursor_left(unsigned shift) { printf("\x1b[%iD", shift); }

  extern void move_cursor_right(unsigned shift) { printf("\x1b[%iC", shift); }

  extern void move_cursor_down(unsigned shift) { printf("\x1b[%iB", shift); }

  extern void clear_line() { printf("\x1b[2K"); }

  extern void set_term_title(std::string title)
  {
    printf("\e]2;%s\007", title.c_str());
  }

  extern std::string bold_text(std::string text, bool add_padding)
  {
    std::string result = "";

    // Padding for the exact same reason as seen in rgb_impl
    if (add_padding)
      result += "               ";
    result += "\x1b[1m" + text + "\x1b[22m";
    return result;
  }

  extern std::string underline_text(std::string text)
  {
    return "\x1b[4m" + text + "\x1b[24m";
  }

  extern void save_cursor_pos() { printf("\x1b[s"); }

  extern void restore_cursor_pos() { printf("\x1b[u"); }

  extern void set_cursor_pos(unsigned line, unsigned column)
  {
    printf("\x1b[%i;%if\n", line, column);
  }

  extern void clear()
  {
    printf("\x1b[2J"); // clears the screen
    printf("\x1b[3J"); // clears the scrollback (history), see (1) clear
    set_cursor_pos(0, 0);
  }

#if defined(unix) || defined(__APPLE__)
  extern char getch()
  {
    // TODO: Add windows support
    struct termios original_termios, raw_termios;
    char result;
    // Save original terminal settings
    tcgetattr(STDIN_FILENO, &original_termios);
    // create settings in RawMode
    cfmakeraw(&raw_termios);
    // change to our raw settings
    tcsetattr(STDIN_FILENO, 0, &raw_termios);
    // read one byte into result
    read(STDIN_FILENO, &result, 1);
    // restore original terminal settings
    tcsetattr(STDIN_FILENO, 0, &original_termios);
    return result;
  }

#else
  extern char getch()
  {
    return (char)_getch();
  }
#endif

#if defined(unix) || defined(__APPLE__)
  extern Term_size get_term_size()
  {
    struct winsize size;
    Term_size result;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    result.width = size.ws_col;
    result.height = size.ws_row;
    return result;
  }

#else
  extern Term_size get_term_size()
  {
    CONSOLE_SCREEN_BUFFER_INFO term_info;
    Term_size result;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &term_info);
    result.width = term_info.dwSize.X;
    result.height = term_info.dwSize.Y;
    return result;
  }
#endif

  extern void hide_cursor()
  {
    printf("\x1b[?25l");
  }

  extern void show_cursor() { printf("\x1b[?25h"); }

  extern std::string center_line(std::string line, unsigned visual_width)
  {
    std::string result = "";

    Term_size console_size = get_term_size();
    unsigned console_middle_point = console_size.width / 2;
    unsigned text_middle_point = 0;

    if (visual_width != 0)
      text_middle_point = visual_width / 2;
    else
      text_middle_point = line.length() / 2;

    unsigned center_point = console_middle_point - text_middle_point;
    for (unsigned i = 0; i < center_point; i++)
    {
      result += " ";
    }
    result += line;
    return result;
  }

  extern std::string center_text(std::string text, unsigned visual_width)
  {
    std::string result = "";
    std::string constructed_line = "";

    for (char &character : text)
    {
      if (character == '\n')
      {
        result += '\n' + center_line(constructed_line, visual_width);
        constructed_line = "";
        continue;
      }
      constructed_line += character;
    }
    return result;
  }

  extern std::string center_text_block(std::string text, unsigned visual_width)
  {
    std::string result = "";
    std::string constructed_line = "";

    Term_size console_size = get_term_size();
    unsigned console_middle_point = console_size.width / 2;
    unsigned text_middle_point = 0;

    if (visual_width != 0)
      text_middle_point = visual_width / 2;
    else
      text_middle_point = text.substr(0, text.find('\n')).length() / 2;

    unsigned center_point = console_middle_point - text_middle_point;

    for (auto &character : text)
    {
      if (character == '\n')
      {
        result += '\n' + std::string(center_point, ' ') + constructed_line;
        constructed_line = "";
        continue;
      }
      constructed_line += character;
    }
    return result;
  }

  void reset_terminal_and_exit(int signal_id) {
    std::cout<<DEFAULT_TERM_STYLE
             << "\x1b[?47l" << std::endl; // switch to normal buffer if available
    exit(0);
  }
#if defined(unix) || defined(__APPLE__) 
  extern void handle_SIGINT() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = reset_terminal_and_exit;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    return;
  }

#else
  BOOL WINAPI winCtrlHandler(DWORD signal_id) {
    if (signal_id != CTRL_C_EVENT) return false;
    reset_terminal_and_exit(0);
    return true; // make the compiler happy, this statement is unreachable 
  }
  
  extern void handle_SIGINT() {
    SetConsoleCtrlHandler(winCtrlHandler, TRUE);  
    return;
  }
#endif
} // namespace termkit
