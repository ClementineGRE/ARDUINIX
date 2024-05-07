#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#define Servo_pin 9
#define LED_PIN     6
#define LED_COUNT   86
#define BRIGHTNESS  50

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo myservo;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  myservo.attach(Servo_pin);
  myservo.write(90); // Positionner le servo à 90 degrés (position centrale) au démarrage
}

void loop() {
  rainbowCycle(20); // Appeler la fonction rainbowCycle avec un délai de 20 ms entre chaque transition de couleur
 
  // Faire tourner le servo dans toutes les directions de manière aléatoire
  for (int i = 0; i < 5; i++) { // Répéter 5 fois
    int pos = random(0, 181); // Générer une position aléatoire entre 0 et 180 degrés
    myservo.write(pos); // Positionner le servo à la position aléatoire
    delay(500); // Attendre 500 ms avant de passer à la prochaine position
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
