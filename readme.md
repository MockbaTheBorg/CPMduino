# CPMduino (deprecated, see below)

CPMduino is an arduino application which allows you to execute old CP/M 8 bits programs on the Arduino DUE.
If you miss powerful programs like Wordstar, dBaseII, Mbasic and others, then RunCPM is for you.

CPMduino builds on Arduino 1.6.6 or later.
CPMduino so far runs only on the Arduino DUE. It requires a fair amount of RAM to run (64K used to be a lot in those days).
CPMduino needs a SDFat library. I am using the one from https://github.com/greiman/SdFat
CPMduino needs a SD (or microSD) card shield.
The file SdFatConfig.h of SdFat must be changed so: #define USE_LONG_FILE_NAMES 0 (if it is 1, CPMDuino will fail if the folder contains files with long names)

Arduino digital and analog read/write added by Krzysztof Klis via BDOS calls (see cpm.h file for details).

## Getting Started

Just format a SD card and create subfolders on it called "A", "B", "C" ... these will be your "disk drives".
There's no need to create clumsy disk images. Just put your CP/M programs and files inside these subfolders, which are seen as drive letters "A:", "B:", until "P:".

CPMduino needs a binary copy of the CP/M CCP to be on the root folder of the SD card. The one provided is CPM22.bin, which is CPM 2.2. Others may work as well, your mileage may vary.

## CPMduino is now merged into RunCPM and won't be upgraded anymore
