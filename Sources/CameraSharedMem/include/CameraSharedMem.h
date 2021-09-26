//
//  CameraSharedMem.h
//  SocketClient
//
//  Created by Dmitriy Borovikov on 21.09.2021.
//

#ifndef CameraSharedMem_h
#define CameraSharedMem_h

#include <stdint.h>
#include "SharedData.h"

DMXBox getBoxRecord(const DMXBoxDetectionReply *reply, int index);
size_t copyDmxString(const DMXCodeDetectionReply *reply, int index, void *dest);
int getDmxRecordLen(const DMXCodeDetectionReply *reply, int index);

int shmOpen(const char *name, int flags, int mode);

#endif /* CameraSharedMem_h */
