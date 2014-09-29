#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer1;
static TextLayer *s_time_layer2;
static TextLayer *s_time_layer3;
static TextLayer *s_time_layer4;

#define FALSE 0
#define TRUE 1

#define TIMEGAP 35
  
static char* getNumber(int number, int asHour) {
  switch(number) {
    case 1:
    case 13:
      return asHour?"μία":"ένα";
    case 2:
    case 14:
      return "δύο";
    case 3:
    case 15:
      return asHour?"τρεις":"τρία";
    case 4:
    case 16:
      return asHour?"τέσσερις":"τέσσερα";
    case 5:
    case 17:
      return "πέντε";
    case 6:
    case 18:
      return "έξι";
    case 7:
    case 19:
      return "επτά";
    case 8:
    case 20:
      return "οκτώ";
    case 9:
    case 21:
      return "εννέα";
    case 10:
    case 22:
      return "δέκα";
    case 11:
    case 23:
      return "έντεκα";
    case 0:    
    case 12:
    case 24:
      return "δώδεκα";
    default:
      return "?λάθος";
  }
}

static char* getHour(int hour, int min) {
  return getNumber(min>=TIMEGAP?hour+1:hour,TRUE);
}

static char* getTimeBridge(int minute) {
  if (minute==0)
    return "ακριβώς";
  if (minute>=TIMEGAP)
    return "παρά";
  else
    return "και";
}

static char* getMin1(int minute) {
  if (minute==0)
    return "";
  else if (minute==15||minute==45)
    return "τέταρτο";
  else if (minute==30)
    return "μισή";
  else if (minute>=TIMEGAP)
    minute = 60-minute;
  if (minute>30)
    return "τριάντα";
  else if (minute>=20)
    return "είκοσι";
  else if (minute>12)
    return "δέκα";
  else
    return getNumber(minute, FALSE);
}

static char* getMin2(int minute) {
  if ((minute%10)==0||(minute%15)==0)
    return "";
  else if (minute>=TIMEGAP)
    minute = 60-minute;
  if (minute<=12)
    return "";
  else if (minute>30)
    minute -= 30;
  else if (minute>20)
    minute-=20;
  else if (minute>10)
    minute-=10;
  return getNumber(minute,FALSE);
}


static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer1, getHour(tick_time->tm_hour, tick_time->tm_min));
  text_layer_set_text(s_time_layer2, getTimeBridge(tick_time->tm_min));
  text_layer_set_text(s_time_layer3, getMin1(tick_time->tm_min));
  text_layer_set_text(s_time_layer4, getMin2(tick_time->tm_min));
  
  if ((tick_time->tm_min%60)==0) {
    vibes_short_pulse();
  }
}

static TextLayer * getTextWidget(int fontsize, int deltay) {
  TextLayer * text = text_layer_create(GRect(2, deltay, 142, 40));
  text_layer_set_font(text, fonts_load_custom_font(resource_get_handle(fontsize)));
  text_layer_set_background_color(text, GColorClear);
  text_layer_set_text_color(text, GColorBlack);
  text_layer_set_text_alignment(text, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(s_main_window), text_layer_get_layer(text));
  return text;
}

static void main_window_load(Window *window) {
  // Create time TextLayer
  s_time_layer1 = getTextWidget(RESOURCE_ID_ARIAL_BLACK_35, 5);
  s_time_layer2 = getTextWidget(RESOURCE_ID_ARIAL_BLACK_28, 52);
  s_time_layer3 = getTextWidget(RESOURCE_ID_ARIAL_BLACK_28, 90);
  s_time_layer4 = getTextWidget(RESOURCE_ID_ARIAL_BLACK_28, 120);

  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer1);
  text_layer_destroy(s_time_layer2);
  text_layer_destroy(s_time_layer3);
  text_layer_destroy(s_time_layer4);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
