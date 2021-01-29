#include <Adafruit_CircuitPlayground.h>
#include <movingAvg.h>

//#include <Adafruit_NeoPixel.h> dont use this with circuit playground, causes errors

// set up for the light strip
#define NEOPIX_PIN    A9
#define NUM_PIXELS 5

Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(NUM_PIXELS, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

// use the movingAvg library to get an average light value instead of instantaneous
movingAvg mySensor(100);

void setup() {
  //initiate libraries
  Serial.begin(115200); //I want this to turn on quickly after opening closet
  CircuitPlayground.begin();
  strip.begin();  
  mySensor.begin();                   
  strip.setBrightness(100); //255 is maximum
}

void loop() {
  int sensorData = analogRead(A5); //light sensor is in analog A5 on the circuit playground
  int sensorMovingAvg = mySensor.reading(sensorData); //get the light values
  Serial.println(sensorMovingAvg); //print the moving average (for reference)

  //turn on lights if value is over 10 and turn them off if lower 
  if (sensorMovingAvg >10) {  
    //apply rgb colors
    for(int i=0; i<5; i++) {
      strip.setPixelColor(i, 0x913d9f); 
    }       
    for(int i=0; i<9; i++) {
      CircuitPlayground.setPixelColor(i, 0x913d9f);         
    } 
    strip.show(); 
  }
  else if (sensorMovingAvg <10) { 
    CircuitPlayground.clearPixels();
    strip.clear(); 
    strip.show();    
  }
  else {
    CircuitPlayground.clearPixels();
    strip.clear();
    strip.show();
  }
}
