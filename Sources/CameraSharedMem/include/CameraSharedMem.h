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

int shmOpen(const char *name, int flags, unsigned short int mode);

#endif /* CameraSharedMem_h */
