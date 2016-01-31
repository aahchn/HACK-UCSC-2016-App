#include <pebble.h>
#include "windows/stats.h"

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static ActionBarLayer *mood_select_bar;
static GBitmap *s_ellipsis_bitmap;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
	GRect window_bounds = layer_get_bounds(window_layer);
	
	mood_select_bar = action_bar_layer_create();
	
	s_ellipsis_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ellipsis);
	action_bar_layer_set_icon_animated(mood_select_bar, BUTTON_ID_SELECT, s_ellipsis_bitmap, true);
	
	text_layer_set_font(s_main_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_background_color(s_main_layer, GColorClear);
	text_layer_set_text(s_main_layer, "THIS IS THE DAILY");
	text_layer_set_text_alignment(s_main_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
	layer_add_child(window_layer, text_layer_get_layer(s_main_layer));
	
	s_menu_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
	
	//TODO: Make navigation buttons
	/*  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = get_num_rows_callback,
      .draw_row = draw_row_callback,
      .get_cell_height = get_cell_height_callback,
      .select_click = select_callback,
	}); */
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
	
  gbitmap_destroy(s_ellipsis_bitmap);
	
  window_destroy(window);
  s_main_window = NULL;
}

void stats_window_push() {
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}
