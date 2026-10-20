#ifndef __LCD_H
#define __LCD_H

#define COLUMN_START	0x00
#define COLUMN_END		0x7F
#define PAGE_START		0x00
#define PAGE_END		0x7F

void LCD_Init(void);
void LCD_ShowColor(uint16_t color);


#endif
