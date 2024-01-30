/*
 * Copyright 2018-2019, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_plu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* PLU module */
#define DEMO_PLU_LUT_BUFFER        0x0000002 /* 0b00000010 */

/* GPIO module */
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void PLU_Configuration(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Configure the PLU combinational logic network
 */
static void PLU_Configuration(void)
{
	/* Connect pin PLU_IN0 to LUT0 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_0, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_PLU_IN_0);
	/* Set a buffer truth table for LUT3 */
	PLU_SetLutTruthTable(PLU0, kPLU_LUT_0, DEMO_PLU_LUT_BUFFER);

	/* Connect FF0 to LUT1 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_1, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_FLIPFLOP_0);
	/* Set a buffer truth table for LUT3 */
	PLU_SetLutTruthTable(PLU0, kPLU_LUT_1, DEMO_PLU_LUT_BUFFER);

	/* Connect FF1 to LUT2 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_2, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_FLIPFLOP_1);
	/* Set a buffer truth table for LUT3 */
	PLU_SetLutTruthTable(PLU0, kPLU_LUT_2, DEMO_PLU_LUT_BUFFER);

	/* Connect FF2 to LUT3 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_3, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_FLIPFLOP_2);
	/* Set a buffer truth table for LUT3 */
	PLU_SetLutTruthTable(PLU0, kPLU_LUT_3, DEMO_PLU_LUT_BUFFER);

	/* Route FlipFlop_0 output to PLU_OUT0 */
	PLU_SetOutputSource(PLU0, kPLU_OUTPUT_0, kPLU_OUT_SRC_FLIPFLOP_0);
	/* Route FlipFlop_1 output to PLU_OUT1 */
	PLU_SetOutputSource(PLU0, kPLU_OUTPUT_1, kPLU_OUT_SRC_FLIPFLOP_1);
	/* Route FlipFlop_2 output to PLU_OUT2 */
	PLU_SetOutputSource(PLU0, kPLU_OUTPUT_2, kPLU_OUT_SRC_FLIPFLOP_2);
	/* Route FlipFlop_3 output to PLU_OUT3 */
	PLU_SetOutputSource(PLU0, kPLU_OUTPUT_3, kPLU_OUT_SRC_FLIPFLOP_3);
}

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
	/* Initialize PLU pins */
    BOARD_InitPins();

    /* Start the clock used for PLU_CLKIN, which is routed from the LED_RED pad */
    CLOCK_EnableClock(kCLOCK_Gpio3);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    LED_RED_INIT(LOGIC_LED_OFF);

    /* Initialize PLU module */
    PLU_Init(PLU0);

    /* Configure input, output, truthtable one time through the API */
    PLU_Configuration();

    /* Once the PLU module is configured, the PLU bus clock can be shut-off to conserve power */
    PLU_Deinit(PLU0);

    /* Set systick reload value to generate 1ms interrupt */
	if (SysTick_Config(SystemCoreClock / 1000U))
	{
		while (1)
		{
		}
	}

	while (1)
	{
		/* Delay 1000 ms */
		SysTick_DelayTicks(1000U);
		GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
	}
}
