/* This code aims to periodically send CAN messages with a specific ID (0x222) and a two-byte payload (incrementing characters starting from '0') over the CAN bus. It uses serial communication for debugging messages and toggles an LED to provide a visual indication of message transmission. */

#include <Arduino.h>
#include <FlexCAN.h>

int led = 13;
// Create CAN object
FlexCAN CANTransmitter(500000);
/*the above line is supposed to be correct as typically the baud rate parameter 
should be an 'unsigned long' or 'uint, but in this case my IDE is giving the error:
unsigned conversion from 'int' to 'uint8_t' {aka 'unsigned char'} changes value from '500000' to '32' [-Woverflow].
If this problem persists, you can try uncommenting the following line, to cast the baud rate to the expected type.
BUT this shouldn't be necessary under normal circumstances 
 */ 
// FlexCAN CANTransmitter((uint32_t)500000);

static CAN_message_t msg;

void setup() {
  // Init CAN bus
  CANTransmitter.begin();
  pinMode(led, OUTPUT);
  delay(1000);
  Serial.begin(9600);
  Serial.println("CAN Transmitter Initialized");
}

void loop() {
  Serial.print("Sending: ");
  msg.id = 0x222; // data length of 2 bytes
  msg.len = 2;
  for(int i = 0; i < msg.len; i++) {
    msg.buf[i] = '0' + i; // Correctly assign values to positions in the array
    Serial.print((char)msg.buf[i]); Serial.print(" "); // Cast to char for correct printing
  }
  Serial.println("");
  CANTransmitter.write(msg);
  digitalWrite(led, !digitalRead(led));
  delay(500);
}