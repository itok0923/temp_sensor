#include <Wire.h>
#include <LCDSet.h>

#define LCD_SDA PB9
#define LCD_SCL PB8
#define LCD_RES PA5
#define LCD_ADR 0x3E
#define LCD_ROW 16
#define LCD_COL 2
#define sensor_pin PA0

LCDSet lcd=LCDSet(LCD_ADR,LCD_ROW,LCD_COL);
char ini[] = "Initialized!";
void setup() {
    lcd.reset(LCD_RES);
    Wire.setSDA(LCD_SDA);
    Wire.setSCL(LCD_SCL);
    Wire.begin();
    lcd.initialize();
    lcd.writeChar(ini);
    delay(5000);
    lcd.clear();
}
void loop() {
    lcd.cursor_set(0,0);
    mesure_Temperature();
    lcd.cursor_set(6,0);
    degc();
    delay(2000);
}
//温度計測値取得
void mesure_Temperature(){
    //
    int sens_value;
    float temp_value;
    char fl2ch[5];
    sens_value = map(analogRead(sensor_pin),0,1023,0,3300);
    temp_value = (sens_value - 600)/10.0;    
    dtostrf(temp_value,5,1,fl2ch);
    lcd.writeChar(fl2ch);
}
//℃表示
void degc(){
    lcd.writeData(0xF2);
    lcd.writeData(0x43);
}