# SeededRNG
Very samll interface that provides channels for random number generation, and the option to save and load these states.
Channels do not interact with each other (unless you'd like them to by abusing the load_channel function).

Usage should be fairly explanatory:
- #include the interface header
- Create the object with a seed
- Use the add_channel function
- Use the use_channel function

The interface file has some additional information.
