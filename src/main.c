#include <pebble.h>

#include "windows/time_of_day.h"
#include "windows/stats.h"
#include "windows/profile.h"

//TODO: Create staticstics and profile page

static Window *s_main_window;
static TextLayer *s_output_layer;
static BitmapLayer *s_bitmap_layer;
static ActionBarLayer *action_bar;
static GBitmap *s_menu_daily_up, *s_menu_stats_select, *s_menu_profile_down, *s_bitmap;

static const bool animated = true;

/********************* CLICKS *****************************/

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	time_of_day_window_push();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	text_layer_set_text(s_output_layer, "Stats");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	text_layer_set_text(s_output_layer, "Profile");
}

static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

/********************* WINDOWS *****************************/

static void main_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect window_bounds = layer_get_bounds(window_layer);
	window_set_background_color(s_main_window, GColorMalachite);

  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MOAR);
  s_bitmap_layer = bitmap_layer_create(window_bounds);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  
	action_bar = action_bar_layer_create();
	action_bar_layer_add_to_window(action_bar, s_main_window);
	action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
	
	action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_UP, s_menu_daily_up, true);
	action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_SELECT, s_menu_stats_select, true);
	action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_DOWN, s_menu_profile_down, true);
		
	s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
	text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_background_color(s_output_layer, GColorClear);
	text_layer_set_text(s_output_layer, "Press a Button");
	text_layer_set_text_alignment(s_output_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
	
	layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer));
}

static void main_window_unload(Window *window) {
	text_layer_destroy(s_output_layer);
  gbitmap_destroy(s_bitmap);
}

/********************* APP *****************************/

static void init() {
	s_menu_daily_up = gbitmap_create_with_resource(RESOURCE_ID_menu_daily_up);
	s_menu_stats_select = gbitmap_create_with_resource(RESOURCE_ID_menu_stats_select);
	s_menu_profile_down = gbitmap_create_with_resource(RESOURCE_ID_menu_profile_down);
	
	s_main_window = window_create();
	window_set_click_config_provider(s_main_window, click_config_provider);
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});
	
	window_stack_push(s_main_window, animated);
}

static void deinit() {
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}