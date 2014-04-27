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
 * @file	ADS85x8.h
 * @author 	Pavlo Milo Manovi
 * @date	April, 2014
 * @brief 	This library is used to set up the peripherals of the pic.
 */

#include "ADCModuleBoard.h"
#include "ParallelIO.h"

/**
 * @brief Sets up the board with the peripherals defined in the header.
 */
void ADCModuleBoard_Init(void)
{
    PARALLEL_PORT_READ rd;
    PARALLEL_PORT_WRITE wr;
    PARALLEL_PORT_TRISTATE trs;

    //Setting up the bitfield to init the parallel port with.
    //PORT registers to read.
    rd.BIT0 = DB0_PORT;
    rd.BIT1 = DB1_PORT;
    rd.BIT2 = DB2_PORT;
    rd.BIT3 = DB3_PORT;
    rd.BIT4 = DB4_PORT;
    rd.BIT5 = DB5_PORT;
    rd.BIT6 = DB6_PORT;
    rd.BIT7 = DB7_PORT;
    rd.BIT8 = DB8_PORT;
    rd.BIT9 = DB9_PORT;
    rd.BIT10 = DB10_PORT;
    rd.BIT11 = DB11_PORT;
    rd.BIT12 = DB12_PORT;
    rd.BIT13 = DB13_PORT;
    rd.BIT14 = DB14_PORT;
    rd.BIT15 = DB15_PORT;

    //Setting up the bitfield to init the parallel port with.
    //LAT registers to read.
    wr.BIT0 = DB0_LAT;
    wr.BIT1 = DB1_LAT;
    wr.BIT2 = DB2_LAT;
    wr.BIT3 = DB3_LAT;
    wr.BIT4 = DB4_LAT;
    wr.BIT5 = DB5_LAT;
    wr.BIT6 = DB6_LAT;
    wr.BIT7 = DB7_LAT;
    wr.BIT8 = DB8_LAT;
    wr.BIT9 = DB9_LAT;
    wr.BIT10 = DB10_LAT;
    wr.BIT11 = DB11_LAT;
    wr.BIT12 = DB12_LAT;
    wr.BIT13 = DB13_LAT;
    wr.BIT14 = DB14_LAT;
    wr.BIT15 = DB15_LAT;

    //Setting up the bitfield to init the parallel port with.
    //TRIS registers to read.
    trs.BIT0 = DB0_TRIS;
    trs.BIT1 = DB1_TRIS;
    trs.BIT2 = DB2_TRIS;
    trs.BIT3 = DB3_TRIS;
    trs.BIT4 = DB4_TRIS;
    trs.BIT5 = DB5_TRIS;
    trs.BIT6 = DB6_TRIS;
    trs.BIT7 = DB7_TRIS;
    trs.BIT8 = DB8_TRIS;
    trs.BIT9 = DB9_TRIS;
    trs.BIT10 = DB10_TRIS;
    trs.BIT11 = DB11_TRIS;
    trs.BIT12 = DB12_TRIS;
    trs.BIT13 = DB13_TRIS;
    trs.BIT14 = DB14_TRIS;
    trs.BIT15 = DB15_TRIS;

    Parallel_IO_Init(rd, trs, wr);

    //TODO: FILL IN THE REST OF THE TRISTATE AND STUFF DEFINED IN THE HEADER
    //FOR THIS LIBRARY.
}
