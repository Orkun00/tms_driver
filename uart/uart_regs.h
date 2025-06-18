#ifndef UART_REGS_H
#define UART_REGS_H

#include "tms570_common.h"

/* Base addresses for SCI modules */
#define TMS570_SCI1_BASE_ADDR                ((tms570_reg*)0xFFF7E400)
#define TMS570_SCI2_BASE_ADDR                ((tms570_reg*)0xFFF7E600)

/* SCI Register Offsets */
#define TMS570_SCI_GCR0_OFFSET               (0x00 / sizeof(tms570_reg))  /* Global Control Register 0 */
#define TMS570_SCI_GCR1_OFFSET               (0x04 / sizeof(tms570_reg))  /* Global Control Register 1 */
#define TMS570_SCI_FORMAT_OFFSET             (0x28 / sizeof(tms570_reg))  /* Format Control Register */
#define TMS570_SCI_BRS_OFFSET                (0x2C / sizeof(tms570_reg))  /* Baud Rate Selection Register */
#define TMS570_SCI_FLR_OFFSET                (0x1C / sizeof(tms570_reg))  /* Flag Register */
#define TMS570_SCI_RD_OFFSET                 (0x34 / sizeof(tms570_reg))  /* Receive Data Buffer */
#define TMS570_SCI_TD_OFFSET                 (0x38 / sizeof(tms570_reg))  /* Transmit Data Buffer */

/* Register Masks */
#define TMS570_SCI_GCR0_MASK                 (0x00000001)
#define TMS570_SCI_GCR1_MASK                 (0x03FFFFFF)
#define TMS570_SCI_FORMAT_MASK               (0x00070007)
#define TMS570_SCI_BRS_MASK                  (0x00FFFFFF)
#define TMS570_SCI_FLR_MASK                  (0xFFFFFFFF)
#define TMS570_SCI_RD_MASK                   (0x000000FF)
#define TMS570_SCI_TD_MASK                   (0x000000FF)

/* GCR0 Fields */
#define TMS570_SCI_GCR0_RESET_BIT_LEN        (1)
#define TMS570_SCI_GCR0_RESET_BIT_OFFSET     (0)

/* GCR1 Fields */
#define TMS570_SCI_GCR1_COMM_MODE_BIT_LEN    (1)
#define TMS570_SCI_GCR1_COMM_MODE_OFFSET     (0)
#define TMS570_SCI_GCR1_TIMING_MODE_OFFSET   (1)
#define TMS570_SCI_GCR1_SWRST_OFFSET         (7)
#define TMS570_SCI_GCR1_RXENA_OFFSET         (24)
#define TMS570_SCI_GCR1_TXENA_OFFSET         (25)

/* FORMAT Fields */
#define TMS570_SCI_FORMAT_CHAR_LEN_MASK      (0x00000007)
#define TMS570_SCI_FORMAT_LENGTH_MASK        (0x00070000)

/* BRS Fields - Chapter 30 SCI-only mode */
#define TMS570_SCI_BRS_BAUD_BIT_LEN          (24)
#define TMS570_SCI_BRS_BAUD_OFFSET           (0)

/* FLR Fields */
#define TMS570_SCI_FLR_TXRDY_OFFSET          (8)
#define TMS570_SCI_FLR_RX_RDY_OFFSET         (9)

#endif // UART_REGS_H
