
#include "string.h"
#include <sys/mman.h>
#include "DMXWrapper.h"

size_t copyDmxString(const DMXRecord *dmxRecord, void *dest) {
    if (dmxRecord->dmxTextLen > MAX_DMX_TEXT_LEN) {
        return 0;
    }
    memcpy(dest, dmxRecord->dmxText, dmxRecord->dmxTextLen);
    return dmxRecord->dmxTextLen;
}

const DMXRecord *getDmxRecord(const void *dmxCommand, int index) {
    const DMXCommand *dmx = dmxCommand;
    const DMXRecord *dmxRecord = dmxCommand + dmx->dmxDataOffset;
    return &dmxRecord[index];
}

int shmOpen(const char *name, int flags, int mode) {
    return shm_open(name, flags, mode);
}
