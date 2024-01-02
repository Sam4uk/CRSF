/**
 * @file PickChennel.ino
 * @author Sam4uk
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <CrsfSerial.h>
#if defined(__AVR_ATmega2560__)
CrsfSerial                  
    crsf(Serial3, CRSF_BAUDRATE); //  receiver connect to Serial3
#else
#error NOT MEGA2560
#endif

/**
 * @brief The function that will be called upon receiving data via control channels
 */
void packetChannels();

/**
 * @brief Executed once on power-up or reboot
 */
void setup(){
    Serial.begin(115200);
    crsf.begin();
    crsf.onPacketChannels = &packetChannels;
}

/**
 * @brief Executes cyclically while the power is on
 */
void loop(){
    crsf.loop();
}

void packetChannels(){
    for (auto ch{1}; ch <= CRSF_NUM_CHANNELS; ++ch) {
    Serial.print(crsf.getChannel(ch));
    if (ch != CRSF_NUM_CHANNELS)
        Serial.print(", ");
    }
    Serial.println();
}