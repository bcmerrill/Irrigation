//Zone Commands
const uint16_t allOff = 0x00;
const uint16_t allOn = 0xFF;

const uint16_t pumpOn = 0x11;
const uint16_t pumpOff = 0x01;

const uint16_t sprinklerOn = 0x12;
const uint16_t sprinklerOff = 0x02;

const uint16_t BackGardenOn = 0x13;
const uint16_t BackGardenOff = 0x03;

const uint16_t FrontGardenOn = 0x14;
const uint16_t FrontGardenOff = 0x04;

const uint16_t SpiceGardenOn = 0x15;
const uint16_t SpiceGardenOff = 0x05;

const uint16_t HoseOn = 0x16;
const uint16_t HoseOff = 0x06;

//System Commands
const uint16_t resetCmd = 0xAA;
//Sensor Commands
const uint16_t GetFlowRateCmd = 0x25;
const uint16_t GetWaterPressureCmd = 0x21;
//const uint16_t GetTempCmd = 0x22;
//const uint16_t GetHumidityCmd = 0x23;
const uint16_t GetWaterStateCmd = 0x24;
//const uint16_t GetLightCmd = 0x25;
//const uint16_t GetAmbientPressureCmd = 0x26;
//const uint16_t GetDitchFlowCmd = 0x27;


void DoCommand()
{
  if (newCommand)
  {
    newCommand = false;
    switch (command)
    {
      case allOn:
        Serial.println(allOn);
        Serial.println("allOn");
        AllOnCMD();
        break;
      case allOff:
        Serial.println(allOff);
        Serial.println("allOff");
        AllOffCMD();
        break;
      case pumpOn:
        Serial.println(pumpOn);
        Serial.println("pumpOn");
        PumpOnCMD();
        break;
      case pumpOff:
        Serial.println(pumpOff);
        Serial.println("pumpOff");
        PumpOffCMD();
        break;
      case sprinklerOn:
        Serial.println(sprinklerOn);
        Serial.println("sprinklerOn");
        SprinklerOnCMD();
        break;
      case sprinklerOff:
        Serial.println(sprinklerOff);
        Serial.println("sprinklerOff");
        SprinklerOffCMD();
        break;
      case BackGardenOn:
        Serial.println(BackGardenOn);
        Serial.println("BackGardenOn");
        BackGardenOnCMD();
        break;
      case BackGardenOff:
        Serial.println(BackGardenOff);
        Serial.println("BackGardenOff");
        BackGardenOffCMD();
        break;
      case FrontGardenOn:
        Serial.println(FrontGardenOn);
        Serial.println("FrontGardenOn");
        FrontGardenOnCMD();
        break;
      case FrontGardenOff:
        Serial.println(FrontGardenOff);
        Serial.println("FrontGardenOff");
        FrontGardenOffCMD();
        break;
      case SpiceGardenOn:
        Serial.println(SpiceGardenOn);
        Serial.println("SpiceGardenOn");
        SpiceGardenOnCMD();
        break;
      case SpiceGardenOff:
        Serial.println(SpiceGardenOff);
        Serial.println("SpiceGardenOff");
        SpiceGardenOffCMD();
        break;
      case HoseOn:
        Serial.println(HoseOn);
        Serial.println("HoseOn");
        HoseOnCMD();
        break;
      case HoseOff:
        Serial.println(HoseOff);
        Serial.println("HoseOff");
        HoseOffCMD();
        break;

      case GetWaterPressureCmd:
        Serial.println(GetWaterPressureCmd);
        Serial.println("GetWaterPressureCmd");
        GetWaterPressure();
        SendRadio(waterPressure);
        break;

      case GetWaterStateCmd:
        Serial.println(GetWaterStateCmd);
        Serial.println("GetWaterStateCmd");
        GetWaterState();
        SendRadio(waterLevel);
        break;

      case GetFlowRateCmd:
        Serial.println(GetFlowRateCmd);
        Serial.println("GetFlowRateCmd");
        GetFlowRate();
        SendRadio(flowRate);
        break;
        
//      case GetTempCmd:
//        Serial.println(HoseOff);
//        Serial.println("HoseOff");
//        HoseOffCMD();
//        break;
//      case GetHumidityCmd:
//        Serial.println(HoseOff);
//        Serial.println("HoseOff");
//        HoseOffCMD();
//        break;
//      case GetWaterStateCmd:
//        Serial.println(HoseOff);
//        Serial.println("HoseOff");
//        HoseOffCMD();
//        break;
//      case GetLightCmd:
//        Serial.println(HoseOff);
//        Serial.println("HoseOff");
//        HoseOffCMD();
//        break;
//      case GetAmbientPressureCmd:
//        Serial.println(HoseOff);
//        Serial.println("HoseOff");
//        HoseOffCMD();
//        break;
//      case GetDitchFlowCmd:
//        Serial.println(HoseOff);
//        Serial.println("HoseOff");
//        HoseOffCMD();
//        break;









    }
  }
}
