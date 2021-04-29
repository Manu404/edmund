# edmund
esp8266 based stats counter for multiplayer mtg edh

## things this stuff do

  ```
  ~ features ~
    - you + 3 opponents stat tracking
      - life
      - received/inflicted commander dmg
      - received/innfliced infect dmg
      - mana pool (you only)
    - dice rolls (configurable dice face count and dice count, default to 20)
    - countdown timer
    - web
      - remote text display
      - player edit
      - game history logs
    - text-to-speech commander effects
    - up to 100fps 84x48 nokia grade lcd screen ! (idle, when it's snowy)
  ```

  ```
  ~ layouts ~
    2 player simple ......................... pv for you, cmdr damage and infect for two
    2 player complete ....................... pv, infect,et cmdr damage for two
    4 player simple ......................... pv for you, cmdr damage dealt to you and by you, infect for 4l
    4 player complete ....................... pv, infect for four, commander damages in all directions
  
  All layout have: 
    manapool counter (WURBGX)
    generic counter panel (can be used for storm or turn count/countdown etc)
  ```

  ```
  ~ power consumption ~
    active .................................. 70mA
    sleep ................................... 20mA (input inactive > 3sec)
    deep sleep .............................. 2mA  (input inactive > 30sec)
    deep sleep (bakclight off) .............. 1mA
  ```

## button to press on the stuff to make it do things
  ```
												
home screen
    rotary encoder .......................... Navigate left/right
    middle .................................. Enter screenn
stat screens
    rotary encoder .......................... Change value
    potentiometer ........................... Navigate left/right
    right ................................... Empty mana pool
    middle .................................. Return to home screen
gonfig screen
    rotary encoder .......................... Select option (available: set variable, erase memory, reset, start test)
    middle .................................. Validate option
    
  ```

## stuffs you need to make the stuff do things

  ```
    												
    1x esp8266 .............................. 6.80€ (might be worth checking set of copies on amazon)
    1x pcd8544 .............................. 8.00€ (often discounted by 3 to 5€, amazon)
    1x mcp23017 ............................. 1.10€
    3x switchs button (*) ................... 0.14€
    1x pot (*) .............................. 0.50€
    1x rotary encoder w/ switch(*) .......... 0.70€
    6x 1k ohm 1/4W .......................... 0.48€
    1x LM7805 regulator ..................... 1.40€
    headers for lcd, pcd8544, knobs, pcb .... 5.00€
                                            ---------
                                             24.20€
                                     - phün x 1.00€
									 
	(*): parts salvaged with respect to the gods of the interwebs

Price source: mouser.com, from belgium
  ```

Most parts were picked based on what I had on hand, pick whatever you want, but most are available for cheap.

### things to know about the stuffs you need to make the stuff do things

I used a log pot instead of lin, might need to update the reading method to your hardware if linear.

The regulator is optional, an usb powerbank can do the job or directly connecting the battery to the lolin. But as I'll use certainly 9v if on battery instead of powerbank, I don't want to load too much the ESP regulator and had the part available. *Yet, might not be the best efficient way of doing this, but provide plenty of heat to get your finger ready for the next shuffling* 

## building the things to install on the stuff

If on Windows, install wsl (https://gist.github.com/trzecieu/8828e9b47b2b553e3ece7f6f899d4d25)

To setup the entire toolchain from a clean environment run

```
bash ./gollum.sh install:gollum && gollum init
```

Which will :

 - make gollum available from cli (create a link in ~/bin/)
 - install requirements to use make with arduino project and esp8266 sdk from espressif
 - install arduino-cli, still used for librairies
 - install required arduino librairies using arduino-cli, also install core:esp8266 (remains from previous build process, low footprint)

Gollum can be read easily and all scripts called resides within ./scripts/

Then, to compile and flash the board

```
gollum build:bin && gollum build:test && gollum run:test && gollum run:flash && gollum run:serial
```

This will build edmund firmware and tests, run the unit  tests, flash the firmware and open a serial monitor.

for a list of the available commands

```
gollum help
```

## testing the stuff do things this stuff is supposed to do

Test were written to meet three goals: 

1. Speed up development by providing a shorter feedback loop
2. Detect regressions
3. Speed up the porting to other plateforms, as esp32 and raspberry zero are two board which will be for sure targeted in the future, but were not envision at start.

 - **unit tests** 

   ```
   gollum run:unit
   ```

   Based on gtest and gmock to mock the API if needed, run on the computer, it's your "F5".

 - **"on chip" unit tests**

   ```
   gollum run:unit:onchip
   ```

   as the target platform acts way differently than a computer, that suite of tests ensure the unit tests pass also on the targeted hardware and help narrowing issues related to hardware specifics (for instance, a type not acting the same way). The unit tests need to be quick, with the shortest feedback loop possible and not tied to any "physical stuffs" (disk, network, etc). 
   These, even tho running on the hardware, will also mock the api/hardware if required, but be executed on the targeted device to test the logic. 
   They should be run  "frequently" but on a more loose basis to cross check those behavior on the hardware from time to time or before commit, having the luxury to watch your firmware flash for few minutes before telling your how miserable you are for having half of the test broken, and a quarter commented out...

 - **"on chip" system tests**  
   These tests are mostly designed to test the overall behavior and rely on scenarios. As the "engine" is mostly frame based, inputs for each computed frame are given either through mock or through I/O instrumentation using another device, acting as a scenario player and recorder. Might seems overkill, but was fun to try. 

   ```
   gollum run:unit:end
   ```

 - **"on chip" smoke tests** 
   A subset of the system tests testing basic functional requirements. Does it complete processing a frame ? Does it catch fire ?

   ```
   gollum run:unit:end
   ```

   