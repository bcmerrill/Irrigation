

import tkinter as tk
import nrf24_send_command001 as NRF
import time
#enums dont work 

allOff = b'00'
allOn = b'FF'

pumpOn = b'11'
pumpOff = b'01'

sprinklerOn = b'12'
sprinklerOff = b'02'

BackGardenOn = b'13'
BackGardenOff = b'03'

FrontGardenOn = b'14'
FrontGardenOff = b'04'

SpiceGardenOn = b'15'
SpiceGardenOff = b'05'

HoseOn = b'16'
HoseOff = b'06'

resetCmd = b'AA'

GetWaterStateCMD = b'24'
GetWaterPressureCMD = b'21'
#GetHumidityCMD = b'22'
#GetTempCMD = b'23'
#GetAirPressureCMD = b'24'
GetFlowRateCMD = b'25'
#GetLightCMD = b'26'
#GetDitchFlowCMD = b'27'




#variables i guess
waterLevel = False
waterPressure = 888
waterState = 888
flowRate = 888

#default start & Stop times---------------------------------------------------------------------------
sprinklerStartTime = "6:00"
sprinklerStopTime = "6:15"

BackGardenStartTime = "6:20"
BackGardenStopTime = "6:35"

FrontGardenStartTime = "6:40"
FrontGardenStopTime = "6:55"

SpiceGardenStartTime = "7:00"
SpiceGardenStopTime = "7:15"

HoseStartTime = "7:20"
HoseStopTime = "7:35"
#Update timers------------------------------------------------------------------------
def enterSprinklerStart():
    sprinklerStartTime = E1.get()
    print(sprinklerStartTime)
def enterSprinklerStop():
    sprinklerStopTime = E11.get()
    print(sprinklerStopTime)

def enterBackGardenStart():
    BackGardenStartTime = E2.get()
    print(BackGardenStartTime)
def enterBackGardenStop():
    BackGardenStopTime = E22.get()
    print(BackGardenStopTime)
 
def enterSpiceGardenStart():
    SpiceGardenStartTime = E3.get()
    print(SpiceGardenStartTime)
def enterSpiceGardenStop():
    SpiceGardenStopTime = E33.get()
    print(SpiceGardenStopTime)

def enterFrontGardenStart():
    FrontGardenStartTime = E4.get()
    print(FrontGardenStartTime)
def enterFrontGardenStop():
    FrontGardenStopTime = E44.get()
    print(FrontGardenStopTime)

def enterHoseStart():
    HoseStartTime = E5.get()
    print(HoseStartTime)
def enterHoseStop():
    HoseStopTime = E55.get()
    print(HoseStopTime)

#Override button state--------------------------------------------------------------------------------

PumpORButtonState = False
SprinklerORButtonState = False
BackGardenORButtonState = False
SpiceGardenORButtonState = False
FrontGardenORButtonState = False
HoseORButtonState = False
#Override Button Events--------------------------------------------------------------------------------
def PumpOR():
    global waterLevel
    global PumpORButtonState
    if ( not PumpORButtonState):
        PumpORButtonState = True
        #waterLevel = True
        #waterLevelLabel.configure(text = str(waterLevel) )
        BORP.configure(relief = "sunken")
        NRF.SendCommand(pumpOn)
    else:
        BORP.configure(relief = "raised")
        PumpORButtonState = False
        #waterLevel = False
        #waterLevelLabel.configure(text = str(waterLevel) )
        NRF.SendCommand(pumpOff)
def SprinklerOR():
    global SprinklerORButtonState
    if ( not SprinklerORButtonState):
        SprinklerORButtonState = True
        BORS.configure(relief = "sunken")
        NRF.SendCommand(sprinklerOn)
    else:
        BORS.configure(relief = "raised")
        SprinklerORButtonState = False
        NRF.SendCommand(sprinklerOff)
def BackGardenOR():
    global BackGardenORButtonState
    if ( not BackGardenORButtonState):
        BackGardenORButtonState = True
        BORBG.configure(relief = "sunken")
        NRF.SendCommand(BackGardenOn)
    else:
        BORBG.configure(relief = "raised")
        BackGardenORButtonState = False
        NRF.SendCommand(BackGardenOff)
def SpiceGardenOR():
    global SpiceGardenORButtonState
    if ( not SpiceGardenORButtonState):
        SpiceGardenORButtonState = True
        BORSG.configure(relief = "sunken")
        NRF.SendCommand(SpiceGardenOn)
    else:
        BORSG.configure(relief = "raised")
        SpiceGardenORButtonState = False
        NRF.SendCommand(SpiceGardenOff)
def FrontGardenOR():
    global FrontGardenORButtonState
    if ( not FrontGardenORButtonState):
        FrontGardenORButtonState = True
        BORFG.configure(relief = "sunken")
        NRF.SendCommand(FrontGardenOn)
    else:
        BORFG.configure(relief = "raised")
        FrontGardenORButtonState = False
        NRF.SendCommand(FrontGardenOff)
def HoseOR():
    global HoseORButtonState
    if ( not HoseORButtonState):
        HoseORButtonState = True
        BORH.configure(relief = "sunken")
        NRF.SendCommand(HoseOn)
    else:
        BORH.configure(relief = "raised")
        HoseORButtonState = False
        NRF.SendCommand(HoseOff)

#Sensors-----------------------------------------------------------------------------------------------------
def GetWaterPressure():
	NRF.SendCommand(GetWaterPressureCMD)
	waterPressure = NRF.GetSensor()
	waterPressureLabel.configure(text = str(waterPressure) )

def GetWaterState():
    NRF.SendCommand(GetWaterStateCMD)
    waterState = NRF.GetSensor()
    waterStateLabel.configure(text = str(waterState) )

def GetFlowRate():
    NRF.SendCommand(GetFlowRateCMD)
    time.sleep(3)
    flowRate = NRF.GetSensor()
    flowRateLabel.configure(text = str(flowRate) )



master = tk.Tk()
#.geometry("window width x window height + position right + position down")
master.geometry("600x400+300+200")


#Sprinkler--------------------------------------------------------------------------------------------------
E1 = tk.IntVar()
L1 = tk.Label(master, text="Sprinkler Start").grid(row=0,column=0,sticky=tk.W,pady=2)
E1 = tk.Entry(master, bd =5, width = 6)
E1.insert(0,sprinklerStartTime)
E1.grid(row=0,column=1,sticky=tk.W,pady=0)
B1 = tk.Button(master, text = 'Enter', command = enterSprinklerStart).grid(row=0,column=2,sticky=tk.W,pady=2)
L11 = tk.Label(master, text="Sprinkler Stop").grid(row=0,column=3,sticky=tk.W,pady=2)
E11 = tk.Entry(master, bd =5, width = 6)
E11.insert(0,sprinklerStopTime)
E11.grid(row=0,column=4,sticky=tk.W,pady=2)
B11 = tk.Button(master, text = 'Enter', command = enterSprinklerStop).grid(row=0,column=5,sticky=tk.W,pady=2)
#BackGarden---------------------------------------------------------------------------------------------------
L2 = tk.Label(master, text="Back Garden Start").grid(row=1,column=0,sticky=tk.W,pady=2)
E2 = tk.Entry(master, bd =5, width = 6)
E2.insert(0,BackGardenStartTime)
E2.grid(row=1,column=1,sticky=tk.W,pady=2)
B2 = tk.Button(master, text = 'Enter', command = enterBackGardenStart).grid(row=1,column=2,sticky=tk.W,pady=2)
L22 = tk.Label(master, text="Back Garden Stop").grid(row=1,column=3,sticky=tk.W,pady=2)
E22 = tk.Entry(master, bd =5, width = 6)
E22.insert(0,BackGardenStopTime)
E22.grid(row=1,column=4,sticky=tk.W,pady=2)
B22 = tk.Button(master, text = 'Enter', command = enterBackGardenStop).grid(row=1,column=5,sticky=tk.W,pady=2)
#SpiceGarden----------------------------------------------------------------------------------------------
L3 = tk.Label(master, text="SpiceGarden Start").grid(row=2,column=0,sticky=tk.W,pady=2)
E3 = tk.Entry(master, bd =5, width = 6)
E3.insert(0,SpiceGardenStartTime)
E3.grid(row=2,column=1,sticky=tk.W,pady=2)
B3 = tk.Button(master, text = 'Enter', command = enterSpiceGardenStart).grid(row=2,column=2,sticky=tk.W,pady=2)
L33 = tk.Label(master, text="SpiceGarden Stop").grid(row=2,column=3,sticky=tk.W,pady=2)
E33 = tk.Entry(master, bd =5, width = 6)
E33.insert(0,SpiceGardenStopTime)
E33.grid(row=2,column=4,sticky=tk.W,pady=2)
B33 = tk.Button(master, text = 'Enter', command = enterSpiceGardenStop).grid(row=2,column=5,sticky=tk.W,pady=2)
#FrontGarden-------------------------------------------------------------------------------------------------
L4 = tk.Label(master, text="FrontGarden Start").grid(row=3,column=0,sticky=tk.W,pady=2)
E4 = tk.Entry(master, bd =5, width = 6)
E4.insert(0,FrontGardenStartTime)
E4.grid(row=3,column=1,sticky=tk.W,pady=2)
B4 = tk.Button(master, text = 'Enter', command = enterFrontGardenStart).grid(row=3,column=2,sticky=tk.W,pady=2)
L44 = tk.Label(master, text="FrontGarden Stop").grid(row=3,column=3,sticky=tk.W,pady=2)
E44 = tk.Entry(master, bd =5, width = 6)
E44.insert(0,FrontGardenStopTime)
E44.grid(row=3,column=4,sticky=tk.W,pady=2)
B44 = tk.Button(master, text = 'Enter', command = enterFrontGardenStop).grid(row=3,column=5,sticky=tk.W,pady=2)
#Hose---------------------------------------------------------------------------------------------------------
L5 = tk.Label(master, text="Hose Start").grid(row=4,column=0,sticky=tk.W,pady=2)
E5 = tk.Entry(master, bd =5, width = 6)
E5.insert(0,HoseStartTime)
E5.grid(row=4,column=1,sticky=tk.W,pady=2)
B5 = tk.Button(master, text = 'Enter', command = enterHoseStart).grid(row=4,column=2,sticky=tk.W,pady=2)
L55 = tk.Label(master, text="Hose Stop").grid(row=4,column=3,sticky=tk.W,pady=2)
E55 = tk.Entry(master, bd =5, width = 6)
E55.insert(0,HoseStopTime)
E55.grid(row=4,column=4,sticky=tk.W,pady=2)
B55 = tk.Button(master, text = 'Enter', command = enterHoseStop).grid(row=4,column=5,sticky=tk.W,pady=2)

#Override!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
L6 = tk.Label(master, text="Override!!").grid(row=5,column=0,sticky=tk.W,pady=2)
BORP = tk.Button(master, text = 'Pump', command = PumpOR)
BORP.grid(row=6,column=0,sticky=tk.W,pady=2)
BORS = tk.Button(master, text = ' Back Sprinkler', command = SprinklerOR)
BORS.grid(row=7,column=0,sticky=tk.W,pady=2)
BORBG = tk.Button(master, text = 'Back Garden', command = BackGardenOR)
BORBG.grid(row=8,column=0,sticky=tk.W,pady=2)
BORSG = tk.Button(master, text = 'Middle Sprinkler', command = SpiceGardenOR)
BORSG.grid(row=9,column=0,sticky=tk.W,pady=2)
BORFG = tk.Button(master, text = 'Front Garden', command = FrontGardenOR)
BORFG.grid(row=10,column=0,sticky=tk.W,pady=2)
BORH = tk.Button(master, text = 'Hose', command = HoseOR)
BORH.grid(row=11,column=0,sticky=tk.W,pady=2)

# Sensors---------------------------------------------------------------------------------------------------------------

waterStateButton = tk.Button(master, text = 'GetWaterSensor', command = GetWaterState)
waterStateButton.grid(row=5,column=2,sticky=tk.W,pady=2)

L7 = tk.Label(master, text="Water State:").grid(row=5,column=3,sticky=tk.W,pady=2)
waterStateLabel = tk.Label(master, text=str(waterState))
waterStateLabel.grid(row=5,column=4,sticky=tk.W,pady=2)

waterPressureButton = tk.Button(master, text = 'GetWaterPressure', command = GetWaterPressure)
waterPressureButton.grid(row=6,column=2,sticky=tk.W,pady=2)

L8 = tk.Label(master, text="Water Pressure:").grid(row=6,column=3,sticky=tk.W,pady=2)
waterPressureLabel = tk.Label(master, text=str(waterPressure))
waterPressureLabel.grid(row=6,column=4,sticky=tk.W,pady=2)


flowRateButton = tk.Button(master, text = 'GetFlowRate', command = GetFlowRate)
flowRateButton.grid(row=7,column=2,sticky=tk.W,pady=2)
L9 = tk.Label(master, text="LPM:").grid(row=7,column=3,sticky=tk.W,pady=2)
flowRateLabel = tk.Label(master, text=str(flowRate))
flowRateLabel.grid(row=7,column=4,sticky=tk.W,pady=2)

L10 = tk.Label(master, text="Radio:").grid(row=8,column=3,sticky=tk.W,pady=2)

def GUImainLoop():
	master.mainloop()



