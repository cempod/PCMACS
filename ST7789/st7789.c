#include "st7789.h"
#include "gpio.h"
#include "spi.h"
#include "rtos.h"

void display_reset(void){
	LL_GPIO_SetOutputPin(Display_CS_Port, Display_CS_Pin);
    LL_GPIO_ResetOutputPin(Display_Reset_Port, Display_Reset_Pin);
	vTaskDelay(pdMS_TO_TICKS(10));
    LL_GPIO_SetOutputPin(Display_Reset_Port, Display_Reset_Pin);
	vTaskDelay(pdMS_TO_TICKS(10));
}

void display_write_command(uint8_t byte) {
    LL_GPIO_ResetOutputPin(Display_CS_Port, Display_CS_Pin);
    LL_GPIO_ResetOutputPin(Display_DC_Port, Display_DC_Pin);
	while (!LL_SPI_IsActiveFlag_TXE(SPI1)) {
        ;
    }
    LL_SPI_TransmitData8(SPI1, byte);
    LL_GPIO_SetOutputPin(Display_CS_Port, Display_CS_Pin);
}

void display_write_data(uint8_t buffer) {
    LL_GPIO_ResetOutputPin(Display_CS_Port, Display_CS_Pin); 
    LL_GPIO_SetOutputPin(Display_DC_Port, Display_DC_Pin);
    while (!LL_SPI_IsActiveFlag_TXE(SPI1)) {
        ;
    }
    LL_SPI_TransmitData8(SPI1, buffer);
    LL_GPIO_SetOutputPin(Display_CS_Port, Display_CS_Pin);
}

/*No comments, only magic*/
void display_init()	{
	display_reset();
	display_write_command(0x36); 
	display_write_data(0x00);

	display_write_command(0x3A); 
	display_write_data(0x05);

	display_write_command(0xB2);
	display_write_data(0x0C);
	display_write_data(0x0C);
	display_write_data(0x00);
	display_write_data(0x33);
	display_write_data(0x33);

	display_write_command(0xB7); 
	display_write_data(0x35);  

	display_write_command(0xBB);
	display_write_data(0x17);

	display_write_command(0xC0);
	display_write_data(0x2C);

	display_write_command(0xC2);
	display_write_data(0x01);

	display_write_command(0xC3);
	display_write_data(0x12);   

	display_write_command(0xC4);
	display_write_data(0x20);  

	display_write_command(0xC6); 
	display_write_data(0x0F);    

	display_write_command(0xD0); 
	display_write_data(0xA4);
	display_write_data(0xA1);

	display_write_command(0xE0);
	display_write_data(0xD0);
	display_write_data(0x04);
	display_write_data(0x0D);
	display_write_data(0x11);
	display_write_data(0x13);
	display_write_data(0x2B);
	display_write_data(0x3F);
	display_write_data(0x54);
	display_write_data(0x4C);
	display_write_data(0x18);
	display_write_data(0x0D);
	display_write_data(0x0B);
	display_write_data(0x1F);
	display_write_data(0x23);

	display_write_command(0xE1);
	display_write_data(0xD0);
	display_write_data(0x04);
	display_write_data(0x0C);
	display_write_data(0x11);
	display_write_data(0x13);
	display_write_data(0x2C);
	display_write_data(0x3F);
	display_write_data(0x44);
	display_write_data(0x51);
	display_write_data(0x2F);
	display_write_data(0x1F);
	display_write_data(0x1F);
	display_write_data(0x20);
	display_write_data(0x23);

	display_write_command(0x21); 

	display_write_command(0x11); 

	display_write_command(0x29); 	

    display_write_command(0x36);
    display_write_data((1<<6)|(1<<5));

   	/*display_set_window(0,0,320,170);
    for(uint32_t i = 0; i<320*170*2;i++){
        display_write_data(0xBF);
    }
	LL_GPIO_ResetOutputPin(LED_GPIO_Port,LED_Pin);*/
}

void display_set_window(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end){
	display_write_command(0x2A);    
	display_write_data(x_start>>8);		
	display_write_data(x_start);
	display_write_data(x_end>>8);		
	display_write_data(x_end);
	display_write_command(0x2B);    
	display_write_data((y_start+35)>>8);		
	display_write_data(y_start+35);
	display_write_data((y_end+35)>>8);		
	display_write_data(y_end+35);
	display_write_command(0x2C);    
}
static void ConvHL(uint8_t *s, int32_t l){
	uint8_t v;
	while (l > 0) {
		v = *(s+1);
		*(s+1) = *s;
		*s = v;
		s += 2;
		l -= 2;
	}
}
void display_send_buffer(uint16_t w, uint16_t h, uint8_t *s){
	LL_GPIO_ResetOutputPin(Display_CS_Port, Display_CS_Pin);
	LL_GPIO_SetOutputPin(Display_DC_Port, Display_DC_Pin);
	ConvHL(s, (int32_t)w*h*2);
	for(uint32_t i = 0; i < (w * h *2); i++){
		while (!LL_SPI_IsActiveFlag_TXE(SPI1)) {}
		LL_SPI_TransmitData8(SPI1, s[i]);
	}
}
