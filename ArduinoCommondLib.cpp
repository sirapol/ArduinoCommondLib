#include "ArduinoCommondLib.h"

#ifdef ARDUINO_ARCH_ESP32
ESP32Time esp32Rtc(60 * 60 * TIME_OFFSET);

/**************************************************************************/
/*!
  \brief ESP get chip id
  @return Stirng chip id
*/
/**************************************************************************/
String espGetChipId()
{
    uint32_t chipId = 0;
#ifdef ESP32
    for (int i = 0; i < 17; i = i + 8)
    {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
#endif
    return String(chipId);
}

/**************************************************************************/
/*!
  \brief Initial SPIFFS files partition
  @return True if completed
*/
/**************************************************************************/
bool initSPIFFS()
{
    if (!SPIFFS.begin(true))
    {
        // USB_SERIAL.println("An error has occurred while mounting SPIFFS");
        return false;
    }
    // USB_SERIAL.println("SPIFFS mounted successfully");
    // USB_SERIAL.println("SPIFFS total=" + String(SPIFFS.totalBytes()));
    // USB_SERIAL.println("SPIFFS used" + String(SPIFFS.usedBytes()));
    // USB_SERIAL.println("SPIFFS free" + String(SPIFFS.totalBytes() - SPIFFS.usedBytes()));
    // listFile(SPIFFS);
    return true;
}

/**************************************************************************/
/*!
  \brief list all file in partition
  @param fs
*/
/**************************************************************************/
void listFile(fs::FS &fs)
{
    // ls spiffs
    File root = fs.open("/");
    File file = root.openNextFile();
    if (file)
    {
        while (file)
        {
            USB_SERIAL.print("FILE: ");
            USB_SERIAL.println(file.name());
            file = root.openNextFile();
        }
    }
    else
    {
        USB_SERIAL.println("File not found");
    }
}
/**************************************************************************/
/*!
  \brief list all file in partition
  @param fs
  @param dirname
  @param levels
*/
/**************************************************************************/
void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    USB_SERIAL.printf("Listing directory: %s\n", dirname);
    File root = fs.open(dirname);
    if (!root)
    {
        USB_SERIAL.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        USB_SERIAL.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            USB_SERIAL.print("  DIR : ");
            USB_SERIAL.println(file.name());
            if (levels)
            {
                listDir(fs, file.name(), levels - 1);
            }
        }
        else
        {
            USB_SERIAL.print("  FILE: ");
            USB_SERIAL.print(file.name());
            USB_SERIAL.print("  SIZE: ");
            USB_SERIAL.println(file.size());
        }
        file = root.openNextFile();
    }
}


/**************************************************************************/
/*!
  \brief list all file in partition
  @param fs
  @param path
*/
/**************************************************************************/
void createDir(fs::FS &fs, const char * path){
  USB_SERIAL.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    USB_SERIAL.println("Dir created");
  } else {
    USB_SERIAL.println("mkdir failed");
  }
}


/**************************************************************************/
/*!
  \brief list all file in partition
  @param fs
  @param path
*/
/**************************************************************************/
void removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

/**************************************************************************/
/*!
  \brief Read all data in file.
  @param fs SPIFFS
  @param path file directory
  @return all string in file.
*/
/**************************************************************************/
String readFile(fs::FS &fs, const char *path)
{
    // Serial.printf("Reading file: %s\r\n", path);
    File file = fs.open(path);
    if (!file || file.isDirectory())
    {
        // Serial.println("- failed to open file for reading");
        return String();
    }
    String fileContent;
    // USB_SERIAL.println("file.available()=" + String(file.available()));
    while (file.available())
    {
        fileContent = fileContent + file.readString();
    }
    return fileContent;
}

/**************************************************************************/
/*!
  \brief Write data into file. Not Append data.
  @param fs SPIFFS
  @param path file directory
  @param message All data in file.
  @return True is write completed
*/
/**************************************************************************/
bool writeFile(fs::FS &fs, const char *path, const char *message)
{
    // Serial.printf("Writing file: %s\r\n", path);
    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        // Serial.println("- failed to open file for writing");
        return false;
    }
    if (file.print(message))
    {
        // USB_SERIAL.println("- file written");
        return true;
    }
    else
    {
        // USB_SERIAL.println("- write failed");
        return false;
    }
}

/**************************************************************************/
/*!
  \brief write append to file
  @param fs SPIFFS
  @param path file directory
  @param message data
  @return True is write append completed
*/
/**************************************************************************/
bool appendFile(fs::FS &fs, const char *path, const char *message)
{
    USB_SERIAL.printf("Appending to file: %s\r\n", path);
    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        USB_SERIAL.println("− failed to open file for appending");
        return false;
    }
    if (file.print(message))
    {
        USB_SERIAL.println("− message appended");
        return true;
    }
    else
    {
        USB_SERIAL.println("− append failed");
        return false;
    }
}

/**************************************************************************/
/*!
  \brief rename of file in SPIFFS
  @param fs SPIFFS
  @param path1 file directory old
  @param path2 file directory new
  @return True is write append completed
*/
/**************************************************************************/
bool renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    USB_SERIAL.printf("Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2))
    {
        USB_SERIAL.println("− file renamed");
        return true;
    }
    else
    {
        USB_SERIAL.println("− rename failed");
        return false;
    }
}

/**************************************************************************/
/*!
  \brief delete file
  @param fs SPIFFS
  @param path file directory
  @return True is write append completed
*/
/**************************************************************************/
bool deleteFile(fs::FS &fs, const char *path)
{
    USB_SERIAL.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path))
    {
        USB_SERIAL.println("− file deleted");
        return true;
    }
    else
    {
        USB_SERIAL.println("− delete failed");
        return false;
    }
}

#elif defined(ARDUINO_ARCH_AVR)

#else

#endif

String strLog(String x)
{
    return "Log:" + x;
}

String strWarn(String x)
{
    return "Warning:" + x;
}

String strError(String x)
{
    return "Error:" + x;
}

/**************************************************************************/
/*!
  \brief Split string with separator.
  @param data All string data for split.
  @param separator What you delimeter.
  @param index What index you want to return.
  @return String split in your index your want.
*/
/**************************************************************************/
String splitString(String data, char separator, int index)
{
    /* How 2 use
     *  String x = splitString(data,',',0);
     */
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

uint16_t checkCRC(uint8_t *data)
{
    uint16_t sizeData = sizeof(data);
    return sizeData;
}

/**************************************************************************/
/*!
  \brief function check time is in timer or not
  @param strNow Current time in string format "23:59"
  @param strStartTime Starting time in string format "23:59"
  @param strDuration Duration time in string format "10:00"
  @return True is in time | False is out time
*/
/**************************************************************************/
bool timerCheck(String strNow, String strStartTime, String strDuration)
{
    // timer check
    uint8_t iStartHH = splitString(strStartTime, ':', 0).toInt();
    uint8_t iStartMM = splitString(strStartTime, ':', 1).toInt();
    uint8_t iDurationHH = splitString(strDuration, ':', 0).toInt();
    uint8_t iDurationMM = splitString(strDuration, ':', 1).toInt();
    uint8_t iNowHH = splitString(strNow, ':', 0).toInt();
    uint8_t iNowMM = splitString(strNow, ':', 1).toInt();
    uint16_t iStartSum = (iStartHH * 60) + iStartMM;
    uint16_t iDurationSum = (iDurationHH * 60) + iDurationMM;
    uint16_t iNowSum = (iNowHH * 60) + iNowMM;
    uint16_t iEndSum = iStartSum + iDurationSum;

    if ((iEndSum) > (23 * 60 + 59))
    {
        iEndSum = iEndSum - 1439;
        if (iNowSum > iStartSum || iNowSum < iEndSum)
            return true;
        else
            return false;
    }
    else
    {
        if (iNowSum > iStartSum && iNowSum < iEndSum)
            return true;
        else
            return false;
    }
}

/**************************************************************************/
/*!
  \brief Calculate day of week.
  @param year Year
  @param month Month
  @param day  Day
  @return Sun = 1 ... Sat = 7 //
 */
/**************************************************************************/
int dayOfWeek(uint16_t year, uint8_t month, uint8_t day)
{
    uint16_t months[] =
        {
            0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 // days until 1st of month
        };
    // sanity checks for input
    if (year > 65000)
        return 0; // to prevent rollover of intermediate variables
    if ((month < 1) || (month > 12))
        return 0;
    if ((month == 2) && (day == 29))
    { // special case leap day
        if ((year % 4) > 0)
            return 0;
        if (((year % 100) == 0) && ((year % 400) > 0))
            return 0;
    }
    else
    {
        if (day == 0)
            return 0;
        if (day > (months[month] - months[month - 1]))
            return 0;
    }
    uint32_t days = year * 365; // days before given year (ignoring leap days)
    uint16_t febs = year;
    if (month > 2)
        febs++; // number of completed Februaries
    // add in the leap days
    days += ((febs + 3) / 4);
    days -= ((febs + 99) / 100);
    days += ((febs + 399) / 400);
    days += months[month - 1] + day;
    // now we have day number such that 0000-01-01(Sat) is day 1
    // return ((days + 4) % 7) + 1; // for Mon = 1 ... Sun = 7
    return ((days + 5) % 7) + 1; // for Sun = 1 ... Sat = 7
}

/**************************************************************************/
/*!
  \brief Check I2C device with address
  @param addr I2C device
  @return True found device
*/
/**************************************************************************/
bool i2cCheck(uint8_t addr)
{
    USB_SERIAL.printf("I2C Checl : 0x%x",addr);
    uint8_t error = 4;
    Wire.beginTransmission(addr);
    error = Wire.endTransmission();
    if (error == 0)
    {
        USB_SERIAL.printf("\tFound\r\n");
        return true;
    }
    else
    {
        USB_SERIAL.printf("\tNot Found\r\n");
        return false;
    }
}

/**************************************************************************/
/*!
  \brief fix floating point to 2dicimal
  @param value
  @return value with 2dicimal
*/
/**************************************************************************/
double round2(double value)
{
    return (int)(value * 100 + 0.5) / 100.0;
}

/**************************************************************************/
/*!
  \brief fix floating point to 2dicimal
  @param destination
  @param source
*/
/**************************************************************************/
void copyMacAddress(uint8_t *destination, const uint8_t *source)
{
    for (int i = 0; i < 6; i++)
    {
        destination[i] = source[i];
    }
}

String getMacAddressToString(const uint8_t *mac_addr)
{
    char addr[18]; // MAC address is 6 bytes, each byte is represented by 2 characters (hexadecimal) and 5 colons in between
    sprintf(addr, "%02X:%02X:%02X:%02X:%02X:%02X",
            mac_addr[0], mac_addr[1], mac_addr[2],
            mac_addr[3], mac_addr[4], mac_addr[5]);
    String strAddr = String(addr);
    return strAddr;
}