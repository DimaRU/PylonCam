//
//  FocusMeasure.h
//  
//
//  Created by Dmitriy Borovikov on 01.09.2021.
//

#pragma once

#include "SwiftDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

double laplacianMeasure(int width, int height, void* _Nonnull imageBuffer) CF_SWIFT_NAME(laplacianMeasure(width:height:imageBuffer:));
double sobelMeasure(int width, int height, void* _Nonnull imageBuffer) CF_SWIFT_NAME(sobelMeasure(width:height:imageBuffer:));
double varianceMeasure(int width, int height, void* _Nonnull imageBuffer) CF_SWIFT_NAME(varianceMeasure(width:height:imageBuffer:));

#ifdef __cplusplus
}
#endif
