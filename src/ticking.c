#include <pebble.h>
#include "config.h"
#include "ticking.h"
#include "watch_layout.h"
#include "logic.h"

void update(void) {
  // Show initial time
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  update_time(tick_time);	
}

void update_time(struct tm *tick_time) {
	static char buffer[] = "88/88";

	// Display this time on the TextLayer
  	text_layer_set_text(l_txt_hour(), getHour(tick_time->tm_hour, tick_time->tm_min));
  	text_layer_set_text(l_txt_bridge(), getTimeBridge(tick_time->tm_min));
  	text_layer_set_text(l_txt_min1(), getMin1(tick_time->tm_min));
  	text_layer_set_text(l_txt_min2(), getMin2(tick_time->tm_min));

  	// Display date
	snprintf(buffer,6,"%d/%d", tick_time->tm_mday, tick_time->tm_mon+1);
  	text_layer_set_text(l_txt_date(), buffer);
	
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