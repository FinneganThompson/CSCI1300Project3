Map should generate randomly 
Enter names of player and party members (each has 50 fullness points, bellow 0 means death)
Start with 100 gold 
game ends when sorcer gets 100 anger 
Get merchnat menu


Map generation
Party info
Gold/ inventory (could potentially to store sorcer)
merchant menu (reuse inventory/ gold) 


check map file

party file:
npc class
	puzzles
	summon monster 

player class (could include other party members)
monster class

npc file:
npc class
	riddles 
monster class
sorcerer class

game file: mso

item file:
	merchant class
	class for each item 
	inventory class? or struct? 
gold
Ingrediants 
Wepons (players can only hold one weapon each) and dead players weapons don’t count
Armor
Cookware
Treasures 
Keys

status update:

(can use inventory same for merchant)
Number of rooms cleared
Keys found
fullness of each party member
Ingredients (kg)
cookware available 
Weapons and armor available 
Gold available 
Treasure items available 
Sorcerer’s anger


figure out how the npc is stored in the map
each type of space has a special action 



game play:

phase 1:

Map should generate randomly 
Enter names of player and party members (each has 50 fullness points, bellow 0 means death)
Start with 100 gold 
game ends when sorcer gets 100 anger 
Get merchnat menu


Each turn:

Display status update 
Display map 
Display action menu
for normal spaces:
	move (20% chance fullness drops 1 point)
	investigate (50% chance fullness drops 1 point unless fought monster) 
		find key
		find treasure
		find random monster
	pick a fight 
	cook and eat
	give up
	
for npc spaces
	move
	speak to npc 
		if complete puzzle can sell 
		if not complete will sommon monster 
		space changes to explored no matter what
	give up
	
for room spaces
	move
	open the door
		if monster is defeated 60% of misfortune 
		if does not defeat monster consequences (key is lost, 40% chance of misfortune)
	give up
	

Use functions to remove room or npc as needed


Game end
win with exiting with at least one other player (must clear all rooms and then go to exit)
	players can die from huuner or monster attack
lose (if all other players die or if anger is 100)

either way print:
	name of leader and remaining members
	number of rooms cleared
	gold remaining
	treasure items
	number of spaces explored
	number of monsters defeated
	number of turns
save results in results.txt


misfortunes (after completing an action 40% chance)
robbed (chosen at random) 30%
	lose ingredients (10kg)
	cookware (1 item)
	armor (1 item(
break either weapon or armor 10%
food poisoning one member loses 10 hunger points (can kill) 30%
locked in room: only happens if player tries to open door with key (nothing happens if picked when not open door) 30% One random member that is not leader (can end game if no more members) 
CAN HAVE POSITIVE ONES

fighting monsters 
Can and should add monsters from 1-5
fight same level monster as number of rooms cleared
if monster is fought it cannot reappear 
Print message for a monster appearing 

actions during encounter: (health can drop 1 poitn) 50%
attack use formula to determine outcome, greater than 0 is a win 0 or less is a loss (can only attack if one person has a weapon)
	win means more gold and ingredients depending on the challenge rating 10% monster will drop key 
	loss means that the party loses a quarter of their gold, rounded to nearest int, up to 30 kg of ingredients, and can die from monster (10% for everyone in party 5% for leader) 
surrender 
	one player has to be left behind 

sorcerer’s anger:
each time party moves to unexplored space anger goes up 1 
if anger reaches 100 game ends and player loses
sorcerer is the monster in the 5th room (normal battle rules unless implement other rules)
if defeated anger will no longer increase and no more monsters

completeing puzzles 
use riddle files for npc
rps for door
redo until result 
win to enter
loss means losing a player 

death by hunger 
if fullness reaches 0 
warning is printed turn before 
