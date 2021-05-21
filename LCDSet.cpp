#include "Arduino.h"
#include "LCDSet.h"

LCDSet::LCDSet(int adr,int row,int col){
    lcd_addr = adr;
    lcd_row = row;
    lcd_col = col;
}
//初期リセット
void LCDSet::LCD_reset(int pin){
    pinMode(pin,OUTPUT);
    delay(5);
    digitalWrite(pin,LOW);
    delay(10);
    digitalWrite(pin,HIGH);
};
//コマンド送信
void LCDSet::writeCommand(uint8_t w_cmd){
    Wire.beginTransmission(lcd_addr);
    Wire.write((uint8_t)0x00);
    Wire.write(w_cmd);
    Wire.endTransmission();
}
//データ送信
void LCDSet::writeData(uint8_t w_data){
    Wire.beginTransmission(lcd_addr);
    Wire.write((uint8_t)0x40);
    Wire.write(w_data);
    Wire.endTransmission();
}
//LCD初期化
void LCDSet::LCD_initialize(){
    delay(41);
    writeCommand(0x38); //FunctionSet IS=0
    delay(20);
    writeCommand(0x39); //FunctionSet IS=1 
    delay(20);
    writeCommand(0x14); //Internal OSC freq
    delay(20);
    writeCommand(0x73); //Contrast set
    delay(20);
    writeCommand(0x56); //Pow/ICONctl/CT ctl
    delay(20);
    writeCommand(0x6C); //Follower control
    delay(20);
    writeCommand(0x38); //Function Set IS=0
    delay(20);
    writeCommand(0x01); //Clear Display
    delay(20);
    writeCommand(0x0C); //Display ON/OFF ctl
    delay(20);
}
//カーソル位置指定
void LCDSet::cursor_set(int row,int col){
    if(col>lcd_col){
        col = lcd_col;
    }       
    writeCommand((row + (col*0x40)) | 0x80);
}