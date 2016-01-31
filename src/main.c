#include <pebble.h>

#include "windows/time_of_day.h"
#include "windows/stats.h"

//TODO: Create staticstics and profile page

static Window *s_main_window;
static TextLayer *s_output_layer;

static ActionBarLayer *action_bar;
static GBitmap *s_menu_daily_up, *s_menu_stats_select, *s_menu_profile_down;

static const bool animated = true;

/********************* CLICKS *****************************/

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	time_of_day_window_push();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	text_layer_set_text(s_output_layer, "Statistics");
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
}

static void main_window_unload(Window *window) {
	text_layer_destroy(s_output_layer);
}

static void menu_daily_window_load(Window *window) {
}

static void menu_statistics_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect window_bounds = layer_get_bounds(window_layer);
	window_set_background_color(s_statistics_window, GColorPurple);

	s_statistics_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
	text_layer_set_font(s_statistics_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_background_color(s_statistics_layer, GColorClear);
	text_layer_set_text(s_statistics_layer, "THIS IS THE STATS");
	text_layer_set_text_alignment(s_statistics_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
	
	layer_add_child(window_layer, text_layer_get_layer(s_statistics_layer));
}

static void menu_statistics_window_unload(Window *window) {
	text_layer_destroy(s_statistics_layer);
}

static void menu_profile_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect window_bounds = layer_get_bounds(window_layer);
	window_set_background_color(s_profile_window, GColorRed);

	s_profile_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
	text_layer_set_font(s_profile_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_background_color(s_profile_layer, GColorClear);
	text_layer_set_text(s_profile_layer, "THIS IS THE PROFILE");
	text_layer_set_text_alignment(s_profile_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
	
	layer_add_child(window_layer, text_layer_get_layer(s_profile_layer));
}

static void menu_profile_window_unload(Window *window) {
	text_layer_destroy(s_profile_layer);
}

/********************* APP *****************************/

static void init() {
	menu_time_of_day_up = gbitmap_create_with_resource(RESOURCE_ID_menu_daily_up);
	s_menu_stats_select = gbitmap_create_with_resource(RESOURCE_ID_menu_stats_select);
	s_menu_profile_down = gbitmap_create_with_resource(RESOURCE_ID_menu_profile_down);
	
	s_main_window = window_create();
	window_set_click_config_provider(s_main_window, click_config_provider);
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});
	
	window_stack_push(s_main_window, animated);
	
	s_statistics_window = window_create();
	window_set_window_handlers(s_statistics_window, (WindowHandlers) {
		.load = menu_statistics_window_load,
		.unload = menu_statistics_window_unload,
	});
	
	s_profile_window = window_create();
	window_set_window_handlers(s_profile_window, (WindowHandlers) {
		.load = menu_profile_window_load,
		.unload = menu_profile_window_unload,
	});
}

static void deinit() {
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}