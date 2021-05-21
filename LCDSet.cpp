#include "Arduino.h"
#include "LCDSet.h"

LCDSet::LCDSet(int adr,int row,int col){
    lcd_addr = adr;
    lcd_row = row;
    lcd_col = col;
}
//初期リセット
void LCDSet::reset(int pin){
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
void LCDSet::initialize(){
    delay(41);
    writeCommand(0x38); //function set IS=0
    delay(1);
    writeCommand(0x39); //function set IS=1
    delay(1);
    writeCommand(0x14); //Internal OSC freq
    delay(1);
    writeCommand(0x73); //Contrast set
    delay(1);
    writeCommand(0x56); //Pow/ICONctl/CT ctl
    delay(1);
    writeCommand(0x6C); //Follower control
    delay(210);
    writeCommand(0x38); //function set IS=0
    delay(1);
    writeCommand(0x01); //Display Clear
    delay(1);
    writeCommand(0x0C); //Display ON/OFF ctl
    delay(1);
}
//カーソル位置指定
void LCDSet::cursor_set(int row,int col){
    function_set(0);
    if(col>lcd_col){
        col = lcd_col;
    }       
    writeCommand((row + (col*0x40)) | 0x80);
}
//charデータ送信
void LCDSet::writeChar(char c[]){
    for(int i=0;i<strlen(c);i++){
        writeData(c[i]);
    }
}
//LCD表示クリア
void LCDSet::clear(){
    function_set(0);
    writeCommand(0x01);
    delay(1);
}
//LCD ON
void LCDSet::on(){
    function_set(0);
    writeCommand(0x0C);
    delay(1);    
}
//LCD OFF
void LCDSet::off(){
    function_set(0);
    writeCommand(0x08);
    delay(1);    
}
//拡張コマンドの切替
void LCDSet::function_set(int is){
    if(is==1){
        writeCommand(0x39); //IS=1
    }else if(is==0){
        writeCommand(0x38); //IS=0
    }else{
        writeCommand(0x38); //IS=不定→0
    }
    delay(1);
}