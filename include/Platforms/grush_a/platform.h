#ifndef _PLATFORM_H_
#define _PLATFORM_H_
/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
*
* This file provides definitions for the BCM920732TAG_Q32 platform
*
*/
#include "bleprofile.h"
#include "spar_utils.h"

/*
 * GPIO settings for the 20732/20737 Tag (~1.5x3 inches)
 */
#define GPIO_PIN_WP          	1
#define GPIO_SETTINGS_WP     	(GPIO_OUTPUT | GPIO_INIT_LOW  | GPIO_WP)

#define GPIO_PIN_LED         	4
#define GPIO_SETTINGS_LED    	(GPIO_OUTPUT | GPIO_INIT_HIGH | GPIO_LED)

#define GPIO_PIN_UART_TX		32
#define GPIO_PIN_UART_RX		33

#endif
