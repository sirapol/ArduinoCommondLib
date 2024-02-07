#ifndef ARDUINO_COMMOND_LIB_H
#define ARDUINO_COMMOND_LIB_H
#endif

#ifndef USB_SERIAL
#define USB_SERIAL Serial
#define USB_SERIAL_TIMEOUT 1000
#define USB_SERIAL_BAUD 115200
#endif

#include <Arduino.h>

#ifdef ARDUINO_ARCH_ESP32
#include <Esp.h>
#include <SPIFFS.h>
/**************************************************************************/
/*!
  \brief ESP get chip id
  @return Stirng chip id
*/
/**************************************************************************/
String espGetChipId();

/**************************************************************************/
/*!
  \brief Initial SPIFFS files partition
  @return True if completed
*/
/**************************************************************************/
bool initSPIFFS();

/**************************************************************************/
/*!
  \brief list all file in partition
  @param fs
*/
/**************************************************************************/
void listFile(fs::FS &fs);

/**************************************************************************/
/*!
  \brief Read all data in file.
  @param fs SPIFFS
  @param path file directory
  @return all string in file.
*/
/**************************************************************************/
String readFile(fs::FS &fs, const char *path);

/**************************************************************************/
/*!
  \brief Write data into file. Not Append data.
  @param fs SPIFFS
  @param path file directory
  @param message All data in file.
  @return True is write completed
*/
/**************************************************************************/
bool writeFile(fs::FS &fs, const char *path, const char *message);

/**************************************************************************/
/*!
  \brief write append to file
  @param fs SPIFFS
  @param path file directory
  @param message data
  @return True is write append completed
*/
/**************************************************************************/
bool appendFile(fs::FS &fs, const char *path, const char *message);

/**************************************************************************/
/*!
  \brief rename of file in SPIFFS
  @param fs SPIFFS
  @param path1 file directory old
  @param path2 file directory new
  @return True is write append completed
*/
/**************************************************************************/
bool renameFile(fs::FS &fs, const char *path1, const char *path2);

/**************************************************************************/
/*!
  \brief delete file
  @param fs SPIFFS
  @param path file directory
  @return True is write append completed
*/
/**************************************************************************/
bool deleteFile(fs::FS &fs, const char *path);

#elif defined(ARDUINO_ARCH_AVR)

#else

#endif

#include <Wire.h>

String strLog(String x);
String strWarn(String x);
String strError(String x);

/**************************************************************************/
/*!
  \brief Split string with separator.
  @param data All string data for split.
  @param separator What you delimeter.
  @param index What index you want to return.
  @return String split in your index your want.
*/
/**************************************************************************/
String splitString(String data, char separator, int index);

uint16_t checkCRC(uint8_t *data);

/**************************************************************************/
/*!
  \brief function check time is in timer or not
  @param strNow Current time in string format "23:59"
  @param strStartTime Starting time in string format "23:59"
  @param strDuration Duration time in string format "10:00"
  @return True is in time | False is out time
*/
/**************************************************************************/
bool timerCheck(String strNow, String strStartTime, String strDuration);

/**************************************************************************/
/*!
  \brief Calculate day of week.
  @param year Year
  @param month Month
  @param day  Day
  @return Sun = 1 ... Sat = 7 //
*/
/**************************************************************************/
int dayOfWeek(uint16_t year, uint8_t month, uint8_t day);

/**************************************************************************/
/*!
  \brief Check I2C device with address
  @param addr I2C device
  @return True found device
*/
/**************************************************************************/
bool i2cCheck(uint8_t addr);

/**************************************************************************/
/*!
  \brief fix floating point to 2dicimal
  @param value
  @return value with 2dicimal
*/
/**************************************************************************/
double round2(double value);

/**************************************************************************/
/*!
  \brief copy mac address from source to destination
  @param destination
  @param source
*/
/**************************************************************************/
void copyMacAddress(uint8_t *destination, const uint8_t *source);

/**************************************************************************/
/*!
  \brief get mac address to String
  @param mac_addr
  @return String mac address
*/
/**************************************************************************/
String getMacAddressToString(const uint8_t *mac_addr);