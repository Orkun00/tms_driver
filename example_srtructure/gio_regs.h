#ifndef INC_TMS570_GIO_REGS_H_
#define INC_TMS570_GIO_REGS_H_

#include "tms570_common.h"

#define TMS570_GIO_BASE_ADDR					((tms570_reg*)0xFFF7BC00)

/* GPIO Register Offset */
#define TMS570_GIO_GIOCR0_OFFSET				(0x00 / sizeof(tms570_reg)) /* GPIO Global Control Register Offset */
#define TMS570_GIO_GIOINTDET_OFFSET				(0x08 / sizeof(tms570_reg)) /* GPIO Interrupt Detect Register */
#define TMS570_GIO_GIOPOL_OFFSET				(0x0C / sizeof(tms570_reg)) /* GPIO Interrupt Polarity Register */
#define TMS570_GIO_GIOENASET_OFFSET				(0x10 / sizeof(tms570_reg)) /* GPIO Interrupt Enable Set Register */
#define TMS570_GIO_GIOENACLR_OFFSET				(0x14 / sizeof(tms570_reg)) /* GPIO Interrupt Enable Clear Register */
#define TMS570_GIO_GIOLVLSET_OFFSET				(0x18 / sizeof(tms570_reg)) /* GPIO Interrupt Priority Set Register */
#define TMS570_GIO_GIOLVLCLR_OFFSET				(0x1C / sizeof(tms570_reg)) /* GPIO Interrupt Priority Clear Register */
#define TMS570_GIO_GIOFLG_OFFSET				(0x20 / sizeof(tms570_reg)) /* GPIO Interrupt Flag Register */
#define TMS570_GIO_GIOOFF1_OFFSET				(0x24 / sizeof(tms570_reg)) /* GPIO Offset 1 Register */
#define TMS570_GIO_GIOOFF2_OFFSET				(0x28 / sizeof(tms570_reg)) /* GPIO Offset 2 Register */
#define TMS570_GIO_GIOEMU1_OFFSET				(0x2C / sizeof(tms570_reg)) /* GPIO Emulation 1 Register */
#define TMS570_GIO_GIOEMU2_OFFSET				(0x30 / sizeof(tms570_reg)) /* GPIO Emulation 2 Register */
#define TMS570_GIO_GIODIR_OFFSET				(0x34 / sizeof(tms570_reg)) /* GPIO Data Direction Register */
#define TMS570_GIO_GIODIN_OFFSET				(0x38 / sizeof(tms570_reg)) /* GPIO Data Input Register */
#define TMS570_GIO_GIODOUT_OFFSET				(0x3C / sizeof(tms570_reg)) /* GPIO Data Output Register */
#define TMS570_GIO_GIODSET_OFFSET				(0x40 / sizeof(tms570_reg)) /* GPIO Data Set Register */
#define TMS570_GIO_GIODCLR_OFFSET				(0x44 / sizeof(tms570_reg)) /* GPIO Data Clear Register */
#define TMS570_GIO_GIOPDR_OFFSET				(0x48 / sizeof(tms570_reg)) /* GPIO Open Drain Register */
#define TMS570_GIO_GIOPULDIS_OFFSET				(0x48 / sizeof(tms570_reg)) /* GPIO Pull Disable Register */
#define TMS570_GIO_GIOPSL_OFFSET				(0x4C / sizeof(tms570_reg)) /* GPIO Pull Select Register */

/* Register offsets between PORT A and PORT B*/
#define TMS570_GIO_PORT_A_OFFSET				(0x00 / sizeof(tms570_reg))
#define TMS570_GIO_PORT_B_OFFSET				(0x20 / sizeof(tms570_reg))

/* GIO Register Masks */
#define TMS570_GIO_GIOCR0_MASK					(0x00000001)
#define TMS570_GIO_GIOINTDET_MASK				(0xFFFFFFFF)
#define TMS570_GIO_GIOPOL_MASK					(0xFFFFFFFF)
#define TMS570_GIO_GIOENAx_MASK					(0xFFFFFFFF)
#define TMS570_GIO_GIOLVLx_MASK					(0xFFFFFFFF)
#define TMS570_GIO_GIOFLG_MASK					(0xFFFFFFFF)
#define TMS570_GIO_GIOOFFn_MASK					(0x0000003F)
#define TMS570_GIO_GIOEMUn_MASK					(0x0000003F)
#define TMS570_GIO_GIODIR_MASK					(0x000000FF)
#define TMS570_GIO_GIODIN_MASK					(0x000000FF)
#define TMS570_GIO_GIODOUT_MASK					(0x000000FF)
#define TMS570_GIO_GIOPDR_MASK					(0x000000FF)
#define TMS570_GIO_GIOPULDIS_MASK				(0x000000FF)
#define TMS570_GIO_GIOPSL_MASK					(0x000000FF)

/* GIOCR0 Fields */
#define TMS570_GIO_GIOCR0_RESET_BIT_LEN			(1)
#define TMS570_GIO_GIOCR0_RESET_BIT_OFFSET		(0)

/* GIOINTDET Fields */
#define TMS570_GIO_GIOINTDET_GIOINTDETn_BIT_LEN (1)

/* GIOPOL Fields */
#define TMS570_GIO_GIOPOL_GIOPOLn_BIT_LEN		(1)

/* GIOENAx Fields */
#define TMS570_GIO_GIOENAx_GIOENAxn_BIT_LEN		(1)

/* GIOLVLx Fields */
#define TMS570_GIO_GIOLVLx_GIOLVLxn_BIT_LEN		(1)

/* GIOFLG Fields */
#define TMS570_GIO_GIOFLG_GIOFLAGn_BIT_LEN		(1)

/* GIOOFFn Fields */
#define TMS570_GIO_GIOOFFn_GIOOFFn_BIT_LEN		(6)
#define TMS570_GIO_GIOOFFn_GIOOFFn_BIT_OFFSET	(0)

/* GIOEMUn Fields */
#define TMS570_GIO_GIOEMUn_GIOEMUn_BIT_LEN		(6)
#define TMS570_GIO_GIOEMUn_GIOEMUn_BIT_OFFSET	(0)

/* GIODIR Fields */
#define TMS570_GIO_GIODIR_GIODIRn_BIT_LEN		(1)

/* GIODIN Fields */
#define TMS570_GIO_GIODIN_GIODINn_BIT_LEN		(1)

/* GIODOUT Fields */
#define TMS570_GIO_GIODOUT_GIODOUTn_BIT_LEN		(1)

/* GIOPDR Fields */
#define TMS570_GIO_GIOPDR_GIOPDRn_BIT_LEN		(1)

/* GIOPULDIS Fields */
#define TMS570_GIO_GIOPULDIS_GIOPULDISn_BIT_LEN (1)

/* GIOPSL Fields */
#define TMS570_GIO_GIOPSL_GIOPSLn_BIT_LEN		(1)

#endif
