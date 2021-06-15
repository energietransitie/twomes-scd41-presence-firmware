#include "../include/i2c.h"
#include "../include/sleepmodes.h"
#include "../include/wifi.h"
#include "../include/crc.h"
#include "../lib/generic_esp_32/generic_esp_32.h"
#include "../include/timer.h"
#include "../include/util.h"
#include "../include/espnow.h"

#include "../include/scd41.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef USE_HTTP
void main_esp_now(void)
{
    #ifdef ESP_NOW_RECEIVER
        espnow_init();
        // with any power saving on, ESP-NOW doesn't work well
        // (about every 9 out of 10 packets get lost)
        esp_wifi_set_ps(WIFI_PS_NONE);
        espnow_recv_pair();
    #else
        espnow_init_on_first_boot();
    #endif // ESP_NOW_RECEIVER

    #ifndef ESP_NOW_RECEIVER
        set_modem_sleep();
    #endif

    while(1)
    {
        #ifndef ESP_NOW_RECEIVER
            //set_light_sleep();
            scd41_measure_co2_temp_rht();
            scd41_store_in_nvs();
            set_deep_sleep();
        #else
            delay(5000); // fix for watchdog issues
        #endif // ESP_NOW_RECEIVER
    }
}
#else
void main_https(void)
{
    initialize_wifi();
    enable_wifi();

    while(1) {
        ESP_LOGI("Main", "Waiting 10 minutes...");
        delay(SCD41_WAIT_TEN_MINUTES_MS);
        scd41_measure_co2_temp_rht();
    }
}
#endif // USE_HTTP

void app_main() 
{
    initialize_nvs();

    #ifndef ESP_NOW_RECEIVER
        i2c_init();
        scd41_init();
    #endif // ESP_NOW_RECEIVER

    #ifndef USE_HTTP
        main_esp_now();
    #else
        main_https();
    #endif // USE_HTTP
}