#include "usb_cdc.h"
#include "rtos.h"
#include "tusb.h"
#include "tusb_config.h"
#include "rtc.h"

static void receive_serial_port(uint8_t buf[], uint32_t count);
static void cdc_task(void);

void
usb_cdc_task(void* arg) {
    tusb_init();

    while (1) {
        tud_task();
        cdc_task();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

static void receive_serial_port(uint8_t buf[], uint32_t count) {
    switch (count)
    {
    case 6:
        if (strcmp((const char *)buf, "PCMACS") == 0) {//Handshake
            tud_cdc_n_write(0, "OK",2);
            tud_cdc_n_write_flush(0);
        }
        break;
    
    case 4:
        if (count == 4) {
            uint32_t telemetry = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
            xTaskNotify(display_task_handle, telemetry, eSetValueWithOverwrite);
            xTaskNotify(backlight_task_handle, 100, eSetValueWithOverwrite);
        }
    break;

    case 3:
        {
            rtc_init(buf[0],buf[1],buf[2]);
        }
    break;
    
    default:
        break;
    }
}

static void cdc_task(void) {
        if (tud_cdc_n_available(0)) {
        uint8_t buf[64];
        uint32_t count = tud_cdc_n_read(0, buf, sizeof(buf));
        receive_serial_port(buf, count);
    }
}


#ifdef __cplusplus
extern "C" {
#endif
void
OTG_FS_IRQHandler(void)
{
  tud_int_handler(0);
}
#ifdef __cplusplus
}
#endif