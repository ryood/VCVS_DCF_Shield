/*
  Digital Pot Control

  AD8403

  2つのPOTの出力電圧を読み取って
  Digi-Potのチャンネル1, 2, 4の抵抗値を可変

  Pinの接続
  A0 POT1
  A1 POT2
  10 CS
  11 MOSI
  13 SCK
  
  Digi-Pot
  A1 - connect this to voltage
  W1 - this is the pot's wiper, which changes when you set it
  B1 - connect this to ground.
*/

// inslude the SPI library:
#include <SPI.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

byte cnt;
byte v0, v1;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  delay(1);

  Serial.begin(9600);  
}

void loop() {
  v0 = analogRead(0) / 4;
  v1 = analogRead(1) / 4;
  
  Serial.print(v0);
  Serial.print("\t");
  Serial.print(v1);
  Serial.print("\n");
  
  digitalPotWrite(0, 255 - v0);
  digitalPotWrite(1, 255 - v1);
  digitalPotWrite(3, 255 - v1);
  delay(1);
}

void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
