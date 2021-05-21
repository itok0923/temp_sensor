#include <Wire.h>
#include <LCDSet.h>

#define LCD_SDA PB9
#define LCD_SCL PB8
#define LCD_RES PA5
#define LCD_ADR 0x3E
#define LCD_ROW 16
#define LCD_COL 2
#define sensor_pin PA0

int p=0;
char moji[]="XYZ";

LCDSet lcd=LCDSet(LCD_ADR,LCD_ROW,LCD_COL);
void setup() {
    attachInterrupt(digitalPinToInterrupt(PC13),push,FALLING);
    Serial.begin(115200);
    lcd.LCD_reset(LCD_RES);
    Wire.setSDA(LCD_SDA);
    Wire.setSCL(LCD_SCL);
    Wire.begin();
    lcd.LCD_initialize();
}

void loop() {
    if(p==0){
        lcd.cursor_set(0,0);
        mesure_Temperature();
        lcd.cursor_set(6,0);
        degc();
    }
    delay(2000);
}
void mesure_Temperature(){
    int sens_value;
    float temp_value;
    char d2c[5];

    sens_value = map(analogRead(sensor_pin),0,1023,0,3300);
    temp_value = (sens_value - 600)/10.0;    
    dtostrf(temp_value,5,1,d2c);
    for(int i=0;i<5;i++){
        lcd.writeData(d2c[i]);
    }
    Serial.println(temp_value,1);
}
void degc(){
    lcd.writeData(0xF2);
    lcd.writeData(0x43);
}
void push(){
    if(p==0){
        p=1;
    }else{
        p=0;
    }
    delay(500);
}
