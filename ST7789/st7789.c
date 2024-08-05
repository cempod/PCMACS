#include "st7789.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi1;

void display_Reset(void){
	HAL_GPIO_WritePin(Display_CS_Port, Display_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Display_Reset_Port, Display_Reset_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(Display_Reset_Port, Display_Reset_Pin, GPIO_PIN_SET);
    HAL_Delay(10);
}

void display_WriteCommand(uint8_t byte) {
    HAL_GPIO_WritePin(Display_CS_Port, Display_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Display_DC_Port, Display_DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t *) &byte, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(Display_CS_Port, Display_CS_Pin, GPIO_PIN_SET);
}

void display_WriteData(uint8_t buffer) {
    HAL_GPIO_WritePin(Display_CS_Port, Display_CS_Pin, GPIO_PIN_RESET); 
    HAL_GPIO_WritePin(Display_DC_Port, Display_DC_Pin, GPIO_PIN_SET);
    HAL_SPI_Transmit(&hspi1, (uint8_t *) &buffer, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(Display_CS_Port, Display_CS_Pin, GPIO_PIN_SET);
}

/*No comments, only magic*/
void display_Init()	{
	display_Reset();
	display_WriteCommand(0x36); 
	display_WriteData(0x00);

	display_WriteCommand(0x3A); 
	display_WriteData(0x05);

	display_WriteCommand(0xB2);
	display_WriteData(0x0C);
	display_WriteData(0x0C);
	display_WriteData(0x00);
	display_WriteData(0x33);
	display_WriteData(0x33);

	display_WriteCommand(0xB7); 
	display_WriteData(0x35);  

	display_WriteCommand(0xBB);
	display_WriteData(0x17);

	display_WriteCommand(0xC0);
	display_WriteData(0x2C);

	display_WriteCommand(0xC2);
	display_WriteData(0x01);

	display_WriteCommand(0xC3);
	display_WriteData(0x12);   

	display_WriteCommand(0xC4);
	display_WriteData(0x20);  

	display_WriteCommand(0xC6); 
	display_WriteData(0x0F);    

	display_WriteCommand(0xD0); 
	display_WriteData(0xA4);
	display_WriteData(0xA1);

	display_WriteCommand(0xE0);
	display_WriteData(0xD0);
	display_WriteData(0x04);
	display_WriteData(0x0D);
	display_WriteData(0x11);
	display_WriteData(0x13);
	display_WriteData(0x2B);
	display_WriteData(0x3F);
	display_WriteData(0x54);
	display_WriteData(0x4C);
	display_WriteData(0x18);
	display_WriteData(0x0D);
	display_WriteData(0x0B);
	display_WriteData(0x1F);
	display_WriteData(0x23);

	display_WriteCommand(0xE1);
	display_WriteData(0xD0);
	display_WriteData(0x04);
	display_WriteData(0x0C);
	display_WriteData(0x11);
	display_WriteData(0x13);
	display_WriteData(0x2C);
	display_WriteData(0x3F);
	display_WriteData(0x44);
	display_WriteData(0x51);
	display_WriteData(0x2F);
	display_WriteData(0x1F);
	display_WriteData(0x1F);
	display_WriteData(0x20);
	display_WriteData(0x23);

	display_WriteCommand(0x21); 

	display_WriteCommand(0x11); 

	display_WriteCommand(0x29); 	

    display_WriteCommand(0x36);
    display_WriteData((1<<6)|(1<<5));

    /*display_set_window(0,0,320,170);
    for(uint32_t i = 0; i<320*170*2;i++){
        display_WriteData(0x00);
    }*/
}

void display_set_window(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end){
	display_WriteCommand(0x2A);    
	display_WriteData(x_start>>8);		
	display_WriteData(x_start);
	display_WriteData(x_end>>8);		
	display_WriteData(x_end);
	display_WriteCommand(0x2B);    
	display_WriteData((y_start+35)>>8);		
	display_WriteData(y_start+35);
	display_WriteData((y_end+35)>>8);		
	display_WriteData(y_end+35);
	display_WriteCommand(0x2C);    
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
	HAL_GPIO_WritePin(Display_CS_Port, Display_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Display_DC_Port, Display_DC_Pin, GPIO_PIN_SET); 
	ConvHL(s, (int32_t)w*h*2);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)s, w * h *2,100);
}
