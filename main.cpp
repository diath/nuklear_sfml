#include <cstdint>
#include <SFML/Graphics.hpp>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_IMPLEMENTATION

#include "nuklear.h"
#include "nuklear_sfml.hpp"

constexpr uint32_t MaxVertexMemory  = 512 * 1024;
constexpr uint32_t MaxElementMemory = 128 * 1024;

int main(int, const char **)
{
	sf::RenderWindow window{{800, 600}, "Nuklear SFML"};
	nk_context *ctx = nk_sfml_init(&window);

	nk_font_atlas *atlas{nullptr};
	nk_sfml_font_stash_begin(&atlas);
		// Adding fonts:
		// nk_font *font = nk_font_atlas_add_from_file(atlas, "path", height, config);
	nk_sfml_font_stash_end();

	// Setting a font:
	// nk_style_set_font(ctx, &font->handle);

	bool running = true;
	sf::Event event{};

	while (running) {
		nk_input_begin(ctx);
		while (window.pollEvent(event)) {
			nk_sfml_handle_event(event);

			if (event.type == sf::Event::Closed) {
				running = false;
				break;
			}
		}
		nk_input_end(ctx);

		/* GUI */
		if (nk_begin(ctx, "Demo", nk_rect(50, 50, 200, 200),
			NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
			NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
		{
			nk_menubar_begin(ctx);
			nk_layout_row_begin(ctx, NK_STATIC, 25, 2);
			nk_layout_row_push(ctx, 45);
			if (nk_menu_begin_label(ctx, "FILE", NK_TEXT_LEFT, nk_vec2(120, 200))) {
				nk_layout_row_dynamic(ctx, 30, 1);
				nk_menu_item_label(ctx, "OPEN", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "CLOSE", NK_TEXT_LEFT);
				nk_menu_end(ctx);
			}
			nk_layout_row_push(ctx, 45);
			if (nk_menu_begin_label(ctx, "EDIT", NK_TEXT_LEFT, nk_vec2(120, 200))) {
				nk_layout_row_dynamic(ctx, 30, 1);
				nk_menu_item_label(ctx, "COPY", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "CUT", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "PASTE", NK_TEXT_LEFT);
				nk_menu_end(ctx);
			}
			nk_layout_row_end(ctx);
			nk_menubar_end(ctx);

			enum {EASY, HARD};
			static int op = EASY;
			static int property = 20;
			nk_layout_row_static(ctx, 30, 80, 1);
			if (nk_button_label(ctx, "button"))
				fprintf(stdout, "button pressed\n");
			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
			if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
		}
		nk_end(ctx);

		window.clear();
		{
			nk_sfml_render(NK_ANTI_ALIASING_ON, MaxVertexMemory, MaxElementMemory);
		}
		window.display();
	}

	window.close();
	nk_sfml_shutdown();

	return 0;
}
