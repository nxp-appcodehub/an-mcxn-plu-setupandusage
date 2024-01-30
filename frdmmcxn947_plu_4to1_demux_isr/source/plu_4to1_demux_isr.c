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
#include "fsl_cmc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SW3 definitions */
#define BOARD_SW_GPIO        BOARD_SW3_GPIO
#define BOARD_SW_PORT        BOARD_SW3_PORT
#define BOARD_SW_GPIO_PIN    BOARD_SW3_GPIO_PIN
#define BOARD_SW_IRQ         BOARD_SW3_IRQ
#define BOARD_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER

/* PLU truth tables */
#define DEMO_PLU_LUT_0_TRUTH_TABLE 0x0000010 /* 0b00010000 */
#define DEMO_PLU_LUT_1_TRUTH_TABLE 0x0000020 /* 0b00100000 */
#define DEMO_PLU_LUT_2_TRUTH_TABLE 0x0000040 /* 0b01000000 */
#define DEMO_PLU_LUT_3_TRUTH_TABLE 0x0000080 /* 0b10000000 */

/* PLU interruption handler */
#define APP_PLU0_IRQHandler	PLU_IRQHandler
#define APP_PLU_IRQN		PLU_IRQn

/* PLU interruption outputs */
#define ENA_INT_PLU_OUT0 1 /* Enable PLU_OUT0 interruption */
#define ENA_INT_PLU_OUT1 0 /* Block PLU_OUT1 interruption */
#define ENA_INT_PLU_OUT2 0 /* Block PLU_OUT2 interruption */
#define ENA_INT_PLU_OUT3 1 /* Enable PLU_OUT3 interruption */

/* Combine PLU output interrupt mask */
#define PLU_INT_REQ_MASK	(ENA_INT_PLU_OUT0 << kPLU_OUTPUT_0) \
						  | (ENA_INT_PLU_OUT1 << kPLU_OUTPUT_1) \
						  | (ENA_INT_PLU_OUT2 << kPLU_OUTPUT_2) \
						  | (ENA_INT_PLU_OUT3 << kPLU_OUTPUT_3)

/* Enable (1) or disable (0) LED usage for corroborating Sleep behavior or doing current measurements */
#define APP_ENABLE_LED 1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void PLU_Configuration(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_ButtonPress = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Configure the PLU combinational logic network
 */
static void PLU_Configuration(void)
{
    /* Set PLU_IN0 pad as input 0 of LUT0 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_0, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_PLU_IN_0);
    /* Set PLU_IN1 pad as input 1 of LUT0 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_0, kPLU_LUT_IN_1, kPLU_LUT_IN_SRC_PLU_IN_1);
    /* Set PLU_IN2 pad as input 2 of LUT0 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_0, kPLU_LUT_IN_2, kPLU_LUT_IN_SRC_PLU_IN_2);
    /* Set truth table for LUT0 */
    PLU_SetLutTruthTable(PLU0, kPLU_LUT_0, DEMO_PLU_LUT_0_TRUTH_TABLE);
    /* Route LUT0 output to PLU_OUT0 pad */
    PLU_SetOutputSource(PLU0, kPLU_OUTPUT_0, kPLU_OUT_SRC_LUT_0);

    /* Set PLU_IN0 pad as input 0 of LUT1 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_1, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_PLU_IN_0);
    /* Set PLU_IN1 pad as input 1 of LUT1 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_1, kPLU_LUT_IN_1, kPLU_LUT_IN_SRC_PLU_IN_1);
    /* Set PLU_IN2 pad as input 2 of LUT1 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_1, kPLU_LUT_IN_2, kPLU_LUT_IN_SRC_PLU_IN_2);
    /* Set truth table for LUT1 */
    PLU_SetLutTruthTable(PLU0, kPLU_LUT_1, DEMO_PLU_LUT_1_TRUTH_TABLE);
    /* Route LUT1 output to PLU_OUT1 pad */
    PLU_SetOutputSource(PLU0, kPLU_OUTPUT_1, kPLU_OUT_SRC_LUT_1);

    /* Set PLU_IN0 pad as input 0 of LUT2 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_2, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_PLU_IN_0);
    /* Set PLU_IN1 pad as input 1 of LUT2 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_2, kPLU_LUT_IN_1, kPLU_LUT_IN_SRC_PLU_IN_1);
    /* Set PLU_IN2 pad as input 2 of LUT2 */
    PLU_SetLutInputSource(PLU0, kPLU_LUT_2, kPLU_LUT_IN_2, kPLU_LUT_IN_SRC_PLU_IN_2);
    /* Set truth table for LUT2 */
    PLU_SetLutTruthTable(PLU0, kPLU_LUT_2, DEMO_PLU_LUT_2_TRUTH_TABLE);
    /* Route LUT2 output to PLU_OUT2 pad */
    PLU_SetOutputSource(PLU0, kPLU_OUTPUT_2, kPLU_OUT_SRC_LUT_2);

    /* Set PLU_IN0 pad as input 0 of LUT3 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_3, kPLU_LUT_IN_0, kPLU_LUT_IN_SRC_PLU_IN_0);
	/* Set PLU_IN1 pad as input 1 of LUT3 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_3, kPLU_LUT_IN_1, kPLU_LUT_IN_SRC_PLU_IN_1);
	/* Set PLU_IN2 pad as input 2 of LUT3 */
	PLU_SetLutInputSource(PLU0, kPLU_LUT_3, kPLU_LUT_IN_2, kPLU_LUT_IN_SRC_PLU_IN_2);
	/* Set truth table for LUT3 */
	PLU_SetLutTruthTable(PLU0, kPLU_LUT_3, DEMO_PLU_LUT_3_TRUTH_TABLE);
	/* Route LUT3 output to PLU_OUT3 pad */
	PLU_SetOutputSource(PLU0, kPLU_OUTPUT_3, kPLU_OUT_SRC_LUT_3);
}

/*!
 * @brief Interrupt service function of PLU.
 * This function returns MCU to Active mode and turns ON the LED if enabled
 */
void APP_PLU0_IRQHandler(void)
{
	/* Clear interrupt for PLU */
	PLU_ClearLatchedInterrupt(PLU0);
	/* Change button status */
	g_ButtonPress = false;
	/* Exit handler */
	SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Interrupt service function of switch 3.
 * This function sends MCU to Deep Sleep mode and turns OFF the LED if enabled
 */
void BOARD_SW_IRQ_HANDLER(void)
{
	/* Clear interrupt flag for SW3 */
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
    /* Change button status */
    g_ButtonPress = true;
    /* Exit handler */
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
	/* Configuration to set domains into Deep Sleep and Gate Core Clock  */
	cmc_power_domain_config_t cmc_config;
	cmc_config.clock_mode  = kCMC_GateNoneClock;
	cmc_config.main_domain = kCMC_DeepSleepMode;
	cmc_config.wake_domain = kCMC_DeepSleepMode;

	/* SW3 button configuration*/
    gpio_pin_config_t sw3_config;
    sw3_config.pinDirection = kGPIO_DigitalInput;
    sw3_config.outputLogic = 0;

	/* Initialize PLU pins */
    BOARD_InitPins();

    /* Enable clock for PLU and blue LED */
    CLOCK_EnableClock(kCLOCK_Gpio3);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

#if (defined(APP_ENABLE_LED) && (APP_ENABLE_LED))
    /* Initialize blue LED status */
    LED_BLUE_INIT(LOGIC_LED_OFF);
#endif

    /* Configure interrupt for SW3 */
    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);
    /* Enable interrupt for SW3 */
	EnableIRQ(BOARD_SW_IRQ);
	/* Initialize SW3 pin */
	GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw3_config);

    /* Initialize PLU module */
    PLU_Init(PLU0);

    /* Configuration for PLU interruption */
    plu_wakeint_config_t plu_wake_config;
    PLU_GetDefaultWakeIntConfig(&plu_wake_config);
    /* Enable Interrupts from PLU Outputs */
    PLU_EnableWakeIntRequest(PLU0, PLU_INT_REQ_MASK, &plu_wake_config);
    /* Enable latched interrupt to prevent glitch */
    PLU0->WAKEINT_CTRL |= PLU_WAKEINT_CTRL_LATCH_ENABLE_MASK;

    /* Enable PLU Interruptions */
    EnableIRQ(APP_PLU_IRQN);

    /* Configure input, output, truthtable one time through the API */
    PLU_Configuration();

    /* Once the PLU module is configured, the PLU bus clock can be shut-off to conserve power */
    PLU_Deinit(PLU0);

    while (1)
    {
    	/* Check status of SW3 press */
    	if(g_ButtonPress)
		{
#if (defined(APP_ENABLE_LED) && (APP_ENABLE_LED))
    		/* Turn OFF blue LED */
    		LED_BLUE_OFF();
    		//GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
#endif
    		/* Enter Deep Sleep */
    		CMC_EnterLowPowerMode(CMC0, &cmc_config);
    		__ASM("nop");
		}
    	else
    	{
#if (defined(APP_ENABLE_LED) && (APP_ENABLE_LED))
    		/* Turn ON blue LED */
    		LED_BLUE_ON();
    		//GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
#endif
    		__ASM("nop");
    	}
    }
}
