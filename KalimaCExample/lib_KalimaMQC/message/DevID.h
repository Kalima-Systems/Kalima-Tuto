#ifndef DevID_h
#define DevID_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>

#define MACAddr_size 6

void random_MACAddress(char macAddr[MACAddr_size]);
void get_MACAddress(char macAddr[MACAddr_size]);

#endif