#include "uart.h"
#include "sci_lin_regs.h"
#include "uart_config.h"

static volatile tms570_reg* sci = TMS570_SCI_LIN_1_BASE_ADDR;

bool uart_init(uart_mode_t mode) {
    if (mode != UART_MODE_NORMAL_OP && mode != UART_MODE_RESET) {
        return false;
    }

    // Step 1: Put SCI in reset
    sci[TMS570_SCI_GCR0] = 0;
    // Step 2: Take SCI out of reset
    sci[TMS570_SCI_GCR0] = 1;

    // Step 3: Configure GCR1 for SCI (UART) mode
    tms570_reg gcr1 = 0;
    gcr1 |= (1U << TMS570_SCI_GCR1_COMM_MODE_OFFSET); // Asynchronous
    gcr1 |= (1U << TMS570_SCI_GCR1_RX_ENA_OFFSET);    // Enable RX
    gcr1 |= (1U << TMS570_SCI_GCR1_TX_ENA_OFFSET);    // Enable TX
    gcr1 &= ~(1U << TMS570_SCI_GCR1_LIN_MODE_OFFSET); // SCI mode (not LIN)
    sci[TMS570_SCI_GCR1] = gcr1;

    // Step 4: Set baud rate
    sci[TMS570_SCI_BRS] = BRS_VAL;

    // Step 5: Set data format (8N1, 8 chars per frame)
    sci[TMS570_SCI_FORMAT] = SCIFORMAT_DEFAULT;

    // Step 6: Release from software reset if normal mode
    if (mode == UART_MODE_NORMAL_OP) {
        sci[TMS570_SCI_GCR1] |= (1U << TMS570_SCI_GCR1_SWnRST_OFFSET);
    }

    return true;
}

bool uart_send_byte(uint8_t byte) {
    // Wait for TX ready
    while (!(sci[TMS570_SCI_FLR] & (1U << TMS570_SCI_FLR_TX_RDY_OFFSET)));
    sci[TMS570_SCI_TD] = byte;
    return true;
}

bool uart_send_string(const char* str) {
    if (!str) return false;
    while (*str) {
        if (!uart_send_byte((uint8_t)*str++)) {
            return false;
        }
    }
    return true;
}

bool uart_receive_byte(uint8_t* byte) {
    if (!byte) return false;
    // Wait for RX ready
    while (!(sci[TMS570_SCI_FLR] & (1U << TMS570_SCI_FLR_RX_RDY_OFFSET)));
    *byte = (uint8_t)(sci[TMS570_SCI_RD] & 0xFF);
    return true;
}

bool uart_data_available(void) {
    return (sci[TMS570_SCI_FLR] & (1U << TMS570_SCI_FLR_RX_RDY_OFFSET)) != 0;
}
