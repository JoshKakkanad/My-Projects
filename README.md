# My-Projects
Some programs I worked on/ developed during my time at UIC

HTTP Server:

  This project was created in C and I developed it within a Linux virtual machine so I could get a better understanding of linux command line arguments when it comes to executing/ developing code. The server only sports simple functionalities, so there isn't much
  technical explanation needed. It utilizes a simple accept loop which accepts clients so long as they are created correctly and allows them to work with these requests: ping, echo, write, read, and stats. Ping simply would respond with pong, echo would repeat back
  to the client the same headers that they had sent in their request, write would take the clients input and save it into a 1024 size buffer and null terminate their input, read would take that saved item from the buffer that was saved using the write call and print it
  back to the user in its response if there is a nothing saved then the string is default to be "<empty>", stats would say how many requests were made and how many errors were thrown from in proper formatting for incorrect filenames etc.

Bomb Game

  This project was a collaborative work between me and my partner Manh Phan in which we used two arduinos to develop a defuse bomb game. The game has three puzzles and makes it so that in order to access the other puzzles the player must solve the previous one except
  in the case of puzzle 3 because we felt that it should be an exception to the rule. The puzzles function as such: puzzle one would have two lights flashing to signify a binary input and we have 4 buttons labled 0, 1, 2, and 3 and the lights would flash in the order
  of 3021 to which the player must press the  buttons in the correct order to solve the puzzle. Puzzle 2 only starts executing once the player had solved the first puzzle this puzzle has 3 questions for the player to solve the first one is quite simple as it is just
  what is 1+1 which obviously is 2. However, the questions get progressively more difficult especially in the third one which would require the player to do some algebra. THe questions are displayed on a LCD screen which scrolls the text in the first row and displays
  the user's input on the second row. The player inputs by using two potentiometers both of which are mapped from 0 to 9 one controls the 10s place while the other controls the 1s place. Once the player has solved both puzzles they're givena hint to solve the last
  puzzle which tells them to use their phone keypad. The hint is "25225" which if decoded correctly would lead the player to see that it is "black" so the player now knows to disconnect the black wire to win the game.


