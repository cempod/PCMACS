#include "usb.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"

void
usb_init(void) {
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_InitTypeDef usb_pins = {
		.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12,
		.Mode = LL_GPIO_MODE_ALTERNATE,
		.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
		.OutputType = LL_GPIO_OUTPUT_PUSHPULL,
		.Pull = LL_GPIO_PULL_NO,
		.Alternate = LL_GPIO_AF_10
	};
    LL_GPIO_Init(GPIOA, &usb_pins);
	
	NVIC_SetPriority(OTG_FS_IRQn, 5);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTGFS);

    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
    USB_OTG_FS->GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
    USB_OTG_FS->GCCFG &= ~USB_OTG_GCCFG_VBUSASEN;
}