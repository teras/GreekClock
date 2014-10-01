#include <pebble.h>
#include "config.h"
#include "tweak_visuals.h"

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  //Get Tuple
  Tuple *t = dict_read_first(iterator);
  if(t)
  {
    switch(t->key)
    {
    case KEY_BLACK:
      //It's the KEY_BLACK key
      if(strcmp(t->value->cstring, "black") == 0) {
        persist_write_bool(KEY_BLACK, true);
      } else if(strcmp(t->value->cstring, "white") == 0) {
        persist_write_bool(KEY_BLACK, false);
      }
      updateVisual();
      break;
    }
  }
}

void registerConfig(void) {
  app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}
