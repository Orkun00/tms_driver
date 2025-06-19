#ifndef SCI_LIN_UTILS_H
#define SCI_LIN_UTILS_H

#include <stdint.h>
#include "sci_lin_regs.h"

//GCR0
/**
 * @brief Reset control for the SCI/LIN module.
 *
 * This bit resets the SCI/LIN module. This bit is effective in both SCI and LIN modes.
 *
 * - 0: SCI/LIN module is in reset.
 * - 1: SCI/LIN module is out of reset.
 *
 * @note Read/Write in privileged mode only.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param reset
 *   - false (0): Put SCI/LIN module in reset.
 *   - true  (1): Take SCI/LIN module out of reset.
 */
void sci_lin_reset(volatile tms570_reg* sci_lin_reg, bool reset);

//GCR1
/**
 * @brief Set the SCI/LIN communication mode.
 *
 * In compatibility mode, this bit selects the SCI communication mode.
 * In LIN mode, it selects the length control option for ID-field bits ID4 and ID5.
 *
 * @par SCI mode:
 *   - 0: Idle-line mode is used.
 *   - 1: Address-bit mode is used.
 *
 * @par LIN mode:
 *   - 0: ID4 and ID5 are not used for length control.
 *   - 1: ID4 and ID5 are used for length control.
 *
 * @param commMode
 *   - In compatibility mode: selects the SCI communication mode.
 *   - In LIN mode: selects the length control option for ID-field bits ID4 and ID5.
 */
void comm_mode(volatile tms570_reg* sci_lin_reg, bool commMode);

/**
 * @brief Set the SCI timing mode (asynchronous or synchronous).
 *
 * This function sets the SCI timing mode bit. This bit is effective in SCI mode only.
 * It selects the SCI timing mode:
 *   - 0: Synchronous timing is used.
 *   - 1: Asynchronous timing is used.
 *
 * @param asyncOrSync
 *   - true (1): Asynchronous timing is used.
 *   - false (0): Synchronous timing is used.
 */
void timing_mode(volatile tms570_reg* sci_lin_reg, bool asyncOrSync);

/**
 * @brief Enable or disable the parity function for SCI/LIN.
 *
 * This bit controls the parity feature:
 * - In SCI or buffered SCI mode:
 *   - 0: Parity is disabled. No parity bit is generated during transmission or expected during reception.
 *   - 1: Parity is enabled. A parity bit is generated during transmission and expected during reception.
 * - In LIN mode:
 *   - 0: ID field parity verification is disabled.
 *   - 1: ID field parity verification is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param parityEnable
 *   - true (1): Enable parity.
 *   - false (0): Disable parity.
 */
void parity_enable(volatile tms570_reg* sci_lin_reg, bool parityEnable);

/**
 * @brief Select SCI parity odd/even mode.
 *
 * This bit is effective in SCI mode only. If the PARITY ENA bit is set, this bit designates odd or even parity.
 * - 0: Odd parity is used. The parity bit is calculated so that the total number of 1s in the frame (data bits + address bit, if used) is odd.
 * - 1: Even parity is used. The parity bit is calculated so that the total number of 1s in the frame (data bits + address bit, if used) is even.
 *
 * The parity bit is calculated based on the data bits in each frame and the address bit (in address-bit mode).
 * The start and stop fields in the frame are not included in the parity calculation.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param parityOddEven
 *   - false (0): Odd parity is used.
 *   - true  (1): Even parity is used.
 */
void parity_odd_even(volatile tms570_reg* sci_lin_reg, bool parityOddEven);

/**
 * @brief Set the number of stop bits per frame in SCI mode.
 *
 * This bit is effective in SCI mode only.
 * - 0: One stop bit is used.
 * - 1: Two stop bits are used.
 *
 * @note The receiver checks for only one stop bit. However, in idle-line mode, the receiver
 * waits until the end of the second stop bit (if STOP = 1) to begin checking for an idle period.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param stopBits
 *   - false (0): One stop bit is used.
 *   - true  (1): Two stop bits are used.
 */
void sci_number_of_stop_bits_per_frame(volatile tms570_reg* sci_lin_reg, bool stopBits);

/**
 * @brief Set the SCI/LIN clock mode (internal/external or master/slave).
 *
 * The CLOCK bit determines the source of the module clock on the SCICLK pin and
 * whether a LIN node is a slave or master.
 *
 * SCI mode:
 *   - 0: The external SCICLK is the clock source.
 *        Note: If an external clock is selected, the internal baud rate generator and
 *        baud rate registers are bypassed. The maximum frequency allowed for an
 *        externally sourced SCI clock is VCLK/16.
 *   - 1: The internal SCICLK is the clock source.
 *
 * LIN mode:
 *   - 0: The node is in slave mode.
 *   - 1: The node is in master mode.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clockMode
 *   - false (0): External clock (SCI) or slave mode (LIN).
 *   - true  (1): Internal clock (SCI) or master mode (LIN).
 */
void clock_mode(volatile tms570_reg* sci_lin_reg, bool clockMode);

/**
 * @brief Set the LIN mode of the SCI/LIN module.
 *
 * This bit is effective in both LIN and SCI modes. It controls the module's mode of operation.
 * - 0: LIN mode is disabled; SCI mode is enabled.
 * - 1: LIN mode is enabled; SCI mode is disabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param linMode
 *   - false (0): LIN mode is disabled (SCI mode enabled).
 *   - true  (1): LIN mode is enabled (SCI mode disabled).
 */
void lin_mode(volatile tms570_reg* sci_lin_reg, bool linMode);

/**
 * @brief Set the Software Reset (SWnRST) state for the SCI/LIN module.
 *
 * Software reset (active low). This bit is effective in LIN and SCI modes.
 * - 0: The SCI/LIN is in its reset state; no data will be transmitted or received.
 *      Writing a 0 to this bit initializes the SCI/LIN state machines and operating flags.
 *      All affected logic is held in the reset state until a 1 is written to this bit.
 * - 1: The SCI/LIN is in its ready state; transmission and reception can be done.
 *      After this bit is set to 1, the configuration of the module should not change.
 *
 * @note The SCI/LIN should only be configured while SWnRST = 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param SWnRST
 *   - false (0): Put SCI/LIN in reset state.
 *   - true  (1): Put SCI/LIN in ready state.
 */
void SWnRST(volatile tms570_reg* sci_lin_reg, bool SWnRST);

/**
 * @brief Set the SCI Sleep mode.
 *
 * This bit is effective in SCI mode only. In a multiprocessor configuration, this bit controls the receive sleep function.
 * - false (0): Sleep mode is disabled. The SCI/LIN is out of sleep mode.
 * - true  (1): Sleep mode is enabled. The receiver still operates, but RXRDY is updated and SCIRD is loaded with new data
 *              only when an address frame is detected. Other receiver status flags and error interrupts are still updated/requested
 *              if their corresponding interrupt enable bits are set, regardless of the SLEEP bit value.
 *
 * @note The SLEEP bit is not automatically cleared when an address byte is detected.
 * @note See Section 29.2.5.1 for more information on using the SLEEP bit for multiprocessor communication.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enableOrDisable
 *   - false (0): Disable sleep mode (SCI/LIN is active).
 *   - true  (1): Enable sleep mode.
 */
void sci_sleep(volatile tms570_reg* sci_lin_reg, bool enableOrDisable);

/**
 * @brief Enable or disable automatic baud rate adjustment (ADAPT bit) for LIN mode.
 *
 * This mode is effective in LIN mode only. The ADAPT bit affects the detection of the
 * synch field. Two LIN protocol bit rate modes can be enabled with this bit: automatic or select,
 * as defined by the node capability file. The software and network configuration determine which
 * mode is enabled. When this bit is cleared (false), the LIN 2.0 protocol fixed bit rate is used.
 * If the ADAPT bit is set (true), a SCI/LIN slave node detecting the baud rate will compare it to
 * the prescalers in the BRS register and update it if they are different. The BRS register will be
 * updated with the new value. If this bit is not set, there will be no adjustment to the BRS register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param automaticBaudRateAdjustment
 *   - false (0): Automatic baud rate adjustment is disabled (fixed bit rate).
 *   - true  (1): Automatic baud rate adjustment is enabled.
 */
void automatic_baud_rate_adjustment(volatile tms570_reg* sci_lin_reg, bool automaticBaudRateAdjustment);

/**
 * @brief Enable or disable Multi-buffer mode for SCI/LIN.
 *
 * This bit is effective in both LIN and SCI modes. It controls the usage of receive/transmit buffers:
 * - When disabled (false), a single register (RD0/TD0) is used for RX/TX.
 * - When enabled (true), the RX/TX multi-buffers are used.
 *
 * @note The multi-buffer mode is disabled when this bit is cleared.
 * @note The multi-buffer mode is enabled when this bit is set.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param multiBufferMode
 *   - false (0): Multi-buffer mode is disabled (single register RD0/TD0 used).
 *   - true  (1): Multi-buffer mode is enabled (multi-buffers used).
 */
void multi_buffer_mode(volatile tms570_reg* sci_lin_reg, bool multiBufferMode);
/**
 * @brief Set the checksum type for LIN mode (classic or enhanced).
 *
 * This bit is effective in LIN mode only. It controls the type of checksum to be used:
 * - false (0): Classic checksum is used.
 * - true  (1): Enhanced checksum is used.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param checksumType
 *   - false (0): Use classic checksum.
 *   - true  (1): Use enhanced checksum.
 */
void checksum_enhanced(volatile tms570_reg* sci_lin_reg, bool checksumType);

/**
 * @brief Set the HGEN control bit for LIN ID filtering mode.
 *
 * This bit is effective in LIN mode only. It controls the type of mask filtering comparison:
 * - When set to 0: ID filtering uses the ID-BYTE field in the LIN Identification Register (LINID).
 *   - A mask of 0xFF in the LIN Mask Register (LINMASK) will result in no match.
 * - When set to 1: ID filtering uses the ID-SlaveTask BYTE (recommended).
 *   - A mask of 0xFF in the LIN Mask Register (LINMASK) will result in ALWAYS match.
 *
 * @note For software compatibility with future LIN modules, the HGEN CTRL bit must be set to 1,
 *       the RX ID MASK must be set to 0xFF, and the TX ID MASK must be set to 0xFF.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param hgenControl
 *   - false (0): Use ID-BYTE field in LINID for filtering.
 *   - true  (1): Use ID-SlaveTask BYTE for filtering (recommended).
 */
void hgen_control(volatile tms570_reg* sci_lin_reg, bool hgenControl);
/**
 * @brief Stop extended frame communication in LIN mode.
 *
 * This bit is effective in LIN mode only and can be written only during extended frame communication.
 * When set, extended frame communication will be stopped when the current frame transmission/reception is completed.
 * The bit is cleared automatically after the operation. If not in extended frame communication, this bit has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param stopExtFrame
 *   - true (1): Stop extended frame communication after current frame.
 *   - false (0): No effect.
 */
void stop_extended_frame_communication(volatile tms570_reg* sci_lin_reg, bool stopExtFrame);

/**
 * @brief Enable or disable loopback mode for SCI/LIN.
 *
 * This bit is effective in both LIN and SCI modes. The self-checking option for the
 * SCI/LIN can be selected with this bit. If the LINTX and LINRX pins are configured with
 * SCI/LIN functionality, then the LINTX pin is internally connected to the LINRX pin.
 * Externally, during loopback operation, the LINTX pin outputs a high value and the LINRX
 * pin is in a high-impedance state.
 *
 * @note If this bit value is changed while the SCI/LIN is transmitting or receiving data,
 *       errors may result.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param loopbackMode
 *   - false (0): Loopback mode is disabled.
 *   - true  (1): Loopback mode is enabled.
 */
void loopback_mode(volatile tms570_reg* sci_lin_reg, bool loopbackMode);
/**
 * @brief Configure the "Continue on Suspend" feature for SCI/LIN.
 *
 * This bit is effective in both LIN and SCI modes, and only has an effect when a program is being debugged with an emulator.
 * It determines how the SCI/LIN operates when the program is suspended (debug mode).
 *
 * - When set to 0: Upon entering debug mode, the SCI/LIN state machine is frozen. Transmissions and LIN counters are halted and resume when debug mode is exited.
 * - When set to 1: Upon entering debug mode, the SCI/LIN continues to operate until the current transmit and receive functions are complete.
 *
 * The SCI/LIN counters are affected by this bit: when the bit is set, the counters are not stopped; when cleared, the counters are stopped during debug mode.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param continueOnSuspend
 *   - false (0): Freeze SCI/LIN state machine and counters during debug suspend.
 *   - true  (1): Allow SCI/LIN to continue until current transmit/receive complete during debug suspend.
 */
void continiue_on_suspend(volatile tms570_reg* sci_lin_reg, bool continueOnSuspend);
/**
 * @brief Enable or disable the receiver for SCI/LIN.
 *
 * This bit is effective in both LIN and SCI modes. RXENA allows or prevents the
 * transfer of data from the shift buffer (SCIRXSHF) to the receive buffer (SCIRD) or the receive multi-buffers.
 *
 * - 0: The receiver will not transfer data from the shift buffer to the receive buffer or multi-buffers.
 * - 1: The receiver will transfer data from the shift buffer to the receive buffer or multi-buffers.
 *
 * @note Clearing RXENA stops received characters from being transferred into the receive
 * buffer or multi-buffers, prevents the RX status flags from being updated by receive data,
 * and inhibits both receive and error interrupts. However, the shift register continues to
 * assemble data regardless of the state of RXENA.
 *
 * @note If RXENA is cleared before a frame is completely received, the data from the frame
 * is not transferred into the receive buffer.
 *
 * @note If RXENA is set before a frame is completely received, the data from the frame is
 * transferred into the receive buffer. If RXENA is set while SCIRXSHF is in the process of
 * assembling a frame, the status flags are not guaranteed to be accurate for that frame. To
 * ensure that the status flags correctly reflect what was detected on the bus during a
 * particular frame, RXENA should be set before the detection of that frame.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param rxEnable
 *   - false (0): Disable receiver (no transfer to receive buffer or multi-buffers).
 *   - true  (1): Enable receiver (allow transfer to receive buffer or multi-buffers).
 */
void rx_enable(volatile tms570_reg* sci_lin_reg, bool rxEnable);
/**
 * @brief Enable or disable the transmitter for SCI/LIN.
 *
 * This bit is effective in both LIN and SCI modes. Data is transferred from SCITD, or
 * the TDy (with y=0, 1,...7) buffers in LIN mode to the SCITXSHF shift out register only when the
 * TXENA bit is set.
 *
 * - 0: Transfers from SCITD or TDy to SCITXSHF are disabled.
 * - 1: Transfers from SCITD or TDy to SCITXSHF are enabled.
 *
 * @note Data written to SCITD or the transmit multi-buffer before TXENA is set is not
 * transmitted. If TXENA is cleared while transmission is ongoing, the data previously
 * written to SCITD is sent (including the checksum byte in LIN mode).
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param txEnable
 *   - false (0): Disable transmitter (no transfer to SCITXSHF).
 *   - true  (1): Enable transmitter (allow transfer to SCITXSHF).
 */
void tx_enable(volatile tms570_reg* sci_lin_reg, bool txEnable);

//GCR2
/**
 * @brief Power down the SCI/LIN module (local low-power mode).
 *
 * This bit is effective in LIN or SCI mode. When this bit is set, the SCI/LIN module
 * attempts to enter local low-power mode. If the POWERDOWN bit is set while the receiver is actively
 * receiving data and the wakeup interrupt is disabled, then the SCI/LIN will delay entering low-power
 * mode until the reception is completed. In LIN mode, you may set the POWERDOWN bit after
 * receiving a sleep command or on idle bus detection (more than 4 seconds). See Section 29.4 for
 * more information on low-power mode.
 *
 * - 0: The SCI/LIN module is in normal operation.
 * - 1: The SCI/LIN module enters local low-power mode.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param powerDown
 *   - false (0): Normal operation.
 *   - true  (1): Enter local low-power mode.
 */
void power_down(volatile tms570_reg* sci_lin_reg, bool powerDown);
/**
 * @brief Generate wakeup signal in LIN mode.
 *
 * This bit is effective in LIN mode only. This bit controls the generation of a wakeup signal,
 * by transmitting the TDO buffer value. The LIN protocol specifies that this signal should be
 * a dominant for T_WUSIG. This bit is cleared on reception of a valid synch break.
 *
 * - 0: No wakeup signal will be generated.
 * - 1: The TDO buffer value will be transmitted for a wakeup signal. The bit will be cleared on a SWnRST.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param generate
 *   - false (0): No wakeup signal will be generated.
 *   - true  (1): Generate a wakeup signal by transmitting the TDO buffer value.
 */
void generate_wakeup_signal(volatile tms570_reg* sci_lin_reg, bool generate);
/**
 * @brief Send checksum byte in LIN mode.
 *
 * This bit is effective in LIN mode only. It is used by the transmitter with extended frames to send a checksum byte.
 * 
 * - In non-multi-buffer mode, the checksum byte will be sent after the current byte transmission.
 * - In multi-buffer mode, the checksum byte will be sent after the last byte count, indicated by SCIFORMAT[18:16].
 *   See Section 29.3.1.6 for more details.
 * - The SC bit will be cleared after the checksum byte has been transmitted.
 * - During multi-buffer mode:
 *   a) The checksum byte will be sent after the last byte count, indicated by SCIFORMAT[18:16].
 *   b) Checksum will not be sent if SC is set before transmitting the very first byte (during interframe space).
 *   c) SC bit will be auto-cleared after the checksum byte has been transmitted.
 *   d) Checksum transmission is not guaranteed if SC bit is write-cleared by software during the checksum transmission.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param sendChecksumByte
 *   - false (0): No checksum byte will be sent.
 *   - true  (1): A checksum byte will be sent.
 */
void send_checksum_byte(volatile tms570_reg* sci_lin_reg, bool sendChecksumByte);

/**
 * @brief Trigger checksum compare in LIN mode (receiver, extended frames).
 *
 * This function sets the Compare Checksum (CC) bit, which is used by the receiver in LIN mode for extended frames
 * to initiate a checksum comparison. The CC bit should be set only after the RX_RDY flag is set for the last received data.
 *
 * - In non-multi-buffer mode: When the CC bit is set, the checksum will be compared on the byte that is expected to be the checksum byte.
 * - In multi-buffer mode:
 *   a) If the CC bit is set during the reception of data, the byte received after the programmed number of data bytes
 *      (as indicated by SCIFORMAT[18:16]) is treated as the checksum byte.
 *   b) If the CC bit is set during the idle period (inter-frame space), the immediate next byte is treated as the checksum byte.
 *   c) The CC bit is auto-cleared after the checksum byte has been received and compared.
 *   d) Checksum reception is not guaranteed if the CC bit is write-cleared by software during checksum reception.
 *
 * @note This bit is effective in LIN mode only. See Section 29.3.1.6 for more details.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param compareChecksum
 *   - false (0): No checksum compare will occur.
 *   - true  (1): Compare checksum on expected checksum byte.
 */
void compare_checksum(volatile tms570_reg* sci_lin_reg, bool compareChecksum);

//SCI_LIN_SET_INT
/**
 * @brief Set break-detect interrupt enable.
 *
 * This bit is effective in SCI-compatible mode only. Setting this bit enables the SCI/LIN
 * to generate an error interrupt if a break condition is detected on the LINRX pin.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable break-detect interrupt.
 *   - true  (1): Enable break-detect interrupt.
 */
void set_brkdt_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set wake-up interrupt enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit enables the SCI/LIN
 * to generate a wakeup interrupt and thereby exit low-power mode. If enabled, the wakeup
 * interrupt is asserted when local low-power mode is requested while the receiver is busy or
 * if a low level is detected on the LINRX pin during low-power mode.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable wake-up interrupt.
 *   - true  (1): Enable wake-up interrupt.
 */
void set_wakeup_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set timeout interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the SCI/LIN
 * to generate an interrupt when there is no LIN bus activity (bus idle) for at least four seconds.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable timeout interrupt.
 *   - true  (1): Enable timeout interrupt.
 */
void set_timeout_int(volatile tms570_reg* sci_lin_reg, bool enable);

/**
 * @brief Set timeout after wakeup signal interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the SCI/LIN
 * to generate an interrupt when a timeout occurs after one wakeup signal has been sent.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable timeout after wakeup signal interrupt.
 *   - true  (1): Enable timeout after wakeup signal interrupt.
 */
void set_timeout_after_wakeup_signal_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set timeout after three wakeup signals interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the SCI/LIN
 * to generate an interrupt when a timeout occurs after three wakeup signals have been sent.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable timeout after three wakeup signals interrupt.
 *   - true  (1): Enable timeout after three wakeup signals interrupt.
 */
void set_timeout_after_3_wakeup_signal_int(volatile tms570_reg* sci_lin_reg, bool enable);

/**
 * @brief Set transmitter interrupt enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit enables the SCI/LIN
 * to generate a transmit interrupt as data is being transferred from SCITD to SCITXSHF and
 * the TXRDY bit is being set.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable transmitter interrupt.
 *   - true  (1): Enable transmitter interrupt.
 */
void set_transmitter_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Receiver interrupt enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit enables the SCI/LIN
 * to generate a receive interrupt after a frame has been completely received and the data is
 * being transferred from SCIRXSHF to SCIRD.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable receiver interrupt.
 *   - true  (1): Enable receiver interrupt.
 */
void set_receiver_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set identification interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the SCI/LIN
 * to generate an interrupt when a valid matching identifier is received.
 * See Section 29.3.1.9 for more details.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Disable identification interrupt.
 *   - true  (1): Enable identification interrupt.
 */
void set_identification_int(volatile tms570_reg* sci_lin_reg, bool enable);

/**
 * @brief Set transmit DMA request enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. To enable DMA requests
 * for the transmitter, this bit must be set. If it is cleared, interrupt requests are generated
 * depending on the SET TX INT bit (SCISETINT).
 *
 * - 0 (Read): Transmit DMA request is disabled. (Write: No effect)
 * - 1 (Read and Write): Transmit DMA request is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Transmit DMA request is disabled.
 *   - true  (1): Transmit DMA request is enabled.
 */
void set_transmit_dma(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set receive DMA request enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. To enable DMA requests
 * for the receiver, this bit must be set. If it is cleared, interrupt requests are generated
 * depending on the SET RX INT bit (SCISETINT).
 *
 * - 0 (Read): Receive DMA request is disabled. (Write: No effect)
 * - 1 (Read and Write): Receive DMA request is enabled for address and data frames.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Receive DMA request is disabled.
 *   - true  (1): Receive DMA request is enabled for address and data frames.
 */
void set_receive_dma(volatile tms570_reg* sci_lin_reg, bool enable);

/**
 * @brief Set receive DMA request for all frames (address and data) in SCI-compatible mode.
 *
 * This bit is effective in SCI-compatible mode only. It determines if a separate interrupt is generated
 * for address frames sent in multiprocessor communications.
 *
 * - When this bit is 0:
 *     - RX interrupt requests are generated for address frames.
 *     - DMA requests are generated for data frames.
 * - When this bit is 1:
 *     - RX DMA requests are generated for both address and data frames.
 *
 * - 0 (Read): The DMA request is disabled for address frames (the receive interrupt request is enabled for address frames).
 *   (Write: No effect)
 * - 1 (Read and Write): The DMA request is enabled for address and data frames.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param receiveDmaAll
 *   - false (0): DMA request is disabled for address frames (interrupt enabled for address frames).
 *   - true  (1): DMA request is enabled for both address and data frames.
 */
void set_receive_dma_all(volatile tms570_reg* sci_lin_reg, bool receiveDmaAll);

/**
 * @brief Set parity error interrupt enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit enables
 * the SCI/LIN module to generate an interrupt when a parity error occurs.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Parity error interrupt is disabled.
 *   - true  (1): Parity error interrupt is enabled.
 */
void set_parity_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set overrun-error interrupt enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit enables
 * the SCI/LIN module to generate an interrupt when an overrun error occurs.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Overrun error interrupt is disabled.
 *   - true  (1): Overrun error interrupt is enabled.
 */
void set_overrun_error_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set framing-error interrupt enable.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit enables
 * the SCI/LIN module to generate an interrupt when a framing error occurs.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Framing error interrupt is disabled.
 *   - true  (1): Framing error interrupt is enabled.
 */
void set_framing_error_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set no-response-error interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables
 * the SCI/LIN module to generate an interrupt when a no-response error occurs.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): No-response-error interrupt is disabled.
 *   - true  (1): No-response-error interrupt is enabled.
 */
void set_no_response_error_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set inconsistent-synch-field-error interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the SCI/LIN module
 * to generate an interrupt when there is an inconsistent synch field error.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Inconsistent-synch-field-error interrupt is disabled.
 *   - true  (1): Inconsistent-synch-field-error interrupt is enabled.
 */
void set_inconsistent_synch_field_error_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set checksum-error interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the
 * SCI/LIN module to generate an interrupt when there is a checksum error.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Checksum-error interrupt is disabled.
 *   - true  (1): Checksum-error interrupt is enabled.
 */
void set_checksum_error_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set physical bus error interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables
 * the SCI/LIN module to generate an interrupt when a physical bus error occurs.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Physical bus error interrupt is disabled.
 *   - true  (1): Physical bus error interrupt is enabled.
 */
void set_physical_bus_error_int(volatile tms570_reg* sci_lin_reg, bool enable);
/**
 * @brief Set bit error interrupt enable.
 *
 * This bit is effective in LIN mode only. Setting this bit enables the SCI/LIN
 * module to generate an interrupt when there is a bit error.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read or Write): The interrupt is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable
 *   - false (0): Bit error interrupt is disabled.
 *   - true  (1): Bit error interrupt is enabled.
 */
void set_bit_error_int(volatile tms570_reg* sci_lin_reg, bool enable);

//SCI_LIN_CLR_INT
/**
 * @brief Clear break-detect interrupt.
 *
 * This bit is effective in SCI-compatible mode only. Setting this bit disables
 * the break-detect interrupt.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the break-detect interrupt.
 *   - false (0): No effect.
 */
void clear_break_detect_int(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear wake-up interrupt.
 *
 * This bit is effective in LIN or SCI-compatible mode. Setting this bit disables
 * the wakeup interrupt.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the wake-up interrupt.
 *   - false (0): No effect.
 */
void clear_wakeup_int(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear timeout interrupt.
 *
 * This bit is effective in LIN mode only. Setting this bit disables the timeout (LIN bus idle) interrupt.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the timeout interrupt.
 *   - false (0): No effect.
 */
void clear_timeout_int(volatile tms570_reg* sci_lin_reg, bool clear);

/**
 * @brief Clear timeout-after-wakeup-signal interrupt.
 *
 * This bit is effective in LIN mode only. Setting this bit disables the timeout-after-wakeup-signal
 * interrupt after one wakeup signal interrupt has occurred.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the timeout-after-wakeup-signal interrupt.
 *   - false (0): No effect.
 */
void clear_timeout_after_wakeup_int(volatile tms570_reg* sci_lin_reg, bool clear);

/**
 * @brief Clear timeout-after-three-wakeup-signals interrupt.
 *
 * This bit is effective in LIN mode only. Setting this bit disables the timeout-after-three-wakeup-signals
 * interrupt after three wakeup signal interrupts have occurred.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the timeout-after-three-wakeup-signals interrupt.
 *   - false (0): No effect.
 */
void clear_timeout_after_three_wakeup_int(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear transmitter interrupt.
 *
 * This bit is effective in LIN or SCI mode. Setting this bit disables the transmitter interrupt.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the transmitter interrupt.
 *   - false (0): No effect.
 */
void clear_tx_int(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear receiver interrupt.
 *
 * This bit is effective in LIN or SCI mode. Setting this bit disables the receiver interrupt.
 *
 * - 0 (Read): The interrupt is disabled. (Write: No effect)
 * - 1 (Read): The interrupt is enabled. (Write: The interrupt is disabled)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Disable the receiver interrupt.
 *   - false (0): No effect.
 */
void clear_rx_int(volatile tms570_reg* sci_lin_reg, bool clear);

//SCI_LIN_SET_INT_LVL
/**
 * @brief Set break-detect interrupt level.
 *
 * This bit is effective in SCI-compatible mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map break-detect interrupt to INT0 line.
 *   - true  (1): Map break-detect interrupt to INT1 line.
 */
void set_brkdt_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set wake-up interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map wake-up interrupt to INT0 line.
 *   - true  (1): Map wake-up interrupt to INT1 line.
 */
void set_wakeup_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set timeout interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map timeout interrupt to INT0 line.
 *   - true  (1): Map timeout interrupt to INT1 line.
 */
void set_timeout_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set timeout-after-wakeup-signal interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map timeout-after-wakeup-signal interrupt to INT0 line.
 *   - true  (1): Map timeout-after-wakeup-signal interrupt to INT1 line.
 */
void set_timeout_after_wakeup_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set timeout-after-three-wakeup-signals interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map timeout-after-three-wakeup-signals interrupt to INT0 line.
 *   - true  (1): Map timeout-after-three-wakeup-signals interrupt to INT1 line.
 */
void set_timeout_after_three_wakeup_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set transmitter interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map transmitter interrupt to INT0 line.
 *   - true  (1): Map transmitter interrupt to INT1 line.
 */
void set_transmitter_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set receiver interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map receiver interrupt to INT0 line.
 *   - true  (1): Map receiver interrupt to INT1 line.
 */
void set_receiver_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set ID interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map ID interrupt to INT0 line.
 *   - true  (1): Map ID interrupt to INT1 line.
 */
void set_id_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set receive DMA all interrupt level.
 *
 * This bit is effective in SCI mode only.
 *
 * - 0 (Read): The receive interrupt request for address frames is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The receive interrupt request for address frames is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map receive DMA all interrupt to INT0 line.
 *   - true  (1): Map receive DMA all interrupt to INT1 line.
 */
void set_receive_dma_all_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set parity error interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map parity error interrupt to INT0 line.
 *   - true  (1): Map parity error interrupt to INT1 line.
 */
void set_parity_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set overrun-error interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map overrun-error interrupt to INT0 line.
 *   - true  (1): Map overrun-error interrupt to INT1 line.
 */
void set_overrun_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set framing-error interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map framing-error interrupt to INT0 line.
 *   - true  (1): Map framing-error interrupt to INT1 line.
 */
void set_framing_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set no-response-error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map no-response-error interrupt to INT0 line.
 *   - true  (1): Map no-response-error interrupt to INT1 line.
 */
void set_no_response_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set inconsistent-synch-field-error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map inconsistent-synch-field-error interrupt to INT0 line.
 *   - true  (1): Map inconsistent-synch-field-error interrupt to INT1 line.
 */
void set_inconsistent_synch_field_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set checksum-error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map checksum-error interrupt to INT0 line.
 *   - true  (1): Map checksum-error interrupt to INT1 line.
 */
void set_checksum_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);

/**
 * @brief Set physical bus error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map physical bus error interrupt to INT0 line.
 *   - true  (1): Map physical bus error interrupt to INT1 line.
 */
void set_physical_bus_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);
/**
 * @brief Set bit error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read or Write): The interrupt level is mapped to the INT1 line.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param intLevel
 *   - false (0): Map bit error interrupt to INT0 line.
 *   - true  (1): Map bit error interrupt to INT1 line.
 */
void set_bit_error_int_level(volatile tms570_reg* sci_lin_reg, bool intLevel);

//SCI_LIN_CLEAR_INT_LVL

/**
 * @brief Clear break-detect interrupt level.
 *
 * This bit is effective in SCI-compatible mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_break_detect_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear wake-up interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_wakeup_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear timeout interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_timeout_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear timeout-after-wakeup-signal interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_timeout_after_wakeup_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear timeout-after-three-wakeup-signals interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_timeout_after_three_wakeup_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear transmitter interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_transmitter_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear receiver interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_receiver_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear ID interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_id_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear receive DMA interrupt level.
 *
 * This bit is effective in SCI-compatible mode only.
 *
 * - 0 (Read): The receive interrupt request for address frames is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The receive interrupt request for address frames is mapped to the INT1 line. (Write: The receive interrupt request for address frames is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the receive interrupt request for address frames to INT0 line.
 *   - false (0): No effect.
 */
void clear_receive_dma_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear parity interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_parity_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear overrun-error interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_overrun_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear framing-error interrupt level.
 *
 * This bit is effective in LIN or SCI-compatible mode.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_framing_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear no-response-error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_no_response_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear inconsistent-synch-field-error (ISFE) interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_inconsistent_synch_field_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear checksum-error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_checksum_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear physical bus error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_physical_bus_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);
/**
 * @brief Clear bit error interrupt level.
 *
 * This bit is effective in LIN mode only.
 *
 * - 0 (Read): The interrupt level is mapped to the INT0 line. (Write: No effect)
 * - 1 (Read): The interrupt level is mapped to the INT1 line. (Write: The interrupt level is mapped to the INT0 line.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param clear
 *   - true (1): Map the interrupt level to INT0 line.
 *   - false (0): No effect.
 */
void clear_bit_error_int_level(volatile tms570_reg* sci_lin_reg, bool clear);

//SCI_LIN_FLR
/**
 * @brief Get the SCI break-detect flag.
 *
 * This bit is effective in SCI-compatible mode only. It is set when the SCI detects a break condition on the LINRX pin.
 * A break condition occurs when the LINRX pin remains continuously low for at least 10 bits after a missing first stop bit,
 * that is, after a framing error. Detection of a break condition causes the SCI to generate an error interrupt if the
 * SET BRKDT INT bit is set.
 *
 * The BRKDT bit is reset by the following:
 *   - Setting of the SWnRST bit
 *   - Setting of the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * @note
 *   - Read: 0 = No break condition has been detected since the last clear. (Write: No effect.)
 *   - Read: 1 = A break condition has been detected. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return
 *   - true (1): A break condition has been detected since the last clear.
 *   - false (0): No break condition has been detected since the last clear.
 */
bool get_break_detect_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the SCI break-detect flag.
 *
 * This function clears the break-detect flag by writing 1 to the corresponding bit.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_break_detect_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the wakeup flag status.
 *
 * This bit is effective in LIN mode only. It is set by the SCI/LIN when receiver or
 * transmitter activity has taken the module out of power-down mode. An interrupt is generated if the
 * SET WAKEUP INT bit (SCISETINT[2]) is set.
 *
 * The wakeup flag is cleared by:
 *   - Setting of the SWnRST bit
 *   - Setting of the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * For compatibility mode, see the SCI documentation for more information on low-power mode.
 *
 * @note
 *   - 0 (Read): The module will not wake up from power-down mode. (Write: No effect.)
 *   - 1 (Read): Wake up from power-down mode. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return
 *   - true (1): Wake up from power-down mode has occurred.
 *   - false (0): No wake up from power-down mode.
 */
bool get_wakeup_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the wakeup flag.
 *
 * This function clears the wakeup flag by writing 1 to the corresponding bit.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void clear_wakeup_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the SCI receiver idle flag status.
 *
 * This bit is effective in SCI-compatible mode only. While this bit is set, the
 * SCI looks for an idle period to resynchronize itself with the bit stream.
 * The receiver does not receive any data while the bit is set. The bus must be
 * idle for 11 bit periods to clear this bit.
 *
 * The SCI enters the idle state if one of the following events occurs:
 *   - A system reset
 *   - An SCI software reset
 *   - A power down
 *   - The RX pin is configured as a general I/O pin
 *
 * @note
 *   - true (1): The idle period has been detected; the SCI is ready to receive.
 *   - false (0): The idle period has not been detected; the SCI will not receive any data.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return
 *   - true (1): Idle period detected, SCI ready to receive.
 *   - false (0): Idle period not detected, SCI will not receive data.
 */
bool get_receiver_idle_flag(volatile tms570_reg* sci_lin_reg);
/**
 * @brief Get the SCI/LIN bus busy flag status.
 *
 * This bit is effective in LIN mode and SCI-compatible mode. It indicates whether the receiver
 * is currently in the process of receiving a frame. The BUSY bit is set to 1 as soon as the receiver
 * detects the beginning of a start bit, and is cleared when the reception of a frame is complete.
 * The BUSY bit can also be cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset occurring
 *
 * If SET WAKEUP INT is set and power down is requested while this bit is set, the SCI/LIN
 * automatically prevents low-power mode from being entered and generates a wakeup interrupt.
 *
 * @note
 *   - 0: The receiver is not currently receiving a frame.
 *   - 1: The receiver is currently receiving a frame.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return
 *   - true (1): The receiver is currently receiving a frame (BUSY).
 *   - false (0): The receiver is not currently receiving a frame.
 */
bool get_bus_busy_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the LIN bus idle timeout flag status.
 *
 * This bit is effective in LIN mode only. It is set after at least four seconds of bus inactivity
 * (no transitions between recessive and dominant). The bit is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * @note
 *   - 0 (false): No bus idle has been detected since this bit was last cleared.
 *   - 1 (true): A LIN bus idle has been detected.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a LIN bus idle has been detected, false otherwise.
 */
bool get_lin_bus_idle_timeout_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the LIN bus idle timeout flag.
 *
 * Writing a 1 to this bit clears it to 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_lin_bus_idle_timeout_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the timeout after wakeup signal flag status.
 *
 * This bit is effective in LIN mode only. It is set if no synch break is received after a wakeup signal
 * has been sent (minimum 150 ms expiration before another wakeup). The bit is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * @note
 *   - 0 (false): No timeout occurred after one wakeup signal (150 ms).
 *   - 1 (true): Timeout occurred after one wakeup signal.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a timeout occurred after a wakeup signal, false otherwise.
 */
bool get_timeout_after_wakeup_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the timeout after wakeup signal flag.
 *
 * Writing a 1 to this bit clears it to 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_timeout_after_wakeup_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the timeout after three wakeup signals flag status.
 *
 * This bit is effective in LIN mode only. It is set if no synch break is received after three wakeup signals
 * and a period of 1.5 seconds has passed (before another round of wakeup signals is issued).
 * The bit is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * See Section 29.4.3 for more information.
 *
 * @note
 *   - 0 (false): No timeout occurred after three wakeup signals.
 *   - 1 (true): Timeout occurred after three wakeup signals and 1.5 seconds.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a timeout occurred after three wakeup signals, false otherwise.
 */
bool get_timeout_after_three_wakeup_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the timeout after three wakeup signals flag.
 *
 * Writing a 1 to this bit clears it to 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_timeout_after_three_wakeup_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the transmitter buffer register is ready (TXRDY flag).
 *
 * This flag indicates whether the transmit buffer(s) (SCITD in SCI mode, LINTD0/LINTD1 in LIN mode)
 * are ready to accept another character from the CPU. In SCI mode, writing data to SCITD clears this bit.
 * In LIN mode, the bit is cleared once byte 0 (TD0) is written to LINTD0. The flag is set after the data
 * in the TX buffer is shifted into the TX shift register (SCITXSHF).
 *
 * @note
 * - In SCI mode:
 *     - 0: SCITD is full.
 *     - 1: SCITD is ready to receive the next character.
 * - In LIN mode:
 *     - 0: Multi-buffers are full.
 *     - 1: Multi-buffers are ready to receive the next character.
 * - TXRDY is also set by RESET, enabling SWnRST, or a system reset.
 * - The TXRDY flag cannot be cleared by reading the corresponding interrupt offset in SCIINTVECT0/1.
 * - For more details, see Section 29.3.1.9 (LIN mode) and the SCI documentation.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if the transmit buffer is ready to accept a new character, false otherwise.
 */
bool get_transmitter_ready_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the receiver ready flag (RXRDY).
 *
 * In SCI-compatible mode, writing a 1 to the RXRDY bit clears it to 0.
 * In LIN mode, writing a 1 also clears the flag. This bit is also cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Reading the SCIRD register in compatibility mode
 *   - Reading the last data byte RDy of the response in LIN mode
 * Note: Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void clear_receiver_ready_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the receiver ready flag (RXRDY) is set.
 *
 * In SCI-compatible mode, RXRDY is set when SCIRD contains new data.
 * In LIN mode, RXRDY is set when a valid frame is received (multi-buffer mode)
 * or for each received byte (non-multi-buffer mode), provided there are no errors.
 *
 * @note
 *   - 0: No new data is in SCIRD.
 *   - 1: New data is ready to be read from SCIRD.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if new data is ready to be read, false otherwise.
 */
bool get_receiver_ready_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the transmitter wakeup method (TX WAKE) for SCI mode.
 *
 * This bit controls whether the next frame to be transmitted is an address or data frame.
 * - In address-bit mode:
 *     - false (0): Frame will be data (address bit = 0).
 *     - true  (1): Frame will be address (address bit = 1).
 * - In idle-line mode:
 *     - false (0): Frame will be data.
 *     - true  (1): Next frame will be address (writing 1 then dummy data to SCITD causes idle period before next frame).
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param txWake
 *   - false (0): Data frame.
 *   - true  (1): Address frame.
 */
void set_tx_wake(volatile tms570_reg* sci_lin_reg, bool txWake);

/**
 * @brief Check if the transmitter empty flag (TX EMPTY) is set.
 *
 * This flag indicates whether the transmitter's buffer register(s) and shift register are empty.
 * - In SCI mode or LIN non-multi-buffer mode:
 *     - 0: Transmitter buffer or shift register (or both) are loaded with data.
 *     - 1: Transmitter buffer and shift registers are both empty.
 * - In LIN mode using multi-buffer mode:
 *     - 0: Multi-buffer or shift register (or all) are loaded with data.
 *     - 1: Multi-buffer and shift registers are all empty.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if transmitter is empty, false otherwise.
 */
bool get_transmitter_empty_flag(volatile tms570_reg* sci_lin_reg);
/**
 * @brief Check if the receiver wakeup detect flag (RX WAKE) is set.
 *
 * This bit is effective in SCI-compatible mode only. The SCI sets this bit
 * to indicate that the data currently in SCIRD is an address.
 * 
 * - 0: The data in SCIRD is not an address.
 * - 1: The data in SCIRD is an address.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if the data in SCIRD is an address, false otherwise.
 */
bool get_receiver_wakeup_detect_flag(volatile tms570_reg* sci_lin_reg);


/**
 * @brief Check if the Identifier on Transmit (ID TX) flag is set.
 *
 * This bit is effective in LIN mode only. It is set when a valid identifier is received with a transmit match and no ID-parity error.
 * The flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the LINID register
 *   - Receiving a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a valid ID TX has been received since the last clear, false otherwise.
 */
bool get_id_transmit_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Identifier on Transmit (ID TX) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_id_transmit_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Identifier on Receive (ID RX) flag is set.
 *
 * This bit is effective in LIN mode only. The flag is set when a valid identifier is received with a receive match and no ID-parity error.
 * The flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the LINID register
 *   - Receiving a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No valid ID has been received since the last clear.
 * 1 Read: A valid ID RX has been received in LINID[23:16] on an RX match.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a valid ID RX has been received since the last clear, false otherwise.
 */
bool get_id_receive_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Identifier on Receive (ID RX) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_id_receive_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Parity Error (PE) flag is set.
 *
 * This bit is effective in LIN or SCI-compatible mode. It is set when a parity error is detected in the received data.
 * - In SCI address-bit mode, parity is calculated on both data and address bit fields.
 * - In idle-line mode, only the data is used for parity calculation.
 * - If the parity function is disabled (SCIGCR[2] = 0), the PE flag is disabled and always reads as 0.
 * - Detection of a parity error may generate an error interrupt if the SET PE INT bit is set.
 *
 * The PE bit is reset by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reception of a new character or frame (depending on mode)
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No parity error has been detected since the last clear.
 * 1 Read: A parity error has been detected.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a parity error has been detected since the last clear, false otherwise.
 */
bool get_parity_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Parity Error (PE) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_parity_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Overrun Error (OE) flag is set.
 *
 * This bit is effective in LIN or SCI-compatible mode. It is set when the transfer of data from SCIRXSHF to SCIRD
 * overwrites unread data already in SCIRD or the RDy buffers in LINRD0 and LINRD1.
 * Detection of an overrun error causes the LIN to generate an error interrupt if the SET OE INT bit = 1.
 *
 * The OE flag is reset by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No overrun error has been detected since the last clear. (Write: No effect.)
 * 1 Read: An overrun error has been detected. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if an overrun error has been detected since the last clear, false otherwise.
 */
bool get_overrun_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Overrun Error (OE) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_overrun_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Framing Error (FE) flag is set.
 *
 * This bit is effective in LIN or SCI-compatible mode. It is set when an expected stop bit is not found.
 * In SCI compatibility mode, only the first stop bit is checked. A missing stop bit indicates loss of
 * synchronization and an incorrectly framed character. Detection of a framing error causes the SCI/LIN
 * to generate an error interrupt if the SET FE INT bit is set in the SCISETINT register.
 *
 * The framing error flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *   - Reception of a new character/frame (depending on SCI or LIN mode)
 *
 * In multi-buffer mode, the frame is defined in the SCIFORMAT register.
 *
 * 0 Read: No framing error has been detected since the last clear. (Write: No effect.)
 * 1 Read: A framing error has been detected since the last clear. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a framing error has been detected since the last clear, false otherwise.
 */
bool get_framing_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Framing Error (FE) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_framing_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the No-Response Error (NRE) flag is set.
 *
 * This bit is effective in LIN mode only. It is set when there is no response to a master's header
 * completed within TFRAME_MAX. This timeout is applied for message frames of known length
 * (identifiers 0 to 61). The error is detected by the synchronizer.
 * See Section 29.3.1.7 for more information.
 *
 * The no-response error flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reception of a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No no-response error has been detected since the last clear. (Write: No effect.)
 * 1 Read: A no-response error has been detected. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a no-response error has been detected since the last clear, false otherwise.
 */
bool get_no_response_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the No-Response Error (NRE) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_no_response_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Inconsistent Synch Field Error (ISFE) flag is set.
 *
 * This bit is effective in LIN mode only. It is set when an inconsistent synch field error
 * has been detected by the synchronizer during header reception.
 * See Section 29.3.1.5.2 for more information.
 *
 * The inconsistent synch field error flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reception of a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No inconsistent synch field error has been detected. (Write: No effect.)
 * 1 Read: An inconsistent synch field error has been detected. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if an inconsistent synch field error has been detected since the last clear, false otherwise.
 */
bool get_inconsistent_synch_field_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Inconsistent Synch Field Error (ISFE) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_inconsistent_synch_field_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Checksum Error flag is set.
 *
 * This bit is effective in LIN mode only. It is set when a checksum error has been detected
 * by a receiving node (detected by the TED logic). See Section 29.3.1.8 for more information.
 * The type of checksum used depends on the CTYPE bit in SCIGCR1.
 *
 * The checksum error flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reception of a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No error has been detected since this bit was last cleared. (Write: No effect.)
 * 1 Read: An error has been detected since this bit was last cleared. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a checksum error has been detected since the last clear, false otherwise.
 */
bool get_checksum_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Checksum Error flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_checksum_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Physical Bus Error (PBE) flag is set.
 *
 * This bit is effective in LIN mode only. It is set when a physical bus error has been detected
 * by the bit monitor in TED. See Section 29.3.1.8 for more information.
 *
 * The physical bus error flag is cleared by:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reception of a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * Note: The PBE will only be flagged if no Synch Break can be generated (e.g., due to a bus shortage to VBAT)
 * or if no Synch Break Delimiter can be generated (e.g., due to a bus shortage to GND).
 *
 * 0 Read: No error has been detected since this bit was last cleared. (Write: No effect.)
 * 1 Read: An error has been detected since this bit was last cleared. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a physical bus error has been detected since the last clear, false otherwise.
 */
bool get_physical_bus_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Physical Bus Error (PBE) flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_physical_bus_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Check if the Bit Error flag is set.
 *
 * This bit is effective in LIN mode only. It is set when a bit error has occurred,
 * as detected by the internal bit monitor. See Section 29.3.1.8 for more information.
 *
 * The bit error flag is cleared by any of the following:
 *   - Setting the SWnRST bit
 *   - Setting the RESET bit
 *   - A system reset
 *   - Writing a 1 to this bit
 *   - Reception of a new synch break
 *   - Reading the corresponding interrupt offset in SCIINTVECT0/1
 *
 * 0 Read: No error has been detected since this bit was last cleared. (Write: No effect.)
 * 1 Read: An error has been detected since this bit was last cleared. (Write: The bit is cleared to 0.)
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return true if a bit error has been detected since the last clear, false otherwise.
 */
bool get_bit_error_flag(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Clear the Bit Error flag.
 *
 * Writing a 1 to this bit clears the flag. Writing 0 has no effect.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void set_bit_error_flag(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_INT_VECT_0
/**
 * @brief Read the SCI Interrupt Vector Offset 0 (SCIINTVECT0) field.
 *
 * This function reads the interrupt vector offset for INT0 from the SCIINTVECT0 register.
 * Reading this register returns the offset (bits 4:0) of the next highest priority pending interrupt in SCIFLR,
 * and clears the corresponding flag in SCIFLR (except for receive [SCIFLR[9]] and transmit [SCIFLR[8]] interrupts,
 * which are not cleared by reading this register).
 *
 * Bits 31-5 are reserved and always read as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return The 5-bit interrupt vector offset (0x00 - 0x1F).
 */
uint8_t get_int_vect_0(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_INT_VECT_1
/**
 * @brief Read the SCI Interrupt Vector Offset 1 (SCIINTVECT1) field.
 *
 * This function reads the interrupt vector offset for INT1 from the SCIINTVECT1 register.
 * Reading this register returns the offset (bits 4:0) of the next highest priority pending interrupt in SCIFLR,
 * and clears the corresponding flag in SCIFLR (except for receive [SCIFLR[9]] and transmit [SCIFLR[8]] interrupts,
 * which are not cleared by reading this register).
 *
 * Bits 31-5 are reserved and always read as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return The 5-bit interrupt vector offset (0x00 - 0x1F).
 */
uint8_t get_int_vect_1(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the character length (SCIFORMAT[2:0]) for SCI/LIN.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param charLength Character length (1-8). Value of 1 sets 1 bit, 8 sets 8 bits, etc.
 *                   Only the lower 3 bits are used.
 */
void set_char_length(volatile tms570_reg* sci_lin_reg, uint8_t charLength);

/**
 * @brief Get the character length (SCIFORMAT[2:0]) for SCI/LIN.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return Character length (1-8). Value of 1 means 1 bit, 8 means 8 bits, etc.
 */
uint8_t get_char_length(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the frame length (SCIFORMAT[18:16]) for SCI/LIN.
 *
 * In LIN mode, this sets the number of bytes in the response field (1-8).
 * In buffered SCI mode, this sets the number of characters (1-8).
 * Only the lower 3 bits of frameLength are used.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param frameLength Frame/response length (1-8). Value of 1 sets 1 byte/character, 8 sets 8 bytes/characters, etc.
 */
void set_frame_length(volatile tms570_reg* sci_lin_reg, uint8_t frameLength);

/**
 * @brief Get the frame length (SCIFORMAT[18:16]) for SCI/LIN.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return Frame/response length (1-8). Value of 1 means 1 byte/character, 8 means 8 bytes/characters, etc.
 */
uint8_t get_frame_length(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_BRS

/**
 * @brief Set the baud rate selection register (BRS) for SCI/LIN.
 *
 * This function sets the prescaler (P), fractional divider (M), and super fractional divider (U)
 * for the SCI/LIN baud rate selection register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param prescaler 24-bit prescaler value (P), valid range: 0x000000 - 0xFFFFFF
 * @param m 4-bit fractional divider value (M), valid range: 0x0 - 0xF
 * @param u 3-bit super fractional divider value (U), valid range: 0x0 - 0x7
 */
void set_baud_rate_selection(volatile tms570_reg* sci_lin_reg, uint32_t prescaler, uint8_t m, uint8_t u);

/**
 * @brief Get the baud rate selection register (BRS) for SCI/LIN.
 *
 * This function retrieves the prescaler (P), fractional divider (M), and super fractional divider (U)
 * from the SCI/LIN baud rate selection register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_baud_rate_selection(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_ED
/**
 * @brief Read the Receiver Emulation Data Buffer (SCIED) for SCI/LIN.
 *
 * This function reads the 8-bit emulator data (ED) from the SCIED register.
 * Reading SCIED[7:0] does NOT clear the RXRDY flag, unlike reading SCIRD.
 * Only the lower 8 bits are valid; upper bits are always zero.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 8-bit emulator data (ED) from SCIED[7:0].
 */
uint8_t read_emulator_data(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_RD
/**
 * @brief Read the Receiver Data Buffer (SCIRD) for SCI/LIN.
 *
 * This function reads the 8-bit receiver data (RD) from the SCIRD register.
 * Reading SCIRD[7:0] automatically clears the RXRDY flag.
 * Only the lower 8 bits are valid; upper bits are always zero.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 8-bit receiver data (RD) from SCIRD[7:0].
 */
uint8_t read_receiver_data(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Write to the Transmit Data Buffer Register (SCITD) for SCI/LIN.
 *
 * This function writes an 8-bit data value to the SCITD register (Transmit Data Buffer).
 * Only the lower 8 bits are used; upper bits are ignored. Data must be right-justified.
 * Writing to SCITD in SCI-compatible mode transfers the data to the transmit shift register (SCITXSHF),
 * sets the TXRDY flag, and, if TX interrupt is enabled, may trigger an interrupt.
 *
 * Note: Data written that is fewer than 8 bits must be right justified.
 *       Reads from this register always return 0; writes have no effect outside bits [7:0].
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param data 8-bit data to transmit (right justified).
 */
void write_transmit_data(volatile tms570_reg* sci_lin_reg, uint8_t data);

//SCI_LIN_PIO0

/**
 * @brief Set the TX and RX pin functions in the SCI Pin I/O Control Register 0 (SCIPIO0).
 *
 * This function configures the LINTX and LINRX pins as either general-purpose digital I/O or as SCI/LIN transmit/receive pins.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_func 0 = LINTX is general-purpose I/O, 1 = LINTX is SCI/LIN transmit pin.
 * @param rx_func 0 = LINRX is general-purpose I/O, 1 = LINRX is SCI/LIN receive pin.
 */
void set_sci_pio0_functions(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func);


/**
 * @brief Get the TX and RX pin functions from the SCI Pin I/O Control Register 0 (SCIPIO0).
 *
 * This function retrieves the current configuration of the LINTX and LINRX pins.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_sci_pio0_functions(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO1

/**
 * @brief Set the TX and RX pin directions in the SCI Pin I/O Control Register 1 (SCIPIO1).
 *
 * This function configures the direction of the LINTX and LINRX pins when they are used as general-purpose I/O.
 * - TX_DIR (bit 2): 0 = LINTX is input, 1 = LINTX is output
 * - RX_DIR (bit 1): 0 = LINRX is input, 1 = LINRX is output
 *
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_dir 0 = LINTX is input, 1 = LINTX is output
 * @param rx_dir 0 = LINRX is input, 1 = LINRX is output
 */
void set_sci_pio1_directions(volatile tms570_reg* sci_lin_reg, uint8_t tx_dir, uint8_t rx_dir);


/**
 * @brief Get the TX and RX pin directions from the SCI Pin I/O Control Register 1 (SCIPIO1).
 *
 * This function retrieves the current direction configuration of the LINTX and LINRX pins.
 * - TX_DIR (bit 2): 0 = LINTX is input, 1 = LINTX is output
 * - RX_DIR (bit 1): 0 = LINRX is input, 1 = LINRX is output
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_sci_pio1_directions(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO2


/**
 * @brief Get the current logic levels of the LINTX and LINRX pins from the SCI Pin I/O Control Register 2 (SCIPIO2).
 *
 * This function reads the current input values of the LINTX and LINRX pins.
 * - TX_IN (bit 2): 0 = LINTX is at logic low, 1 = LINTX is at logic high
 * - RX_IN (bit 1): 0 = LINRX is at logic low, 1 = LINRX is at logic high
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_sci_pio2_inputs(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO3

/**
 * @brief Set the output logic levels for the LINTX and LINRX pins in the SCI Pin I/O Control Register 3 (SCIPIO3).
 *
 * This function sets the output value for the LINTX and LINRX pins when they are configured as general-purpose outputs.
 * - TX_OUT (bit 2): 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * - RX_OUT (bit 1): 0 = LINRX output is logic low, 1 = LINRX output is logic high
 *
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_out 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * @param rx_out 0 = LINRX output is logic low, 1 = LINRX output is logic high
 */
void set_sci_pio3_outputs(volatile tms570_reg* sci_lin_reg, uint8_t tx_out, uint8_t rx_out);

/**
 * @brief Get the output logic levels for the LINTX and LINRX pins from the SCI Pin I/O Control Register 3 (SCIPIO3).
 *
 * This function retrieves the current output value for the LINTX and LINRX pins.
 * - TX_OUT (bit 2): 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * - RX_OUT (bit 1): 0 = LINRX output is logic low, 1 = LINRX output is logic high
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_sci_pio3_outputs(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO4

/**
 * @brief Set the output logic levels for the LINTX and LINRX pins in the SCI Pin I/O Control Register 4 (SCIPIO4).
 *
 * This function sets the output value for the LINTX and LINRX pins when they are configured as general-purpose outputs.
 * - TX SET (bit 2): 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * - RX SET (bit 1): 0 = LINRX output is logic low, 1 = LINRX output is logic high
 *
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_set 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * @param rx_set 0 = LINRX output is logic low, 1 = LINRX output is logic high
 */
void set_sci_pio4_outputs(volatile tms570_reg* sci_lin_reg, uint8_t tx_set, uint8_t rx_set);

/**
 * @brief Get the output logic levels for the LINTX and LINRX pins from the SCI Pin I/O Control Register 4 (SCIPIO4).
 *
 * This function retrieves the current output value for the LINTX and LINRX pins.
 * - TX SET (bit 2): 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * - RX SET (bit 1): 0 = LINRX output is logic low, 1 = LINRX output is logic high
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_sci_pio4_outputs(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO5

/**
 * @brief Set the output logic levels for the LINTX and LINRX pins in the SCI Pin I/O Control Register 5 (SCIPIO5).
 *
 * This function clears (sets to logic low) the output value for the LINTX and LINRX pins when they are configured as general-purpose outputs.
 * - TX CLR (bit 2): Write 1 to clear LINTX output to logic low (if TX FUNC = 0 and TX DIR = 1)
 * - RX CLR (bit 1): Write 1 to clear LINRX output to logic low (if RX FUNC = 0 and RX DIR = 1)
 *
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_clr 1 = Clear LINTX output to logic low, 0 = No effect
 * @param rx_clr 1 = Clear LINRX output to logic low, 0 = No effect
 */
void set_sci_pio5_outputs(volatile tms570_reg* sci_lin_reg, uint8_t tx_clr, uint8_t rx_clr);

/**
 * @brief Get the output logic levels for the LINTX and LINRX pins from the SCI Pin I/O Control Register 5 (SCIPIO5).
 *
 * This function retrieves the current output value for the LINTX and LINRX pins.
 * - TX CLR (bit 2): 0 = LINTX output is logic low, 1 = LINTX output is logic high
 * - RX CLR (bit 1): 0 = LINRX output is logic low, 1 = LINRX output is logic high
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_sci_pio5_outputs(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO6

/**
 * @brief Set the open-drain enable for the LINTX and LINRX pins in the SCI Pin I/O Control Register 6 (SCIPIO6).
 *
 * This function sets the open-drain capability for the LINTX (TX PDR, bit 2) and LINRX (RX PDR, bit 1) pins.
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_pdr 1 = Enable open-drain for LINTX, 0 = Disable open-drain
 * @param rx_pdr 1 = Enable open-drain for LINRX, 0 = Disable open-drain
 */
void set_sci_pio6_open_drain(volatile tms570_reg* sci_lin_reg, uint8_t tx_pdr, uint8_t rx_pdr);

/**
 * @brief Get the open-drain enable status for the LINTX and LINRX pins from the SCI Pin I/O Control Register 6 (SCIPIO6).
 *
 * This function retrieves the current open-drain enable status for the LINTX (TX PDR, bit 2) and LINRX (RX PDR, bit 1) pins.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint8_t Bitfield: bit 2 = TX PDR, bit 1 = RX PDR
 */
uint8_t get_sci_pio6_open_drain(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO7

/**
 * @brief Set the pull control disable for the LINTX and LINRX pins in the SCI Pin I/O Control Register 7 (SCIPIO7).
 *
 * This function sets the pull control disable for the LINTX (TX PD, bit 2) and LINRX (RX PD, bit 1) pins.
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_pd 1 = Disable pull control for LINTX, 0 = Enable pull control
 * @param rx_pd 1 = Disable pull control for LINRX, 0 = Enable pull control
 */
void set_sci_pio7_pull_disable(volatile tms570_reg* sci_lin_reg, uint8_t tx_pd, uint8_t rx_pd);

/**
 * @brief Get the pull control disable status for the LINTX and LINRX pins from the SCI Pin I/O Control Register 7 (SCIPIO7).
 *
 * This function retrieves the current pull control disable status for the LINTX (TX PD, bit 2) and LINRX (RX PD, bit 1) pins.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint8_t Bitfield: bit 2 = TX PD, bit 1 = RX PD
 */
uint8_t get_sci_pio7_pull_disable(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_PIO8

/**
 * @brief Set the pull select (pull-up or pull-down) for the LINTX and LINRX pins in the SCI Pin I/O Control Register 8 (SCIPIO8).
 *
 * This function sets the pull type for the LINTX (TX PSL, bit 2) and LINRX (RX PSL, bit 1) pins.
 * Only bits 2 and 1 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_psl 0 = Pull-down for LINTX, 1 = Pull-up for LINTX
 * @param rx_psl 0 = Pull-down for LINRX, 1 = Pull-up for LINRX
 */
void set_sci_pio8_pull_select(volatile tms570_reg* sci_lin_reg, uint8_t tx_psl, uint8_t rx_psl);

/**
 * @brief Get the pull select (pull-up or pull-down) status for the LINTX and LINRX pins from the SCI Pin I/O Control Register 8 (SCIPIO8).
 *
 * This function retrieves the current pull select status for the LINTX (TX PSL, bit 2) and LINRX (RX PSL, bit 1) pins.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint8_t Bitfield: bit 2 = TX PSL, bit 1 = RX PSL
 */
uint8_t get_sci_pio8_pull_select(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_COMPARE

/**
 * @brief Set the LIN Compare Register (LINCOMPARE).
 *
 * This function sets the SDEL (bits 18:16) and SBREAK (bits 2:0) fields of the LIN Compare Register.
 * - SDEL: Synchronization delimiter length (0-7, but only 0-3 are valid per datasheet; 2-bit field)
 *         TSDEL = (SDEL + 1) Tbit
 * - SBREAK: Synchronization break extension (0-7, 3-bit field)
 *         TSYNBRK = 13Tbit + (SBREAK × Tbit)
 *
 * Only bits 18:16 and 2:0 are writable; all other bits are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param sdel Value for SDEL field (0-3).
 * @param sbreak Value for SBREAK field (0-7).
 */
void set_lin_compare(volatile tms570_reg* sci_lin_reg, uint8_t sdel, uint8_t sbreak);

/**
 * @brief Get the SDEL and SBREAK fields from the LIN Compare Register (LINCOMPARE).
 *
 * This function reads the SDEL (bits 18:16) and SBREAK (bits 2:0) fields from the LIN Compare Register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 */
void get_lin_compare(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_RD0

/**
 * @brief Read the LIN Receive Buffer 0 Register (LINRD0).
 *
 * This function reads the 32-bit LIN Receive Buffer 0 Register (LINRD0), which contains up to four received data bytes.
 * - Bits 31-24: RD0 (Byte 0 of response data)
 * - Bits 23-16: RD1 (Byte 1 of response data)
 * - Bits 15-8 : RD2 (Byte 2 of response data)
 * - Bits 7-0  : RD3 (Byte 3 of response data)
 *
 * Each response data byte received in the SCIRXSHFT register is transferred to the corresponding RDy field.
 * Reading a byte clears the RXDY byte.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint32_t 32-bit value containing RD0 (bits 31-24), RD1 (23-16), RD2 (15-8), RD3 (7-0)
 */
uint32_t read_lin_receive_buffer0(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Read a specific byte from the LIN Receive Buffer 0 Register (LINRD0).
 *
 * This function reads a specific data byte (0-3) from the LINRD0 register.
 * Reading a byte clears the corresponding RXDY byte.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param byte_index Index of the byte to read (0 = RD0, 1 = RD1, 2 = RD2, 3 = RD3)
 * @return uint8_t Value of the requested data byte, or 0 if index is out of range.
 */
uint8_t read_lin_receive_buffer0_byte(volatile tms570_reg* sci_lin_reg, uint8_t byte_index);

//SCI_LIN_RD1

/**
 * @brief Read the LIN Receive Buffer 1 Register (LINRD1).
 *
 * This function reads the 32-bit LIN Receive Buffer 1 Register (LINRD1), which contains up to four received data bytes.
 * - Bits 31-24: RD4 (Byte 4 of response data)
 * - Bits 23-16: RD5 (Byte 5 of response data)
 * - Bits 15-8 : RD6 (Byte 6 of response data)
 * - Bits 7-0  : RD7 (Byte 7 of response data)
 *
 * Each response data byte received in the SCIRXSHFT register is transferred to the corresponding RDy field.
 * Reading a byte clears the RXDY byte.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint32_t 32-bit value containing RD4 (bits 31-24), RD5 (23-16), RD6 (15-8), RD7 (7-0)
 */
uint32_t read_lin_receive_buffer1(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Read a specific byte from the LIN Receive Buffer 1 Register (LINRD1).
 *
 * This function reads a specific data byte (4-7) from the LINRD1 register.
 * Reading a byte clears the corresponding RXDY byte.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param byte_index Index of the byte to read (4 = RD4, 5 = RD5, 6 = RD6, 7 = RD7)
 * @return uint8_t Value of the requested data byte, or 0 if index is out of range.
 */
uint8_t read_lin_receive_buffer1_byte(volatile tms570_reg* sci_lin_reg, uint8_t byte_index);

//SCI_LIN_MASK

/**
 * @brief Read the LIN Mask Register (LINMASK).
 *
 * This function reads the 32-bit LIN Mask Register (LINMASK), which contains the RX ID MASK (bits 23-16)
 * and TX ID MASK (bits 7-0). Reserved bits always read as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint32_t 32-bit value of the LINMASK register.
 */
uint32_t read_lin_mask(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Write to the LIN Mask Register (LINMASK).
 *
 * This function writes the RX ID MASK and TX ID MASK fields of the LINMASK register.
 * Only bits 23-16 (RX ID MASK) and 7-0 (TX ID MASK) are writable; reserved bits are ignored.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param rx_id_mask 8-bit RX ID mask (bits 23-16).
 * @param tx_id_mask 8-bit TX ID mask (bits 7-0).
 */
void write_lin_mask(volatile tms570_reg* sci_lin_reg, uint8_t rx_id_mask, uint8_t tx_id_mask);

/**
 * @brief Get the RX ID MASK field from the LIN Mask Register (LINMASK).
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint8_t RX ID MASK (bits 23-16).
 */
uint8_t get_lin_rx_id_mask(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the TX ID MASK field from the LIN Mask Register (LINMASK).
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return uint8_t TX ID MASK (bits 7-0).
 */
uint8_t get_lin_tx_id_mask(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the RX ID MASK field in the LIN Mask Register (LINMASK).
 *
 * Only bits 23-16 are affected; other bits are unchanged.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param rx_id_mask 8-bit RX ID mask.
 */
void set_lin_rx_id_mask(volatile tms570_reg* sci_lin_reg, uint8_t rx_id_mask);

/**
 * @brief Set the TX ID MASK field in the LIN Mask Register (LINMASK).
 *
 * Only bits 7-0 are affected; other bits are unchanged.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_id_mask 8-bit TX ID mask.
 */
void set_lin_tx_id_mask(volatile tms570_reg* sci_lin_reg, uint8_t tx_id_mask);

//SCI_LIN_ID

/**
 * @brief Write to the LIN Identification Register (LINID).
 *
 * This function writes the ID-SlaveTask Byte (bits 15-8) and ID Byte (bits 7-0) of the LINID register.
 * Only bits 15-0 are writable; bits 23-16 (Received ID) and 31-24 (Reserved) are read-only.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param id_slave_task 8-bit value for the ID-SlaveTask Byte (bits 15-8).
 * @param id 8-bit value for the ID Byte (bits 7-0).
 */
void write_lin_id(volatile tms570_reg* sci_lin_reg, uint8_t id_slave_task, uint8_t id);

/**
 * @brief Get the RECEIVED ID field from the LIN Identification Register (LINID).
 *
 * This function returns the 8-bit RECEIVED ID (bits 23-16) from the LINID register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 8-bit RECEIVED ID.
 */
uint8_t get_lin_received_id(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the ID-SlaveTask Byte from the LIN Identification Register (LINID).
 *
 * This function returns the 8-bit ID-SlaveTask Byte (bits 15-8) from the LINID register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 8-bit ID-SlaveTask Byte.
 */
uint8_t get_lin_id_slave_task(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Get the ID Byte from the LIN Identification Register (LINID).
 *
 * This function returns the 8-bit ID Byte (bits 7-0) from the LINID register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 8-bit ID Byte.
 */
uint8_t get_lin_id(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the ID-SlaveTask Byte in the LIN Identification Register (LINID).
 *
 * This function sets the 8-bit ID-SlaveTask Byte (bits 15-8) in the LINID register.
 * Only bits 15-8 are affected; other bits are unchanged.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param id_slave_task 8-bit value for the ID-SlaveTask Byte.
 */
void set_lin_id_slave_task(volatile tms570_reg* sci_lin_reg, uint8_t id_slave_task);

/**
 * @brief Set the ID Byte in the LIN Identification Register (LINID).
 *
 * This function sets the 8-bit ID Byte (bits 7-0) in the LINID register.
 * Only bits 7-0 are affected; other bits are unchanged.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param id 8-bit value for the ID Byte.
 */
void set_lin_id(volatile tms570_reg* sci_lin_reg, uint8_t id);

//SCI_LIN_TD0


/**
 * @brief Write to the LIN Transmit Buffer 0 Register (LINTD0).
 *
 * This function writes a 32-bit value to the LINTD0 register, which contains up to four transmit data bytes.
 * - Bits 31-24: TD0 (Byte 0 of transmit data)
 * - Bits 23-16: TD1 (Byte 1 of transmit data)
 * - Bits 15-8 : TD2 (Byte 2 of transmit data)
 * - Bits 7-0  : TD3 (Byte 3 of transmit data)
 *
 * Writing to TD0 (bits 31-24) initiates transmission.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param value 32-bit value containing TD0 (bits 31-24), TD1 (23-16), TD2 (15-8), TD3 (7-0)
 */
void write_lin_transmit_buffer0(volatile tms570_reg* sci_lin_reg, uint32_t value);

/**
 * @brief Write a specific byte to the LIN Transmit Buffer 0 Register (LINTD0).
 *
 * This function writes a specific data byte (0-3) to the LINTD0 register.
 * Writing to byte 0 (TD0) initiates transmission.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param byte_index Index of the byte to write (0 = TD0, 1 = TD1, 2 = TD2, 3 = TD3)
 * @param data 8-bit value to write to the specified byte.
 */
void write_lin_transmit_buffer0_byte(volatile tms570_reg* sci_lin_reg, uint8_t byte_index, uint8_t data);

//SCI_LIN_TD1

/**
 * @brief Write to the LIN Transmit Buffer 1 Register (LINTD1).
 *
 * This function writes a 32-bit value to the LINTD1 register, which contains up to four transmit data bytes.
 * - Bits 31-24: TD4 (Byte 4 of transmit data)
 * - Bits 23-16: TD5 (Byte 5 of transmit data)
 * - Bits 15-8 : TD6 (Byte 6 of transmit data)
 * - Bits 7-0  : TD7 (Byte 7 of transmit data)
 *
 * Writing to any of these fields loads the corresponding transmit buffer for the LIN frame.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param value 32-bit value containing TD4 (bits 31-24), TD5 (23-16), TD6 (15-8), TD7 (7-0)
 */
void write_lin_transmit_buffer1(volatile tms570_reg* sci_lin_reg, uint32_t value);

/**
 * @brief Write a specific byte to the LIN Transmit Buffer 1 Register (LINTD1).
 *
 * This function writes a specific data byte (4-7) to the LINTD1 register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param byte_index Index of the byte to write (4 = TD4, 5 = TD5, 6 = TD6, 7 = TD7)
 * @param data 8-bit value to write to the specified byte.
 */
void write_lin_transmit_buffer1_byte(volatile tms570_reg* sci_lin_reg, uint8_t byte_index, uint8_t data);

//SCI_LIN_MBRS

/**
 * @brief Set the Maximum Baud Rate (MBR) field in the Maximum Baud Rate Selection Register (MBRS).
 *
 * This function sets the 13-bit MBR field (bits 12:0) of the MBRS register.
 * Only bits 12:0 are writable; bits 31:13 are reserved and should be left as 0.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param mbr 13-bit value for the Maximum Baud Rate prescaler (0-0x1FFF).
 */
void set_lin_max_baud_rate(volatile tms570_reg* sci_lin_reg, uint16_t mbr);

/**
 * @brief Get the Maximum Baud Rate (MBR) field from the Maximum Baud Rate Selection Register (MBRS).
 *
 * This function returns the 13-bit MBR field (bits 12:0) from the MBRS register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 13-bit value of the Maximum Baud Rate prescaler (0-0x1FFF).
 */
uint16_t get_lin_max_baud_rate(volatile tms570_reg* sci_lin_reg);

//SCI_LIN_IODFTCTRL

/**
 * @brief Set the RXP ENA bit in the IODFTCTRL register to select analog loopback path.
 *
 * This function sets the RXP ENA bit (bit 0) in the IODFTCTRL register to select whether
 * the analog loopback is through the transmit pin (0) or the receive pin (1).
 * Write access is permitted in Privilege mode only.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param rxp_ena 0 = Analog loopback through transmit pin, 1 = Analog loopback through receive pin.
 */
void set_sci_iodftctrl_rxp_ena(volatile tms570_reg* sci_lin_reg, uint8_t rxp_ena);

/**
 * @brief Get the RXP ENA bit from the IODFTCTRL register.
 *
 * This function returns the current value of the RXP ENA bit (bit 0) in the IODFTCTRL register,
 * indicating whether analog loopback is through the transmit or receive pin.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 = Analog loopback through transmit pin, 1 = Analog loopback through receive pin.
 */
uint8_t get_sci_iodftctrl_rxp_ena(volatile tms570_reg* sci_lin_reg);


/**
 * @brief Set the LPB ENA (Loopback Enable) bit in the IODFTCTRL register.
 *
 * This function sets the LPB ENA bit (bit 1) in the IODFTCTRL register to select between
 * digital and analog loopback modes. Write access is permitted in Privilege mode only.
 *
 * - 0: Digital loopback is enabled (I/O buffers are excluded from the path).
 * - 1: Analog loopback is enabled in module I/O DFT mode when IODFTENA = 0b1010.
 *      The complete communication path through the I/Os can be tested.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param lpb_ena 0 = Digital loopback, 1 = Analog loopback (in IODFTENA = 1010 mode).
 */
void set_sci_iodftctrl_lpb_ena(volatile tms570_reg* sci_lin_reg, uint8_t lpb_ena);

/**
 * @brief Get the LPB ENA (Loopback Enable) bit from the IODFTCTRL register.
 *
 * This function returns the current value of the LPB ENA bit (bit 1) in the IODFTCTRL register,
 * indicating whether digital or analog loopback is enabled.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 = Digital loopback enabled, 1 = Analog loopback enabled (in IODFTENA = 1010 mode).
 */
uint8_t get_sci_iodftctrl_lpb_ena(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the IODFTENA field (bits 11:8) in the IODFTCTRL register.
 *
 * This function sets the IODFTENA field (bits 11:8) in the IODFTCTRL register to enable or disable
 * the I/O DFT (Design For Test) mode. The value 0xA (1010b) enables IODFT; all other values disable it.
 * Write access is permitted in Privilege mode only.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param iodftena 4-bit value to write to IODFTENA (bits 11:8). 0xA enables IODFT, others disable.
 */
void set_sci_iodftctrl_iodftena(volatile tms570_reg* sci_lin_reg, uint8_t iodftena);

/**
 * @brief Get the IODFTENA field (bits 11:8) from the IODFTCTRL register.
 *
 * This function returns the current value of the IODFTENA field (bits 11:8) in the IODFTCTRL register,
 * indicating whether IODFT is enabled (0xA) or disabled (any other value).
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 4-bit value of IODFTENA (bits 11:8). 0xA means IODFT is enabled, others mean disabled.
 */
uint8_t get_sci_iodftctrl_iodftena(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the TX SHIFT field (bits 18:16) in the SCI/LIN register.
 *
 * This function sets the TX SHIFT field, which defines the amount by which the value on the TX pin is delayed
 * so that the value on the RX pin is asynchronous. This feature is not applicable to the start bit.
 * - 0: No delay occurs.
 * - 1: The value is delayed by 1 SCLK.
 * - 2: The value is delayed by 2 SCLK.
 * - 3: The value is delayed by 3 SCLK.
 * - 4: The value is delayed by 4 SCLK.
 * - 5: The value is delayed by 5 SCLK.
 * - 6: The value is delayed by 6 SCLK.
 * - 7: The value is delayed by 7 SCLK.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param tx_shift Value to set for TX SHIFT (0-7).
 */
void set_sci_tx_shift(volatile tms570_reg* sci_lin_reg, uint8_t tx_shift);

/**
 * @brief Get the TX SHIFT field (bits 18:16) from the SCI/LIN register.
 *
 * This function returns the current value of the TX SHIFT field, which defines the delay applied to the TX pin.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return Value of TX SHIFT (0-7).
 */
uint8_t get_sci_tx_shift(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Set the PIN SAMPLE MASK field (bits 20:19) in the SCI/LIN register.
 *
 * This function sets the PIN SAMPLE MASK field, which defines the sample number at which the TX pin value
 * being transmitted will be inverted to verify the receive pin samples majority detection circuitry.
 * Note: In IODFT mode, testing for pin_sample mask must be done with prescalar P programmed greater than 2 (P > 2).
 * - 0: No mask is used.
 * - 1: Invert the TX Pin value at TBIT_CENTER.
 * - 2: Invert the TX Pin value at TBIT_CENTER + SCLK.
 * - 3: Invert the TX Pin value at TBIT_CENTER + 2 SCLK.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param pin_sample_mask Value to set for PIN SAMPLE MASK (0-3).
 */
void set_sci_pin_sample_mask(volatile tms570_reg* sci_lin_reg, uint8_t pin_sample_mask);

/**
 * @brief Get the PIN SAMPLE MASK field (bits 20:19) from the SCI/LIN register.
 *
 * This function returns the current value of the PIN SAMPLE MASK field, which defines the sample number
 * at which the TX pin value being transmitted will be inverted.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return Value of PIN SAMPLE MASK (0-3).
 */
uint8_t get_sci_pin_sample_mask(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Enable or disable Break Detect Error (BRKDT ENA) in the SCI/LIN module.
 *
 * This function sets or clears the Break Detect Error Enable bit (BRKDT ENA, bit 24) in the appropriate SCI/LIN control register.
 * When enabled (1), the stop bit of the frame is ANDed with 0 and passed to the RSM so that a frame error occurs,
 * and the RX pin is forced to continuous low for 10 Tbit so that a BRKDT error occurs.
 * When disabled (0), no error is created.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No error is created, 1 = Force BRKDT error as described.
 */
void set_sci_brkdt_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Break Detect Error Enable (BRKDT ENA) bit.
 *
 * This function returns the current value of the BRKDT ENA bit (bit 24) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if BRKDT error is not enabled, 1 if enabled.
 */
uint8_t get_sci_brkdt_enable(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Enable or disable Parity Error (PEN) in the SCI/LIN module.
 *
 * This function sets or clears the Parity Error Enable bit (PEN, bit 25) in the appropriate SCI/LIN control register.
 * When enabled (1), the parity bit received is toggled so that a parity error occurs (effective in SCI-compatible mode only).
 * When disabled (0), no parity error occurs.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No parity error occurs, 1 = Force parity error as described.
 */
void set_sci_parity_error_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Parity Error Enable (PEN) bit.
 *
 * This function returns the current value of the PEN bit (bit 25) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if parity error is not enabled, 1 if enabled.
 */
uint8_t get_sci_parity_error_enable(volatile tms570_reg* sci_lin_reg);


/**
 * @brief Enable or disable Frame Error (FEN) in the SCI/LIN module.
 *
 * This function sets or clears the Frame Error Enable bit (FEN, bit 26) in the appropriate SCI/LIN control register.
 * When enabled (1), the stop bit received is ANDed with 0 and passed to the stop bit check circuitry, causing a frame error.
 * When disabled (0), no frame error is created.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No error is created, 1 = Force frame error as described.
 */
void set_sci_frame_error_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Frame Error Enable (FEN) bit.
 *
 * This function returns the current value of the FEN bit (bit 26) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if frame error is not enabled, 1 if enabled.
 */
uint8_t get_sci_frame_error_enable(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Enable or disable Inconsistent Synch Field Error (ISFE) in the SCI/LIN module.
 *
 * This function sets or clears the Inconsistent Synch Field Error Enable bit (ISFE, bit 28) in the appropriate SCI/LIN control register.
 * When enabled (1), the bit widths in the synch field are varied so that the ISF check fails and the error flag is set (effective in LIN mode only).
 * When disabled (0), no ISF error is created.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No error is created, 1 = Force ISF error as described.
 */
void set_sci_isfe_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Inconsistent Synch Field Error Enable (ISFE) bit.
 *
 * This function returns the current value of the ISFE bit (bit 28) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if ISF error is not enabled, 1 if enabled.
 */
uint8_t get_sci_isfe_enable(volatile tms570_reg* sci_lin_reg);


/**
 * @brief Enable or disable Checksum Error (CEN) in the SCI/LIN module.
 *
 * This function sets or clears the Checksum Error Enable bit (CEN, bit 29) in the appropriate SCI/LIN control register.
 * When enabled (1), the polarity of the CTYPE (checksum type) in the receive checksum calculator is changed,
 * causing a checksum error (effective in LIN mode only).
 * When disabled (0), no checksum error is created.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No error is created, 1 = Force checksum error as described.
 */
void set_sci_checksum_error_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Checksum Error Enable (CEN) bit.
 *
 * This function returns the current value of the CEN bit (bit 29) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if checksum error is not enabled, 1 if enabled.
 */
uint8_t get_sci_checksum_error_enable(volatile tms570_reg* sci_lin_reg);


/**
 * @brief Enable or disable Physical Bus Error (PBEN) in the SCI/LIN module.
 *
 * This function sets or clears the Physical Bus Error Enable bit (PBEN, bit 30) in the appropriate SCI/LIN control register.
 * When enabled (1), the bit received during synch break field transmission is ORed with 1 and passed to the bit monitor circuitry,
 * creating a physical bus error (effective in LIN mode only).
 * When disabled (0), no error is created.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No error is created, 1 = Force physical bus error as described.
 */
void set_sci_physical_bus_error_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Physical Bus Error Enable (PBEN) bit.
 *
 * This function returns the current value of the PBEN bit (bit 30) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if physical bus error is not enabled, 1 if enabled.
 */
uint8_t get_sci_physical_bus_error_enable(volatile tms570_reg* sci_lin_reg);

/**
 * @brief Enable or disable Bit Error (BEN) in the SCI/LIN module.
 *
 * This function sets or clears the Bit Error Enable bit (BEN, bit 31) in the appropriate SCI/LIN control register.
 * When enabled (1), the bit received is ORed with 1 and passed to the bit monitor circuitry,
 * creating a bit error (effective in LIN mode only).
 * When disabled (0), no bit error is created.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @param enable 0 = No bit error is created, 1 = Force bit error as described.
 */
void set_sci_bit_error_enable(volatile tms570_reg* sci_lin_reg, uint8_t enable);

/**
 * @brief Get the current state of the Bit Error Enable (BEN) bit.
 *
 * This function returns the current value of the BEN bit (bit 31) from the appropriate SCI/LIN control register.
 *
 * @param sci_lin_reg Pointer to the SCI/LIN register base.
 * @return 0 if bit error is not enabled, 1 if enabled.
 */
uint8_t get_sci_bit_error_enable(volatile tms570_reg* sci_lin_reg);

#endif // SCI_LIN_UTILS_H