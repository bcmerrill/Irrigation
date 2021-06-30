/*
  // https://www.amazon.com/gp/product/B0748BHLQL/ref=ppx_yo_dt_b_asin_title_o06_s04?ie=UTF8&psc=1
  //Pressure sensor
  // 100psi
  //.5-4.5v,
  //3.3v drive->  .33- 2.97v maybe?
  //12 bit ADC ->4096
  //37.87 pressure constant

  //https://www.amazon.com/gp/product/B00VKAT50U/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
  // flow rate sensor
  //F=0.5Q(l/min)
  //2×number of pulses per second = liters/ minute

  https://www.aliexpress.com/item/32916856751.html?spm=a2g0s.9042311.0.0.27424c4d2JCpHn
  optical water level sensor
  130mV or so when there is water
  3.2v or so when there is no water
  condensation could be an issue
  50k load resistor (significant signal loss to lower voltage)

*/
void GetWaterPressure(void)
{
  //returns the value of the pressure sensor in psi
  float pressureCount = analogRead(pressureSensorPin);
  float pressureVoltage = (pressureCount / 4095) * driveVoltage;
  float pressure = pressureConstant * (pressureVoltage - .33);
  waterPressure = pressure;
  if(pressure > pressureSetPointHigh)
  {
    pressureLevel = false;
  }
  else if (pressure < pressureSetPointLow)
  {
    pressureLevel = true;
  }
}

float GetFlowRate()
{
  durationHigh = pulseIn(flowRateSensorPin, HIGH,1500000);
//  if (durationHigh == 0)
//  {
//    Serial.println("high  0");
//  }
  durationLow = pulseIn(flowRateSensorPin, LOW,1500000);
//  if (durationLow == 0)
//  {
//    Serial.println("low  0");
//  }
  frequency = 1000000000 / (durationHigh + durationLow);
  frequency = frequency/1000;
  LPM = frequency * 2;
  flowRate = LPM;
  
}
/*
 * 
 */
void FlowDetected()
{
  startTime = stopTime;
  stopTime = millis();
  pulseLength = startTime - stopTime;
  freq = 1000 / pulseLength;
  lpm = 2 * freq;

}
/*
   checks ADC pin for voltage on optical water sensor. If there is no water, IR light TIRs and turns on phototransistor hard, creating high signal.
   If there is water, IR light does not TIR, and photodiode is only on slightly (Dark Current, etc)
   Testing with 3.3v, 330R LED, 3.3v phototransitor collector, 50k load in glass of water:
   out of water - 3.23v
   in water- 134mV
   single drop on optic - 3.22
   all 4 faces with a single droplet 3.02
   condensation (lots of little droplets) not tested
   Dirty water not tested
*/
void GetWaterState(void)
{
   
 float waterCount = analogRead(waterSensorPin);
 float waterVoltage = driveVoltage * (waterCount/4095.00);
 Serial.print("waterCount, waterVoltage: ");
 Serial.print(waterCount);
  Serial.print(", ");
 Serial.println(waterVoltage);
  if (waterVoltage > waterSpHigh)
  {
    waterLevel =  false;
  }
  else if (waterVoltage < waterSpLow)
  {
    waterLevel = true;
  }

}
