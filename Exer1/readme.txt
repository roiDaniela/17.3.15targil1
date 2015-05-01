theMathGame
Student Name 1 Motty Katz ID  036753234 Class Group: maof B
Student Name 2 Roi Fogler ID  302882527 Class Group: maof B

General Descrbtion:
In this game there are 2 players who needs to solve mathematical equations which includes 4 aretmetical operators (+,-,*,/).
The operator and the exercise selected randomlly by the game.
One of the varibles is missing and 2 players have to complete the equations. The players are in competition who fills more equaations.
The total range of the missing varibles is between (1 - 99).
The players has 3 errors, and if the players or both of them eats wrong numbers they are dead, if its the right number he get a point andmoving on to the next level.
The winner is the player who scored the heigest number of points.

FYI:
* We chose to randomise a number to the screen 1 to 5 iteratuions in order to make it friendly and efficient.
* 

classes:

TheMathGame: This file responsible for the logical part of the game. its realizes the exercise and moves the players.
             The 2 major methods are: startLevel, doIteration. we added other helper methods to realize the logic.
Sign: This file declares a class with an enum for the possible signs.
ScreenData: This file is the DATA BASE of the game. its saves all locations and values on the screen.
	    it uses "map" instead of 2 large matrix (mat[80][24]) in order to save memory.
randomOutput: This file represents the random output (numbers, points, signs) in the game.
Point: This file responsible for the new type: Point. this type is neccessery beacuse we want to respresnt location
       of the values\players on the screen
Player: This file is responsible to the new type = player: players in the game. here we set the players locations. signs and moves
        All the data on the players should be on this member.
IspercificGame: ISpecificGame is an abstract base class without any implementation.
               (We call such a class "interface" though there are no interfaces in C++).
                This class is the base class for any actual game that wants to be managed by GameManager.
                All relevant operations that GameManager needs from an actual game will be declared here, however specific operations
                which are specific for a certain game and are not generic will not be declared here.
                NOTE that this class doesn't have any cpp file as there are NO actual implemenations, only signatures.
io_utils: This file is not a oop class, its responsible to all the io global functions. 
GameManager: GameManager is the top level manager, the game starts from here.
             This class manages the game iterations, menus etc., but WITHOUT knowing anything about the actual game itself.
Direction: This file declares a class with an enum for the possible directions, including "STAY" which we consider as direction
CreateExercise: This file responsible on the type: "exercise". this type shuold carries the exercise and its solution:
	        The exercise to show and the hidden value. it is specialy for the guide of this game
Config: windows / linux
Color: enum for colors.