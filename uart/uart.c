#include "uart.h"
#include "sci_lin_regs.h"
#include "uart_config.h"
#include "sci_lin_utils.h"

bool linInit(void){
    volatile tms570_reg* sci_lin_reg = TMS570_SCI_LIN_1_BASE_ADDR;

    // 1. Enter reset state (optional, but safe)
    sciEnterResetState(sci_lin_reg);

    // 2. Bring GCR0 out of reset
    gcr0_reset(sci_lin_reg, true);

    // 3. Disable all interrupts
    disable_all_interrupts(sci_lin_reg);

    // 4. Configure GCR1 (TX, RX, clock, stop bits, parity, etc.)
    gcr1_global_control_1(sci_lin_reg, true, true, true, true, false, false, true);

    // 5. Set baudrate
    sciSetBaudrate(sci_lin_reg, 1000000U);

    // 6. Set format (8 bits)
    set_format(sci_lin_reg, 8U - 1U);

    // 7. Configure pins (PIO0, PIO1, etc.)
    set_pio0(sci_lin_reg, 1, 1); // TX/RX functional
    set_pio3(sci_lin_reg, 0, 0); // Default output
    set_pio1(sci_lin_reg, 0, 0); // Output direction
    set_pio6(sci_lin_reg, 0, 0); // Open drain
    set_pio7(sci_lin_reg, 0, 0); // Pullup/pulldown enable
    set_pio8(sci_lin_reg, 1, 1); // Pullup/pulldown select

    // 8. Initialize global transfer variables
    initialize_global_transfer_variables(0U);

    // 9. Exit reset state (start SCI)
    sciExitResetState(sci_lin_reg);

    // 10. Optionally, send a test byte
    sciSendByte(sci_lin_reg, 0x55U);

    return true;
}

int main(void){
    uart_init(UART_MODE_NORMAL_OP);
    return 0;
}