/**
 * @file tms570_common.h
 * @brief Common utility macros and inline functions for TMS570 microcontroller register manipulation.
 *
 * This header provides:
 * - Bit mask creation and manipulation macros
 * - Range checking macros
 * - Inline functions for safely updating registers and register fields
 * - A typedef for a volatile 32-bit register type
 *
 * @note These utilities are designed for use with 32-bit registers typical in TMS570 MCU peripherals.
 */

#ifndef INC_TMS570_COMMON_H_
#define INC_TMS570_COMMON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Creates a mask with the least significant n bits set to 1.
 * 
 * Example: MASK_N(3) = 0b111 = 7
 * 
 * @param n Number of bits to set
 * @return Bitmask with n lower bits set
 */
#define MASK_N(n)						((1 << n) - 1)

/**
 * @brief Checks if all bits specified by mask are set in reg.
 * 
 * @param reg Register value to check
 * @param mask Bitmask to compare against
 * @return true if all bits in mask are set in reg, false otherwise
 */
#define MASK_EQ(reg, mask)				(((reg & mask) == mask))

/**
 * @brief Creates a mask of length len starting at bit offset.
 * 
 * @param offset Bit offset where mask starts
 * @param len Length of the mask in bits
 * @return Bitmask shifted to start at offset
 */
#define MAKE_MASK(offset, len)			(MASK_N(len) << (offset))

/**
 * @brief Extracts a bit field from reg starting at offset with length len.
 * 
 * @param reg Register value
 * @param offset Bit offset to start extraction
 * @param len Length of the bit field
 * @return Extracted bits as a right-aligned value
 */
#define GET_BITS(reg, offset, len)		((reg >> offset) & MASK_N(len))

/**
 * @brief Converts a value to a bit field at offset with length len.
 * 
 * @param val Value to convert
 * @param offset Bit offset for the field
 * @param len Length of the bit field
 * @return Value shifted and masked for insertion into a register field
 */
#define VAL2FIELD(val, offset, len)		(((val & MASK_N(len)) << offset))

/**
 * @brief Checks if the bits set in reg are a subset of bits set in mask.
 * 
 * @param reg Register value
 * @param mask Bitmask to compare against
 * @return true if reg bits are all masked by mask, false otherwise
 */
#define IS_MASKED(reg, mask)			(((reg & mask) == reg))

/**
 * @brief Checks if a value is strictly between MIN and MAX.
 * 
 * @param VAL Value to check
 * @param MIN Minimum bound (exclusive)
 * @param MAX Maximum bound (exclusive)
 * @return true if VAL > MIN and VAL < MAX, false otherwise
 */
#define IS_IN_RANGE(VAL, MIN, MAX)		((VAL > MIN) && (VAL < MAX))

/**
 * @brief Checks if a value is between MIN and MAX inclusively.
 * 
 * @param VAL Value to check
 * @param MIN Minimum bound (inclusive)
 * @param MAX Maximum bound (inclusive)
 * @return true if VAL >= MIN and VAL <= MAX, false otherwise
 */
#define IS_IN_RANGE_EQ(VAL, MIN, MAX)	((VAL >= MIN) && (VAL <= MAX))

/**
 * @brief Checks if an enum value is within valid range assuming 0-based enums.
 * 
 * @param val Enum value
 * @param enum_max Maximum valid enum value (exclusive)
 * @return true if val is valid enum index, false otherwise
 */
#define IS_ENUM_IN_RANGE(val, enum_max) ((val >= 0) && (val < enum_max))

/**
 * @typedef tms570_reg
 * @brief Represents a volatile 32-bit TMS570 register.
 */
typedef volatile uint32_t tms570_reg;

/**
 * @brief Updates bits of a register specified by a mask.
 *
 * Writes the masked bits of value to *reg, leaving other bits unchanged.
 * Returns true if the write was successful and the register bits match the value.
 * 
 * @param reg Pointer to the register to update
 * @param value Value to write (only masked bits are written)
 * @param mask Bitmask specifying which bits to update
 * @return true if register bits match the written value after update, false otherwise
 */
static inline bool tms570_update_register(tms570_reg* reg, tms570_reg value, tms570_reg mask) {
	value &= mask;
	*reg = value;
	return ((*reg & mask) == value);
}

/**
 * @brief Updates a bit field inside a register value.
 * 
 * Clears the bit field specified by bit_offset and bit_len in reg and
 * inserts the provided value into that field.
 * 
 * @param reg Original register value
 * @param value New value to insert into the bit field
 * @param bit_offset Bit offset of the field within the register
 * @param bit_len Length in bits of the field
 * @return New register value with the updated bit field
 */
static inline tms570_reg tms570_update_field(tms570_reg reg, tms570_reg value, uintptr_t bit_offset, size_t bit_len) {
	reg &= ~MAKE_MASK(bit_offset, bit_len);
	reg |= VAL2FIELD(value, bit_offset, bit_len);
	return (reg);
}

#endif
