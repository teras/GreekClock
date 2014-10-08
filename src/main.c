#include <pebble.h>
#include "logic.h"
#include "watch_layout.h"
#include "config.h"
#include "ticking.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void init() {
  show_watch_layout();
  registerConfig();
  updateBack();

  update();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  hide_watch_layout();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
