#define CLONELIB

#include "include/inc/KalimaCUtil/aesKalima.h"
#include "include/inc/KalimaCUtil/BufferChain.h"
#include "include/inc/KalimaCUtil/ByteBuffer.h"
#include "include/inc/KalimaCUtil/BytesArray.h"
#include "include/inc/KalimaCUtil/compare.h"
#include "include/inc/KalimaCUtil/config.h"
#include "include/inc/KalimaCUtil/LinkedList.h"
#include "include/inc/KalimaCUtil/logger.h"
#include "include/inc/KalimaCUtil/opensslUtil.h"
#include "include/inc/KalimaCUtil/rsaKalima.h"
#include "include/inc/KalimaCUtil/skiplist.h"
#include "include/inc/KalimaCUtil/skiplist.h"

#include "include/inc/MQ2/message/checksum.h"
#include "include/inc/MQ2/message/DevID.h"
#include "include/inc/MQ2/message/Header.h"
#include "include/inc/MQ2/message/KMessage.h"
#include "include/inc/MQ2/message/KMsg.h"
#include "include/inc/MQ2/message/UUID.h"
#include "include/inc/MQ2/netlib/Client.h"
#include "include/inc/MQ2/netlib/ClientCallback.h"
#include "include/inc/MQ2/nodelib/Node.h"
#include "include/inc/MQ2/nodelib/prop.h"

#include "include/inc/NodeLib/clone.h"
#include "include/inc/NodeLib/memcache.h"
#include "include/inc/NodeLib/memcacheCallback.h"

#include "include/inc/ContractManager/ContractList.h"
#include "include/inc/ContractManager/decrypt.h"
#include "include/inc/ContractManager/filewatcher.h"
#include "include/inc/ContractManager/Lua/lua.h"