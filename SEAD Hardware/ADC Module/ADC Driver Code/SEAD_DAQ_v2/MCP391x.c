/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Pavlo Milo Manovi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/**
 * @file	
 * @author 	Pavlo Milo Manovi
 * @date	April, 2014
 * @brief 	This library provides implementation of methods to init and read the MCP391x.
 *
 */

#include "MCP391x.h"
#include "ADCModuleBoard.h"
#include "ParallelIO.h"
#include <stdint.h>
#include <stdlib.h>

static MCP391x_Info *passedInfoStruct;

/**
 * @brief Sets up the MCP391x.
 * @param MCP391x_Params A pointer to a MCP391x_Info struct which will be updated.
 * @return Returns EXIT_SUCCESS if the device responds with the set configuration.
 */
uint8_t MCP391x_Init(MCP391x_Info *DS85x8Info)
{
	MCP391x_CONFIG0_REG config0
	MCP391x_CONFIG1_REG config1;
	MCP391x_GAINCAL_CH0_REG gainCalCh0;
	MCP391x_GAINCAL_CH1_REG gainCalCh1;
	MCP391x_GAINCAL_CH2_REG gainCalCh2;
	MCP391x_GAINCAL_CH3_REG gainCalCh3;
	MCP391x_GAIN_REG gain;
	MCP391x_LOCK_CRC_REG lockCrc;
	MCP391x_MOD_REG mod;
	MCP391x_OFFCAL_CH0_REG offsetCalCh0;
	MCP391x_OFFCAL_CH1_REG offsetCalCh1;
	MCP391x_OFFCAL_CH2_REG offsetCalCh2;
	MCP391x_OFFCAL_CH3_REG offsetCalCh3;
	MCP391x_PHASE_REG phase;
	MCP391x_STATUSCOM_REG statusData;  //Read from the MCP3912
	
	//Setting bits for configuration of the MCP3912;
	

	passedInfoStruct = DS85x8Info;
	return(EXIT_SUCCESS);
}