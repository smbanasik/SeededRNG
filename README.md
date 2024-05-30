# SeededRNG
A simple interace that provides a savable random number generation state. I utilized a channel system so users only need to instantiate one class.
As an experiemnt, I implemented this interface using the PIMPL method, so as long as the interface remains the same, a user would only need to recompile the 
`.cpp` file instead of everything that the interface touches.

I may consider redoing the interface to provide a better method of accessing RNG channels, since it falls onto the user to handle that information right now.

## Adding to a project

To add to a project, add the two header files to the director where your headers are, and add the source file to the directory where your source files are.

## Usage

Usage should be fairly explanatory:
- #include the interface header
- Create the object with a seed
- Use the `add_channel` function to create an RNG channel
  - Modifying a channel's minimum and maximum parameters can be done with `config_channel`
  - Removing a channel may be done with `remove_channel`
- Call the `use_channel` function to retrieve a channels output
- It is up to the user to keep track of what channels are what,
  - `get_num_channels` provides the number of active channels
- For saving the state, of a channel, call `save_channel`
  - This number must be stored by the user
- To load the state, call `load_channel` with a number provided by `save_channel`
