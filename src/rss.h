//
// Created by whs on 2/20/16.
//

#ifndef THAIENGINE_RSS_H
#define THAIENGINE_RSS_H

#include <stdio.h>

/**
 * Returns the peak (maximum so far) resident set size (physical
 * memory use) measured in bytes, or zero if the value cannot be
 * determined on this OS.
 */
size_t getPeakRSS();

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t getCurrentRSS();

#endif //THAIENGINE_RSS_H
