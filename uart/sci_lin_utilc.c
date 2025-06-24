#include "sci_lin_utils.h"
#include "sci_lin_regs.h"
#include "math.h"

static volatile struct g_sciTransfer
{
    uint32_t   mode;         /* Used to check for TX interrupt Enable */  
    uint32_t   tx_length;    /* Transmit data length in number of Bytes */
    uint32_t   rx_length;    /* Receive data length in number of Bytes */  
    uint8_t    * tx_data;    /* Transmit data pointer */      
    uint8_t    * rx_data;    /* Receive data pointer */  
} g_sciTransfer_t[4U];

bool gcr0_reset(volatile tms570_reg* sci_lin_reg, bool reset){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR0]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        reset,                                   // new value for the field
        TMS570_SCI_GCR0_RESET_BIT_OFFSET,            // field offset
        TMS570_SCI_GCR0_RESET_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR0], reg_val, TMS570_SCI_GCR0_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_comm_mode(volatile tms570_reg* sci_lin_reg, bool commMode){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        commMode,                                // new value for the field
        TMS570_SCI_GCR1_COMM_MODE_OFFSET,        // field offset
        TMS570_SCI_GCR1_COMM_MODE_BIT_LEN        // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_timing_mode(volatile tms570_reg* sci_lin_reg, bool timingMode){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        timingMode,                              // new value for the field
        TMS570_SCI_GCR1_TIMING_MODE_OFFSET,      // field offset
        TMS570_SCI_GCR1_TIMING_MODE_BIT_LEN      // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_parity_enable(volatile tms570_reg* sci_lin_reg, bool parityEnable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        parityEnable,                            // new value for the field
        TMS570_SCI_GCR1_PARITY_ENA_OFFSET,    // field offset
        TMS570_SCI_GCR1_PARITY_ENA_BIT_LEN    // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_parity_odd_even(volatile tms570_reg* sci_lin_reg, bool parityOddEven){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        parityOddEven,                           // new value for the field
        TMS570_SCI_GCR1_PARITY_OFFSET,           // field offset
        TMS570_SCI_GCR1_PARITY_BIT_LEN           // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_sci_number_of_stop_bits_per_frame(volatile tms570_reg* sci_lin_reg, bool stopBitsPerFrame){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        stopBitsPerFrame,                        // new value for the field
        TMS570_SCI_GCR1_STOP_OFFSET,             // field offset
        TMS570_SCI_GCR1_STOP_BIT_LEN             // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_clock_mode(volatile tms570_reg* sci_lin_reg, bool clockMode){    
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        clockMode,                               // new value for the field
        TMS570_SCI_GCR1_CLOCK_OFFSET,            // field offset
        TMS570_SCI_GCR1_CLOCK_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_lin_mode(volatile tms570_reg* sci_lin_reg, bool linMode){  
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        linMode,                                 // new value for the field
        TMS570_SCI_GCR1_LIN_MODE_OFFSET,         // field offset
        TMS570_SCI_GCR1_LIN_MODE_BIT_LEN         // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_SWnRST(volatile tms570_reg* sci_lin_reg, bool SWnRST){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        SWnRST,                                  // new value for the field
        TMS570_SCI_GCR1_SWnRST_OFFSET,           // field offset
        TMS570_SCI_GCR1_SWnRST_BIT_LEN           // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_sleep(volatile tms570_reg* sci_lin_reg, bool sleep){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        sleep,                                   // new value for the field
        TMS570_SCI_GCR1_SLEEP_OFFSET,            // field offset
        TMS570_SCI_GCR1_SLEEP_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_adapt(volatile tms570_reg* sci_lin_reg, bool adapt){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        adapt,                                   // new value for the field
        TMS570_SCI_GCR1_ADAPT_OFFSET,            // field offset
        TMS570_SCI_GCR1_ADAPT_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_mbuf(volatile tms570_reg* sci_lin_reg, bool multiBufferMode){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        multiBufferMode,                         // new value for the field
        TMS570_SCI_GCR1_MBUF_OFFSET,             // field offset
        TMS570_SCI_GCR1_MBUF_BIT_LEN             // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_ctype(volatile tms570_reg* sci_lin_reg, bool checksumType){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        checksumType,                            // new value for the field
        TMS570_SCI_GCR1_CTYPE_OFFSET,            // field offset
        TMS570_SCI_GCR1_CTYPE_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_hgen_ctrl(volatile tms570_reg* sci_lin_reg, bool hgenControl){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        hgenControl,                             // new value for the field
        TMS570_SCI_GCR1_HGEN_CTRL_OFFSET,        // field offset
        TMS570_SCI_GCR1_HGEN_CTRL_BIT_LEN        // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_stop_ext_frame(volatile tms570_reg* sci_lin_reg, bool stopExtFrame){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        stopExtFrame,                            // new value for the field
        TMS570_SCI_GCR1_STOP_EXT_FRAME_OFFSET,   // field offset
        TMS570_SCI_GCR1_STOP_EXT_FRAME_BIT_LEN   // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_loopback_mode(volatile tms570_reg* sci_lin_reg, bool loopbackMode){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        loopbackMode,                            // new value for the field
        TMS570_SCI_GCR1_LOOP_BACK_OFFSET,    // field offset
        TMS570_SCI_GCR1_LOOP_BACK_BIT_LEN    // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_continue_on_suspend(volatile tms570_reg* sci_lin_reg, bool continueOnSuspend){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        continueOnSuspend,                       // new value for the field
        TMS570_SCI_GCR1_CONT_OFFSET,             // field offset
        TMS570_SCI_GCR1_CONT_BIT_LEN             // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_rx_ena(volatile tms570_reg* sci_lin_reg, bool rxEnable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        rxEnable,                                // new value for the field
        TMS570_SCI_GCR1_RX_ENA_OFFSET,            // field offset
        TMS570_SCI_GCR1_RX_ENA_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

bool gcr1_tx_ena(volatile tms570_reg* sci_lin_reg, bool txEnable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        txEnable,                                // new value for the field
        TMS570_SCI_GCR1_TX_ENA_OFFSET,            // field offset
        TMS570_SCI_GCR1_TX_ENA_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }
    return (true);
}

//GCR2
bool gcr2_power_down(volatile tms570_reg* sci_lin_reg, bool powerDown){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR2]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        powerDown,                               // new value for the field
        TMS570_SCI_GCR2_POWERDOWN_OFFSET,       // field offset
        TMS570_SCI_GCR2_POWERDOWN_BIT_LEN       // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR2], reg_val, TMS570_SCI_GCR2_MASK)){
        return (false);
    }
    return (true);
}

bool gcr2_gen_wu(volatile tms570_reg* sci_lin_reg, bool generate){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR2]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        generate,                                // new value for the field
        TMS570_SCI_GCR2_GEN_WU_OFFSET,            // field offset
        TMS570_SCI_GCR2_GEN_WU_BIT_LEN            // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR2], reg_val, TMS570_SCI_GCR2_MASK)){
        return (false);
    }
    return (true);
}

bool gcr2_sc(volatile tms570_reg* sci_lin_reg, bool sendChecksumByte){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR2]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        sendChecksumByte,                        // new value for the field
        TMS570_SCI_GCR2_SC_OFFSET,                // field offset
        TMS570_SCI_GCR2_SC_BIT_LEN                // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR2], reg_val, TMS570_SCI_GCR2_MASK)){
        return (false);
    }
    return (true);
}

bool gcr2_cc(volatile tms570_reg* sci_lin_reg, bool compareChecksum){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR2]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        compareChecksum,                         // new value for the field
        TMS570_SCI_GCR2_CC_OFFSET,                // field offset
        TMS570_SCI_GCR2_CC_BIT_LEN                // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR2], reg_val, TMS570_SCI_GCR2_MASK)){
        return (false);
    }
    return (true);
}

//SCI_LIN_SET_INT
bool sci_set_int_brkdt(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_BRKDT_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_BRKDT_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_wakeup(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_WAKEUP_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_WAKEUP_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_timeout(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_TIMEOUT_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_TIMEOUT_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_toawus(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_TOAWUS_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_TOAWUS_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_toa3wus(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_TOA3WUS_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_TOA3WUS_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_tx(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_TX_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_TX_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_rx(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_RX_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_RX_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_id(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_ID_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_ID_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_tx_dma(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_TX_DMA_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_TX_DMA_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_rx_dma(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_RX_DMA_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_RX_DMA_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_rx_dma_all(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_RX_DMA_ALL_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_RX_DMA_ALL_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_parity(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_PE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_PE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_overrun(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_OE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_OE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_framing(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_FE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_FE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_no_response(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_NRE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_NRE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_inconsistent_synch_field(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_ISFE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_ISFE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_checksum(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_CE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_CE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_physical_bus_error(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_PBE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_PBE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_set_int_bit_error(volatile tms570_reg* sci_lin_reg, bool enable){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_SET_INT]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        enable,                                  // new value for the field
        TMS570_SCI_SET_INT_SET_BE_INT_OFFSET, // field offset
        TMS570_SCI_SET_INT_SET_BE_INT_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], reg_val, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool sci_reset(volatile tms570_reg* sci_lin_reg, bool reset){
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR0]; // Step 1: Read current value
    reg_val = tms570_update_field(
        reg_val,                                 // original register value
        reset,                                  // new value for the field
        TMS570_SCI_GCR0_RESET_BIT_OFFSET, // field offset
        TMS570_SCI_GCR0_RESET_BIT_LEN // field length
    ); // Step 2: Update only the field
    if(tms570_update_register(sci_lin_reg[TMS570_SCI_GCR0], reg_val, TMS570_SCI_GCR0_MASK)){
        return (false);
    }
    return (true);
}

bool disable_all_interrupts(volatile tms570_reg* sci_lin_reg){
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], 0xFFFFFFFFU, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT_LVL], 0xFFFFFFFFU, TMS570_SCI_SET_INT_LVL_MASK)){
        return (false);
    }

    return (true);
}

bool gcr1_global_control_1(volatile tms570_reg* sci_lin_reg, bool tx_ena, bool rx_ena, bool clock, bool stop, bool parity, bool parity_ena, bool timing_mode){

    // This function configures the SCI/LIN GCR1 register to enable TX, RX, internal clock,
    // 2 stop bits, even parity (disabled), and asynchronous timing mode,
    // matching the initialization in HL_sci.c.
    tms570_reg reg_val = sci_lin_reg[TMS570_SCI_GCR1];

    // Enable transmit (TX_ENA = 1)
    reg_val = tms570_update_field(reg_val, tx_ena, TMS570_SCI_GCR1_TX_ENA_OFFSET, TMS570_SCI_GCR1_TX_ENA_BIT_LEN);

    // Enable receive (RX_ENA = 1)
    reg_val = tms570_update_field(reg_val, rx_ena, TMS570_SCI_GCR1_RX_ENA_OFFSET, TMS570_SCI_GCR1_RX_ENA_BIT_LEN);

    // Internal clock (CLOCK = 1)
    reg_val = tms570_update_field(reg_val, clock, TMS570_SCI_GCR1_CLOCK_OFFSET, TMS570_SCI_GCR1_CLOCK_BIT_LEN);

    // Number of stop bits: 2 (STOP = 1 for 2 stop bits)
    reg_val = tms570_update_field(reg_val, stop, TMS570_SCI_GCR1_STOP_OFFSET, TMS570_SCI_GCR1_STOP_BIT_LEN);

    // Even parity (PARITY = 0)
    reg_val = tms570_update_field(reg_val, parity, TMS570_SCI_GCR1_PARITY_OFFSET, TMS570_SCI_GCR1_PARITY_BIT_LEN);

    // Parity disabled (PARITY_ENA = 0)
    reg_val = tms570_update_field(reg_val, parity_ena, TMS570_SCI_GCR1_PARITY_ENA_OFFSET, TMS570_SCI_GCR1_PARITY_ENA_BIT_LEN);

    // Asynchronous timing mode (TIMING_MODE = 1)
    reg_val = tms570_update_field(reg_val, timing_mode, TMS570_SCI_GCR1_TIMING_MODE_OFFSET, TMS570_SCI_GCR1_TIMING_MODE_BIT_LEN);

    // Write back the updated value to the register
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], reg_val, TMS570_SCI_GCR1_MASK)){
        return (false);
    }

    return (true);
}

bool set_baud_rate(volatile tms570_reg* sci_lin_reg, uint32_t prescaler, uint16_t m, uint32_t* baudrate){
    uint32_t baudrate_val = (prescaler * 1000000U) / (16U * (m + 1U));
    *baudrate = baudrate_val;
    volatile tms570_reg brs_reg = sci_lin_reg[TMS570_SCI_BRS];
    brs_reg = tms570_update_field(brs_reg, baudrate_val, TMS570_SCI_BRS_PRESCALER_P_OFFSET, TMS570_SCI_BRS_PRESCALER_P_BIT_LEN);
    brs_reg = tms570_update_field(brs_reg, m, TMS570_SCI_BRS_M_OFFSET, TMS570_SCI_BRS_M_BIT_LEN);
    brs_reg = tms570_update_field(brs_reg, 0U, TMS570_SCI_BRS_U_OFFSET, TMS570_SCI_BRS_U_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_BRS], brs_reg, TMS570_SCI_BRS_MASK)){
        return (false);
    }
    return (true);
}

bool set_format(volatile tms570_reg* sci_lin_reg, uint8_t length){
    volatile tms570_reg format_reg = sci_lin_reg[TMS570_SCI_FORMAT];
    format_reg = tms570_update_field(format_reg, length, TMS570_SCI_FORMAT_CHAR_OFFSET, TMS570_SCI_FORMAT_CHAR_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_FORMAT], format_reg, TMS570_SCI_FORMAT_MASK)){
        return (false);
    }
    return (true);
}

//set SCI1 pins functional mode
bool set_pio0(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func){
    volatile tms570_reg pio0_reg = sci_lin_reg[TMS570_SCI_PIO_0];
    pio0_reg = tms570_update_field(pio0_reg, tx_func, TMS570_SCI_PIO_0_TX_FUNC_OFFSET, TMS570_SCI_PIO_0_TX_FUNC_BIT_LEN);
    pio0_reg = tms570_update_field(pio0_reg, rx_func, TMS570_SCI_PIO_0_RX_FUNC_OFFSET, TMS570_SCI_PIO_0_RX_FUNC_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_0], pio0_reg, TMS570_SCI_PIO_0_MASK)){
        return (false);
    }
    return (true);
}

//set SCI1 pins default output value
bool set_pio3(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func){
    volatile tms570_reg pio3_reg = sci_lin_reg[TMS570_SCI_PIO_3];
    pio3_reg = tms570_update_field(pio3_reg, tx_func, TMS570_SCI_PIO_3_TX_OUT_OFFSET, TMS570_SCI_PIO_3_TX_OUT_BIT_LEN);
    pio3_reg = tms570_update_field(pio3_reg, rx_func, TMS570_SCI_PIO_3_RX_OUT_OFFSET, TMS570_SCI_PIO_3_RX_OUT_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_3], pio3_reg, TMS570_SCI_PIO_3_MASK)){
        return (false);
    }
    return (true);
}

//set SCI1 pins output direction
bool set_pio1(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func){
    volatile tms570_reg pio1_reg = sci_lin_reg[TMS570_SCI_PIO_1];
    pio1_reg = tms570_update_field(pio1_reg, tx_func, TMS570_SCI_PIO_1_TX_DIR_OFFSET, TMS570_SCI_PIO_1_TX_DIR_BIT_LEN);
    pio1_reg = tms570_update_field(pio1_reg, rx_func, TMS570_SCI_PIO_1_RX_DIR_OFFSET, TMS570_SCI_PIO_1_RX_DIR_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_1], pio1_reg, TMS570_SCI_PIO_1_MASK)){
        return (false);
    }
    return (true);
}

//set SCI1 pins open drain enable
bool set_pio6(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func){
    volatile tms570_reg pio6_reg = sci_lin_reg[TMS570_SCI_PIO_6];
    pio6_reg = tms570_update_field(pio6_reg, tx_func, TMS570_SCI_PIO_6_TX_PDR_OFFSET, TMS570_SCI_PIO_6_TX_PDR_BIT_LEN);
    pio6_reg = tms570_update_field(pio6_reg, rx_func, TMS570_SCI_PIO_6_RX_PDR_OFFSET, TMS570_SCI_PIO_6_RX_PDR_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_6], pio6_reg, TMS570_SCI_PIO_6_MASK)){
        return (false);
    }
    return (true);
}

//set SCI1 pins pullup/pulldown enable
bool set_pio7(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func){
    volatile tms570_reg pio7_reg = sci_lin_reg[TMS570_SCI_PIO_7];
    pio7_reg = tms570_update_field(pio7_reg, tx_func, TMS570_SCI_PIO_7_TX_PD_OFFSET, TMS570_SCI_PIO_7_TX_PD_BIT_LEN);
    pio7_reg = tms570_update_field(pio7_reg, rx_func, TMS570_SCI_PIO_7_RX_PD_OFFSET, TMS570_SCI_PIO_7_RX_PD_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_7], pio7_reg, TMS570_SCI_PIO_7_MASK)){
        return (false);
    }
    return (true);
}

//set SCI1 pins pullup/pulldown select
bool set_pio8(volatile tms570_reg* sci_lin_reg, uint8_t tx_func, uint8_t rx_func){
    volatile tms570_reg pio8_reg = sci_lin_reg[TMS570_SCI_PIO_8];
    pio8_reg = tms570_update_field(pio8_reg, tx_func, TMS570_SCI_PIO_8_TX_PSL_OFFSET, TMS570_SCI_PIO_8_TX_PSL_BIT_LEN);
    pio8_reg = tms570_update_field(pio8_reg, rx_func, TMS570_SCI_PIO_8_RX_PSL_OFFSET, TMS570_SCI_PIO_8_RX_PSL_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_8], pio8_reg, TMS570_SCI_PIO_8_MASK)){
        return (false);
    }
    return (true);
}

bool set_int_level(volatile tms570_reg* sci_lin_reg, uint8_t framing_error, uint8_t overrun_error, uint8_t parity_error, uint8_t receive, uint8_t transmit, uint8_t wakeup, uint8_t break_detect){
    volatile tms570_reg int_level_reg = sci_lin_reg[TMS570_SCI_SET_INT_LVL];
    int_level_reg = tms570_update_field(int_level_reg, framing_error, TMS570_SCI_SET_INT_LVL_SET_FE_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_FE_INT_LVL_BIT_LEN);
    int_level_reg = tms570_update_field(int_level_reg, overrun_error, TMS570_SCI_SET_INT_LVL_SET_OE_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_OE_INT_LVL_BIT_LEN);
    int_level_reg = tms570_update_field(int_level_reg, parity_error, TMS570_SCI_SET_INT_LVL_SET_PE_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_PE_INT_LVL_BIT_LEN);
    int_level_reg = tms570_update_field(int_level_reg, receive, TMS570_SCI_SET_INT_LVL_SET_RX_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_RX_INT_LVL_BIT_LEN);
    int_level_reg = tms570_update_field(int_level_reg, transmit, TMS570_SCI_SET_INT_LVL_SET_TX_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_TX_INT_LVL_BIT_LEN);
    int_level_reg = tms570_update_field(int_level_reg, wakeup, TMS570_SCI_SET_INT_LVL_SET_WAKEUP_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_WAKEUP_INT_LVL_BIT_LEN);
    int_level_reg = tms570_update_field(int_level_reg, break_detect, TMS570_SCI_SET_INT_LVL_SET_BRKDT_INT_LVL_OFFSET, TMS570_SCI_SET_INT_LVL_SET_BRKDT_INT_LVL_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT_LVL], int_level_reg, TMS570_SCI_SET_INT_LVL_MASK)){
        return (false);
    }
    return (true);
}

bool set_int_enable(volatile tms570_reg* sci_lin_reg, uint8_t framing_error, uint8_t overrun_error, uint8_t parity_error, uint8_t receive, uint8_t wakeup, uint8_t break_detect){
    volatile tms570_reg int_enable_reg = sci_lin_reg[TMS570_SCI_SET_INT];
    int_enable_reg = tms570_update_field(int_enable_reg, framing_error, TMS570_SCI_SET_INT_SET_FE_INT_OFFSET, TMS570_SCI_SET_INT_SET_FE_INT_BIT_LEN);
    int_enable_reg = tms570_update_field(int_enable_reg, overrun_error, TMS570_SCI_SET_INT_SET_OE_INT_OFFSET, TMS570_SCI_SET_INT_SET_OE_INT_BIT_LEN);
    int_enable_reg = tms570_update_field(int_enable_reg, parity_error, TMS570_SCI_SET_INT_SET_PE_INT_OFFSET, TMS570_SCI_SET_INT_SET_PE_INT_BIT_LEN);
    int_enable_reg = tms570_update_field(int_enable_reg, receive, TMS570_SCI_SET_INT_SET_RX_INT_OFFSET, TMS570_SCI_SET_INT_SET_RX_INT_BIT_LEN);
    int_enable_reg = tms570_update_field(int_enable_reg, wakeup, TMS570_SCI_SET_INT_SET_WAKEUP_INT_OFFSET, TMS570_SCI_SET_INT_SET_WAKEUP_INT_BIT_LEN);
    int_enable_reg = tms570_update_field(int_enable_reg, break_detect, TMS570_SCI_SET_INT_SET_BRKDT_INT_OFFSET, TMS570_SCI_SET_INT_SET_BRKDT_INT_BIT_LEN);
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], int_enable_reg, TMS570_SCI_SET_INT_MASK)){
        return (false);
    }
    return (true);
}

bool initialize_global_transfer_variables(uint8_t sci_num){
    g_sciTransfer_t[sci_num].mode = 0U << 8U;
    g_sciTransfer_t[sci_num].tx_length = 0U;
    g_sciTransfer_t[sci_num].rx_length = 0U;
    return (true);
}

bool start_sci(uint8_t sci_num){
    g_sciTransfer_t[sci_num].mode |= 0x80U;
    return (true);
}

bool stop_sci(uint8_t sci_num){
    g_sciTransfer_t[sci_num].mode &= ~0x80U;
    return (true);
}

bool sciSetFunctional(volatile tms570_reg* sci_lin_reg, uint32_t port){
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_PIO_0], port, TMS570_SCI_PIO_0_MASK)){
        return (false);
    }
    return (true);
}

bool sciSetBaudrate(volatile tms570_reg* sci_lin_reg, uint32_t baud){
    // This function sets the baud rate for the SCI/LIN module, matching the logic in HL_sci.c.
    // vclk is the VCLK2 frequency, typically 75 MHz for TMS570.
    // The prescaler 'f' is 16 if asynchronous mode, otherwise 1.
    // The BRS register is set to the calculated value.

    double vclk = 75.0 * 1000000.0; // 75 MHz
    uint32_t f = ((GET_BITS(sci_lin_reg[TMS570_SCI_GCR1], TMS570_SCI_GCR1_TIMING_MODE_OFFSET, TMS570_SCI_GCR1_TIMING_MODE_BIT_LEN) == 2U) ? 16U : 1U);
    uint32_t temp = f * baud;
    double temp2;

    temp = (f*(baud));
    temp2 = ((vclk)/((double)temp))-1U;
    temp2 = floor(temp2 + 0.5); // Round to nearest integer

    uint32_t brs_val = VAL2FIELD((uint32_t)temp2, TMS570_SCI_BRS_PRESCALER_P_OFFSET, TMS570_SCI_BRS_PRESCALER_P_BIT_LEN);

    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_BRS], brs_val, TMS570_SCI_BRS_MASK)) {
        return false;
    }
    return true;
}

bool sciIsTxReady(volatile tms570_reg* sci_lin_reg){
    return (GET_BITS(sci_lin_reg[TMS570_SCI_FLR], TMS570_SCI_FLR_TX_RDY_OFFSET, TMS570_SCI_FLR_TX_RDY_BIT_LEN) == 1U);
}

bool sciSendByte(volatile tms570_reg* sci_lin_reg, uint8_t byte){
    while (!sciIsTxReady(sci_lin_reg)){
    }
    if (!tms570_update_register(sci_lin_reg[TMS570_SCI_TD], byte, TMS570_SCI_TD_MASK)){
        return (false);
    }
    return (true);
}

bool sciSend(volatile tms570_reg* sci_lin_reg, uint32_t length, uint8_t* data)
{
    uint32_t index = (sci_lin_reg == TMS570_SCI_LIN_1_BASE_ADDR) ? 0U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_2_BASE_ADDR) ? 1U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_3_BASE_ADDR) ? 2U : 3U));
    uint8_t txdata;

    // Check if interrupt mode is enabled (SCI_TX_INT = 0x00000100U)
    if ((g_sciTransfer_t[index].mode & 0x00000100U) != 0U)
    {
        // Interrupt mode: set up transfer and send first byte
        g_sciTransfer_t[index].tx_length = length;
        g_sciTransfer_t[index].tx_data   = data;

        txdata = *g_sciTransfer_t[index].tx_data;
        if (!tms570_update_register(sci_lin_reg[TMS570_SCI_TD], txdata, TMS570_SCI_TD_MASK)){
            return false;
        }
        g_sciTransfer_t[index].tx_data++;
        // Enable TX interrupt
        tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], 0x00000100U, TMS570_SCI_SET_INT_SET_TX_INT_OFFSET);
    }
    else
    {
        // Polling mode: send all bytes, waiting for TX ready each time
        while (length > 0U)
        {
            while (!sciIsTxReady(sci_lin_reg))
            {
                // Wait for TX ready
            }
            txdata = *data;
            if (!tms570_update_register(sci_lin_reg[TMS570_SCI_TD], txdata, TMS570_SCI_TD_MASK)){
                return false;
            }
            data++;
            length--;
        }
    }
    return true;
}

bool sciIsRxReady(volatile tms570_reg* sci_lin_reg){
    return (GET_BITS(sci_lin_reg[TMS570_SCI_FLR], TMS570_SCI_FLR_RX_RDY_OFFSET, TMS570_SCI_FLR_RX_RDY_BIT_LEN) == 1U);
}

bool sciIsIdleDetected(volatile tms570_reg* sci_lin_reg){
    return (GET_BITS(sci_lin_reg[TMS570_SCI_FLR], TMS570_SCI_FLR_IDLE_OFFSET, TMS570_SCI_FLR_IDLE_BIT_LEN) == 1U);
}

bool sciRxError(volatile tms570_reg* sci_lin_reg, uint32_t* error_flags){
    uint32_t pe = GET_BITS(sci_lin_reg[TMS570_SCI_FLR], TMS570_SCI_FLR_PE_OFFSET, TMS570_SCI_FLR_PE_BIT_LEN);
    uint32_t oe = GET_BITS(sci_lin_reg[TMS570_SCI_FLR], TMS570_SCI_FLR_OE_OFFSET, TMS570_SCI_FLR_OE_BIT_LEN);
    uint32_t fe = GET_BITS(sci_lin_reg[TMS570_SCI_FLR], TMS570_SCI_FLR_FE_OFFSET, TMS570_SCI_FLR_FE_BIT_LEN);
    *error_flags = (pe << TMS570_SCI_FLR_PE_OFFSET) | (oe << TMS570_SCI_FLR_OE_OFFSET) | (fe << TMS570_SCI_FLR_FE_OFFSET);
    return (true);
}

bool sciReceiveByte(volatile tms570_reg* sci_lin_reg){
    while (sciIsRxReady(sci_lin_reg)==0){
    }
    return GET_BITS(sci_lin_reg[TMS570_SCI_RD], TMS570_SCI_RD_RD_OFFSET, TMS570_SCI_RD_RD_BIT_LEN);
}

bool sciReceive(volatile tms570_reg* sci_lin_reg, uint32_t length, uint8_t* data){
    if(sciIsRxReady(sci_lin_reg)==GET_BITS(sci_lin_reg[TMS570_SCI_SET_INT], TMS570_SCI_SET_INT_SET_RX_INT_OFFSET, TMS570_SCI_SET_INT_SET_RX_INT_BIT_LEN)){
        uint32_t index = (sci_lin_reg == TMS570_SCI_LIN_1_BASE_ADDR) ? 0U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_2_BASE_ADDR) ? 1U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_3_BASE_ADDR) ? 2U : 3U));

        volatile tms570_reg flr_reg = sci_lin_reg[TMS570_SCI_FLR];
        flr_reg = tms570_update_field(flr_reg, 0x04000000U, TMS570_SCI_FLR_FE_OFFSET, TMS570_SCI_FLR_FE_BIT_LEN);
        flr_reg = tms570_update_field(flr_reg, 0x02000000U, TMS570_SCI_FLR_OE_OFFSET, TMS570_SCI_FLR_OE_BIT_LEN);
        flr_reg = tms570_update_field(flr_reg, 0x01000000U, TMS570_SCI_FLR_PE_OFFSET, TMS570_SCI_FLR_PE_BIT_LEN);
        tms570_update_register(sci_lin_reg[TMS570_SCI_FLR], flr_reg, TMS570_SCI_FLR_MASK);

        g_sciTransfer_t[index].rx_length = length;
        g_sciTransfer_t[index].rx_data   = data;
    }
    else{
        while (length > 0U)
        {
            while (sciIsRxReady(sci_lin_reg)==0){
            }
            *data = GET_BITS(sci_lin_reg[TMS570_SCI_RD], TMS570_SCI_RD_RD_OFFSET, TMS570_SCI_RD_RD_BIT_LEN);
            data++;
            length--;
        }
    }
    return (true);
}

bool sciEnableLoopback(volatile tms570_reg* sci_lin_reg, bool loopbackMode) {
    // Clear Loopback in case enabled already
    tms570_update_register(sci_lin_reg[TMS570_IODFTCTRL], 0U, TMS570_IODFTCTRL_MASK);

    // Enable Loopback either in Analog or Digital Mode
    tms570_update_register(sci_lin_reg[TMS570_IODFTCTRL], 0x00000A00U | ((loopbackMode ? 1U : 0U) << 1U), TMS570_IODFTCTRL_MASK);

    return true;
}

bool sciDisableLoopback(volatile tms570_reg* sci_lin_reg){
    // Disable Loopback Mode by writing 0x00000500U to IODFTCTRL, matching HAL behavior
    tms570_update_register(&sci_lin_reg[TMS570_IODFTCTRL], 0x00000500U, TMS570_IODFTCTRL_MASK);
    return true;
}

bool sciEnableNotification(volatile tms570_reg* sci_lin_reg, uint32_t flags){
    uint32_t index = (sci_lin_reg == TMS570_SCI_LIN_1_BASE_ADDR) ? 0U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_2_BASE_ADDR) ? 1U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_3_BASE_ADDR) ? 2U : 3U));
    g_sciTransfer_t[index].mode |= (flags & 0x00000100U);
    tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], (flags & (~(0x00000100U))), TMS570_SCI_SET_INT_MASK);
    return true;
}

bool sciDisableNotification(volatile tms570_reg* sci_lin_reg, uint32_t flags){
    uint32_t index = (sci_lin_reg == TMS570_SCI_LIN_1_BASE_ADDR) ? 0U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_2_BASE_ADDR) ? 1U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_3_BASE_ADDR) ? 2U : 3U));
    g_sciTransfer_t[index].mode |= (flags & MAKE_MASK(TMS570_SCI_SET_INT_SET_TX_INT_OFFSET, TMS570_SCI_SET_INT_SET_TX_INT_BIT_LEN));
    tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], (flags & (~MAKE_MASK(TMS570_SCI_SET_INT_SET_TX_INT_OFFSET, TMS570_SCI_SET_INT_SET_TX_INT_BIT_LEN))), TMS570_SCI_SET_INT_MASK);
    return true;
}

bool sciDisableNotification(volatile tms570_reg* sci_lin_reg, uint32_t flags){
    uint32_t index = (sci_lin_reg == TMS570_SCI_LIN_1_BASE_ADDR) ? 0U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_2_BASE_ADDR) ? 1U : 
                         ((sci_lin_reg == TMS570_SCI_LIN_3_BASE_ADDR) ? 2U : 3U));
    g_sciTransfer_t[index].mode &= ~(flags & MAKE_MASK(TMS570_SCI_SET_INT_SET_TX_INT_OFFSET, TMS570_SCI_SET_INT_SET_TX_INT_BIT_LEN));
    tms570_update_register(sci_lin_reg[TMS570_SCI_SET_INT], (flags & (~MAKE_MASK(TMS570_SCI_SET_INT_SET_TX_INT_OFFSET, TMS570_SCI_SET_INT_SET_TX_INT_BIT_LEN))), TMS570_SCI_SET_INT_MASK);
    return true;
}

bool sciEnterResetState(volatile tms570_reg* sci_lin_reg){
    tms570_reg gcr1_reg = sci_lin_reg[TMS570_SCI_GCR1];
    gcr1_reg = tms570_update_field(gcr1_reg, 0, TMS570_SCI_GCR1_SWnRST_OFFSET, TMS570_SCI_GCR1_SWnRST_BIT_LEN);
    tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], gcr1_reg, TMS570_SCI_GCR1_MASK);
    return true;
}

bool sciExitResetState(volatile tms570_reg* sci_lin_reg){
    tms570_reg gcr1_reg = sci_lin_reg[TMS570_SCI_GCR1];
    gcr1_reg = tms570_update_field(gcr1_reg, 1, TMS570_SCI_GCR1_SWnRST_OFFSET, TMS570_SCI_GCR1_SWnRST_BIT_LEN);
    tms570_update_register(sci_lin_reg[TMS570_SCI_GCR1], gcr1_reg, TMS570_SCI_GCR1_MASK);
    return true;
}
