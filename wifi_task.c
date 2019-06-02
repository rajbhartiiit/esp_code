#include "espressif/esp_common.h"
#include <espressif/esp_wifi.h>

#include <FreeRTOS.h>
#include <task.h>

#include "wifi_task.h"

// #define WIFI_SSID "LinkSky"
// #define WIFI_PASS "fuuckkyoumc"

#define WIFI_SSID "stone"
#define WIFI_PASS "nahidunga"

static uint8_t wifi_alive = 0;

void wifi_config(void)
{
    struct sdk_station_config wifi_config = {
        .ssid = WIFI_SSID,
        .password = WIFI_PASS,
    };
    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_set_auto_connect(true);
    sdk_wifi_station_set_config(&wifi_config);

}

void wifi_task()
{
    uint8_t status = 0;
    uint8_t retries = 50;

    printf("%s: Connecting to WiFi\n\r", __func__);

    while (1)
    {
        wifi_alive = 0;
        while (status != STATION_GOT_IP && retries)
        {
            status = sdk_wifi_station_get_connect_status();
            printf("%s: status = %d\n", __func__, status);

            if (status == STATION_WRONG_PASSWORD)
            {
                printf("%s: STATION_WRONG_PASSWORD\n", __func__);
                break;
            }
            else if (status == STATION_NO_AP_FOUND)
            {
                printf("%s: STATION_NO_AP_FOUND\n", __func__);
                break;
            }
            else if (status == STATION_CONNECT_FAIL)
            {
                printf("%s: STATION_CONNECT_FAIL\n", __func__);
                break;
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            retries--;
        }

        while ((status = sdk_wifi_station_get_connect_status()) == STATION_GOT_IP)
        {
            if (wifi_alive = 0)
            {
                printf("WiFi Connected\n");
                wifi_alive = 1;
            }
            // Remember to set flag else it will keep om printing
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        wifi_alive = 0;
        printf("WiFi Disconnected\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void wifi_task_init(void)
{
    xTaskCreate(&wifi_task, "wifi_task", 256, NULL, 3, NULL);
}