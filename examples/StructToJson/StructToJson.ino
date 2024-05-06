#include <ArduinoJson.h>

// Function to convert struct to JSON string
template <typename T>
String structToJson(const T &data, const char *fieldNames[], const void *fieldPointers[], size_t numFields)
{
  // Create a JSON object
  DynamicJsonDocument doc(200);

  // Serialize the struct fields into the JSON object
  JsonObject obj = doc.to<JsonObject>();
  for (size_t i = 0; i < numFields; ++i)
  {
    // Cast the pointer to the correct type
    if (const int *intValue = static_cast<const int *>(fieldPointers[i]))
    {
      obj[fieldNames[i]] = *intValue;
    }
    else if (const float *floatValue = static_cast<const float *>(fieldPointers[i]))
    {
      obj[fieldNames[i]] = *floatValue;
    } // Add more types if necessary
  }

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(doc, jsonString);

  return jsonString;
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // Define your struct
  struct SensorData
  {
    int temperature;
    int humidity;
    float pressure;
  };

  // Create an instance of SensorData
  SensorData sensorData = {25, 50, 1013.25};

  // Define field names and pointers to fields
  const char *fieldNames[] = {"temperature", "humidity", "pressure"};
  const void *fieldPointers[] = {&sensorData.temperature, &sensorData.humidity, &sensorData.pressure};

  // Convert struct to JSON string
  String jsonStr = structToJson(sensorData, fieldNames, fieldPointers, 3); // 3 is the number of fields

  // Print JSON string
  Serial.println(jsonStr);
}

void loop()
{
  // Nothing here for this example
}
