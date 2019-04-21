# MKII

## Specifications

## Getting Started

### Get git submodules
Run the follow commands:
```bash
git submodule init
git submodule update
```

## Running
### Add files to include dir
- Right click on project name.
- Select Build.
- Select ARM Compiler.
- Select Include Options.
- Add the include directory.

### Setup the environment
Follow the next indications:

- Create a new CCS Project in `[repo]/project` directory.
- Set target: MSP432P401R.
- Set project name.
- Select empty project.
- Add the files in `[repo]/lib/MSP432P4xx/driverlib/MSP432P4xx/` to the project.
- Add the files `[repo]/src/peripheral` to the project.
- Add `[repo]/include` directory to include path.
- Build project.

### Running a test
#### Blink a led with the Timer32
Add the file `[repo]/test/blink_p1_timer32.cpp` and use it like the `main.cpp`
of the project and build it.

## Contributors
- Emilio Rojas Álvarez `@emilio93`
- Brian Morera Madriz `@BRJMM`