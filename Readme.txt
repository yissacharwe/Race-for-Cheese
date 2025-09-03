
 ██▀███   ▄▄▄       ▄████▄  ▓█████      █████▒▒█████   ██▀███  
▓██ ▒ ██▒▒████▄    ▒██▀ ▀█  ▓█   ▀    ▓██   ▒▒██▒  ██▒▓██ ▒ ██▒
▓██ ░▄█ ▒▒██  ▀█▄  ▒▓█    ▄ ▒███      ▒████ ░▒██░  ██▒▓██ ░▄█ ▒
▒██▀▀█▄  ░██▄▄▄▄██ ▒▓▓▄ ▄██▒▒▓█  ▄    ░▓█▒  ░▒██   ██░▒██▀▀█▄  
░██▓ ▒██▒ ▓█   ▓██▒▒ ▓███▀ ░░▒████▒   ░▒█░   ░ ████▓▒░░██▓ ▒██▒
░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ░▒ ▒  ░░░ ▒░ ░    ▒ ░   ░ ▒░▒░▒░ ░ ▒▓ ░▒▓░
  ░▒ ░ ▒░  ▒   ▒▒ ░  ░  ▒    ░ ░  ░    ░       ░ ▒ ▒░   ░▒ ░ ▒░
  ░░   ░   ░   ▒   ░           ░       ░ ░   ░ ░ ░ ▒    ░░   ░ 
   ░           ░  ░░ ░         ░  ░              ░ ░     ░     
                   ░                                           
 ▄████▄   ██░ ██ ▓█████ ▓█████   ██████ ▓█████                 
▒██▀ ▀█  ▓██░ ██▒▓█   ▀ ▓█   ▀ ▒██    ▒ ▓█   ▀                 
▒▓█    ▄ ▒██▀▀██░▒███   ▒███   ░ ▓██▄   ▒███                   
▒▓▓▄ ▄██▒░▓█ ░██ ▒▓█  ▄ ▒▓█  ▄   ▒   ██▒▒▓█  ▄                 
▒ ▓███▀ ░░▓█▒░██▓░▒████▒░▒████▒▒██████▒▒░▒████▒                
░ ░▒ ▒  ░ ▒ ░░▒░▒░░ ▒░ ░░░ ▒░ ░▒ ▒▓▒ ▒ ░░░ ▒░ ░                
  ░  ▒    ▒ ░▒░ ░ ░ ░  ░ ░ ░  ░░ ░▒  ░ ░ ░ ░  ░                
░         ░  ░░ ░   ░      ░   ░  ░  ░     ░                   
░ ░       ░  ░  ░   ░  ░   ░  ░      ░     ░  ░                
░

Jerusalem Multidisciplinary College
Course: Object Oriented Programming with C++
Exercise #2: "Race For Cheese"

---------------------------------------------------------------------------------------------------
General description:
---------------------------------------------------------------------------------------------------
"Race for Cheese" is an old style action game,
the entire Game's User Interface runs from the user console (terminal).

The Player controls a Mouse to move around the board, avoiding Cats and collecting objects
such as gifts, keys and most importantly, Cheese. The player can open a door with a key,
diminish a Cat with a gift, or lose a life when getting caught by a melicious Cat.

In order to avoid being eaten by the cats, a Player can choose to skip his turn
by pressing the Space Bar, thus forcing the cats to move again.

Object of the Game: Collect all the cheese.

---------------------------------------------------------------------------------------------------

List of files:

Main Datastructres:

Algorithms:

Design:

Known Bugs:

Any Other Notes:


Instructions to Adding new Levels to the Game:
-----------------------------------------------
Add new levels by editing the Board.txt file in the \resources directory.
you must separate different levels by a blank line.
for each new level, there should be two numbers on the first line,
indicating the size of the game board, ie. number of rows and columns.

rows - number of lines
columns - number of characters per line

all lines must be of same length. different characters represent different objects.
^ : Cats
* : Cheese
# : Wall
D : Door
F : Key
$ : Gift
  : Empty Space
% : Mouse (the Player)

make sure there is a string EOF at the end of the file to indicate there are
no more levels to the game.     

notes:
Future work:

-Add Key Functions:
F1 - Display Game Instructions
F2 - Toggle Sound ON/OFF
Esc - Exit Game
'q' - Cheat code for level complete

-Add HighScores
