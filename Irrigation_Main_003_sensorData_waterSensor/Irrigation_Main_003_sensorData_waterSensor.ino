
/*Zone 1: sprinklers
   Zone 2: Back Garden
   Zone 3: Spice Garden
   Zone 4: Front Garden
   Zone 5: Hose

   Purpose:
   RPI with RTC & internet has chron jobs to send commands to arduino over NRF24/LORA .user can also log in to manually send commands over GUI/ command prompt
   
   Arduino runs those commands
   commands:
   get sprinkler states
   turn on spinkler x for y amount of time
   turn on all sprinklers
   turn off all sprinklers
   solenoid always turns on first, then pump

   always checking water level & water pressure
   


*/
// there are only 4 timers for stm32. what does millis, pulsein & SPI use?
HardwareTimer PWM1(1);  //direct hardware toggle for solenoid drive
HardwareTimer PWM2(2);  //interrupt driven output compare (flow rate freq) not currently used, since pulsein is used
HardwareTimer PWM4(4);  //direct hardware toggle for solenoid drive


//HardwareTimer Timer3(3);  // Heartbeat?
#include <libmaple/iwdg.h>
#include <SPI.h>
//#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h"


// defines constants
#define ledRate 500000 //500ms
float driveVoltage = 3.30;
float pressureConstant = 37.87;


// bools
bool heartBeatState = false;
volatile bool int1State = false;
volatile bool int2State = false;
bool safteyError = false;
int safetyOverride = 1;    //as a bool it gets changed during other button presses
//int myffOverRide = 1;    
bool waterLevel = false;
bool pressureLevel = false;

bool pumpState = false;
bool sprinklerState = false;
bool frontGardenState = false;
bool backGardenState = false;
bool spiceGardenState = false;
bool hoseState = false;
bool newCommand = false;
bool toggle = false;


// flow rate stuff
// #define flowRateSensorPin PA15  already defined
unsigned long durationHigh;
unsigned long durationLow;
float frequency;
float LPM;
float flowRate;


//vars Imm not really sure about. could be junk
int stopTime = 0;
int startTime = 0;
int period = 1000;
int pulseLength = 0;
float freq = 0;
float lpm = 0;
int count;
float waterSpLow = 1.5 ;
float waterSpHigh = 2 ;
float pressureSetPointHigh = 60;
float pressureSetPointLow = 55;
float waterPressure;
float sensorData;

// defines pin numbers for solenoid drives (Hardware PWM)
#define sprinklerDrive PA8      //PA8 T1_CH1 Sprinkler       Zone1
#define backGardenDrive PB8     //PA9 T1_CH2 Back Garden     Zone2
#define spiceGardenDrive PA10   //PA10 T1_CH3 Spice Garden   Zone3
#define frontGardenDrive PA9   //PB8 T4_CH3 Front Garden    Zone4
#define hoseDrive PB9           //PB9 T4_CH4 Hose            Zone5
#define extra1 PB14
#define extra2 PB15

// defines pin numbers for pump
#define pumpDrive PB1  //On off only

// defines pin numbers for ADC
#define pressureSensorPin PB0
#define flowRateSensorPin PA15
#define waterSensorPin PA0

// Defines other pin Numbers
#define heartBeat PC13

// Radio stuff
#define CE PA4
#define CSN PB10
// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins PA3, PA4 (CE, CSN)
RF24 radio(CE, CSN);
uint16_t command = 0x1F;








//----------------------------------------------------------------------------------------------------------------
void setup(void)
{
  //Initialize watchdog
  iwdg_init(IWDG_PRE_256, 1250); // prescaler, rollover (1/40kHz clk*256 * 1250 ->init an 8 second wd timer
  SetTimers();
  Serial.begin(115200);
  
  //setup inputs
  pinMode(flowRateSensorPin, INPUT);
  pinMode(pressureSensorPin, INPUT);
  pinMode(waterSensorPin, INPUT);
  
  // setup outputs
  pinMode(heartBeat, OUTPUT);
  pinMode(pumpDrive, OUTPUT);
  
  // solenoid control outputs
  pinMode(sprinklerDrive, OUTPUT);
  pinMode(backGardenDrive, OUTPUT);
  pinMode(spiceGardenDrive, OUTPUT);
  pinMode(frontGardenDrive, OUTPUT);
  pinMode(hoseDrive, OUTPUT);
  pinMode(extra1, OUTPUT);
  pinMode(extra2, OUTPUT);
  //pinMode(PC13, OUTPUT);
  
  //make sure all outputs are High (optoisolator is active LOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
  digitalWrite(heartBeat, HIGH);
  digitalWrite(sprinklerDrive, HIGH);
  digitalWrite(backGardenDrive, HIGH);
  digitalWrite(spiceGardenDrive, HIGH);
  digitalWrite(frontGardenDrive, HIGH);
  digitalWrite(hoseDrive, HIGH);
  digitalWrite(pumpDrive, HIGH);
  digitalWrite(extra1, HIGH);
  digitalWrite(extra2, HIGH);

  digitalWrite(heartBeat, HIGH);
  delay(500);
  digitalWrite(heartBeat, LOW);
  delay(500);
  digitalWrite(heartBeat, HIGH);
  delay(500);
  digitalWrite(heartBeat, LOW);

  SetupRadio();
}

void loop(void)
{
  //GetWaterLevel();
  //GetWaterPressure();
  //SafteyStates();
  //Serial.println(myffOverRide);
  GetRadio();
  iwdg_feed();
  DoCommand();
  //Serial.println("running");
  delay(500);
}

    
void RunZone( unsigned char zone, int runTime)
{
//PA8 T1_CH1 Sprinkler       Zone1
//PA9 T1_CH2 Back Garden     Zone2
//PA10 T1_CH3 Spice Garden   Zone3
//PB8 T4_CH3 Front Garden    Zone4
//PB9 T4_CH4 Hose            Zone5
  //turn on pump and zone (zone) 1-5 for time (runTime)
  //pinMode(zone, HIGH);
  
}

void StopAll()
{
  //Turn off pumps and all zones

}

void sixtySecondHandler(void)
{
  count++;
  digitalWrite(PC13,toggle);
  toggle = !toggle;
}
