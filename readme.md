Ground 2
========


Development plan
================

See Zenboard on github.
Here's an initial sketch of what's required.

1. Music theory lib
    - Create a good music theory library of modular functionality that can later be used by generators
    - Write some demo example
  
1. Synthesis lib
    - Create some wave types
    - Implement filter chaining
    - Implement ADSR filter
    - Implement reverb filter
    - Write some demo examples

1. Sound mixer lib
    - Use synthesis lib and write a mixer
    - Write some demo examples

1. Generator lib
    - Write a generator library. It should be possible to send commands to a generator while it's running.
    - There will probably be many generators running at once; one for the large scale structure of the piece(s), one per instrument, and probably lots of others. They may or may not appear in tree-like structures. Let's flesh that out while it's implemented. We may want to do this with [Rx streams](https://github.com/Reactive-Extensions/RxCpp).
    - Write some demo examples.

1. Music parser
    - Make a parser converting generator output to sounds

1. Connect the dots
    - Write a generator and connect it to a synth

1. Optimize
    - Make it all run smoothly

1. Later TODOs
    - Sampling
    - FFT of samples
    - Synthesis from Fourier coefficients

Form
----

1. Add features
