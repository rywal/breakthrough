# Breakthrough Online

Contains a C++ server and Java GUI to play breakthrough game. The game server supports network play and can be accessed by connectiong to the host and port via `telnet`. The server supports three game methods:
* Human to Human
  * Turn based play, locally via command-line interface or the Java GUI
* Human to AI
  * Turn based play, locally via command-line interface or the Java GUI
  * AI has three difficulties:
    * *Easy*: uses a random algorithm to pick the next move
    * *Medium*: uses minimax algorithm at a depth of 4 to determine the best move for the AI
    * *Hard*: uses minimax algorithm with alpha-beta pruning
* AI to AI
  * Direct two servers to play each other with their respective AIs.

Client-Server protocol:
```
statement           ::= password | command | move | comment
password            ::= arbitrary string
command             ::= EXIT 
                    | DISPLAY 
                    | UNDO 
                    | HUMAN-HUMAN
                    | HUMAN-AI difficulty
                    |AI-AI server port password my-difficulty opponent-difficulty
move                ::= column row move-dir
move-dir            ::= FWD | LEFT | RIGHT
difficulty          ::= EASY | MEDIUM | HARD
my-difficulty       ::= difficulty
opponent-difficulty	::= difficulty
comment	            ::= ; *
column	            ::= a | b | c | d | e | f | g
row                 ::= 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8
server              ::= IP address or hostname
port                ::= positive integer
```

Command descriptions:
* `EXIT`: exit and disconnect from the server
* `DISPLAY`: toggles board display
* `UNDO`: undo AI's move and your last move. Up to 10 UNDOs are supported.
* `HUMAN-HUMAN`: human against human. Match up users as they connect.
* `HUMAN-AI difficulty`: human client against server AI with the selected difficulty.
* `AI-AI server port password my-difficulty opponent-difficulty`: this server's AI against another server's AI running on server port. password is the other server's password. my-difficulty and opponent-difficulty sets the AI's difficulty level on the client side and the server side, respectively.

###Compile##

* To compile the game, use `make breakthrough`
* To compile and run the Java GUI, use `make gui`

###Run###

* To run the game executable, use `./breakthrough [port number (default: 5155)]`

###Server Password###
* Use password `breakthrough` to connect to server

***
_Created as part of CSCE 315 at Texas A&M University. Some parts of this Readme borrowed from Project 2 Outline created by Dr. Choe_

Contributors:
* Ryan Walters
* Nathan Blattman
* Jonathan Grimes
* Victor Vasquez
