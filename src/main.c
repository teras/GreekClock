#include <pebble.h>
#include "logic.h"
#include "watch_layout.h"
#include "config.h"

static void update_time(struct tm *tick_time) {
  // Display this time on the TextLayer
  text_layer_set_text(l_txt_hour(), getHour(tick_time->tm_hour, tick_time->tm_min));
  text_layer_set_text(l_txt_bridge(), getTimeBridge(tick_time->tm_min));
  text_layer_set_text(l_txt_min1(), getMin1(tick_time->tm_min));
  text_layer_set_text(l_txt_min2(), getMin2(tick_time->tm_min));

  // Vibrate if required
  if ((tick_time->tm_min % 60) == 0) {
    int now = tick_time->tm_hour;
    int from = getFromTime();
    int to = getToTime();
    if (from > to) {
      if (now >= from || now <= to)
        vibes_short_pulse();
    } else if (from < to) {
      if (now >= from && now <= to)
        vibes_short_pulse();
    }
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void init() {
  show_watch_layout();
  registerConfig();
  updateVisual();

  // Show initial time
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  update_time(tick_time);

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
