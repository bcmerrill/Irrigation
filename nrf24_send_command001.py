#!/usr/bin/env python

#
# Example using Dynamic Payloads
# 
#  This is an example of how to use payloads of a varying (dynamic) size.
# 

from __future__ import print_function
import time
from RF24 import *
import RPi.GPIO as GPIO

irq_gpio_pin = None

########### USER CONFIGURATION ###########
# See https://github.com/TMRh20/RF24/blob/master/pyRF24/readme.md
# Radio CE Pin, CSN Pin, SPI Speed
# CE Pin uses GPIO number with BCM and SPIDEV drivers, other platforms use their own pin numbering
# CS Pin addresses the SPI bus number at /dev/spidev<a>.<b>
# ie: RF24 radio(<ce_pin>, <a>*10+<b>); spidev1.0 is 10, spidev1.1 is 11 etc..

# Generic:
radio = RF24(24,0);

# RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
#radio = RF24(22, 0);


# Setup for connected IRQ pin, GPIO 24 on RPi B+; uncomment to activate
# irq_gpio_pin = 24

##########################################
def try_read_data(channel=0):
    if radio.available():
        while radio.available():
            len = radio.getDynamicPayloadSize()
            receive_payload = radio.read(len)
            print('Got payload size={} value="{}"'.format(len, receive_payload.decode('utf-8')))
            # First, stop listening so we can talk
            radio.stopListening()

            # Send the final one back.
            radio.write(receive_payload)
            print('Sent response.')

            # Now, resume listening so we catch the next packets.
            radio.startListening()


pipes = [0xF0F0F0F0E1, 0xF0F0F0F0D2]
min_payload_size = 4
max_payload_size = 32
payload_size_increments_by = 1
next_payload_size = min_payload_size
inp_role = '1'
send_payload = b'ABCDEFGHIJKLMNOPQRSTUVWXYZ789012'
millis = lambda: int(round(time.time() * 1000))

print('pyRF24/examples/pingpair_dyn/')
radio.begin()
radio.setDataRate(RF24_250KBPS);
radio.enableDynamicPayloads()
radio.setChannel(76);
radio.setRetries(5, 15)
radio.setPALevel(RF24_PA_HIGH,1)
radio.printDetails()

radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1, pipes[1])
#radio.startListening()


# forever loop
def SendCommand(command):
    
    # The payload will always be the same, what will change is how much of it we send.

    # First, stop listening so we can talk.
    # tx_ds, tx_df, rx_dr = radio.whatHappened()  # get IRQ status flags
    # print("tx_ds: {}, tx_df: {}, rx_dr: {}".format(tx_ds, tx_df, rx_dr))
    while (radio.available()):
            len = radio.getDynamicPayloadSize()
            junk = radio.read(len)
            print('got first junk response size={} value="{}"'.format(len, junk.decode('utf-8')))
    radio.stopListening()
    #radio.flush_rx()
    # Take the time, and send it.  This will block until complete
    print('Now sending command {} ... '.format(command), end="")
    radio.write(command)

    # Now, continue listening
    radio.startListening()

    # Wait here until we get a response, or timeout
    started_waiting_at = millis()
    timeout = False
    while (not radio.available()) and (not timeout):
        if (millis() - started_waiting_at) > 1000:
            timeout = True

    # Describe the results
    if timeout:
        print('failed, response timed out.')
        while (radio.available()):
            len = radio.getDynamicPayloadSize()
            junk = radio.read(len)
            print('got second junk response size={} value="{}"'.format(len, junk.decode('utf-8')))
    else:
        # Grab the response, compare, and send to debugging spew
        len = radio.getDynamicPayloadSize()
        receive_payload = radio.read(len)

        # Spew it
        print('got response size={} value="{}"'.format(len, receive_payload.decode('utf-8')))
        while (radio.available()):
            len = radio.getDynamicPayloadSize()
            junk = radio.read(len)
            print('got third junk response size={} value="{}"'.format(len, junk.decode('utf-8')))

    # Update size for next time.
    # next_payload_size += payload_size_increments_by
    # if next_payload_size > max_payload_size:
    #     next_payload_size = min_payload_size
    time.sleep(0.1)

def GetSensor():
    
    # Now, continue listening
    radio.startListening()

    # Wait here until we get a response, or timeout
    started_waiting_at = millis()
    timeout = False
    while (not radio.available()) and (not timeout):
        if (millis() - started_waiting_at) > 1000:
            timeout = True

    # Describe the results
    if timeout:
        print('failed, response timed out.')
        return 999
    else:
        # Grab the response, compare, and send to debugging spew
        len = radio.getDynamicPayloadSize()
        receive_payload = radio.read(len)
        #sensorMessage = receive_payload.decode('utf-8')

        # Spew it
        print(receive_payload)
        try:
            sensorMessage = receive_payload.decode('utf-8')
            print('got response size={} value="{}"'.format(len, sensorMessage))

        except:
            print('ya fucked')
    time.sleep(0.1)
    # Update size for next time.
    # next_payload_size += payload_size_increments_by
    # if next_payload_size > max_payload_size:
    #     next_payload_size = min_payload_size
    #
    return sensorMessage
    
