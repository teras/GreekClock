#include <pebble.h>
#include "logic.h"
#include "watch_layout.h"
#include "config.h"
#include "ticking.h"
#include "hardware.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void init() {
  show_watch_layout();
  registerConfig();
  updateBack();

  update();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(handle_battery);
  bluetooth_connection_service_subscribe(handle_bluetooth);
  handle_battery(battery_state_service_peek());
  handle_bluetooth(bluetooth_connection_service_peek());
}

static void deinit() {
  hide_watch_layout();
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
