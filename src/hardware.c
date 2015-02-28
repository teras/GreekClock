#include <pebble.h>
#include "hardware.h"
#include "watch_layout.h"

static void handle_hardware(char* batteryTXT, char* bluetoothTXT) {
	static char buffer[] = "100% - BT";

	static char* battery = "";
	static char* bluetooth = "";
	
	if (batteryTXT != NULL) {
		battery = batteryTXT; 
	}
	if (bluetoothTXT != NULL) {
		bluetooth = bluetoothTXT;
	}
	snprintf(buffer, sizeof(buffer), "%s  %s", battery, bluetooth);
	text_layer_set_text(l_txt_info(), buffer);
}

void handle_battery(BatteryChargeState charge_state) {
	static char battery_text[] = "100%";
	if (charge_state.is_charging) {
	    handle_hardware("[||]" , NULL);
	} else {
		snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);
	    handle_hardware(battery_text , NULL);
	}
}

void handle_bluetooth(bool connected) {
	handle_hardware(NULL, connected?"BT":"");
}
