void SetTimers()
{
  // setup Hardware PWM pinmodes to outputs low
  pinMode(sprinklerDrive, OUTPUT);  //PA8 T1_CH1 Sprinkler
  pinMode(backGardenDrive, OUTPUT);  //PA9 T1_CH2 Back Garden
  pinMode(spiceGardenDrive, OUTPUT);  //PA10 T1_CH3 Spice Garden
  pinMode(frontGardenDrive, OUTPUT);  //PB8 T4_CH3 Front Garden
  pinMode(hoseDrive, OUTPUT);         //PB9 T4_CH4 Hose

  digitalWrite(sprinklerDrive, LOW);
  digitalWrite(backGardenDrive, LOW);
  digitalWrite(spiceGardenDrive, LOW);
  digitalWrite(frontGardenDrive, LOW);
  digitalWrite(hoseDrive, LOW);

  //setup Timer 1 CH 1,2,3
  PWM1.pause();
  PWM1.setPrescaleFactor(7200); // 72MHZ/7200 = 10000
  PWM1.setOverflow(100 - 1); // 10kHZ / 100 = 100HZ period
  PWM1.setCompare(TIMER_CH1, 50);  // 50% duty cycle
  PWM1.setCompare(TIMER_CH2, 50);  // 50% duty cycle
  PWM1.setCompare(TIMER_CH3, 50);  // 50% duty cycle
  //setup Timer 2 CH 1. ~60 sec per toggle
  PWM2.pause();
  PWM2.setPrescaleFactor(65536); // 72MHZ/65536 = 1098.632HZ  1/(72000000/65536)x1099 = 1.003
  PWM2.setOverflow(1099); //  1.003 sec each overflow
  //PWM2.setOverflow(65536 - 1); //  59.652 sec each overflow
  PWM2.attachCompare1Interrupt(sixtySecondHandler);
  

  //setup Timer 4 CH 3,4
  PWM4.pause();
  PWM4.setPrescaleFactor(7200); // 72MHZ/7200 = 10000
  PWM4.setOverflow(100 - 1); // 10kHZ / 100 = 100HZ period
  PWM4.setCompare(TIMER_CH3, 50);  // 50% duty cycle
  PWM4.setCompare(TIMER_CH4, 50);  // 50% duty cycle
  
  //start timers togetherish
  PWM1.refresh();
  PWM2.refresh();
  PWM4.refresh();
  PWM4.resume();
  PWM1.resume();
  PWM2.resume();
}
