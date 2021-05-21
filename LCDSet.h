#ifndef LCDSet_h
#define LCDSet_h

#include  <Arduino.h>
#include  <Wire.h>

class LCDSet{
    public:
        LCDSet(int adr,int row,int col);
        void LCD_reset(int pin);
        void LCD_initialize();
        void writeCommand(uint8_t w_cmd);
        void writeData(uint8_t w_data);
        void cursor_set(int row,int col);
    private:
        int lcd_addr;
        int lcd_row;
        int lcd_col;
};

#endif