
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void SetupRadio(void)
{
  //
  // Print preamble
  //
  Serial.begin(115200);
  //printf_begin();
  delay(5000);

  //
  // Setup and configure rf radio
  //
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  // Enable dynamic payloads
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_HIGH, 1);

  // Optionally, increase the delay between retries & # of retries
  radio.setRetries(5, 15);


  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
 
  // Start listening
  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //
  radio.printDetails();
  Serial.print("radio channel: ");
  Serial.println(radio.getChannel());
}
