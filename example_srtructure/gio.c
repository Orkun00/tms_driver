/**
 * @file gio.c
 * @author Onur Alp Kayacan (okayacan@netas.com.tr)
 * @author Furkan Kırlangıç (fkirlangic@netas.com.tr)
 * @brief General-Purpose Input/Output (GIO) driver source file.
 * 
 * Provides functions to configure and control the GIO ports and pins.
 * 
 * @copyright Copyright (c) 2025
 */

#include "gio.h"

#include "gio_regs.h"

/** @brief Converts given port and pin enumerations to bit position in all-covering registers. */
#define GIO_PORT_PIN_TO_BIT_OFFSET(port, pin) (((port) << 3) + (pin))

bool gio_set_mode(tGIO_mode mode) {
	if (!IS_ENUM_IN_RANGE(mode, NUM_OF_GIO_MODE)) {
		return (false);
	}

	tms570_reg* giogcr0_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOCR0_OFFSET;
	tms570_reg	giogcr0_val = tms570_update_field(*giogcr0_reg, (tms570_reg)mode, TMS570_GIO_GIOCR0_RESET_BIT_OFFSET, TMS570_GIO_GIOCR0_RESET_BIT_LEN);

	return (tms570_update_register(giogcr0_reg, giogcr0_val, TMS570_GIO_GIOCR0_MASK));
}

bool gio_configure_input(tGIO_port port, tGIO_pin pin, tGIO_pull pull) {
	if (!IS_ENUM_IN_RANGE(port, NUM_OF_GIO_PORT) || !IS_ENUM_IN_RANGE(pin, NUM_OF_GIO_PIN) || !IS_ENUM_IN_RANGE(pull, NUM_OF_GIO_PULL)) {
		return (false);
	}

	/* Set direction as input. */
	tms570_reg* giodir_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIODIR_OFFSET + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
	tms570_reg	giodir_val = tms570_update_field(*giodir_reg, false, pin, TMS570_GIO_GIODIR_GIODIRn_BIT_LEN);

	if (tms570_update_register(giodir_reg, giodir_val, TMS570_GIO_GIODIR_MASK)) {
		return (false);
	}

	/* Set pull configuration. */
	tms570_reg* giopuldis_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOPULDIS_OFFSET + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
	tms570_reg	giopuldis_val = tms570_update_field(*giopuldis_reg, (pull == GIO_PULL_NO_PULL) ? true : false, pin, TMS570_GIO_GIOPULDIS_GIOPULDISn_BIT_LEN);

	if (tms570_update_register(giopuldis_reg, giopuldis_val, TMS570_GIO_GIOPULDIS_MASK)) {
		return (false);
	}

	/* Set pull select configuration. */
	if (pull != GIO_PULL_NO_PULL) {
		tms570_reg* giopsl_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOPSL_OFFSET + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
		tms570_reg* giopsl_val = tms570_update_field(*giopsl_reg, (pull == GIO_PULL_UP) ? true : false, pin, TMS570_GIO_GIOPSL_GIOPSLn_BIT_LEN);
		if (tms570_update_register(giopsl_reg, giopsl_val, TMS570_GIO_GIOPSL_MASK)) {
			return (false);
		}
	}

	return (true);
}

bool gio_configure_output(tGIO_port port, tGIO_pin pin, tGIO_open_drain od) {
	if (!IS_ENUM_IN_RANGE(port, NUM_OF_GIO_PORT) || !IS_ENUM_IN_RANGE(pin, NUM_OF_GIO_PIN) || !IS_ENUM_IN_RANGE(od, NUM_OF_GIO_OPEN_DRAIN)) {
		return (false);
	}

	/* Set direction as output. */
	tms570_reg* giodir_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIODIR_OFFSET + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
	tms570_reg	giodir_val = tms570_update_field(*giodir_reg, true, pin, TMS570_GIO_GIODIR_GIODIRn_BIT_LEN);

	if (tms570_update_register(giodir_reg, giodir_val, TMS570_GIO_GIODIR_MASK)) {
		return (false);
	}

	/* Set open-drain configuration. */
	tms570_reg* giopdr_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOPDR_OFFSET + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
	tms570_reg	giopdr_val = tms570_update_field(*giopdr_reg, (tms570_reg)od, pin, TMS570_GIO_GIOPDR_GIOPDRn_BIT_LEN);

	return (tms570_update_register(giopdr_reg, giopdr_val, TMS570_GIO_GIOPDR_MASK));
}

bool gio_set_pin(tGIO_port port, tGIO_pin pin, bool en) {
	if (!IS_ENUM_IN_RANGE(port, NUM_OF_GIO_PORT) || !IS_ENUM_IN_RANGE(pin, NUM_OF_GIO_PIN)) {
		return (false);
	}

	tms570_reg* giodx_reg = TMS570_GIO_BASE_ADDR + ((en) ? TMS570_GIO_GIODSET_OFFSET : TMS570_GIO_GIODCLR_OFFSET) + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
	tms570_reg	giodx_val = tms570_update_field(*giodx_reg, true, pin, TMS570_GIO_GIODOUT_GIODOUTn_BIT_LEN);

	return (tms570_update_register(giodx_reg, giodx_val, TMS570_GIO_GIODOUT_MASK));
}

bool gio_get_pin(tGIO_port port, tGIO_pin pin, bool* en) {
	if (!IS_ENUM_IN_RANGE(port, NUM_OF_GIO_PORT) || !IS_ENUM_IN_RANGE(pin, NUM_OF_GIO_PIN) || (en == NULL)) {
		return (false);
	}

	tms570_reg* giodin_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIODIN_OFFSET + ((port == GIO_PORT_A) ? TMS570_GIO_PORT_A_OFFSET : TMS570_GIO_PORT_B_OFFSET);
	*en = GET_BITS(*giodin_reg, pin, TMS570_GIO_GIODIN_GIODINn_BIT_LEN);

	return (true);
}

bool gio_configure_interrupt(tGIO_port port, tGIO_pin pin, tGIO_int_pol pol, tGIO_int_level level) {
	if (!IS_ENUM_IN_RANGE(port, NUM_OF_GIO_PORT) || !IS_ENUM_IN_RANGE(pin, NUM_OF_GIO_PIN), !IS_ENUM_IN_RANGE(pol, NUM_OF_GIO_INT_POL) || !IS_ENUM_IN_RANGE(level, NUM_OF_GIO_INT_LEVEL)) {
		return (false);
	}

	/* Set trigger edge polarity configuration. */
	if (pol != GIO_INT_POL_BOTH_EDGE) {
		tms570_reg* giopol_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOPOL_OFFSET;
		tms570_reg	giopol_val = tms570_update_field(*giopol_reg, pol, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOPOL_GIOPOLn_BIT_LEN);

		if (tms570_update_register(giopol_reg, giopol_val, TMS570_GIO_GIOPOL_MASK)) {
			return (false);
		}
	}

	/* Set if interrupt detection is on single edge of both edge. */
	tms570_reg* giointdet_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOINTDET_OFFSET;
	tms570_reg	giointdet_val = tms570_update_field(*giointdet_reg, (pol == GIO_INT_POL_BOTH_EDGE) ? true : false, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOINTDET_GIOINTDETn_BIT_LEN);

	if (tms570_update_register(giointdet_reg, giointdet_val, TMS570_GIO_GIOINTDET_MASK)) {
		return (false);
	}

	/* Set interrupt level. */
	tms570_reg* giolvlx_reg = TMS570_GIO_BASE_ADDR + ((level == GIO_INT_LEVEL_HIGH) ? TMS570_GIO_GIOLVLSET_OFFSET : TMS570_GIO_GIOLVLCLR_OFFSET);
	tms570_reg	giolvlx_val = tms570_update_field(*giolvlx_reg, true, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOLVLx_GIOLVLxn_BIT_LEN);

	/* Read-back value should equal to the given parameter itself. */
	*giolvlx_reg = giolvlx_val & TMS570_GIO_GIOLVLx_MASK;
	return (level == GET_BITS(*giolvlx_reg, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOLVLx_GIOLVLxn_BIT_LEN));
}

bool gio_enable_interrupt(tGIO_port port, tGIO_pin pin, bool en) {
	if (!IS_ENUM_IN_RANGE(port, NUM_OF_GIO_PORT) || !IS_ENUM_IN_RANGE(pin, NUM_OF_GIO_PIN)) {
		return (false);
	}

	/* An interrupt flag gets set when the selected transition happens on the corresponding GIO pin regardless of whether
	the interrupt generation is enabled or not. It is recommended to clear a flag before enabling the interrupt generation.*/
	tms570_reg* gioflag_reg = TMS570_GIO_BASE_ADDR + TMS570_GIO_GIOFLG_MASK;
	tms570_reg	gioflag_val = tms570_update_field(*gioflag_reg, true, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOFLG_GIOFLAGn_BIT_LEN);

	if (tms570_update_register(gioflag_reg, gioflag_val, TMS570_GIO_GIOFLG_MASK)) {
		return (false);
	}

	tms570_reg* gioenax_reg = TMS570_GIO_BASE_ADDR + ((en) ? TMS570_GIO_GIOENASET_OFFSET : TMS570_GIO_GIOENACLR_OFFSET);
	tms570_reg	gioenax_val = tms570_update_field(*gioenax_reg, true, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOENAx_GIOENAxn_BIT_LEN);

	/* Read-back value should equal to the given parameter itself. */
	*gioenax_reg = gioenax_val & TMS570_GIO_GIOENAx_MASK;
	return (en == GET_BITS(*gioenax_reg, GIO_PORT_PIN_TO_BIT_OFFSET(port, pin), TMS570_GIO_GIOENAx_GIOENAxn_BIT_LEN));
}

bool gio_get_pending_irq(tGIO_int_level level, tGIO_port* port, tGIO_pin* pin) {
	if (!IS_ENUM_IN_RANGE(level, NUM_OF_GIO_INT_LEVEL) || (port == NULL) || (pin == NULL)) {
		return (false);
	}

	/* Select the offset register based in IRQ level. */
	tms570_reg* giooffn_reg = TMS570_GIO_BASE_ADDR + ((level == GIO_INT_LEVEL_HIGH) ? TMS570_GIO_GIOOFF1_OFFSET : TMS570_GIO_GIOOFF2_OFFSET);
	tms570_reg	pending_irq = GET_BITS(*giooffn_reg, TMS570_GIO_GIOOFFn_GIOOFFn_BIT_OFFSET, TMS570_GIO_GIOOFFn_GIOOFFn_BIT_LEN);

	/* pending_irq equals zero means no interrupt has occurred.*/
	if (pending_irq == 0) {
		return (false);
	}

	pending_irq--;						  /* Decrement the offset. */
	*port = pending_irq / NUM_OF_GIO_PIN; /* Calculate corresponding port*/
	*pin = pending_irq & NUM_OF_GIO_PIN;  /* Calculate corresponding pin */

	return (true);
}
