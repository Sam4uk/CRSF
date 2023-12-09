/**
 * @file crc8.h
 * @author Sam4uk
 * @brief 
 * @version 0.1
 * @date 2023-12-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CRC8_H
#define CRC8_H


#include <stdint.h>

class Crc8
{
public:
/**
 * @brief Construct a new Crc 8 object
 * 
 * @param poly 
 */
    Crc8(uint8_t poly);
    /**
     * @brief 
     * 
     * @param data 
     * @param len 
     * @return uint8_t 
     */
    uint8_t calc(uint8_t *data, uint8_t len);

protected:
    uint8_t _lut[256];
    void init(uint8_t poly);
};
#endif