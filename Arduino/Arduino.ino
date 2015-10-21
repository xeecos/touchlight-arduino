#include "MeTouchSensor.h"
#include "MeRGBLed.h"
#include "MeOrion.h"
MeTouchSensor ts(PORT_4);
MeRGBLed led(PORT_3);
void setup() {
  Serial.begin(115200);
}
int touches = -1;
long prevTime = 0;
bool prevTouch = false;
int gray = 0;

float j, f, k;
void loop() {
  if(prevTouch!=ts.touched()){
    prevTouch = ts.touched();
    touches++;
    touches = touches%4;
    if(touches==0){
      lightOff();
    }
  }
  if(touches==1){
    lightOn();
  }else if(touches==2){
    colorloop();
  }else if(touches==3){
    twinkling();
  }
}
void lightOff(){
  led.setColor(0,0,0);
  led.show();
}
void lightOn(){
  led.setColor(128,128,128);
  led.show();
}
void colorloop(){
  if(micros()-prevTime>30000){
    prevTime = micros();
    uint8_t red  = 100 * (1 + sin(j / 4.0) );
    uint8_t green = 100 * (1 + sin(f / 9.0 + 2.1) );
    uint8_t blue = 100 * (1 + sin(k / 14.0 + 4.2) );
    led.setColor(red, green, blue);
    led.show();
    j += random(1, 6) / 6.0;
    f += random(1, 6) / 6.0;
    k += random(1, 6) / 6.0;
  }
}
void twinkling(){
  if(micros()-prevTime>50000){
    prevTime = micros();
    gray = 100 - gray;
    led.setColor(gray,gray,gray);
    led.show();
  }
}

