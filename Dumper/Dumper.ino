#include <Wire.h>

#define DEVICE1_PAGE1 0x50 //Адрес устройства
#define DEVICE1_PAGE2 0x51 //Адрес устройства
#define DEVICE1_PAGE3 0x52 //Адрес устройства
#define DEVICE1_PAGE4 0x53 //Адрес устройства
#define DEVICE1_PAGE5 0x54 //Адрес устройства
#define DEVICE1_PAGE6 0x55 //Адрес устройства
#define DEVICE1_PAGE7 0x56 //Адрес устройства
#define DEVICE1_PAGE8 0x57 //Адрес устройства
#define DEVICE1_PAGE9 0x58 //Адрес устройства

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}
int iP = 0, i = 0, maxI = 255;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {      // If anything comes in Serial (USB),
    byte reads = Serial.read();   // read it and send it out Serial1 (pins 0 & 1)
    delay(5);    
    if(i < maxI){
      EEPROM_WriteByte(DEVICE1_PAGE1 + iP, i, reads);
      Serial.println("Page is "+(String)iP+". Byte is "+(String)i+". Data as "+String(reads, HEX));
      i++;
    }
    else{
      iP++;
      i = 0;
      EEPROM_WriteByte(DEVICE1_PAGE1 + iP, i, reads);
      Serial.println("Page is "+(String)iP+". Byte is "+(String)i+". Data as "+String(reads, HEX));
    }
  }
}
void EEPROM_WriteByte(byte dev, byte Address, byte data)
{
  Wire.beginTransmission(dev);
  Wire.write(Address);
  Wire.write(data);
  delay(5); //Не знаю точно, но в Datasheet описана задержка записи в 5мс, поправьте меня, если я не прав.
  Wire.endTransmission();
}
