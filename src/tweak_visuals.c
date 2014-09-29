#include "tweak_visuals.h"
#include "watch_layout.h"
#include "config.h"

static void setTo(GColor back, GColor fore) {
  window_set_background_color(l_window(), back);
  text_layer_set_text_color(l_txt_hour(), fore);
  text_layer_set_text_color(l_txt_bridge(), fore);
  text_layer_set_text_color(l_txt_min1(), fore);
  text_layer_set_text_color(l_txt_min2(), fore);
}

void updateVisual(void) {
  bool black = persist_read_bool(KEY_BLACK);
  if (black)
    setTo(GColorBlack, GColorWhite);
  else
    setTo(GColorWhite, GColorBlack);
}