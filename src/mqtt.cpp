#include "mqtt.h"

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

bool mqtt_start(void) {
  int8_t ret;
  if (mqtt.connected()) return true;
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = RETRIES;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0) {
         log_e("COULD NOT CONNECT TO MQTT");
         return false;
       }
  }
  Serial.println("MQTT Connected!");
  return true;
}

bool mqtt_publish(String msg, String topic)
{
  Adafruit_MQTT_Publish package_pub = Adafruit_MQTT_Publish(&mqtt, topic.c_str(), MQTT_QOS_1);
  log_i("TOPIC: %s, MESSAGE: %s", topic.c_str(), msg.c_str());
  // Publish to topic
  for(uint8_t retry_counter = 0; retry_counter < 10; retry_counter++){
    if(!mqtt_reconnect()) return false;
    bool status = package_pub.publish(msg.c_str());
    delay(WAIT_BETWEEN_PUBLISHES);
    if(status == true) break;
    else{
      if(retry_counter >= 9) {
        log_e("FAILED TO DELIVER MQTT MESSAGE.");
        return false;
      }
      log_e("FAILED TO DELIVER MQTT MESSAGE, RETRYING...");
    }
  }
  return true;
}

void mqtt_disconnect(void){
  mqtt.disconnect();
  log_i("MQTT DISCONNECTED");
}

bool mqtt_reconnect(){
  if(!mqtt.connected()){
    if(modem.isNetworkConnected()){
      for(uint8_t mqtt_con_retry = 0; mqtt_con_retry < 10; mqtt_con_retry++){
        if (mqtt.connect() == 0){ // 0: success, otherwise not connected
          log_i("MQTT RECONNECTED");
          return true;
        }
        else if(mqtt_con_retry >= 9) {
          log_e("COULD NOT RECONNECT TO MQTT");
          return false;
          }
        delay(5000);
      }
    }
    else{ 
      log_e("NETWORK DISCONNECTED DURING MESSAGE SEND");
      return false;
    }
  }
  return true;
}
