#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

static const uint8_t TX = 43;
static const uint8_t RX = 44;

static const uint8_t SDA = 47;
static const uint8_t SCL = 48;

static const uint8_t SS = 3;
static const uint8_t MOSI = 17;
static const uint8_t MISO = 8;
static const uint8_t SCK = 18;

#define SERIAL_RX RX
#define SERIAL_TX TX
#define BAD_RX SERIAL_RX
#define BAD_TX SERIAL_TX
#define USB_as_HID 1

#define BTN_ALIAS "\"OK\""
#define HAS_5_BUTTONS
#define SEL_BTN 37
#define UP_BTN 33
#define DW_BTN 34
#define R_BTN 36
#define L_BTN 35
#define RST_BTN 45
#define BTN_ACT LOW

#define RXLED 4
#define LED 5
#define LED_ON HIGH
#define LED_OFF LOW

#define USE_CC1101_VIA_SPI
#define CC1101_GDO0_PIN 38
#define CC1101_GDO2_PIN 39
#define CC1101_SS_PIN 14
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

#define USE_NRF24_VIA_SPI
#define NRF24_CE_PIN 40
#define NRF24_SS_PIN 41
#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

#define FP 1
#define FM 2
#define FG 3

#define HAS_SCREEN 1
#define ROTATION 1
#define MINBRIGHT (uint8_t)15

#define USER_SETUP_LOADED 1
#define ILI9341_DRIVER 1
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_BACKLIGHT_ON 1
#define TFT_BL 21
#define TFT_RST 16
#define TFT_DC 15
#define TFT_MISO 8
#define TFT_MOSI 17
#define TFT_SCLK 18
#define TFT_CS 7
#define TOUCH_CS -1
#define SMOOTH_FONT 1
#define SPI_FREQUENCY 27000000
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000

#define SDCARD_CS 3
#define SDCARD_SCK 18
#define SDCARD_MISO 8
#define SDCARD_MOSI 17

#define GROVE_SDA SDA
#define GROVE_SCL SCL

#define SPI_SCK_PIN 13
#define SPI_MOSI_PIN 12
#define SPI_MISO_PIN 11
#define SPI_SS_PIN 43

#define HAS_RGB_LED 0

#endif /* Pins_Arduino_h */
