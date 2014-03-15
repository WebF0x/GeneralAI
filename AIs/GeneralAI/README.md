GeneralAI
=========

All AI's should inherit from this. It provides an interface to methods common to all AI's

Interface
---------
- Input and output validation
- Save/load mechanism - Supports binary, JSON and XML formats

How to use
----------
Use this as your starting point: [ExampleAI](./ExampleAI "Minimalistic code for subclasses of GeneralAI")!

Make sure your compiler can find the [cereal library](https://github.com/USCiLab/cereal "C++11 Serialization library by University of Southern California").

Here's how to setup Code::Blocks :
- Project - Build options... - Search directories - Add - "PATH_TO_CEREAL_FOLDER\cereal-X.Y.Z\include"
- Or for all your projects: Settings - Compiler... - Search directories - "PATH_TO_CEREAL_FOLDER\cereal-X.Y.Z\include"


Thanks
------
University of Southern California - The makers of [cereal](https://github.com/USCiLab/cereal "C++11 Serialization library by University of Southern California")!
