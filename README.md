# projectors
Arduino scripts to advance 3 Kodak slide projectors in various ways.

# building and uploading
Tool used to flash the Arduino is called Arturo, and is a fork of ino. Ino is no longer supported, but for the most part documentation is still accurate for Arturo if you replace "ino" with "ano" everywhere.

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
