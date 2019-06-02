#include <unistd.h>
#include <string.h>

#include "espressif/esp_common.h"
#include "esp/uart.h"

#include "wifi_task.h"
bool wifi = false;

// #define WIFI_SSID "LinkSky"
// #define WIFI_PASS "fuuckkyoumc"
#define WIFI_SSID "stone"
#define WIFI_PASS "nahidunga"

void user_init(void)
{
  uart_set_baud(0, 19200);
  printf("SDK version:%s\n", sdk_system_get_sdk_version());
  wifi_config();
  wifi_task_init();
  udp_server_init();

}
