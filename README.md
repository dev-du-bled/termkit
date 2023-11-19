# Termkit: C++ Terminal Management Library

![license](https://img.shields.io/badge/license-GPLv3-blue.svg)
![language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
## Overview

Termkit is a lightweight and versatile C++ library for managing terminals. It provides functionalities such as text coloring, text centering, window title manipulation, getch functionality, and more. This library aims to simplify terminal interactions and enhance the user experience when working with console applications.

## Features

- **Text Coloring:** Easily add color to your terminal output with simple function calls.
- **Text Center:** Align your text to the center for a cleaner display.
- **Window Title Manipulation:** Change the title of the terminal window dynamically.
- **getch Functionality:** Capture single keypresses without the need for pressing Enter.

## Installation

To use Termkit in your project, follow these steps:

1. Add Termkit as a submodule to your project:

   ```bash
   git submodule add https://github.com/dev-du-bled/termkit.git libs/termkit
   ```
2. Initialize and update the submodule:

   ```bash
   git submodule update --init --recursive
   ```
3. Include Termkit code
   ```cpp
   #include "libs/termkit/termkit.cpp"
   ```
4. You're done! You can now use Termkit in your project !

## Usage
### Text effects
#### Colouring

  ```cpp
  std::cout<<termkit::rgb_fg("Hello World", 142,34,34)<<std::endl;
  ```
#### Centering

  ```cpp
  std::cout<<termkit::center_line("This line is centered")<<std::endl;
  ```
### Terminal manipulation
#### Set Window title

  ```cpp
  termkit::set_term_title("My cool Termkit powered app");
  ```
#### Getch functionality

  ```cpp
  std::cout<<"Is Termkit cool ? (y/n)"<<std::endl;
  if ( getch() == 'y' ) {
    std::cout<<"Please consider starring the repo on github ;)"<<std::endl
  }
  ```
## License
This library is licensed under the GNU General Public License v3.0 - see the [LICENSE](https://github.com/dev-du-bled/termkit/blob/main/LICENSE) file for details.

## Contributing
Feel free to contribute to the development of Termkit by opening issues or pull requests on the GitHub repository.

Happy coding!
