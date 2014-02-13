GeneralAI
=========

All AI's must inherit from GeneralAI. It provides an intuitive interface for users.

Interface
---------
- Constructor(input and output size and amplitude)
- Output output(input)
- void learn(lesson)
- Lesson lastLessonLearned()
- void save(fileName)
- void load(fileName)
- void reset() //Basically, clear short-term memory but remember long-term memory  e.g.: Starting new game
