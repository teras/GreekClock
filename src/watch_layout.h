#pragma once
#include <pebble.h>

void show_watch_layout(void);
void hide_watch_layout(void);

Window * l_window(void);
TextLayer * l_txt_hour(void);
TextLayer * l_txt_bridge(void);
TextLayer * l_txt_min1(void);
TextLayer * l_txt_min2(void);
