#ifndef LCDSet_h
#define LCDSet_h

#include  <Arduino.h>
#include  <Wire.h>

class LCDSet{
    public:
        LCDSet(int adr,int row,int col);
        void reset(int pin);
        void initialize();
        void writeCommand(uint8_t w_cmd);
        void writeData(uint8_t w_data);
        void writeChar(char c[]);
        void cursor_set(int row,int col);
        void clear();
        void on();
        void off();
    private:
        int lcd_addr;
        int lcd_row;
        int lcd_col;
        void function_set(int is);
};

#endif