#include "display.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "state.h"

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void displayInit() {

    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (true);
    }

}

void drawVolumeScreen() {

    display.clearDisplay();

    // Title
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Volume");

    // Percentage
    display.setTextSize(2);
    display.setCursor(0, 16);

    if (state.muted) {
        display.print("MUTED");
    } else {
        display.print(state.volume);
        display.print("%");
    }

    display.drawRect(10, 50, 108, 10, SSD1306_WHITE);

    int barWidth = map(state.volume, 0, 100, 0, 106);

    if (!state.muted) {
        display.fillRect(11, 51, barWidth, 8, SSD1306_WHITE);
    }

    display.display();

}