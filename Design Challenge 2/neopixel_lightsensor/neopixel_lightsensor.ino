#include <Adafruit_CircuitPlayground.h>
#include <movingAvg.h>


//#include <Adafruit_NeoPixel.h> dont use this with circuit playground, causes errors

#define NEOPIX_PIN    A9
#define NUM_PIXELS 5

int lightValue;

//int red = 86;
//int green = 78;
//int blue = 109;


Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(NUM_PIXELS, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

movingAvg mySensor(100);

void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();
  strip.begin();  
  mySensor.begin();                   
  strip.setBrightness(100); //255 is maximum
}

void loop() {
  int sensorData = analogRead(A5);
  int sensorMovingAvg = mySensor.reading(sensorData);
  Serial.println(sensorMovingAvg);

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
