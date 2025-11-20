#include "core/powerSave.h"
#include <Wire.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio() {
    if (UP_BTN >= 0) pinMode(UP_BTN, INPUT_PULLUP);
    if (SEL_BTN >= 0) pinMode(SEL_BTN, INPUT_PULLUP);
    if (DW_BTN >= 0) pinMode(DW_BTN, INPUT_PULLUP);
    if (R_BTN >= 0) pinMode(R_BTN, INPUT_PULLUP);
    if (L_BTN >= 0) pinMode(L_BTN, INPUT_PULLUP);
    if (RST_BTN >= 0) pinMode(RST_BTN, INPUT_PULLUP);

    pinMode(CC1101_SS_PIN, OUTPUT);
    pinMode(NRF24_SS_PIN, OUTPUT);

    digitalWrite(CC1101_SS_PIN, HIGH);
    digitalWrite(NRF24_SS_PIN, HIGH);

    bruceConfig.rfModule = CC1101_SPI_MODULE;
    bruceConfig.irRx = RXLED;

    Wire.setPins(GROVE_SDA, GROVE_SCL);
    Wire.begin(GROVE_SDA, GROVE_SCL);
}

bool isCharging() { return false; }

int getBattery() { return -1; }

/*********************************************************************
** Function: setBrightness
** location: settings.cpp
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    if (brightval == 0) {
        analogWrite(TFT_BL, brightval);
    } else {
        int bl = MINBRIGHT + round(((255 - MINBRIGHT) * brightval / 100));
        analogWrite(TFT_BL, bl);
    }
}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = 0;
    if (millis() - tm < 200 && !LongPress) return;

    // Joystick instalado rotacionado: o eixo lógico não coincide com os fios do módulo.
    // Mapeamos as leituras "brutas" para os gestos físicos informados:
    //  - movimento para a direita aciona o pino UP do módulo
    //  - movimento para baixo aciona o pino RIGHT do módulo
    //  - movimento para a esquerda aciona o pino DOWN do módulo
    //  - movimento para cima aciona o pino LEFT do módulo
    bool rawUp = digitalRead(UP_BTN);
    bool rawDown = digitalRead(DW_BTN);
    bool rawLeft = digitalRead(L_BTN);
    bool rawRight = digitalRead(R_BTN);
    bool rawSel = digitalRead(SEL_BTN);
    bool rawRst = (RST_BTN >= 0) ? digitalRead(RST_BTN) : true;

    bool navRight = rawUp;    // físico: direita
    bool navDown = rawRight;  // físico: baixo
    bool navLeft = rawDown;   // físico: esquerda
    bool navUp = rawLeft;     // físico: cima

    if (!rawSel || !navUp || !navDown || !navLeft || !navRight || !rawRst) {
        tm = millis();
        if (!wakeUpScreen()) AnyKeyPress = true;
        else return;
    }
    if (!navLeft) { PrevPress = true; }
    if (!navRight) { NextPress = true; }
    if (!navUp) {
        UpPress = true;
        PrevPagePress = true;
    }
    if (!navDown) {
        DownPress = true;
        NextPagePress = true;
    }
    if (!rawSel) { SelPress = true; }
    if ((!navLeft && !navRight) || !rawRst) {
        EscPress = true;
        NextPress = false;
        PrevPress = false;
    }
}

/*********************************************************************
** Function: powerOff
** location: mykeyboard.cpp
** Turns off the device (or try to)
**********************************************************************/
void powerOff() {
    esp_sleep_enable_ext0_wakeup((gpio_num_t)SEL_BTN, BTN_ACT);
    esp_deep_sleep_start();
}

/*********************************************************************
** Function: checkReboot
** location: mykeyboard.cpp
** Btn logic to turn off the device (name is odd btw)
**********************************************************************/
void checkReboot() {
    int countDown;
    if (digitalRead(L_BTN) == BTN_ACT && digitalRead(R_BTN) == BTN_ACT) {
        uint32_t time_count = millis();
        while (digitalRead(L_BTN) == BTN_ACT && digitalRead(R_BTN) == BTN_ACT) {
            if (millis() - time_count > 500) {
                tft.setTextSize(1);
                tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
                countDown = (millis() - time_count) / 1000 + 1;
                if (countDown < 4)
                    tft.drawCentreString("PWR OFF IN " + String(countDown) + "/3", tftWidth / 2, 12, 1);
                else {
                    tft.fillScreen(bruceConfig.bgColor);
                    while (digitalRead(L_BTN) == BTN_ACT || digitalRead(R_BTN) == BTN_ACT);
                    delay(200);
                    powerOff();
                }
                delay(10);
            }
        }

        delay(30);
        tft.fillRect(60, 12, tftWidth - 60, tft.fontHeight(1), bruceConfig.bgColor);
    }
}
