#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>
#include "sci_lin_regs.h"

/**
 * @enum uart_mode
 * @brief UART operation modes.
 */
typedef enum uart_mode_e {
    UART_MODE_RESET = 0,    /** Reset mode */
    UART_MODE_NORMAL_OP,    /** Normal operation mode */
    NUM_OF_UART_MODE        /** Number of UART modes */
} uart_mode_t;

/**
 * @brief Initialize UART with specified mode.
 * 
 * Takes the SCI module out of reset, configures baud rate,
 * enables RX and TX, and sets the communication mode.
 * 
 * @param[in] mode UART mode to set. @see uart_mode_t
 * @return true if initialized successfully, false otherwise.
 */
bool uart_init(uart_mode_t mode);

/**
 * @brief Send a single byte via UART.
 * 
 * Waits until the transmitter is ready before sending.
 * 
 * @param[in] byte The byte to send
 * @return true if sent successfully, false otherwise.
 */
bool uart_send_byte(uint8_t byte);

/**
 * @brief Send a null-terminated string via UART.
 * 
 * Uses uart_send_byte() in a loop.
 * 
 * @param[in] str Null-terminated string to send
 * @return true if sent successfully, false otherwise.
 */
bool uart_send_string(const char* str);

/**
 * @brief Receive a single byte via UART (blocking).
 * 
 * Waits until a byte is available in RX buffer.
 * 
 * @param[out] byte Pointer to store received byte
 * @return true if received successfully, false otherwise.
 */
bool uart_receive_byte(uint8_t* byte);

/**
 * @brief Check if RX data is available.
 * 
 * Non-blocking check on RXRDY flag.
 * 
 * @return true if data is ready to read, false otherwise.
 */
bool uart_data_available(void);

#endif // UART_H
