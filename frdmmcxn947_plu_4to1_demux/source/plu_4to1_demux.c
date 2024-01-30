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
#define DEMO_PLU_LUT_0_TRUTH_TABLE 0x0000010 /* 0b00010000 */
#define DEMO_PLU_LUT_1_TRUTH_TABLE 0x0000020 /* 0b00100000 */
#define DEMO_PLU_LUT_2_TRUTH_TABLE 0x0000040 /* 0b01000000 */
#define DEMO_PLU_LUT_3_TRUTH_TABLE 0x0000080 /* 0b10000000 */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void PLU_Configuration(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

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
 * @brief Main function
 */
int main(void)
{
	/* Initialize PLU pins */
    BOARD_InitPins();

    /* Initialize PLU module */
    PLU_Init(PLU0);

    /* Configure input, output, truthtable one time through the API */
    PLU_Configuration();

    /* Once the PLU module is configured, the PLU bus clock can be shut-off to conserve power */
    PLU_Deinit(PLU0);

    while (1)
    {
    }
}
