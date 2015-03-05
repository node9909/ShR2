/**
 * @file	main.c
 * @author 	Pavlo Milo Manovi, Henry Crute
 * @date	February, 2015
 * @brief 	Main acquire script to read data from the SEAD device.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

#include "ftd2xx.h"
#include "lib_crc.h"
#include "daq_config.h"

#define BUF_SIZE 0x10000

enum {
	BUFFER_A,
	BUFFER_B
};

DWORD dwBytesRead;
DWORD dwBytesWritten;
DWORD fifoRxQueueSize;
DWORD lpdwAmountInTxQueue;
DWORD lpdwEventStatus;
DWORD bytes;

FILE * fh;
FT_HANDLE ftFIFO;
FT_STATUS ftStatus;

int runningTotalA = 0;
int runningTotalB = 0;
int rxCrc = 0xFFFF;
int crc;
int i;

/* Variables associated with getopt */
int iport = 0;
char *outfile = "data.txt";
int bandwidth = 4000;
int channels = 4;
bool verbose = false;

static uint8_t tmpBuff[BUF_SIZE];
static uint8_t tmpBuff2[BUF_SIZE];
static char exit_thread = 0;
static char current_buffer = BUFFER_A;

//reads from the usb uart fifio
void *read_fifo(void *pArgs)
{
	(void)pArgs;
	while(exit_thread != 1) {
		if (current_buffer == BUFFER_A) {
			FT_GetStatus(ftFIFO, &fifoRxQueueSize, &lpdwAmountInTxQueue, &lpdwEventStatus);
			FT_Read(ftFIFO, &tmpBuff[runningTotalA], fifoRxQueueSize, &dwBytesRead);
			runningTotalA += dwBytesRead;
		
			if (fifoRxQueueSize > 4000) {
				fprintf(stdout, "ERROR: toRead: %i > 4000.  DATA WILL BE CORRUPTED!\r\n", fifoRxQueueSize);
				fflush(stdout);
			}

			if (runningTotalA >= 26007) {
				current_buffer = BUFFER_B;
			}
		} else if (current_buffer == BUFFER_B) {
			FT_GetStatus(ftFIFO, &fifoRxQueueSize, &lpdwAmountInTxQueue, &lpdwEventStatus);
			FT_Read(ftFIFO, &tmpBuff2[runningTotalB], fifoRxQueueSize, &dwBytesRead);
			runningTotalB += dwBytesRead;

			if (fifoRxQueueSize > 4000) {
				fprintf(stdout, "ERROR: toRead: %i > 4000.  DATA WILL BE CORRUPTED!\r\n", fifoRxQueueSize);
				fflush(stdout);
			}

			if (runningTotalB >= 26007) {
				current_buffer = BUFFER_A;
			}
		}
	}
	(void)FT_Close(ftFIFO);
	return NULL;
}

//goes over the main acquire loop
void acquire_loop()
{
	int i;
	pthread_t thread_id;
	FT_ResetDevice(ftFIFO);
	FT_SetTimeouts(ftFIFO, 1000, 1000); //1 Second Timeout
	pthread_create(&thread_id, NULL, &read_fifo, NULL);
	int32_t ch0 = 0;
	int32_t ch1 = 0;
	int32_t ch2 = 0;
	int32_t ch3 = 0;
	while(1) {
		if(runningTotalA >= 26007 && current_buffer == BUFFER_B) {
			for (i = 0; i < 26000; i++) {
				rxCrc = update_crc_ccitt(rxCrc, tmpBuff[i]);
			}
			crc = ((tmpBuff[26006] << 8) | (tmpBuff[26007]));
			fprintf(stdout, "Block transfer complete, TX-CRC:%i,"
				" RX-CRX:%i\r\n", crc, rxCrc);
			fflush(stdout);
			for (i = 0; i < 26000;) {
				ch0 |= (tmpBuff[i+2] << 16);
				ch0 |= (tmpBuff[i+3] << 8);
				ch0 |= (tmpBuff[i]);
				ch1 |= (tmpBuff[i+5] << 16);
				ch1 |= (tmpBuff[i+6] << 8);
				ch1 |= (tmpBuff[i+4]);
				ch2 |= (tmpBuff[i+8] << 16);
				ch2 |= (tmpBuff[i+9] << 8);
				ch2 |= (tmpBuff[i+7]);
				ch3 |= (tmpBuff[i+11] << 16);
				ch3 |= (tmpBuff[i+12] << 8);
				ch3 |= (tmpBuff[i+10]);
				//sign extension
				ch0 = ((ch0 << 8) >> 8);
				ch1 = ((ch1 << 8) >> 8);
				ch2 = ((ch2 << 8) >> 8);
				ch3 = ((ch3 << 8) >> 8);
				fprintf(fh, "%i, %i, %i, %i\r\n", ch0, ch1, ch2, ch3);
				//fprintf(fh, "%08X, %08X, %08X, %08X i=%i\r\n", ch0, ch1, ch2, ch3, i);
				i += 13;
				ch0 = 0;
				ch1 = 0;
				ch2 = 0;
				ch3 = 0;
			}
			fflush(fh);
			runningTotalA = 0;
			rxCrc = 0xFFFF;
		} else if (runningTotalB >= 26007 && current_buffer == BUFFER_A) {
			for (i = 0; i < 26000; i++) {
				rxCrc = update_crc_ccitt(rxCrc, tmpBuff2[i]);
			}
			crc = ((tmpBuff2[26006] << 8) | (tmpBuff2[26007]));
			fprintf(stdout, "Block transfer complete, TX-CRC:%i, RX-CRX:%i\r\n", crc, rxCrc);
			fflush(stdout);
			for (i = 0; i < 26000;) {
				ch0 |=  (tmpBuff2[i+2] << 16);
				ch0 |=  (tmpBuff2[i+3] << 8);
				ch0 |=  (tmpBuff2[i]);
				ch1 |=  (tmpBuff2[i+5] << 16);
				ch1 |=  (tmpBuff2[i+6] << 8);
				ch1 |=  (tmpBuff2[i+4]);
				ch2 |=  (tmpBuff2[i+8] << 16);
				ch2 |=  (tmpBuff2[i+9] << 8);
				ch2 |=  (tmpBuff2[i+7]);
				ch3 |=  (tmpBuff2[i+11] << 16);
				ch3 |=  (tmpBuff2[i+12] << 8);
				ch3 |=  (tmpBuff2[i+10]);
				//sign extension
				ch0 = ((ch0 << 8) >> 8);
				ch1 = ((ch1 << 8) >> 8);
				ch2 = ((ch2 << 8) >> 8);
				ch3 = ((ch3 << 8) >> 8);
				fprintf(fh, "%i, %i, %i, %i\r\n", ch0, ch1, ch2, ch3);
				//fprintf(fh, "%08X, %08X, %08X, %08X i=%i\r\n", ch0, ch1, ch2, ch3, i);
				i += 13;
				ch0 = 0;
				ch1 = 0;
				ch2 = 0;
				ch3 = 0;
			}
			fflush(fh);
			runningTotalB = 0;
			rxCrc = 0xFFFF;
		}
	}
	return;
}

//prints the usage for the program
void print_usage()
{
	printf("Usage: Acquire [-h] [-v] [-p port] [-b bandwidth] [-f file] [-c channels]\n");
	return;
}

void print_config()
{
	printf("iport %d\n", iport);
	printf("bandwidth %d\n", bandwidth);
	printf("outfile: %s\n", outfile);
	printf("channels: %d\n", channels);
}

//gets options, and populates global option variables
void get_options(int argc, char **argv)
{
	opterr = 0;
	int c;
	while ((c = getopt (argc, argv, "hvp:b:f:c:")) != -1) {
		switch (c)
		{
		case 'h':
			print_usage();
			break;
		case 'v':
			verbose = true;
			break;
		case 'p':
			iport = strtol(optarg, (char **)NULL, 10);
			break;
		case 'b':
			bandwidth = strtol(optarg, (char **)NULL, 10);
			break;
		case 'f':
			outfile = optarg;
			break;
		case 'c':
			channels = strtol(optarg, (char **)NULL, 10);
			break;
		case '?':
			if (optopt == 'c' || optopt =='f' || optopt == 'b' || optopt == 'p')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr, "Unknown option character `\\x%x'.\n",
                   optopt);
			exit(1);
		default:
			abort ();
		}
	}
	//print out the option config if we are in verbose mode.
	return;
}

daq_config default_config()
{
	daq_config config;
	//config0 register for the MCP
	config.BOOST = 0b11;
	config.DITHER = 0b11;
	config.EN_GAINCAL = 0;
	config.EN_OFFCAL = 0;
	config.OSR = 0b010; //OSR = 128
	config.PRE = 0b00; //prescalar = 1
	config.VREFCAL = 64;
	//programmable gain amplifier register
	config.PGA_CH0 = 0b011;
	config.PGA_CH1 = 0b011;
	config.PGA_CH2 = 0b011;
	config.PGA_CH3 = 0b011;
	return config;
}

/* 16MHz Clock / 4 / PRE / OSR = DRCLK
 * PRE	OSR	Bandwidth
 * 00	000	32500
 * 00	001	16250
 * 00	010	8125
 * 00	011	4062.5
 * 00	100	2031.25
 * 00	101	1445.3125
 * 00	110	820.3125
 * 00	111	419.921875
*/

//packages config struct from the input parameters
daq_config package_config()
{
	//create a config struct with default values
	daq_config config = default_config();
	if (bandwidth < 419.921875) {
		config.OSR = 0b111;
		bandwidth = 419.921875;
	} else if (bandwidth < 820.3125) {
		config.OSR = 0b110;
		bandwidth = 820.3125;
	} else if (bandwidth < 1445.3125) {
		config.OSR = 0b101;
		bandwidth = 1445.3125;
	} else if (bandwidth < 2031.25) {
		config.OSR = 0b100;
		bandwidth = 2031.25;
	} else if (bandwidth < 4062.5) {
		config.OSR = 0b011;
		bandwidth = 4062.5;
	} else if (bandwidth < 8125) {
		config.OSR = 0b010;
		bandwidth = 8125;
	} else {
		config.OSR = 0b001;
		bandwidth = 16250;
	//} else {
	//	config.OSR = 0b000;
	//	bandwidth = 32500;
	}
	return config;
}

//sends the config struct over the ft tx
void send_config(daq_config config)
{
	FT_Write(ftFIFO, &config, (DWORD)sizeof(config), &bytes);
	return;
}

int main(int argc, char *argv[])
{
	FT_STATUS ftStatus;
	//process options
	get_options(argc, argv);
	//calculate and populate config struct
	daq_config config = package_config();
	if (verbose) {
		print_config();
	}
	//file handle
	fh = fopen(outfile, "w");
	if(fh == NULL) {
		printf("Cant open source file\n");
		exit(1);
	}
	ftStatus = FT_Open(0, &ftFIFO);
	if(ftStatus != FT_OK) {
		printf("FT_Open(%d) failed, check that ftdi_sio and"
			"usbserial are unloaded.\r\n Use rmmod.\r\n",
			iport);
		exit(1);
	}
	send_config(config);
	acquire_loop();
	exit_thread = 1;
	fclose(fh);
	exit(0);
}