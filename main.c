#include "uart/uart.h"
#include "uart/uart_regs.h"

int main(void) {
    uart_t uart1 = {
        .baudrate = 115200,
        .regs = SCI1
    };

    uart_init(&uart1);
    uart_send_string(&uart1, "UART Initialized!\r\n");

    while (1) {
        if (uart_data_available(&uart1)) {
            uint8_t ch = uart_receive_byte(&uart1);
            uart_send_byte(&uart1, ch); // Echo
        }
    }
}
