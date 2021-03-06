//
//  SharedData.h
//  
//
//  Created by Dmitriy Borovikov on 26.09.2021.
//

#pragma once
#include <stdint.h>

#define MaxDMXCodeLen 150   // Max DMX code len 2 byte aligned
#define MaxDMXCodes 300     // Max DMX codes per image

// Структура запроса
typedef struct __attribute__((__packed__)) {
    uint64_t    frameId;        // Unique frame ID
    uint64_t    width;          //
    uint64_t    height;         //
    int32_t     bufferNum;      // Buffer number
} BoxDetectionRequest;

typedef struct __attribute__((__packed__)) {
	uint64_t    frameId;        // Unique frame ID
	double      timestampBegin; // Время начала распознования
	double      timeStampEnd;   // Время конца распознования
	int16_t     replyType;      // Тип ответа. = 0
								// 0: распознавание квадратов
								// 1: распознование кодов
	int16_t     error;          // if not zero, interal error no
} DMXReplyHeader;

// Координаты распознанного квадрата с кодом.
typedef struct __attribute__((__packed__)) {
    uint16_t    x;
    uint16_t    y;
    uint16_t    xx;
    uint16_t    yy;
} DMXBox;

// Ответ с распознанными областями
typedef struct __attribute__((__packed__)) {
    uint64_t    frameId;        // Unique frame ID
    double      timestampBegin; // Время начала распознования
    double      timeStampEnd;   // Время конца распознования
    int16_t     replyId;        // Идентификатор ответа. = 0
                                // 0: распознавание квадратов
                                // 1: распознование кодов
    int16_t     error;          // if not zero, interal error no

	int16_t     detectedCount;  // Количество распознанных квадратов
    DMXBox      dmxBoxes[];     // Массив распознанных квадратов.
} DMXBoxDetectionReply;

// Строка с кодом
typedef struct __attribute__((__packed__)) {
    int16_t     len;            // == 0 - не распознан
    int8_t      code[MaxDMXCodeLen];
} DMXCode;

// Ответ с распознанными кодами DMX
typedef struct __attribute__((__packed__)) {
    uint64_t    frameId;        // Unique frame ID
    double      timestampBegin; // Время начала распознования
    double      timeStampEnd;   // Время конца распознования
    int16_t     replyId;        // Идентификатор ответа. = 1
                                // 0: распознавание квадратов
                                // 1: распознование кодов
    int16_t     error;          // if not zero, interal error no

	int16_t     maxDMXCodeLen;  // Размер строки c DMX кодом. (150)
    DMXCode     dmxCode[];      // Массив кодов.
} DMXCodeDetectionReply;
