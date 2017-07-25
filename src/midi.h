#ifndef GROUND_MIDI_H
#define GROUND_MIDI_H
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>

inline void w (std::ostream &w, int x, int size) {
  const int lasti = size - 1;
  for (int i = 0; i != size; ++i) {
    w << (char)(x >> (lasti - i) * 8);
  }
}

inline void midiTest () {
  // http://www.music.mcgill.ca/~ich/classes/mumt306/midiformat.pdf
  {
    std::ofstream file("test.mid", std::ios::binary);

    // Write MIDI header
    file << "MThd";
    w(file, 6, 4); // header length
    w(file, 0, 2); // format
    w(file, 1, 2); // numTracks
    w(file, 96, 2); // division

    // Write MIDI track chunks
    {
      std::stringstream track;

      w(track, 0, 1); // delta time
      w(track, 0xFF58, 2); // event code: time signature
      w(track, 4, 1); // event length
      w(track, 4, 1); // top time signature number
      w(track, 2, 1); // bottom time signature power
      w(track, 24, 1); // clocks per click
      w(track, 8, 1); // thirtytwo-notes per click

      w(track, 0, 1); // delta time
      w(track, 0xFF51, 2); // set tempo
      w(track, 3, 1); // numBytes
      w(track, 500000, 3); // microseconds per quarter note

      w(track, 0, 1); // delta time
      w(track, 0xC0, 1); // set program
      w(track, 5, 1); // TODO parse 5 ??

      w(track, 0, 1); // delta time
      w(track, 0x90, 1); // note on
      w(track, 76, 1); // note, E4
      w(track, 32, 1); // velocity piano

      w(track, 96, 1); // delta time
      w(track, 0x80, 1); // Note off
      w(track, 76, 1); // note, E4
      w(track, 64, 1); // velocity

      w(track, 0, 1); // delta time
      w(track, 0xFF2F, 2); // Track end
      w(track, 0, 1); // obligatory end

      file << "MTrk";
      std::streampos len = track.tellp();
      w(file, len, 4);
      file << track.rdbuf();
    }
  }
}

#endif
