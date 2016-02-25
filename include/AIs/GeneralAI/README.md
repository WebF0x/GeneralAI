GeneralAI
=========

All AI's should inherit from this. It provides an interface to methods common to all AI's

Interface
---------
- Input and output validation
- Learning
- Save/load mechanism - Supports binary, JSON and XML formats

How to use
----------
First, download and extract [cereal](https://github.com/USCiLab/cereal "C++11 Serialization library by University of Southern California"). It can be anywhere, for example: "C:\Program Files (x86)\CodeBlocks\cereal-X.Y.Z"

Here's how to setup your project with Code::Blocks:
- Project - Build options... - Search directories - Add - "PATH_TO_CEREAL_FOLDER\cereal-X.Y.Z\include"

Or for all your projects: 
- Settings - Compiler... - Search directories - "PATH_TO_CEREAL_FOLDER\cereal-X.Y.Z\include"

Now, you can use this as your starting point: [ExampleAI](./ExampleAI "Minimalistic code for subclasses of GeneralAI")!


Thanks
------
University of Southern California - The makers of [cereal](https://github.com/USCiLab/cereal "C++11 Serialization library by University of Southern California")!
