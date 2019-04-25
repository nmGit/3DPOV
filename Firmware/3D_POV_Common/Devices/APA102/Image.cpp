/*
 * Image.cpp
 *
 *  Created on: Apr 25, 2019
 *      Author: CMPE_STUDENT
 */


#include "Image.h"
img_pos_packet test_bars[TOTAL_POS] = (img_pos_packet[TOTAL_POS])
                    {{73, 77, 71, 0, 0, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 1, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 2, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 3, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 4, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 5, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 6, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 7, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 8, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 9, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 10, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 11, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 12, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 13, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 14, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 15, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 16, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 17, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 18, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 19, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 20, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 21, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 22, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 23, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 24, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 25, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 26, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 27, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 28, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 29, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 30, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 31, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 32, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 33, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 34, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 35, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 36, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 37, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 38, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 39, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 40, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 41, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 42, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 43, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 44, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 45, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 46, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 47, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 48, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 49, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 50, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 51, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 52, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 53, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 54, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 55, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 56, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 57, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 58, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 59, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 60, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 61, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 62, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 63, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 64, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 65, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 66, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 67, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 68, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 69, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 70, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 71, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 72, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 73, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 74, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 75, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 76, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 77, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 78, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 79, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 80, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 81, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 82, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 83, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 84, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 85, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 86, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 87, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 88, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 89, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 90, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 91, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 92, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 93, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 94, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 95, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 96, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240},
                    {73, 77, 71, 0, 0, 97, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 240},
                    {73, 77, 71, 0, 0, 98, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 240},
                    {73, 77, 71, 0, 0, 99, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 3, 252, 0, 240}};

