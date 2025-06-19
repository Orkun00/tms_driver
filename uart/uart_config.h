#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#define UART_BAUDRATE 115200U
#define VCLK_FREQ 80000000U

// Baud Rate Register Value (SCIBRS)
#define BRS_VAL (((VCLK_FREQ / (16U * UART_BAUDRATE)) - 1U) & 0x00FFFFFFU)

// Character length (CHAR: bits 2:0)
#define SCIFORMAT_CHAR_8BIT       (7U << 0)  // 8-bit character
// Frame length (LENGTH: bits 18:16)
#define SCIFORMAT_FRAME_8CHARS    (7U << 16)
// Combined default format: 8-bit character, 8 characters per frame
#define SCIFORMAT_DEFAULT         (SCIFORMAT_CHAR_8BIT | SCIFORMAT_FRAME_8CHARS)

#endif // UART_CONFIG_H
