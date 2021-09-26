//
//  CameraSharedMem.c
//  SocketClient
//
//  Created by Dmitriy Borovikov on 21.09.2021.
//

#include <string.h>
#include <sys/mman.h>
#include "CameraSharedMem.h"

size_t copyDmxString(const DMXCodeDetectionReply *reply, int index, void *dest) {
    if (reply->dmxCode[index].len > reply->maxDMXCodeLen) {
        return 0;
    }
    memcpy(dest, reply->dmxCode[index].code, reply->dmxCode[index].len);
    return reply->dmxCode[index].len;
}

DMXBox getBoxRecord(const DMXBoxDetectionReply *reply, int index) {
    return reply->dmxBoxes[index];
}

int getDmxRecordLen(const DMXCodeDetectionReply *reply, int index) {
    return reply->dmxCode[index].len;
}

int shmOpen(const char *name, int flags, int mode) {
    return shm_open(name, flags, mode);
}
