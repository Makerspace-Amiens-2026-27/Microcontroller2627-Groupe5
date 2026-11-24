
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "config.h"

constexpr uint32_t FRAME_TIME_MS = 16;

float dotX = 120, dotY = 160;
int drawnX = 120, drawnY = 160;

Adafruit_ST7789 tft(&SPI, PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RESET);

// Détection du déplacement du bouton
bool previousButtonState = false;

float normalizeJoystick(int rawValue, int center) {
    return (rawValue - center) / 2048.0f;
}

bool justPressed(bool currentState) {
    bool result = currentState && !previousButtonState;
    previousButtonState = currentState;
    return result;
}

void setup() {

    SPI.begin(PIN_TFT_SCK, -1, PIN_TFT_MOSI, PIN_TFT_CS);

    tft.init(240, 320, SPI_MODE3);
    tft.invertDisplay(false);
    tft.setRotation(2);
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextSize(4);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(72, 40);
    tft.print("PONG");

    tft.drawRect(20, 120, 200, 60, ST77XX_WHITE);
    tft.fillCircle(120, 250, 20, ST77XX_YELLOW);

    Serial.begin(115200);

    pinMode(PIN_JOYSTICK_SELECT, INPUT_PULLUP);
    pinMode(PIN_BUZZER, OUTPUT);

    analogReadResolution(12);
}


void loop() {

    static uint32_t lastFrameMs = 0;

    uint32_t nowMs = millis();

    if (nowMs - lastFrameMs < FRAME_TIME_MS) {
        return;
    }

    lastFrameMs = nowMs;

    // 1. Lire le joystick

    int rawX = analogRead(PIN_JOYSTICK_X);
    int rawY = analogRead(PIN_JOYSTICK_Y);

    bool pressed = digitalRead(PIN_JOYSTICK_SELECT) == LOW;

    float normalizedX = normalizeJoystick(rawX, joystickCenterX);
    float normalizedY = normalizeJoystick(rawY, joystickCenterY);

    bool beep = justPressed(pressed);

    // 2. Calculer les déplacements

    dotX = constrain(dotX + normalizedX * 4.0f, 21.0f, 214.0f); // direction lecture joystick ( inversé ou non )

    dotY = constrain(dotY + normalizedY * 4.0f, 121.0f, 174.0f);  //pareil
    if (beep) {
        tone(PIN_BUZZER, 880, 50);
    }

    // 3. Afficher : effacer l'ancienne position
    // et dessiner la nouvelle

    if ((int)dotX != drawnX || (int)dotY != drawnY) {

        tft.fillRect(drawnX, drawnY, 5, 5, ST77XX_BLACK);

        drawnX = (int)dotX;
        drawnY = (int)dotY;

        tft.fillRect(drawnX, drawnY, 5, 5, ST77XX_WHITE);
    }

    Serial.printf("X=%d Y=%d\n", rawX, rawY);
}
