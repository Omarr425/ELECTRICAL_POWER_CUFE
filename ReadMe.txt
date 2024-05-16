
Basic energy monitor functionalities are expected to be provided in this project 
1. *CURRENT/Voltage/Power/Energy Readings*
2. Basic signal processing *THD (Total Harmonic Distortion) / RMS Calculation / ...etc*
3. Reactive and Active power analysis (POWER FACTOR CALculation)
4. OverVoltage/OverCurrent Alarm
5. Simple CLI interface 

MAY BE PROVIDED LATER ON DEPENDING ON PRIORITY
A WEB/DESKTOP UI
PDF format export

## **RECENT ADDITIONS**
    ADDED_FREQUENCY_CALCULATION BASED ON A TRIGGER trigger_level
    ADDED_FREQUENCY_CALCULATION WITH HYSTERESIS TO OVERCOME NOISE CAUSING DOUBLE TRIGGERING  
    ADDED_PDF_EXPORT FOR SIGNALS DATA REPORT

## **MORE TO COME**
    WEB_UI / QT_UI
    PARSER
    FAST FORRIER TRANSFORM FFT ALGORITHM 

## **MORE TO COME BUT LESS PRIORITY**
    REAL_TIME_DIGITAL_FILTERING by using an MCU for sampling and signal output (multithreaded/multicore MCU's recommended)
    REAL_TIME_SIGNAL_ANALYSIS by using an external MCU for sampling (multithreaded/multicore MCU's recommended)


## **PROJECTS DOCUMENTATION**
  --DOXYGEN Generated Documentation 
  https://omar-magdy0.github.io/ELECTRICAL_POWER_CUFE/

THIS project is missing proper EXCEPTION HANDLING FOR NOW (CRASHES / UNEXPECTED BEHAVIOR is expected)!!