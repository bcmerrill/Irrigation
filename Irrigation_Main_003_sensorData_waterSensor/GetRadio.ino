/*
    Communicate with RPI via NRF24
    zone (1-5), time on(1-60) or off(0)
*/

const int min_payload_size = 4;
const int max_payload_size = 32;
const int payload_size_increments_by = 1;
int next_payload_size = min_payload_size;

char receive_payload[max_payload_size + 1]; // +1 to allow room for a terminating NULL char


void GetRadio()
{
  bool tx_ok;
  bool tx_fail;
  bool rx_ready;
  radio.whatHappened(tx_ok, tx_fail, rx_ready);
  while (radio.available()) {
    //Serial.println("radio available!");

    // Fetch the payload, and see if this was the last one.
    uint8_t len = radio.getDynamicPayloadSize();

    // If a corrupt dynamic payload is received, it will be flushed
    if (!len) {
      continue;
    }

    radio.read(receive_payload, len);
    radio.flush_rx();

    // Put a zero at the end for easy printing
    receive_payload[len] = 0;

    // Spew it
    Serial.print(F("Got response size="));
    Serial.print(len);
    Serial.print(F(" value="));
    Serial.println(receive_payload);

    // First, stop listening so we can talk
    radio.stopListening();

    // Send a reply that the packet was received
    // you could also use the ACK functionality
    //
    // You might have a bit better luck delivering your message
    // if you wait for the other side to start listening first
    delay(20);
    radio.write(receive_payload, len);
    Serial.println(F("Sent response."));
    sscanf(receive_payload, "%X", &command);
    Serial.println(command, HEX);
    //DoRadioCommand();
    newCommand = true;

    // Now, resume listening so we catch the next packets.
    radio.flush_rx();
    radio.startListening();
  }
}

void SendRadio(float sensorData)
{
  bool tx_ok;
  bool tx_fail;
  bool rx_ready;
  radio.whatHappened(tx_ok, tx_fail, rx_ready);


  // First, stop listening so we can talk
  radio.stopListening();

  // Send a reply that the packet was received
  // you could also use the ACK functionality
  //
  // You might have a bit better luck delivering your message
  // if you wait for the other side to start listening first
  delay(20);
  //float datr = 101.267;
  char sensorBuffer[6];
  //float myData = 12.7;
  
  //int ret = sprintf(sensorBuffer, "%f", myData);
  dtostrf(sensorData, 6, 2, sensorBuffer);
  Serial.println(sensorBuffer);
  Serial.println(sizeof(sensorBuffer));
  for (int i = 0; i <= 6; i++) {
    Serial.print(i);
    Serial.print(" ");
    Serial.println(sensorBuffer[i]);
  }


//if (ret >= sizeof sensorBuffer) 
//{
//    /* Result was truncated - resize the buffer and retry.
//     *  
//     */
//     Serial.println("sprintf didn't work");
//}  
  radio.write(sensorBuffer, 6);
  Serial.println(F("Sent response."));
  //sscanf(receive_payload, "%X", &command);
  //Serial.println(command, HEX);
  //DoRadioCommand();
  //newCommand = true;

  // Now, resume listening so we catch the next packets.
  radio.startListening();
}
