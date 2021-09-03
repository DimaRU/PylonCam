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

double LaplacianMeasure(int height, int width, void* imageBuffer) CF_SWIFT_NAME(LaplacianMeasure(height:width:imageBuffer:));
double SobelMeasure(int height, int width, void* imageBuffer) CF_SWIFT_NAME(SobelMeasure(height:width:imageBuffer:));
double VarianceMeasure(int height, int width, void* imageBuffer) CF_SWIFT_NAME(VarianceMeasure(height:width:imageBuffer:));

#ifdef __cplusplus
}
#endif

