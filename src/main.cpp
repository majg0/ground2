#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

#include "interval.h"

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

enum NoteId {
  C,
  Db,
  D,
  Eb,
  E,
  F,
  Gb,
  G,
  Ab,
  A,
  Bb,
  B,
  NUM
};

enum OctaveId {
  DoubleContra = -5,
  SubContra,
  Contra,
  Great,
  Small,
  FirstLine = 0,
  SecondLine,
  ThirdLine,
  FourthLine,
  FifthLine,
  SixthLine
};

struct AbstractNote {
  NoteId noteId;

  AbstractNote (NoteId id)
  : noteId(id) {
    cout << "abstract note " << id << endl;
  }

  AbstractNote operator +(int rhs) const {
    int nc = (int)noteId + rhs;
    int n = nc % 12;
    return AbstractNote((NoteId)n);
  }

  AbstractNote operator +(Interval rhs) const {
    return *this + rhs.getDistance();
  }
};

struct Note {
  NoteId noteId;
  OctaveId octaveId;

  Note (NoteId nid)
  : noteId(nid), octaveId(FirstLine) {
    cout << "note " << noteId << " in " << octaveId << endl;
  }

  Note (NoteId nid, OctaveId oid)
  : noteId(nid), octaveId(oid) {
    cout << "note " << noteId << " in " << octaveId << endl;
  }

  const char* toString () {
    return "C";
  }

  Note operator +(int rhs) const {
    int nc = (int)noteId + rhs;
    int n = nc % 12;
    int oc = nc / 12;
    int o = (int)octaveId + oc;
    return Note((NoteId)n, (OctaveId)o);
  }

  Note operator +(Interval rhs) const {
    return *this + rhs.getDistance();
  }
};

void w (std::ofstream &file, int x, uint size) {
  char b[size];
  const int lasti = size - 1;
  for (int i = 0; i != size; ++i) {
    b[i] = (char)(x >> (lasti - i) * 8u);
  }
  file.write(b, size);
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
    file << "MThd";
    // <Header Chunk> = <chunk type><length><format><ntrks><division>

    // Write MIDI header
    w(file, 6, 4); // length of header
    w(file, 0, 2); // format
    w(file, 1, 2); // numTracks
    w(file, 96, 2); // tempo

    // Write MIDI track chunks
    file << "MTrk";
    w(file, 30, 4);

    w(file, 0, 1); // delta time
    w(file, 0xFF58, 2); // event code: time signature
    w(file, 4, 1); // event length
    w(file, 4, 1); // top time signature number
    w(file, 2, 1); // bottom time signature power
    w(file, 24, 1); // clocks per click
    w(file, 8, 1); // thirtytwo-notes per click
    
    w(file, 0, 1); // delta time
    w(file, 0xFF51, 2); // set tempo
    w(file, 3, 1); // numBytes
    w(file, 500000, 3); // microseconds per quarter note

    w(file, 0, 1); // delta time
    w(file, 0xC0, 1); // set program
    w(file, 5, 1); // TODO parse 5 ??

    w(file, 0, 1); // delta time
    w(file, 0x90, 1); // note on
    w(file, 76, 1); // note, E4
    w(file, 32, 1); // velocity piano

    w(file, 96, 1); // delta time
    w(file, 0x80, 1); // Note off
    w(file, 76, 1); // note, E4
    w(file, 64, 1); // velocity

    w(file, 0, 1); // delta time
    w(file, 0xFF2F, 2); // Track end
    w(file, 0, 1); // obligatory end
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