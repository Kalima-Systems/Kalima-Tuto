#ifndef CALLBACK_H
#define CALLBACK_H

#define CLONELIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libs/KalimaLib/MQ2/nodelib/Node.h"
#include "../libs/KalimaLib/ContractManager/ContractList.h"

ClientCallback* set_callback();

#endif