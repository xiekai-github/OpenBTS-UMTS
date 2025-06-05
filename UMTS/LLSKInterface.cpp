#include "LLSKInterface.h"
#include <Logger.h>
#include <Globals.h>

LLSKInterface::LLSKInterface()
    : mSocket(0)
{
    const char* addr = gConfig.getStr("LLSK.RemoteAddr").c_str();
    unsigned port = gConfig.getNum("LLSK.RemotePort");
    mSocket.destination(addr, port);
}

void LLSKInterface::start()
{
    mDriveThread.start((void*(*)(void*))[](void* arg){
        ((LLSKInterface*)arg)->drive();
        return (void*)0;
    }, this);
}

void LLSKInterface::drive()
{
    while (1) {
        int len = mSocket.read(mReadBuffer, 1000);
        if (len <= 0)
            continue;
        LOG(INFO) << "LLSK RX " << len << " bytes";
    }
}

void LLSKInterface::send(const void* data, size_t len)
{
    mSocket.write((const char*)data, len);
}
