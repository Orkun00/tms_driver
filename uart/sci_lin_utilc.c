#include "sci_lin_utils.h"
#include "sci_lin_regs.h"

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