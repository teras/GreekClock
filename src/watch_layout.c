#include "watch_layout.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_arial_black_31;
static GFont s_res_arial_black_28;
static TextLayer *s_txt_hour;
static TextLayer *s_txt_bridge;
static TextLayer *s_txt_min1;
static TextLayer *s_txt_min2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_arial_black_31 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ARIAL_BLACK_31));
  s_res_arial_black_28 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ARIAL_BLACK_28));
  // s_txt_hour
  s_txt_hour = text_layer_create(GRect(0, 4, 146, 39));
  text_layer_set_background_color(s_txt_hour, GColorClear);
  text_layer_set_text_color(s_txt_hour, GColorWhite);
  text_layer_set_text(s_txt_hour, "τέσσερις");
  text_layer_set_font(s_txt_hour, s_res_arial_black_31);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_txt_hour);
  
  // s_txt_bridge
  s_txt_bridge = text_layer_create(GRect(2, 45, 142, 32));
  text_layer_set_background_color(s_txt_bridge, GColorClear);
  text_layer_set_text_color(s_txt_bridge, GColorWhite);
  text_layer_set_text(s_txt_bridge, "παρά");
  text_layer_set_font(s_txt_bridge, s_res_arial_black_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_txt_bridge);
  
  // s_txt_min1
  s_txt_min1 = text_layer_create(GRect(2, 80, 142, 32));
  text_layer_set_background_color(s_txt_min1, GColorClear);
  text_layer_set_text_color(s_txt_min1, GColorWhite);
  text_layer_set_text(s_txt_min1, "είκοσι");
  text_layer_set_font(s_txt_min1, s_res_arial_black_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_txt_min1);
  
  // s_txt_min2
  s_txt_min2 = text_layer_create(GRect(2, 115, 142, 35));
  text_layer_set_background_color(s_txt_min2, GColorClear);
  text_layer_set_text_color(s_txt_min2, GColorWhite);
  text_layer_set_text(s_txt_min2, "εννέα");
  text_layer_set_font(s_txt_min2, s_res_arial_black_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_txt_min2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_txt_hour);
  text_layer_destroy(s_txt_bridge);
  text_layer_destroy(s_txt_min1);
  text_layer_destroy(s_txt_min2);
  fonts_unload_custom_font(s_res_arial_black_31);
  fonts_unload_custom_font(s_res_arial_black_28);
}
// END AUTO-GENERATED UI CODE

Window * l_window(void) {
  return s_window;
}
TextLayer * l_txt_hour(void) {
  return s_txt_hour;
}
TextLayer * l_txt_bridge(void) {
  return s_txt_bridge;
}
TextLayer * l_txt_min1(void) {
  return s_txt_min1;
}
TextLayer * l_txt_min2(void) {
  return s_txt_min2;
}


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_watch_layout(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_watch_layout(void) {
  window_stack_remove(s_window, true);
}
