/**
 * @file gio.h
 * @author Onur Alp Kayacan (okayacan@netas.com.tr)
 * @author Furkan Kırlangıç (fkirlangic@netas.com.tr)
 * @brief Interface for the General Input/Output (GIO) configuration and control.
 * 
 * @note Provides enums and functions for setting GIO pin modes, input/output,
 * pull-up/down, open-drain, and interrupts.
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef INC_TMS570_GIO_H_
#define INC_TMS570_GIO_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @enum tGIO_mode
 * @brief GIO operation modes.
 */
typedef enum gio_mode_e {
	GIO_MODE_RESET = 0, /** Reset mode */
	GIO_MODE_NORMAL_OP, /** Normal operation mode */
	NUM_OF_GIO_MODE,	/** Number of GIO modes */
} tGIO_mode;

/**
 * @enum tGIO_port
 * @brief Available GIO ports.
 */
typedef enum gio_port_e {
	GIO_PORT_A = 0, /** GIO Port A */
	GIO_PORT_B,		/** GIO Port B */
	NUM_OF_GIO_PORT /** Number of GIO ports */
} tGIO_port;

/**
 * @enum tGIO_pin
 * @brief Individual pins available on each GIO port.
 */
typedef enum gio_pin_e {
	GIO_PIN_0 = 0, /**< Pin 0 */
	GIO_PIN_1,	   /**< Pin 1 */
	GIO_PIN_2,	   /**< Pin 2 */
	GIO_PIN_3,	   /**< Pin 3 */
	GIO_PIN_4,	   /**< Pin 4 */
	GIO_PIN_5,	   /**< Pin 5 */
	GIO_PIN_6,	   /**< Pin 6 */
	GIO_PIN_7,	   /**< Pin 7 */
	NUM_OF_GIO_PIN /**< Number of pins */
} tGIO_pin;

/**
 * @enum tGIO_pull
 * @brief Specifies the pull resistor configurations available for GIO pins.
 */
typedef enum gio_pull_e {
	GIO_PULL_NO_PULL = 0, /**< No pull resistor enabled; pin is floating */
	GIO_PULL_DOWN,		  /**< Pull-down resistor enabled to ground the pin */
	GIO_PULL_UP,		  /**< Pull-up resistor enabled to pull the pin high */
	NUM_OF_GIO_PULL		  /**< Number of pull configuration options */
} tGIO_pull;

/**
 * @enum tGIO_open_drain
 * @brief Controls the open-drain output mode configuration for GIO pins.
 */
typedef enum gio_open_drain_e {
	GIO_OPEN_DRAIN_DISABLE = 0, /**< Disables open-drain, normal push-pull output */
	GIO_OPEN_DRAIN_ENABLE,		/**< Enables open-drain mode for the pin */
	NUM_OF_GIO_OPEN_DRAIN		/**< Number of open-drain options */
} tGIO_open_drain;

/**
 * @enum tGIO_int_pol
 * @brief Defines the interrupt polarity triggering conditions for GIO pins.
 */
typedef enum gio_int_pol_e {
	GIO_INT_POL_FALLING_EDGE = 0, /**< Interrupt on falling edge */
	GIO_INT_POL_RISING_EDGE,	  /**< Interrupt on rising edge */
	GIO_INT_POL_BOTH_EDGE,		  /**< Interrupt on both edges */
	NUM_OF_GIO_INT_POL			  /**< Number of interrupt polarity options */
} tGIO_int_pol;

/**
 * @enum tGIO_int_level
 * @brief Interrupt level options for GIO pins.
 */
typedef enum gio_int_level_e {
	GIO_INT_LEVEL_LOW = 0, /**< Interrupt level low */
	GIO_INT_LEVEL_HIGH,	   /**< Interrupt level high */
	NUM_OF_GIO_INT_LEVEL   /**< Number of interrupt level options */
} tGIO_int_level;

/**
 * @brief Set the global GIO mode.
 * 
 * @param[in] mode GIO mode to set. @see tGIO_mode
 * @return true if mode set successfully, false otherwise.
 */
bool gio_set_mode(tGIO_mode mode);

/**
 * @brief Configure a GIO pin as input with pull-up/down.
 * 
 * @param[in] port GIO port to configure. @see tGIO_port
 * @param[in] pin GIO pin number to configure. @see tGIO_pin
 * @param[in] pull Pull-up/down setting. @see tGIO_pull
 * @return true if configured successfully, false otherwise.
 */
bool gio_configure_input(tGIO_port port, tGIO_pin pin, tGIO_pull pull);

/**
 * @brief Configure a GIO pin as output with open-drain option.
 * 
 * @param[in] port GIO port to configure. @see tGIO_port
 * @param[in] pin GIO pin number to configure. @see tGIO_pin
 * @param[in] od Open-drain setting. @see tGIO_open_drain
 * @return true if configured successfully, false otherwise.
 */
bool gio_configure_output(tGIO_port port, tGIO_pin pin, tGIO_open_drain od);

/**
 * @brief Set the output level of a GIO pin.
 * 
 * @param[in] port GIO port of the pin. @see tGIO_port
 * @param[in] pin GIO pin number. @see tGIO_pin
 * @param[in] en Output enable state: true = high, false = low.
 * @return true if pin set successfully, false otherwise.
 */
bool gio_set_pin(tGIO_port port, tGIO_pin pin, bool en);

/**
 * @brief Get the input level of a GIO pin.
 * 
 * @param[in] port GIO port of the pin. @see tGIO_port
 * @param[in] pin GIO pin number. @see tGIO_pin
 * @param[out] en Pointer to bool where the pin level is stored (true = high, false = low).
 * @return true if pin read successfully, false otherwise.
 */
bool gio_get_pin(tGIO_port port, tGIO_pin pin, bool* en);

/**
 * @brief Configure interrupt settings for a GIO pin.
 * 
 * @param[in] port GIO port of the pin. @see tGIO_port
 * @param[in] pin GIO pin number. @see tGIO_pin
 * @param[in] pol Interrupt polarity. @see tGIO_int_pol
 * @param[in] level Interrupt level. @see tGIO_int_level
 * @return true if interrupt configured successfully, false otherwise.
 */
bool gio_configure_interrupt(tGIO_port port, tGIO_pin pin, tGIO_int_pol pol, tGIO_int_level level);

/**
 * @brief Enable or disable interrupt for a GIO pin.
 * 
 * @param[in] port GIO port of the pin. @see tGIO_port
 * @param[in] pin GIO pin number. @see tGIO_pin
 * @param[in] en true to enable, false to disable.
 * @return true if interrupt enable/disable succeeded, false otherwise.
 */
bool gio_enable_interrupt(tGIO_port port, tGIO_pin pin, bool en);

/**
 * @brief Returns the highest priority pending GIO interrupt for a given level and clears the flag.
 * 
 * Checks for any pending GIO interrupt at the specified interrupt level, clears the corresponding flag, 
 * and outputs the port and pin of the highest priority interrupt.
 * 
 * @param[in] level Interrupt level to query. @see tGIO_int_level
 * @param[out] port Pointer to store the port of the pending interrupt. @see tGIO_port
 * @param[out] pin Pointer to store the pin of the pending interrupt. @see tGIO_pin
 * 
 * @return true if a pending interrupt exists and was retrieved, false otherwise.
 */
bool gio_get_pending_irq(tGIO_int_level level, tGIO_port* port, tGIO_pin* pin);

#endif
