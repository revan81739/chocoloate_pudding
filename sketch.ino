#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 11
#define OLED_SCL 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

  Serial.begin(115200);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed!");
    while (true);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);
  display.println("HELLO!");

  display.display();
}
int counter = 0;
void loop() {

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(10,20);
  display.print(counter);

  display.display();

  counter++;

  delay(500);
}

