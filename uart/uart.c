#include "uart.h"
#include "uart_regs.h"
#include "uart_config.h"

/* Static pointer to the SCI registers we're using */
static volatile tms570_reg* sci_base = TMS570_SCI1_BASE_ADDR;

bool uart_init(uart_mode_t mode) {
    if (!IS_ENUM_IN_RANGE(mode, NUM_OF_UART_MODE)) {
        return false;
    }

    /* Step 1: Bring SCI out of reset (SCIGCR0) */
    tms570_reg* gcr0_reg = sci_base + TMS570_SCI_GCR0_OFFSET;
    tms570_reg gcr0_val = tms570_update_field(*gcr0_reg, 1, 
                          TMS570_SCI_GCR0_RESET_BIT_OFFSET,
                          TMS570_SCI_GCR0_RESET_BIT_LEN);

    if (!tms570_update_register(gcr0_reg, gcr0_val, TMS570_SCI_GCR0_MASK)) {
        return false;
    }

    /* Step 2: Keep in reset while configuring */
    tms570_reg* gcr1_reg = sci_base + TMS570_SCI_GCR1_OFFSET;
    *gcr1_reg &= ~(1U << TMS570_SCI_GCR1_SWRST_OFFSET);

    /* Configure communication mode */
    tms570_reg gcr1_val = *gcr1_reg;
    gcr1_val |= (1U << TMS570_SCI_GCR1_RXENA_OFFSET)    /* Enable receiver */
              | (1U << TMS570_SCI_GCR1_TXENA_OFFSET)    /* Enable transmitter */
              | (1U << TMS570_SCI_GCR1_COMM_MODE_OFFSET); /* Asynchronous mode */

    if (!tms570_update_register(gcr1_reg, gcr1_val, TMS570_SCI_GCR1_MASK)) {
        return false;
    }

    /* Step 3: Set Baud Rate */
    tms570_reg* brs_reg = sci_base + TMS570_SCI_BRS_OFFSET;
    if (!tms570_update_register(brs_reg, BRS_VAL, TMS570_SCI_BRS_MASK)) {
        return false;
    }

    /* Step 4: Set Format */
    tms570_reg* format_reg = sci_base + TMS570_SCI_FORMAT_OFFSET;
    if (!tms570_update_register(format_reg, SCIFORMAT_DEFAULT, TMS570_SCI_FORMAT_MASK)) {
        return false;
    }

    /* Step 5: Release from software reset if in normal mode */
    if (mode == UART_MODE_NORMAL_OP) {
        gcr1_val = *gcr1_reg;
        gcr1_val |= (1U << TMS570_SCI_GCR1_SWRST_OFFSET);
        if (!tms570_update_register(gcr1_reg, gcr1_val, TMS570_SCI_GCR1_MASK)) {
            return false;
        }
    }

    return true;
}

bool uart_send_byte(uint8_t byte) {
    /* Wait until TX is ready */
    tms570_reg* flr_reg = sci_base + TMS570_SCI_FLR_OFFSET;
    while (!(*flr_reg & (1U << TMS570_SCI_FLR_TXRDY_OFFSET)));

    /* Send the byte */
    tms570_reg* td_reg = sci_base + TMS570_SCI_TD_OFFSET;
    return tms570_update_register(td_reg, byte, TMS570_SCI_TD_MASK);
}

bool uart_send_string(const char* str) {
    if (str == NULL) {
        return false;
    }

    while (*str) {
        if (!uart_send_byte((uint8_t)(*str))) {
            return false;
        }
        str++;
    }

    return true;
}

bool uart_receive_byte(uint8_t* byte) {
    if (byte == NULL) {
        return false;
    }

    /* Wait until RX is ready */
    tms570_reg* flr_reg = sci_base + TMS570_SCI_FLR_OFFSET;
    while (!(*flr_reg & (1U << TMS570_SCI_FLR_RX_RDY_OFFSET)));

    /* Read received byte */
    tms570_reg* rd_reg = sci_base + TMS570_SCI_RD_OFFSET;
    *byte = (uint8_t)(*rd_reg & TMS570_SCI_RD_MASK);

    return true;
}

bool uart_data_available(void) {
    tms570_reg* flr_reg = sci_base + TMS570_SCI_FLR_OFFSET;
    return (*flr_reg & (1U << TMS570_SCI_FLR_RX_RDY_OFFSET)) != 0;
}

