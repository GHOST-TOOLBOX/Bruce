# Mapeamento de pinos – Ghost (ESP32-S3 DevKitC-1 + ILI9341)

Tabela de referência rápida para o ambiente **Ghost**, correlacionando os GPIOs do DevKitC-1 aos periféricos conectados.

## Visão geral dos barramentos
- **SPI (rádios)**: compartilhado entre CC1101 e NRF24 (SCK/MISO/MOSI comuns), cada um com pino CS dedicado.
- **SPI (TFT/SD)**: barramento usado pelo display ILI9341 e pelo slot SD (se presente); pinos separados de CS para cada dispositivo.
- **I2C**: PN532 e demais periféricos I2C no par SDA/SCL padrão.
- **Entradas**: joystick/botões com `INPUT_PULLUP`, ativos em nível baixo.

## Tabela detalhada
| Subsistema | Função / Sinal | GPIO ESP32-S3 | Observações |
| --- | --- | --- | --- |
| Serial | TX | 43 | `SERIAL_TX` / `BAD_TX` |
| Serial | RX | 44 | `SERIAL_RX` / `BAD_RX` |
| I2C | SDA | 47 | `GROVE_SDA` / PN532 quando em I2C |
| I2C | SCL | 48 | `GROVE_SCL` / PN532 quando em I2C |
| SPI (TFT/SD) | SCK | 18 | Barramento do display e SD |
| SPI (TFT/SD) | MOSI | 17 | Barramento do display e SD |
| SPI (TFT/SD) | MISO | 8 | Barramento do display e SD |
| Display ILI9341 | CS | 7 | `TFT_CS` |
| Display ILI9341 | DC | 15 | `TFT_DC` |
| Display ILI9341 | RST | 16 | `TFT_RST` |
| Display ILI9341 | BL | 21 | `TFT_BL`, ativo em HIGH |
| Slot SD (opcional) | CS | 3 | `SDCARD_CS` |
| SPI (rádios) | SCK | 13 | Barramento dedicado aos rádios |
| SPI (rádios) | MOSI | 12 | Barramento dedicado aos rádios |
| SPI (rádios) | MISO | 11 | Barramento dedicado aos rádios |
| CC1101 | CS | 14 | `CC1101_SS_PIN` |
| CC1101 | GDO0 | 38 | Interrupção/IRQ |
| CC1101 | GDO2 | 39 | Interrupção/IRQ |
| NRF24L01+ | CE | 40 | `NRF24_CE_PIN` |
| NRF24L01+ | CSN | 41 | `NRF24_SS_PIN` |
| Joystick/Botões | UP (sinal lógico) | 35 | Físico: mover para **cima** aciona o fio LEFT do módulo |
| Joystick/Botões | DOWN (sinal lógico) | 36 | Físico: mover para **baixo** aciona o fio RIGHT do módulo |
| Joystick/Botões | LEFT / ESC | 34 | Físico: mover para **esquerda** aciona o fio DOWN do módulo |
| Joystick/Botões | RIGHT | 33 | Físico: mover para **direita** aciona o fio UP do módulo |
| Joystick/Botões | SELECT / OK (MID + SET jumpeados) | 37 | Ativo em LOW, `INPUT_PULLUP` |
| Botão auxiliar | RST → ESC | 45 | Ativo em LOW, `INPUT_PULLUP`; mapeado para cancelar/voltar |
| LEDs | RX LED | 4 | Usado como `irRx` por padrão |
| LEDs | Estado | 5 | `LED` (ativo em HIGH) |

## Notas
- Os pinos de SPI dos rádios (`SPI_SCK_PIN`, `SPI_MISO_PIN`, `SPI_MOSI_PIN`) são independentes do barramento do display/SD para reduzir interferência; basta manter cada módulo com seu CS em nível alto quando inativo.
- O PN532 pode usar este mesmo par de I2C sem conflito com outros dispositivos I2C.
- Se necessário economizar GPIOs, é possível unificar os barramentos SPI, mas manter as definições atuais garante maior estabilidade gráfica (TFT) e dos rádios.
- O joystick foi instalado rotacionado: a tabela já reflete a correspondência entre movimento físico e fio do módulo. O pino MID está jumpeado ao SET para compartilhar a função de seleção, e o botão RST foi mapeado para a ação de cancelar/voltar.
