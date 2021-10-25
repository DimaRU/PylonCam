//
//  DMXWrapper.h
//
//
//  Created by Dmitriy Borovikov on 21.09.2021.
//

#ifndef DMXWrapper_h
#define DMXWrapper_h

#include "SharedData.h"

int shmOpen(const char *name, int flags, unsigned short int mode);

#endif /* DMXWrapper_h */
