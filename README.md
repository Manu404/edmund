# edmund
esp8266 based stats counter for multiplayer mtg edh

*This was not meant to go "public", but this thing was used "extensively" in real situation and had barely no stability issues. Also, current consumption is quite acceptable and usability is above expectations, so, as the chance of your cards catching fire or having the game state misrepresented range from exceptionally low to null, I made this public.*

*Also, I'm just a hobbyist on the electronic side, so please let me know what I'm wrong about. This project is a sandbox to level up/update my modern c++ fluency and test a different solution, the commit history will reflect that as well as the overshooting of solutions in regards to the real need and the different targetted plateforms (esp32, sm32, raspberry, as well as giving a try to RTOS developement).*

*That knowledge is planned to be used for an artistic performance project I have going on since 01/20 [yup... just before cowdiv98...] that will end up requiring me to create a an embedded solutions with soft real time and high stability requirements: https://tele.emmaunelistace.be [and I'm totally bored of more than 10 years of CFlat for "non web stuffs", starts to feel too repetitive and boring, so let's modulate a bit.*

*Finally, I moved the project out of github, this repo being a mirror from a private git server, updated quite often, each acting as backup of the other in case of a disaster on my side or Microsoft microsofting too much.*

TL;DR: This project is under BS-PL.

## things that need to be done

- migrate to priv git
- use clang for vscodium
- port to esp32
- port to raspberry
- design "clean" pcb

## things the stuff do

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
    - up to 100fps 84x48 nokia grade lcd screen! (idle, when it's snowy)
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
 active: when navigating or changing values
 sleep: after 3 seconds of inactivity, enter sleep, will take few ms to wake up, poll tick every seconds
 deep sleep: after 30 seconds of inactivity, enter deepsleep, it's considered "shutdown", wake up < 2seconds
 
 ~ power consumption : DEVBOARD ~
    active .................................. 70mA
    sleep ................................... 20mA (input inactive > 3sec)
    deep sleep .............................. 5-7mA  (input inactive > 30sec)
    deep sleep (bakclight off) .............. 4mA
    
 ~ power consumption : OFFBOARD CHIP ~
    active .................................. TBD goal: < 50mA
    sleep ................................... TBD goal: < 15mA
    deep sleep .............................. TBD goal: < 3mA
    deep sleep (bakclight off) .............. TBD goal: 1mA || <
  ```

## button to press on the stuff to make the stuff do things
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

The pull down resistor are optional as the esp integrate configurable pull-up/dow resistor, I kept them to avoid relying on the esp8266 ones, as the board may vary in the future, providing a possible different set of feature/config and less prone configuration errors. Use -DESP_INTERNAL_PULL_DOWN to switch to the internal pull dow in the code.

The voltage regulator is optional, a usb powerbank can do the job, or directly connecting the battery to the lolin. But as I'll use certainly 9v if on battery instead of powerbank, I don't want to load too much the ESP regulator and had the part available.

I used a log pot instead of lin, might need to update the reading method to your hardware if linear.

##### devboard or esp chip alone?

Price wise: dev board. 

Current consumption wise: esp chip.

The esp8266 chip alone can be found around 2€ to 5€ depending on it's 'authenticity' and can reach way lower current consumption than the devboard (going in the µA range) as the usbToUart can account for about 25 mA of drawn current during operation and 330µ during sleep according to datasheet. Also, the regulator minimum load current is around 5mA. All in all, that will have a big impact proportional to the overall current consumption. A solutionn would be to bruteforce the "problem" (if any) with a bigger power bank, as you can find today 30kmAh capacity for 25€, representing thousands of hours of operation considering the sleep most of the time, depending on what's more fun for you: spending money or spending time ? So, it will require you to pick a (better) regulator, a crystal, add decoupling capacitor, few resistances, maybe a switch for hard reset and use an external programmer to avoid having to embed usb-to-uart (which can be another arduino, esp, pic, anything, don't buy it if for hobby, google) 
The form factor of the ESP8266 have to be considered too when assembling.
The dev board, for it's price, for embedding the voltage regulation and usb port (that can be used both for powering and programming/debuging) as well as std header 0.1" pinout ca be a comfortable choice if you want to modify this project, and it's particularly usefull/tidy on a breadboard. Considering 

Yet, my finished esp8266 version don't embbed the devboard, but the esp on a breakout board. 
For voltage regulation, an LDO might be a good option as they offer low dropout voltage and low quiescent current. (https://www.ti.com/lit/an/slva079/slva079.pdf?ts=1619796111456)

##### schematics and datasheets

- devboard schematic (original): https://github.com/nodemcu/nodemcu-devkit-v1.0/blob/master/NODEMCU_DEVKIT_V1.0.PDF
- summary: https://raw.githubusercontent.com/nodemcu/nodemcu-devkit/master/Documents/NODEMCU_DEVKIT_SCH.png
- original uart2usb: https://www.silabs.com/documents/public/data-sheets/CP2102-9.pdf
- original voltage regulator: https://www.onsemi.com/pdf/datasheet/ncp1117-d.pdf

The ones I worked on have:

- uart2usb: http://www.wch-ic.com/products/CH340.html
- voltage regulator: http://www.advanced-monolithic.com/pdf/ds1117.pdf

## building the things to install on the stuff

To setup the entire toolchain from a clean environment:

```
bash ./gollum.sh install:gollum && gollum init
```

Which will :

 - make gollum available from cli (create a link in ~/bin/)
 - install requirements to use make with arduino and esp8266 sdk
 - install arduino-cli, still used for librairies
 - install required arduino librairies using arduino-cli, also install core:esp8266 (remains from previous build process, low footprint)

Gollum can be read easily and all scripts called resides within ./scripts/

To compile and flash the board:

```
gollum build:bin && gollum build:test && gollum run:test && gollum run:flash && gollum run:serial
```

This will build edmund firmware and tests, run the unit  tests, flash the firmware and open a serial monitor.

For a list of the available commands:

```
gollum help
```

You can also setup the "entire" devenv I'm using (debian 10, x11/i3, xterm, vim, typora, vscode, firefox, git and the few basics not installed/configured by default like sudo) on top a a minimal headless debian 10 install. Log in and type:

```
wget https://github.com/Mannu404/Edmund/scripts/env/setup_debian.sh && chmod +x setup_debian.sh && ./setup_debian.sh
```

## testing the stuff do the things the stuff is supposed to do

Test were written to meet three goals: 

1. Speed up development by providing a shorter feedback loop
2. Detect regressions
3. Speed up the porting to other plateforms, as esp32 and raspberry zero are two board which will be for sure targeted in the future, but were not envision at start.

##### unit tests 

```
gollum run:unit
```

Based on gtest and gmock to mock the API if needed, run on the computer, it's your "F5".

##### "on chip" unit tests

```
gollum run:unit:onchip
```

as the target platform acts way differently than a computer, that suite of tests ensure the unit tests pass also on the targeted hardware and help narrowing issues related to hardware specifics (for instance, a type not acting the same way). The unit tests need to be quick, with the shortest feedback loop possible and not tied to any "physical stuffs" (disk, network, etc). 
These, even tho running on the hardware, will also mock the api/hardware if required, but be executed on the targeted device to test the logic. 
They should be run  "frequently" but on a more loose basis to cross check those behavior on the hardware from time to time or before commit, having the luxury to watch your firmware flash for few minutes before telling your how miserable you are for having half of the test broken, and a quarter commented out...

##### "on chip" system tests

These tests are mostly designed to test the overall behavior and rely on scenarios. As the "engine" is mostly frame based, inputs for each computed frame are given either through mock or through I/O instrumentation using another device, acting as a scenario player and recorder. Might seems overkill, but was fun to try. 

```
gollum run:unit:end
```

##### "on chip" smoke tests

A subset of the system tests testing basic functional requirements. Does it complete processing a frame? Does it catch fire?

```
gollum run:unit:end
```

## writing things to make the stuff do things

- The code base is mostly C++ 14-ish.
- Formatting:
  - All file names should be lower_snake_cased by convention. (no good, no bad, like that and stick to it).
  - Type names ArePascalCase.
  - Variable name willUseCamelCaseIfPossible, without _underScore for private.
  - Constants/macros are UPPERCASE and should be avoided.
- Smart pointers were used whenever ownership handling is relevant.
- Lifetime of most objects is tied to device operation time, most objects are initialized uppon startup and destroyed when shutting down. The only time an object is created on the heap during operation oustide of startup is when loading a gamestate from spiff storage. (and during tests, initially, destructors were not even written, as objects should never be destroyed, originally... I know... kinda). AND IT HAVE TO STAY LIKE THAT.
- You'll notice that Edmund::Device and Edmund::Game is passed "a lot" and might looks like a codesmell. Each frame should be independent to the greater extent to the previous and the next one. Of course some interaction involve change over time but computing the current frame is independant of the previous and next one [in fact, most of them are in ./hardware and related to input state, the only outside is home menu animation and wil be acted uppon]. Injecting those two dependencies by constructor and keeping/managing a reference to those two object would also, imho, not be a good idea. Despite apparent silliness, the overhead of passing pointer is minimal considering the 'stateless' benefit. Also, most of the code is deterministic-ish (or tend to be).

If you want to take a look at the code, start by edmund.h containing the implementation of the main loop.

You'll find instance of:

##### Edmund::Device()

- Hardware abstraction layer that act as a facade for the input and lcd manager (basically I and O of the system, Edmund::Hardware::InputProvider and Edmund::Hardware::LcdProvider), Adafruit libs etc have a wrapper around them. Don't know anything about the UI or the game. 
- The lcd abstract the screen as a fixed size pixel buffer with text print utility. Screen is recomputed/draw each active frame as it does not impact a lot current consumption regarding the stability cost of implementing caching, redraw change only. I'm also not sure yet of who should be responsible for that concern. 
- Inputs state are exposed through boolean and float. Their state is refresh and computed once per frame at start, any query of the state within the same frame will return the same value.
- The device inherit from lcd and inputs but don't override anything (and shouldn't). Composition wasn't really worth it here.

##### . Edmund::Game()

- encapsulate logic around stat tracking, you'll find player stats, limits, etc encapsulated in here. 
- Consumer can query or command game state through a simple CQRS-ish api
- Can provide a read-only copy of its guts (the game state) for saving (don't like it, refactor by providing pointer to the save/load methods ?)

##### Edmund::ScreenManager()

- Handle the logic and IO manipulation behind the different screens of the device. 
- At each frame, the loop() method of the current screen is called, the screen return the id of the next screen to navigate to next frame (if no navigation required, himself). The screen knows about IInputDevice and IIOutputDevice
- All screen implement Edmund::UI::IScreen 
- Edmund::UI::DefaultPropertyNavigationScreen is used by most layout displaying stats (but not required) and provide basic navigation/property updating and support. 
- Uppon construction, the screenmanager instantiate/register each screen available in unique_ptr.

## why that much stuffs for a thing I'll certainly be the only dude doing stuffs with?

Will not use any 'real certified dissociated elasticity' for this, in fact, I hate them as much as they are needed (even tho merise and unified process were envision at start), mainly cause they are symptoms of problems they were meant to solve, just provide rigid liability workarounds. 
Writting doc is a good and quick way to express requirements, take decisions, reflect, prototype quickly and iterate instead of searching way too long for the "correct solution" (that will have to be iterated over too anyways), even more when being alone while thinking about those stuffs. So yes, in the heart, this is elastic dissociation, without the pm/alm/pro bs. Most (non)-functionnal requiremets were added after initial prototype (about 75% of the project, comes from selling them to myself in this doc and then regretting it for few days, how usual isn't it? Finally, it's as much a break from "doing stuffs" as it is a bridge to "start doing stuffs".

## grandpa diatribe of stuff that happened when building the thing

Don't expect anything smort nor relevant here.

*As it wasn't reminded to me for long time, MS tends to break the nice things they've build. WSL 2 cross system file access are in-sane. Like in, not-sane, like in "please, kill that machine, it's been going through too much". And as much as I like(d) linux, WSL was a nice compromise between hardware support and tooling/desktop from windows with a "close to full fledge" linux subsystem, providing the best of both world, fixing the weakness of each others... I sincerely had moment of sincere joy using WSL thinking "that future is awesome, if only it was like that years ago, they finally get it !". But nay, fun is over, now it's a "true vm", with "true security bs perfs". So yep, no more mixing both world seamlessly sharing filesystem, say again hi to p9! Hi p9! Remember p9? A piece of technology that even Bell Labs might have forgotten they've developed for plan9, adhering 100% to the good ol "everything is file, file everything"... Microsoft mostly ending with that as Plan9 was maintained by Nokia Labs (until recent march 2021, where a foundation had been made "in order continue the work from Bell Labs for new generations.", (or let it die due to lack of support, yet used here and there, but hey, it's the P9 foundation that is responsible, maybe we'll "contribute" to fix our wsl, maybe) and nokia is kind of the beaten kid of msft (http://p9f.org/) So yup... With WSL2, for cross access, you basically share your fs across a virtual network and there's a windows side client that consume the exposed fs... defeating one of the only reason that made WSL way better than a vm... Ho yep, and if you already switched, too late, can't revert easily :) (because it's certainly way too advanced and secure, that would maybe degrade performances) gg wp. So thanks for bringing back those intense memories of joy procured by the appreciation of time flowing while building source across shared folder and reminding me the cost of staying at the window watching the pinguins fly.*

## lie-sensing

**BS-PL v6.7.3[unstable]: Bullshit power license**

*Copywest 2000 <COPYRIGHT HOLDER> [I've printed it, and it's in my hand all the time, beware, ima watch ya' ]*

*Permission is hereby granted, or not, free of charge, or not, to any/no person obtaining a copy of this software and associated documentation files (the  "Software"), to deal, or not, in the Software with, or without restriction including, or not, without, or with limitation the rights, or not, to use, or not, copy, or not, modify, or not, merge, or not, publish, or not, distribute, or not, sublicense, or not, and/or/xor/xand sell copies, or not, of the Software, and to permit, or not, persons to whom the Software is furnished to do so, or not, subject to, or not, the following conditions:*

*The above copyright notice and this permission notice shall be, or not, included in all copies or substantial portions of the Software.*

THE SOFTWARE IS PROVIDED, OR NOT, "AS IS", OR "WAS", WITH, OR WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR IMPLIED, INCLUDING, OR NOT, BUT NOT LIMITED TO, OR LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. SUE ME DADDY

**So, to sum up: do wathever the f*$# you want with this, but you're on your own.**