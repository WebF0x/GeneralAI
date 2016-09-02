StrongAI
=========

Core principles
---------------
These core principles guide the project's development:

- Quality - StrongAI must take intelligent decisions
- Versatility - StrongAI must be adaptable to any type of problems
- Simplicity - StrongAI must be easy to use and understand
- Freedom - StrongAI must respect the user's [freedom](https://www.gnu.org/philosophy/free-sw.html)

Current plan
------------
- Make a general AI that can play any type of game
- Transpose real world problems as games
- Use the AI to solve them

Example
-------
Let's pretend we want an AI to drive a car. We'll need to somehow hook it to its environment. 
- Input. It may need to know: its position, its destination, the position of obstacles, etc.
- Output. It may need to control: the gas and break pedals, the force on the steering wheel, the turn signals, etc.

Now we need a way to measure its performance. We'll use what's called a fitness function that tests the AI and returns its fitness score. This score might:
- Increase as the time of travel goes down
- Decrease as it goes over the speed limit or crushes innocent citizens

This fitness function might initially test the AI in a simulated driving environment before moving on to a closed circuit and finally to the real world as our confidence in the AI increases.

If everything goes well, we now have our own car driving AI!

What we have
============

AI's
----
- [GeneralAI](https://github.com/WebF0x/StrongAI/tree/master/include/StrongAI/AI/GeneralAI "The starting point") - Common interface of all AI's
- [RandomAI](https://github.com/WebF0x/StrongAI/tree/master/include/StrongAI/AI/RandomAI "As dumb as it gets") - Takes random decisions
- [HumanAI](https://github.com/WebF0x/StrongAI/tree/master/include/StrongAI/AI/HumanAI "Take the commands") - You manually control the AI
- [CaseBasedAI](https://github.com/WebF0x/StrongAI/tree/master/include/StrongAI/AI/CaseBasedAI "May the brute force be with you") - A brute force approach
- [NeuralNetAI](https://github.com/WebF0x/StrongAI/tree/master/include/StrongAI/AI/NeuralNetAI "Pale imitation of nature's greatest achievement") - Simple mutating artificial neural network
- [DarwinAI](https://github.com/WebF0x/StrongAI/tree/master/include/StrongAI/AI/NeuralNetAI "Thanks Darwin") - Evolves a NeuralNetAI population by natural selection

Others
----------
- [Cereal](https://github.com/USCiLab/cereal "cereal, a C++11 library for serialization by University of South California") - A C++11 library for serialization
- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp/ "A lightweight unit testing framework for C++") - A lightweight unit testing framework for C++

Brainstorm
============

Send your ideas at: webf0x@hotmail.com

AI's
----
- NAND gates AI
- Dispatcher - Separate tasks in subtasks

Worlds
------
- Interface with any game/software - Audio/video input and keyboard/mouse output
- Deterministic games - Chess, Checkers, Reversi, etc
- Chance games - Poker, Blackjack, Backgammon, Minesweeper, Solitaire
- Real-time games - Minecraft, Starcraft, Heroes of the Storm
- Robots - Sensors and actuators

Build instructions
------------------
- Linux: `make tests`

Unlicense:
--------
[Unlicense Yourself: Set Your Code Free](http://unlicense.org/ "Unlicense Yourself: Set Your Code Free")
