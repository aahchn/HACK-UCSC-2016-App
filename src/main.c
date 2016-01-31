#include <pebble.h>

static Window *s_main_window, *s_progress_window, *s_statistics_window, *s_settings_window;
static TextLayer *s_output_layer, *s_progress_layer, *s_statistics_layer, *s_settings_layer;
static ActionBarLayer *action_bar, *mood_select_bar;
static GBitmap *menu_daily_up, *menu_stats_select, *menu_settings_down;
static const bool animated = true;
static GBitmap *s_ellipsis_bitmap;

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Daily Progress");
  window_stack_push(s_progress_window, animated);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Statistics");
  window_stack_push(s_statistics_window, animated);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Settings");
  window_stack_push(s_settings_window, animated);
}

static void mood_select_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_progress_layer, "TESTEEEE");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
  window_set_background_color(s_main_window, GColorMalachite);

  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, s_main_window);
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
  
  action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_UP, menu_daily_up, true);
  action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_SELECT, menu_stats_select, true);
  action_bar_layer_set_icon_animated(action_bar, BUTTON_ID_DOWN, menu_settings_down, true);
    
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

static void menu_progress_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
  window_set_background_color(s_progress_window, GColorCyan);
  
  mood_select_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(mood_select_bar, s_progress_window);
  //action_bar_layer_set_click_config_provider(mood_select_bar, mood_select_handler);
  
  action_bar_layer_set_icon_animated(mood_select_bar, BUTTON_ID_SELECT, s_ellipsis_bitmap, true);

  s_progress_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_progress_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_background_color(s_progress_layer, GColorClear);
  text_layer_set_text(s_progress_layer, "THIS IS THE PROGRESS");
  text_layer_set_text_alignment(s_progress_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
  
  layer_add_child(window_layer, text_layer_get_layer(s_progress_layer));
}

static void menu_progress_window_unload(Window *window) {
  text_layer_destroy(s_progress_layer);
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

static void menu_settings_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
  window_set_background_color(s_settings_window, GColorRed);

  s_settings_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_settings_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_background_color(s_settings_layer, GColorClear);
  text_layer_set_text(s_settings_layer, "THIS IS THE SETTINGS");
  text_layer_set_text_alignment(s_settings_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
  
  layer_add_child(window_layer, text_layer_get_layer(s_settings_layer));
}

static void menu_settings_window_unload(Window *window) {
  text_layer_destroy(s_settings_layer);
}

static void init() {
 menu_daily_up = gbitmap_create_with_resource(RESOURCE_ID_menu_daily_up);
 menu_stats_select = gbitmap_create_with_resource(RESOURCE_ID_menu_stats_select);
 menu_settings_down = gbitmap_create_with_resource(RESOURCE_ID_menu_settings_down);
 s_ellipsis_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ELLIPSIS);
  
  s_main_window = window_create();
  window_set_click_config_provider(s_main_window, click_config_provider);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  window_stack_push(s_main_window, animated);
  
  s_progress_window = window_create();
  window_set_window_handlers(s_progress_window, (WindowHandlers) {
    .load = menu_progress_window_load,
    .unload = menu_progress_window_unload,
  });
  
  s_statistics_window = window_create();
  window_set_window_handlers(s_statistics_window, (WindowHandlers) {
    .load = menu_statistics_window_load,
    .unload = menu_statistics_window_unload,
  });
  
  s_settings_window = window_create();
  window_set_window_handlers(s_settings_window, (WindowHandlers) {
    .load = menu_settings_window_load,
    .unload = menu_settings_window_unload,
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