//extern bool safetyOverride = true;
//extern volatile bool myffOverRide;
int safteyOverride = 1;
void AllOnCMD(void)
{
  PumpOnCMD();
  SprinklerOnCMD();
  FrontGardenOnCMD();
  BackGardenOnCMD();
  HoseOnCMD();
  SpiceGardenOnCMD();
  
}

void AllOffCMD(void)
{
  PumpOffCMD();
  SprinklerOffCMD();
  FrontGardenOffCMD();
  BackGardenOffCMD();
  HoseOffCMD();
  SpiceGardenOffCMD();
}

void PumpOnCMD(void)
{
  if(safteyOverride)
  {
    digitalWrite(pumpDrive, LOW);
    pumpState = true;
    Serial.println("logic pump On");
  }
  else
  {   // makes sure that at least one valve is open, and both water is present and pressure isn't too high
    if((hoseState || spiceGardenState || backGardenState || frontGardenState || sprinklerState) && waterLevel && pressureLevel )
    {
      digitalWrite(pumpDrive, LOW);
      pumpState = true;
    }
  }
}

void PumpOffCMD(void)
{
  digitalWrite(pumpDrive, HIGH);
  pumpState = false;
}

void SprinklerOnCMD(void)
{
  digitalWrite(sprinklerDrive,LOW);
  sprinklerState = true;
}
void SprinklerOffCMD(void)
{
  digitalWrite(sprinklerDrive,HIGH);
  sprinklerState = false;
}
void BackGardenOnCMD(void)
{
  digitalWrite(backGardenDrive,LOW);
  backGardenState = true;
}
void BackGardenOffCMD(void)
{
  digitalWrite(backGardenDrive,HIGH);
  backGardenState = false;
}
void FrontGardenOnCMD(void)
{
  digitalWrite(frontGardenDrive,LOW);
  frontGardenState = true;
}
void FrontGardenOffCMD(void)
{
  digitalWrite(frontGardenDrive,HIGH);
  frontGardenState = false;
}
void SpiceGardenOnCMD(void)
{
  digitalWrite(spiceGardenDrive,LOW);
  spiceGardenState = true;
}
void SpiceGardenOffCMD(void)
{
  digitalWrite(spiceGardenDrive,HIGH);
  spiceGardenState = false;
}
void HoseOnCMD(void)
{
  digitalWrite(hoseDrive,LOW);
  hoseState = true;
}
void HoseOffCMD(void)
{
  digitalWrite(hoseDrive,HIGH);
  hoseState = false;
}
