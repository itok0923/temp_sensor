#include <Wire.h>
#include <LCDSet.h>

#define LCD_SDA PB9
#define LCD_SCL PB8
#define LCD_RES PA5
#define LCD_ADR 0x3E
#define LCD_ROW 16
#define LCD_COLUMN 2
#define sensor_pin PA0


void setup() {
  lcd.LCD_reset(LCD_RES);

  pinMode(Sensor_pin,INPUT);
}

void loop() {
    mesure_Temperature();
    delay(1000);
}
void mesure_Temperature(){
    int sens_value;
    double temp_value;

    sens_value = map(analogRead(Sensor_pin),0,1023,0,3300);
    temp_value = (sens_value - 600)/10;    
    lcd.cursor_set(1, 1);
    lcd.writeCommand(temp_value);
}