#include "../lib/generic_esp_32/generic_esp_32.h"
#include "../include/usart.h"
#include "../include/spi.h"
#include "../include/util.h"
#include "../include/i2c.h"
#include "../include/Wifi.h"
#include "../include/timer.h"

#define LOCAL_SERVER "http://192.168.178.48:8000/device/measurements/fixed-interval"
#define OFFICIAL_SERVER "https://api.tst.energietransitiewindesheim.nl/device/measurements/variable-interval"
#define OFFICIAL_SERVER_DEVICE_ACTIVATION "https://api.tst.energietransitiewindesheim.nl/device/activate"
static const char *TAG = "Twomes Heartbeat Test Application ESP32";

char *bearer;
const char *rootCAR3 = "-----BEGIN CERTIFICATE-----\n"
                       "MIIEZTCCA02gAwIBAgIQQAF1BIMUpMghjISpDBbN3zANBgkqhkiG9w0BAQsFADA/\n"
                       "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
                       "DkRTVCBSb290IENBIFgzMB4XDTIwMTAwNzE5MjE0MFoXDTIxMDkyOTE5MjE0MFow\n"
                       "MjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxCzAJBgNVBAMT\n"
                       "AlIzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuwIVKMz2oJTTDxLs\n"
                       "jVWSw/iC8ZmmekKIp10mqrUrucVMsa+Oa/l1yKPXD0eUFFU1V4yeqKI5GfWCPEKp\n"
                       "Tm71O8Mu243AsFzzWTjn7c9p8FoLG77AlCQlh/o3cbMT5xys4Zvv2+Q7RVJFlqnB\n"
                       "U840yFLuta7tj95gcOKlVKu2bQ6XpUA0ayvTvGbrZjR8+muLj1cpmfgwF126cm/7\n"
                       "gcWt0oZYPRfH5wm78Sv3htzB2nFd1EbjzK0lwYi8YGd1ZrPxGPeiXOZT/zqItkel\n"
                       "/xMY6pgJdz+dU/nPAeX1pnAXFK9jpP+Zs5Od3FOnBv5IhR2haa4ldbsTzFID9e1R\n"
                       "oYvbFQIDAQABo4IBaDCCAWQwEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8E\n"
                       "BAMCAYYwSwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5p\n"
                       "ZGVudHJ1c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTE\n"
                       "p7Gkeyxx+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEE\n"
                       "AYLfEwEBATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2Vu\n"
                       "Y3J5cHQub3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0\n"
                       "LmNvbS9EU1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFBQusxe3WFbLrlAJQOYf\n"
                       "r52LFMLGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjANBgkqhkiG9w0B\n"
                       "AQsFAAOCAQEA2UzgyfWEiDcx27sT4rP8i2tiEmxYt0l+PAK3qB8oYevO4C5z70kH\n"
                       "ejWEHx2taPDY/laBL21/WKZuNTYQHHPD5b1tXgHXbnL7KqC401dk5VvCadTQsvd8\n"
                       "S8MXjohyc9z9/G2948kLjmE6Flh9dDYrVYA9x2O+hEPGOaEOa1eePynBgPayvUfL\n"
                       "qjBstzLhWVQLGAkXXmNs+5ZnPBxzDJOLxhF2JIbeQAcH5H0tZrUlo5ZYyOqA7s9p\n"
                       "O5b85o3AM/OJ+CktFBQtfvBhcJVd9wvlwPsk+uyOy2HI7mNxKKgsBTt375teA2Tw\n"
                       "UdHkhVNcsAKX1H7GNNLOEADksd86wuoXvg==\n"
                       "-----END CERTIFICATE-----\n";


void connect_to_WiFi(){
    wifi_prov_mgr_config_t config = initialize_provisioning();
    //start_provisioning(config);
}

void wifi_init_espnow(void)
{
    initialize_nvs();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start());
}

void initialize_wifi(){
    esp_err_t err;
    initialize_nvs();
    initialize();
    /* Initialize TCP/IP */
    ESP_ERROR_CHECK(esp_netif_init());
    uint32_t pop;
    nvs_handle_t pop_handle;
    err = nvs_open("twomes_storage", NVS_READWRITE, &pop_handle);
    if (err)
    {
        ESP_LOGE(TAG, "Failed to open NVS twomes_storage: %s", esp_err_to_name(err));
    }
    else
    {
        ESP_LOGE(TAG, "Succesfully opened NVS twomes_storage!");
        err = nvs_get_u32(pop_handle, "pop", &pop);
        switch (err)
        {
        case ESP_OK:
            ESP_LOGI(TAG, "The PoP has been initialized already!\n");
            ESP_LOGI(TAG, "The PoP is: %u\n", pop);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            ESP_LOGI(TAG, "The PoP is not initialized yet!");
            ESP_LOGI(TAG, "Creating PoP");
            pop = esp_random();
            ESP_LOGI(TAG, "Attempting to store PoP: %d", pop);
            err = nvs_set_u32(pop_handle, "pop", pop);
            if (!err)
            {
                ESP_LOGI(TAG, "Succesfully wrote PoP: %u to NVS twomes_storage", pop);
            }
            else
            {
                ESP_LOGE(TAG, "Failed to write PoP to NVS twomes_storage: %s", esp_err_to_name(err));
            }
            break;
        default:
            printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
    }
    ESP_LOGI(TAG, "POP: %u", pop);

    int msgSize = variable_sprintf_size("%u", 1, pop);
    //Allocating enough memory so inputting the variables into the string doesn't overflow
    char *popStr = malloc(msgSize);
    //Inputting variables into the plain json string from above(msgPlain).
    snprintf(popStr, msgSize, "%u", pop);

    wifi_prov_mgr_config_t config = initialize_provisioning();
    //Starts provisioning if not provisioned, otherwise skips provisioning.
    //If set to false it will not autoconnect after provisioning.
    //If set to true it will autonnect.
    start_provisioning(config, popStr, "Generic-Test", true);

    //Initialize time with timezone Europe and city Amsterdam
    initialize_time("CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00");
    //URL Do not forget to use https:// when using the https() function.

    //Gets time as epoch time.
    ESP_LOGI(TAG, "Getting time!");
    uint32_t now = time(NULL);
    ESP_LOGI(TAG, "Time is: %d", now);
    //Creates data string replacing %d with the time integer.
    char *dataPlain = "{\"deviceMac\":\"8C:AA:B5:85:A2:3D\",\"measurements\": [{\"property\":\"testy\",\"value\":\"hello_world\"}],\"time\":%d}";
    char data[strlen(dataPlain)];
    sprintf(data, dataPlain, now);

    char *bearer = get_bearer();
    if (strlen(bearer) > 1)
    {
        ESP_LOGI(TAG, "Bearer read: %s", bearer);
    }
    else if (strcmp(bearer, "") == 0)
    {
        ESP_LOGI(TAG, "Bearer not found, activating device!");
        activate_device(OFFICIAL_SERVER_DEVICE_ACTIVATION, pop, rootCAR3);
        bearer = get_bearer();
    }
    else if (!bearer)
    {
        ESP_LOGE(TAG, "Something went wrong whilst reading the bearer!");
    }

}

char *url = OFFICIAL_SERVER;
char *msg2Plain = "{\"upload_time\": \"%d\",\"property_measurements\":[    {"
                      "\"property_name\": %s,"
                      "\"measurements\": ["
                       "{ \"timestamp\":\"%d\","
                       "\"value\":\"1\"}"
                      "]}]}";

void send_HTTPS(){
    enable_wifi();
    vTaskDelay(1000);
    bearer = get_bearer();
    char *measurementType = "\"heartbeat\"";
    //Updates Epoch Time
    uint32_t now = time(NULL);
    //Get size of the message after inputting variables.
    int msgSize = variable_sprintf_size(msg2Plain, 3, now, measurementType, now);
    //Allocating enough memory so inputting the variables into the string doesn't overflow
    char *msg = malloc(msgSize);
    //Inputting variables into the plain json string from above(msgPlain).
    snprintf(msg, msgSize, msg2Plain, now, measurementType, now);
    //Posting data over HTTP for local testing(will be https later), using url, msg and bearer token.
    ESP_LOGI(TAG, "Data: %s", msg);
    //printf("%s", bearer);
    //ESP_LOGI(TAG, "de bearer is: %s", bearer);
    post_https(url, msg, rootCAR3, bearer);
    vTaskDelay(1000);
    //Disconnect WiFi
    disable_wifi();
}