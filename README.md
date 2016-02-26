# CSCE315 - Project 2
## Breakthrough Online

***

### Game Mechanics

* **Board Representation** - Showing the board and location of its pieces

 * White = 'o'
	
 * Black = 'x'
	
 * Empty = '_'
	
 * Rows are indexed: 1-8 (bottom to top)
	
 * Columns are indexed: a-h (left to right)
	
 * Client will **always** start with white
	
* **Game State Representation**

  * _State_ class will contain:
	  * `vector< vector< char >> board` - Contains the board pieces
		
		* `int num_moves` - Total number of moves made in the game
		
	* Previous moves/Undo function:
	  * Previous states will be stored in a vector of States. This will allow for "undoing" of moves
		
* **Operators** - Possible moves according to a given piece

|   -   | Moves   |   -   |
| :---: | :---: | :---: |
| Left | Forward | Right |
|   -  |   o/x   |   -   |
| Left | Forward | Right |

* **Operator Validity**

  * Checks to see if a move can legally be done
	
* **Move**

  * Performs the move
	
	* Adds previous State to *Previous States* vector
	
	* Updates the board
	
* **Termination Condition Check** - Checks to see if the game should be over

  * If the game should be over, report the results
	
* **Command Parser**

  * Takes the input commands
	
	* Breaks them down based on delimiters
	
	* Interprets the command's validity
	
	* If the command given was valid, direct it to the appropriate function