# C++ Playground
A repository to show example and play around with c++. It was started just as a playground to test some stuff and explain how things work to coworkers, and I needed to store it somewhere. Feel free to use it within the limits of the GPLv3 license.

Using the gnu c++ compiler, compile the samples with `g++ -o <somefile> <somefile>.cpp` and execute with `./somefile`. I assume you already have a c++ compiler setup. Personally I am using the gnu c++ compiler, but it should work with any c++ compiler.

Make sure to read the comments in the code. They explain how/why things work.

Contents:
* array_playground: play around with arrays and pointers. Double pointers aren't in there.
* eepromtest: this is a sample of how EEPROM works in embedded (arduino) code. Of course the actual communication and storage of the EEPROM memory is not through an array/pointer, but this gets the point across on how arduino's and other EEPROM libraries handle storing a struct (or any arbitrary data) in EEPROM. It covers templates mostly, and builds upon the array_playground.
