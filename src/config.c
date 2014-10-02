#include <pebble.h>
#include "config.h"
#include "watch_layout.h"

static int from = -1;
static int to = -1;

static void setTo(GColor back, GColor fore) {
  window_set_background_color(l_window(), back);
  text_layer_set_text_color(l_txt_hour(), fore);
  text_layer_set_text_color(l_txt_bridge(), fore);
  text_layer_set_text_color(l_txt_min1(), fore);
  text_layer_set_text_color(l_txt_min2(), fore);
}

static void in_recv_handler(DictionaryIterator *iterator, void *context) {
  //Get Tuple
  Tuple *t = dict_read_first(iterator);
	while (t!=NULL) {
    switch (t->key) {
      case KEY_BLACK:
        //It's the KEY_BLACK key
        if (strcmp(t->value->cstring, "black") == 0) {
          persist_write_bool(KEY_BLACK, true);
        } else if (strcmp(t->value->cstring, "white") == 0) {
          persist_write_bool(KEY_BLACK, false);
        }
        updateVisual();
        break;
      case KEY_FROM:
        persist_write_int(KEY_FROM, from = atoi(t->value->cstring));
		app_log(1, "config.c", 31, "from: %d", getFromTime());
        break;
      case KEY_TO:
        persist_write_int(KEY_TO, to = atoi(t->value->cstring));
		app_log(1, "config.c", 37, "to: %d", getToTime());
        break;
    }
	t = dict_read_next(iterator);
  }
}

void registerConfig(void) {
  app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

int getFromTime() {
  if (from < 0) {
    from = persist_exists(KEY_FROM) ? persist_read_int(KEY_FROM) : 8;
  }
  return from;
}

int getToTime() {
  static int to = -1;
  if (to < 0) {
    to = persist_exists(KEY_TO) ? persist_read_int(KEY_TO) : 20;
  }
  return to;
}

void updateVisual(void) {
  bool black = persist_exists(KEY_BLACK) ? persist_read_bool(KEY_BLACK) : true;
  if (black)
    setTo(GColorBlack, GColorWhite);
  else
    setTo(GColorWhite, GColorBlack);
}