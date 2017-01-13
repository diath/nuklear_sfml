## nuklear_sfml
This is a simple header that provides SFML backend implementation for the [nuklear](https://github.com/vurtun/nuklear) library.

It requires C++14 to compile.

## Usage
Drop [nuklear.h](nuklear.h) and [nuklear_sfml.hpp](nuklear_sfml.hpp) into your project and see [main.cpp](main.cpp) for integration example.

## Extras
* `nk_sfml_image(const sf::Texture &)` that converts `sf::Texture` to `nk_image` type.
* `nk_sfml_image(const sf::Sprite &)` that converts `sf::Sprite` to `nk_image` type.

## Known Issues
Clipboard will not work because SFML does not provide functionality to interface with the system clipboard. You can still get it to work if you write clipboard functionality for your platform and assign function pointers to `sfml.ctx.clip.copy` and `sfml.ctx.clip.paste`.

## License
Public Domain
