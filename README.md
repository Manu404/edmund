# edmund
hardware esp32 based stats counter for multiplayer edh

## things this stuff do

- you + 3 opponents stat tracking
	- life
	- received/inflicted cmdr dmg
	- received/innfliced infect dmg
	- mana pool (you only)
- roll dices
- web
	- remote text display
	- player edit
	- game history logs
- text-to-speech commander effects
- up to 130fps 84x48 nokia grade lcd screen ! (idle, when it's snowy)


## button to press on the stuff to make it do things

- left/right => value
- pot => navigation
- middle => switch to manapool edit
- reset => debug menu, then left + right + middle with pot at max value
- refresh config from server => debug menu, then left + right + middle with pot at min value

## stuffs you need to make the stuff do things

- 1x esp32
- 1x pcd8544 
- 3x buttons (*)
- 1x pot (*)
- 1x rotary encoder (*)
- 3x 1k ohm
- 7505 regulator
- (headers for lcd and pcd8544)

(*): All parts were salvaged with respect to the gods of the interwebs

## things to know about the stuffs you need to make the stuff do things

I used a log pot instead of lin, might need to update the reading method to your hardware, *due to rupture of stock in my personal inventory. Sales dpt is working on it. Apparently due to recent covid issues, a lot of projects had started in house as most employees prefered to work here at home rather than being at home, leading tons of demand and a real pressure on the supply. We might need to reduce R&D budget as those guys seems to have lost focus, working on stuffs like a gameboy color MTG counter cartridge or applying data analysis on cardgame datasets to find the best bear available... f_,k?ng loosers*

The regulator is optional, an usb powerbank can do the job or directly connecting the battery to the lolin. But as I'll use certainly 9v if on battery instead of powerbank, I don't want to load too much the ESP regulator and had the part available. *Yet, might not be the best efficient way of doing this, but provide plenty of heat to get your finger ready for the next shuffling*
