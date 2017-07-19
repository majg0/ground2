#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

#include "interval.h"
#include "note.h"

using namespace std;

/******************************************************************************
Chords
******************************************************************************/

enum AbstractChordId {
  TriadChord,
  SixthChord,
  SeventhChord,
  NinthChord,
  EleventhChord,
  ThirteenthChord
};

vector<AbstractIntervalId> triad = { Third, Fifth };
vector<AbstractIntervalId> sixth = { Third, Fifth, Sixth };
vector<AbstractIntervalId> seventh = { Third, Fifth, Seventh };
vector<AbstractIntervalId> ninth = { Third, Fifth, Seventh, Ninth };
vector<AbstractIntervalId> eleventh = { Third, Fifth, Seventh, Ninth, Eleventh };
vector<AbstractIntervalId> thirteenth = { Third, Fifth, Seventh, Ninth, Eleventh, Thirteenth };
// TODO (Martin): add abstract chords

vector<AbstractIntervalId> _abstractChordIntervals[] = {
  triad,
  sixth,
  seventh,
  ninth,
  eleventh,
  thirteenth
};

struct AbstractChord {
  vector<AbstractIntervalId> intervals;

  AbstractChord (AbstractChordId id) {
    cout << "abstract chord ";
    intervals = _abstractChordIntervals[id];
    for (auto i : intervals) {
      cout << i << ", ";
    }
    cout << "!" << endl;
  }
};

enum ChordId {
  MajorTriadChord,
  MinorTriadChord,
  MajorSixthChord,
  MinorSixthChord,
  DominantSeventhSharpNinth
};

vector<Interval> major_triad = { Interval(Third, Major), Interval(Fifth, Perfect) };
vector<Interval> minor_triad = { Interval(Third, Minor), Interval(Fifth, Perfect) };
vector<Interval> major_sixth = { Interval(Third, Major), Interval(Fifth, Perfect), Interval(Sixth, Major) };
vector<Interval> minor_sixth = { Interval(Third, Minor), Interval(Fifth, Perfect), Interval(Sixth, Minor) };
vector<Interval> dominant_seventh_sharp_ninth = { Interval(Third, Major), Interval(Fifth, Perfect), Interval(Seventh, Minor), Interval(Ninth, Augmented) };
// TODO (Martin): add chords

vector<Interval> _chordIntervals[] = {
  major_triad,
  minor_triad,
  major_sixth,
  minor_sixth
};

struct Chord {
  std::vector<Interval> intervals;

  Chord (ChordId id)
  : intervals(_chordIntervals[id]) {
    cout << "chord " << getIntervalsNotation() << endl;
  }

  std::string getIntervalsNotation () {
    std::stringstream ss;
    const auto end = intervals.end() - 1;
    std::for_each(
      intervals.begin(),
      end,
      [&ss] (const Interval& i) { ss << i.getNotation() << ", "; }
    );
    ss << end->getNotation();
    std::string a = ss.str();
    return a;
  }
};

// TODO implement famouschord lookups for notation etc.
// TODO upgrade famouschord to use murmurhash and hashtable, as lookups will be much faster.

/******************************************************************************
other
******************************************************************************/

// void w1 (std::ostream &w, int x) {
//   w << (char)x;
// }

void w (std::ostream &w, int x, int size) {
  const int lasti = size - 1;
  for (int i = 0; i != size; ++i) {
    w << (char)(x >> (lasti - i) * 8);
  }
}

// class Song {
//   std::vector<Instrument> instrumentPool;

//   Song (std::vector<Instrument> _instrumentPool)
//   : instrumentPool(_instrumentPool)
//   {}

//   void writeSong () {
//     // get track count from instrument pool
//     // write some structural data of current chunk
//     // send structural data to instruments, according to current arrangement
//     // write instrument output to each track
//     // output data as midi
//   }

//   void writeFile (const std::string &fileName) {
//     std::ofstream file(fileName, std::ios::binary);
//     // Write MIDI header
//     file << "MThd";
//     w(file, 6, 4); // length of header
//     w(file, 1, 2); // format
//     w(file, numTracks + 1, 2); // numTracks
//     w(file, 96, 2); // tempo
//   }
// };

void midiTest () {
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

int main (int argc, char *argv[]) {
  // cout << *chords[MajorSixth] << endl;
  vector<Chord> chords = {
    Chord(MinorTriadChord),
    Chord(MajorTriadChord)
  };

  {
    Note note(C, FirstLine);
    note + Interval(Sixth, Minor);
  }

  {
    AbstractNote c(C);
    c + 5;
  }

  {
    Chord chord(MinorSixthChord);
  }

  {
    AbstractChord chord(SixthChord);
  }

  midiTest();

  return 0;
}
