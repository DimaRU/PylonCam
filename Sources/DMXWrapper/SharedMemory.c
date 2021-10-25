//
//  SharedMemory.c
//  
//
//  Created by Dmitriy Borovikov on 03.10.2021.
//

#include "DMXWrapper.h"
#include <sys/mman.h>

int shmOpen(const char *name, int flags, unsigned short int mode) {
    return shm_open(name, flags, mode);
}
