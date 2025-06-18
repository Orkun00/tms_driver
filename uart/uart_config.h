#ifndef UART_CONFIG_H
#define UART_CONFIG_H

// 1. Peripheral Clock Frequency (VCLK or functional clock to SCI)
//#define VCLK_FREQ <value_from_TRM_or_your_board>  // e.g., 80000000U for 80 MHz

// 2. Default Baud Rate
//#define UART_BAUDRATE <desired_baudrate>          // e.g., 115200U

#define UART_BAUDRATE 115200U
#define VCLK_FREQ 80000000U

// 3. Baud Rate Register Value (SCIBRS) - Chapter 30 SCI-only mode
// Bits 31-24: Reserved (writes have no effect)
// Bits 23-0: BAUD value
// Formula: Baud = VCLK_FREQ / (16 * (BAUD + 1))
#define BRS_VAL (((VCLK_FREQ / (16U * UART_BAUDRATE)) - 1U) & 0x00FFFFFFU)



// 4. SCIFLR Register Flags — Section 29.7.8
#define SCIFLR_BRKDT        (1U << 0)  
#define SCIFLR_WAKEUP       (1U << 1)  
#define SCIFLR_IDLE         (1U << 2)  
#define SCIFLR_BUSY         (1U << 3)  
#define SCIFLR_TIMEOUT      (1U << 4)
//Reserved
#define SCIFLR_TOAWUS       (1U << 6)
#define SCIFLR_TOA3WUS      (1U << 7)
#define SCIFLR_TXRDY        (1U << 8)
#define SCIFLR_RX_RDY       (1U << 9)
#define SCIFLR_TX_WAKE      (1U << 10)
#define SCIFLR_TX_EMPTY     (1U << 11)
#define SCIFLR_RX_WAKE      (1U << 12)
#define SCIFLR_ID_TX        (1U << 13)
#define SCIFLR_ID_RX        (1U << 14)
//Reserved from 15 to 23
#define SCIFLR_PE           (1U << 24)
#define SCIFLR_OE           (1U << 25)
#define SCIFLR_FE           (1U << 26)
#define SCIFLR_NRE          (1U << 27)
#define SCIFLR_ISFE         (1U << 28)
#define SCIFLR_CE           (1U << 29)
#define SCIFLR_PBE          (1U << 30)
#define SCIFLR_BE           (1U << 31)

// 5. SCIGCR1 Bit Definitions — Section 29.7.2
#define GCR1_COMM_MODE (1U << 0)
#define GCR1_TIMING_MODE (1U << 1)
#define GCR1_PARITY_ENA (1U << 2)
#define GCR1_PARITY (1U << 3)
#define GCR1_STOP (1U << 4)
#define GCR1_CLOCK (1U << 5)
#define GCR1_LIN_MODE (1U << 6)
#define GCR1_SWnRST (1U << 7)
#define GCR1_SLEEP (1U << 8)
#define GCR1_ADAPT (1U << 9)
#define GCR1_MBUF_MODE (1U << 10)
#define GCR1_CTYPE (1U << 11)
#define GCR1_HGEN_CTRL (1U << 12)
#define GCR1_STOP_EXT_FRAME (1U << 13)
//Reserved from 14 to 15
#define GCR1_LOOP_BACK (1U << 16)
#define GCR1_CONT (1U << 17)
//Reserved from 18 to 23
#define GCR1_RXENA (1U << 24)
#define GCR1_TXENA (1U << 25)
//Reserved from 26 to 31

// 6. SCIGCR0 Reset/Enable — Section 29.7.1
#define GCR0_OUT_RESET          (1U << 0)  // Must set to 1 to take SCI out of reset
#define GCR0_IN_RESET          (0U << 0)  // Must set to 0 to take SCI out of reset
//Reserved from 1 to 31. Reads return 0. Writes have no effect.

// Character length (CHAR: bits 2:0)
#define SCIFORMAT_CHAR_8BIT       (7U << 0)  // 8-bit character

// Frame length (LENGTH: bits 18:16)
#define SCIFORMAT_FRAME_1CHAR     (0U << 16)
#define SCIFORMAT_FRAME_2CHARS    (1U << 16)
#define SCIFORMAT_FRAME_4CHARS    (3U << 16)
#define SCIFORMAT_FRAME_8CHARS    (7U << 16)

// Combined default format: 8-bit character, 8 characters per frame
#define SCIFORMAT_DEFAULT         (SCIFORMAT_CHAR_8BIT | SCIFORMAT_FRAME_8CHARS)

//0-7 bit used for SCIRD
#define SCIRD_MASK (255U << 0)
#define SCIRD_SHIFT 0
//Reserved from 8 to 31

#define SCITD_MASK (255U << 0)
#define SCITD_SHIFT 0
//Reserved from 8 to 31

// 8. Optional: Toggle which SCI to use
#define UART_USE_SCI1 1
#define UART_USE_SCI2 0

#endif // UART_CONFIG_H
