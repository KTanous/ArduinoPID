#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define NUMSAMPLES 100
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int sensorPin = A0;
int samples[NUMSAMPLES];

void setup() {

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(250);

  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  
  uint8_t i;
  float temp;
  float fconvert = 0.0;
  // Read voltage and convert to Fahrenheit
  for (i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(sensorPin);  
    delay(10);
  }
  
  temp = 0.0;
  for (i = 0; i < NUMSAMPLES; i++) {
    temp += samples[i];
  }
  temp /= NUMSAMPLES;
  
  temp *= 5.0;
  temp /= 1024.0;
  temp = (temp - 0.5) * 100;
  fconvert = temp * 9.0 / 5.0;
  fconvert = fconvert + 32;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print((int)fconvert);
  display.println(" F");
  display.print("Volume: ");
  // display.print();
  display.display();
  delay(250);
}
