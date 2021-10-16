//
//  CameraSharedMem.c
//  SocketClient
//
//  Created by Dmitriy Borovikov on 21.09.2021.
//

#include <string.h>
#include <sys/mman.h>
#include "CameraSharedMem.h"

int shmOpen(const char *name, int flags, unsigned short int mode) {
    return shm_open(name, flags, mode);
}
