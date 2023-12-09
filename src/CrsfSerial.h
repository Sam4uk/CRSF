/**
 * @file CrsfSerial.h
 * @author Sam4uk
 * @brief
 * @version 0.1
 * @date 2023-12-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CRSF_SERIAL_H
#define CRSF_SERIAL_H
#ifdef ARDUINO
#include <Arduino.h>
#endif
#include <crc8.h>

#include "crsf_protocol.h"

/// @brief
enum eFailsafeAction {
  fsaNoPulses,  ///<
  fsaHold       ///<
};

class CrsfSerial {
 public:
  // Packet timeout where buffer is flushed if no data is received in this time
  static const unsigned int CRSF_PACKET_TIMEOUT_MS = 100;
  static const unsigned int CRSF_FAILSAFE_STAGE1_MS = 300;

  /**
   * @brief Construct a new Crsf Serial object
   *
   * @param port
   * @param baud
   */
  CrsfSerial(HardwareSerial &port, uint32_t baud = CRSF_BAUDRATE);
  /**
   * @brief
   *
   * @param baud
   */
  void begin(uint32_t baud = 0);
  /**
   * @brief Call from main loop to update
   *
   */
  void loop();
  /**
   * @brief
   *
   * @param b
   */
  void write(uint8_t b);
  /**
   * @brief
   *
   * @param buf
   * @param len
   */
  void write(const uint8_t *buf, size_t len);
  /**
   * @brief
   *
   * @param addr
   * @param type
   * @param payload
   * @param len
   */
  void queuePacket(uint8_t addr, uint8_t type, const void *payload,
                   uint8_t len);

  /**
   * @brief Get the Baud object
   *
   * @return uint32_t
   */
  uint32_t getBaud() const;
  /**
   * @brief Return current channel value (1-based) in us
   *
   * @param ch
   * @return int
   */
  int getChannel(unsigned int ch) const;
  /**
   * @brief Get the Link Statistics object
   *
   * @return const crsfLinkStatistics_t*
   */
  const crsfLinkStatistics_t *getLinkStatistics() const;
  /**
   * @brief Get the Gps Sensor object
   *
   * @return const crsf_sensor_gps_t*
   */
  const crsf_sensor_gps_t *getGpsSensor() const;
  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool isLinkUp() const;
  /**
   * @brief Get the Passthrough Mode object
   *
   * @return true
   * @return false
   */
  bool getPassthroughMode() const;
  /**
   * @brief   Enter passthrough mode (serial sent directly to shiftybyte),
   *          optionally changing the baud rate used during passthrough mode
   * @param val
   *          True to start passthrough mode, false to resume processing CRSF
   * @param passthroughBaud
   *          New baud rate for passthrough mode, or 0 to not change baud
   *          Not used if disabling passthough
   */
  void setPassthroughMode(bool val, uint32_t passthroughBaud = 0);

  // Event Handlers
  /**
   * @brief
   *
   */
  void (*onLinkUp)();
  /**
   * @brief
   *
   */
  void (*onLinkDown)();
  // OobData is any byte which is not CRSF, including passthrough
  /**
   * @brief
   *
   */
  void (*onOobData)(uint8_t b);
  // CRSF Packet Callbacks
  /**
   * @brief
   *
   */
  void (*onPacketChannels)();
  /**
   * @brief
   *
   */
  void (*onPacketLinkStatistics)(crsfLinkStatistics_t *ls);
  /**
   * @brief
   *
   */
  void (*onPacketGps)(crsf_sensor_gps_t *gpsSensor);

 private:
  HardwareSerial &_port;
  uint8_t _rxBuf[CRSF_MAX_PACKET_SIZE];
  uint8_t _rxBufPos;
  Crc8 _crc;
  crsfLinkStatistics_t _linkStatistics;
  crsf_sensor_gps_t _gpsSensor;
  uint32_t _baud;
  uint32_t _lastReceive;
  uint32_t _lastChannelsPacket;
  bool _linkIsUp;
  uint32_t _passthroughBaud;
  int _channels[CRSF_NUM_CHANNELS];

  void handleSerialIn();
  void handleByteReceived();
  void shiftRxBuffer(uint8_t cnt);
  void processPacketIn(uint8_t len);
  void checkPacketTimeout();
  void checkLinkDown();

  // Packet Handlers
  void packetChannelsPacked(const crsf_header_t *p);
  void packetLinkStatistics(const crsf_header_t *p);
  void packetGps(const crsf_header_t *p);
};

#endif