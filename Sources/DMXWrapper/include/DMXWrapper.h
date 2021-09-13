//
//  DMXWrapper.h
//  
//
//  Created by Dmitriy Borovikov on 14.05.2021.
//

#ifndef DMXDefs_h
#define DMXDefs_h
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#if __has_attribute(swift_name)
# define CF_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#else
# define CF_SWIFT_NAME(_name)
#endif

//######################################################################
// Address  len  type     description
// [0..7]    8    UINT64  frame counter
// [8..9]    2    UINT16  image width
// [10..11]  2    UINT16  image height
// [12]      1    UINT8   1 set for new frame, client has to write 0 as frame is read, this blocks detector
// [13]      1    UINT8   1 set for detection and decoding has finished, client has to write 0 as frame is read, this blocks detector
// [14]      1    UINT8   detection state (f, d)
// [15]      1    UINT8   not used
// [16..17]  2    UINT16  number of detected[decoded] DMX codes
// [18..19]  2    INT16   DMX_RECORD_LEN length of one DMX record
// [20..23]  4    UINT32  DMX_DATA_MEM_OFFSET Memory offset for dmx data
// [24..27]  4    INT32   PID pid for signaled process
//
// [DMX_DATA_MEM_OFFSET ... +DMX_RECORD_LEN * MAX_DMX_NUMBER]
// [DMX_ITEM_IX memory allocation]
//    + 0    2    UINT16  X box
//    + 2    2    UINT16  Y box
//    + 4    2    UINT16  XX box
//    + 6    2    UINT16  YY box
//    + 8    2    UINT16  DMX text length if decoded, 0 is not detected but not decoded
//    + 10   MAX_DMX_TEXT_LEN
//                UCHAR[MAX_DMX_TEXT_LEN]
//######################################################################

#define MAX_DMX_NUMBER 300
#define MAX_DMX_TEXT_LEN 150
#define DMX_RECORD_LEN (MAX_DMX_TEXT_LEN + 10)
#define DMX_DATA_MEM_OFFSET 32
#define DMX_MEM_SIZE (DMX_DATA_MEM_OFFSET + DMX_RECORD_LEN)

typedef struct _DMXRecord {
    uint16_t    x;
    uint16_t    y;
    uint16_t    xx;
    uint16_t    yy;
    uint16_t    dmxTextLen;
    uint8_t     dmxText[MAX_DMX_TEXT_LEN];
} DMXRecord;

typedef struct _DMXCommand {
    uint64_t    frameCounter;       // 0
    uint16_t    width;              // 8
    uint16_t    height;             // 10
    uint8_t     isNewFrame;         // 12
    uint8_t     isFinished;         // 13
    uint8_t     dectectionState;    // 14
    uint8_t     dummy1;             // 15
    uint16_t    detectedCount;      // 16
    int16_t     dmxRecordLen;       // 18
    uint32_t    dmxDataOffset;      // 20
    int32_t     pid;                // 24
    uint8_t     padding[4];         // 28
    DMXRecord   dmxRecord[MAX_DMX_NUMBER];  // 32
} DMXCommand;

size_t copyDmxString(const DMXRecord *dmxRecord, void *dest);
const DMXRecord *getDmxRecord(const void *dmxCommand, int index);
int shmOpen(const char *name, int flags, int mode);

#endif /* DMXDefs_h */
