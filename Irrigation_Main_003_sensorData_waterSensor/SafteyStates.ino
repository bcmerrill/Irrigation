void SafteyStates(void)
{ // if any valves turn off, or the water level drops, or pressure drops, turn off the pump!
  if ((hoseState || spiceGardenState || backGardenState || frontGardenState || sprinklerState) && waterLevel && pressureLevel )
  {

    safteyError = false;
  }
  else
  {
    PumpOffCMD();
    safteyError = true;
  }
}
