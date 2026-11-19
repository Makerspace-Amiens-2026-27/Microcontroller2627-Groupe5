#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "config.h"
constexpr uint32_t FRAME_TIME_MS = 16;
float dotX = 120, dotY = 160;   // position calculée
int drawnX = 120, drawnY = 160; // position affichée

Adafruit_ST7789 tft(&SPI, PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RESET);


void setup() {
    SPI.begin(PIN_TFT_SCK, -1, PIN_TFT_MOSI, PIN_TFT_CS);  // pas de MISO
    tft.init(240, 320, SPI_MODE3); // ligne pour inverser les couleurs
    tft.invertDisplay(false);
    tft.setRotation(2);                                     // portrait
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextSize(4);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(72, 40);
    tft.print("PONG");

    tft.drawRect(20, 120, 200, 60, ST77XX_WHITE);   // rectangle
    tft.fillCircle(120, 250, 20, ST77XX_YELLOW);    // disque
    Serial.begin(115200);
    pinMode(PIN_JOYSTICK_SELECT, INPUT_PULLUP);
    analogReadResolution(12);  // lectures entre 0 et 4095
    
}

void loop() {
    
    int x = analogRead(PIN_JOYSTICK_X);
    int y = analogRead(PIN_JOYSTICK_Y);
    bool pressed = digitalRead(PIN_JOYSTICK_SELECT) == LOW;

    Serial.printf("x=%d y=%d select=%d\n", x, y, pressed);
    static uint32_t lastFrameMs = 0;
    uint32_t nowMs = millis();
    if (nowMs - lastFrameMs < FRAME_TIME_MS) {
        return;
    }
    lastFrameMs = nowMs;

    // 1. Lire
    float x = normalizeJoystick(analogRead(PIN_JOYSTICK_X), joystickCenterX);
    bool beep = justPressed(button);

    // 2. Calculer
    dotX = constrain(dotX + x * 4.0f, 0.0f, 235.0f);
    if (beep) {
        tone(PIN_BUZZER, 880, 50);
    }

    // 3. Afficher : effacer l'ancien point, dessiner le nouveau
    if ((int)dotX != drawnX) {
        tft.fillRect(drawnX, drawnY, 5, 5, ST77XX_BLACK);
        drawnX = (int)dotX;
        tft.fillRect(drawnX, drawnY, 5, 5, ST77XX_WHITE);
    }
}