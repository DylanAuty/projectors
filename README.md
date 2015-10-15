# projectors
Arduino scripts to advance 3 Kodak slide projectors in various ways.

# POWER ON/POWER OFF OF THE SYSTEM
In order for the projectors to remain in sync, the following must be observed:

## Power ON
1. Ensure that all power is OFF.
2. Ensure all data and power plugs are connected, to both projectors and control box.
3. Ensure all projector power switches are OFF.
4. Turn on power to the control box/power rail, and wait for 2-3 seconds to allow it to start. *You now have 30 seconds to do the next step.*
5. Turn on the power switches for all 3 projectors. When the 30 seconds have elapsed, the cycle will begin as normal

## Power OFF
1. Immediately *AFTER* projector *A* has FINISHED switching, turn the switch on the back to the OFF position.
2. Do the same thing for projectors B and C, *IN ORDER* and *IMMEDIATELY* to prevent the slides getting out of sync.
3. Now switch the power to the control box/power rail off.

# building and uploading
Tool used to flash the Arduino is called Arturo, and is a fork of ino. Ino is no longer supported, but for the most part documentation is still accurate for Arturo if you replace "ino" with "ano" everywhere.

Using the official Arduino GUI, sketches need to be in their own folder because of reasons. This is what the director `staggered_reformat` is for. This version of the code is also the most up-to-date one.

## Folder structure
Ano needs each file to be in its own project folder, with the following structure:

```
.
|-- lib
|   `-- .holder
|-- src
|   `-- sketch.ino
|-- ano.ini
```

*lib* is for any dependencies.
*src* contains the project source code.
*ano.ini* is the config file for that project.

## ano.ini
Ano needs to know which board and architecture it is building for and uploading to - this can be done every time a build command is run using the `--board-model`, `--cpu` and `--serial-port` flags.

Alternatively the ano.ini file can be created to specify these parameters. The current one may not be correct - check that the serial port specified is the right one.

## Hardware
The hardware is a SEEEduino v3.0, with an Atmel ATmega328 microcontroller. The build/upload/serial parameters are:

```
board-model = diecimila
cpu = atmega328
serial-port = /dev/ttyUSB0
```

Please note that serial port will change depending on machine and operating system. 

## To upload:
1. `cd` into the project directory, e.g. `cd ./staggered`
2. Check that `ano.ini` is set up correctly
3. Run `ano build`
4. If there are no errors, run `ano upload`. **Note that you may need root privileges to access the serial port**.
