#ifndef CALLBACK_H
#define CALLBACK_H

#define CLONELIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "LuaFunctions.h"

ClientCallback* set_clientCallback();
MemCacheCallback* set_memcacheCallback();

#endif