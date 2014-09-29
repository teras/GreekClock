#include "tweak_visuals.h"

static void setTo(GColor back, GColor fore) {
  window_set_background_color(l_window(), back);
  text_layer_set_text_color(l_txt_hour(), fore);
  text_layer_set_text_color(l_txt_bridge(), fore);
  text_layer_set_text_color(l_txt_min1(), fore);
  text_layer_set_text_color(l_txt_min2(), fore);
}

void setToBlack(void) {
  setTo(GColorBlack, GColorWhite);
}

void setToWhite(void) {
  setTo(GColorWhite, GColorBlack);
}