#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

enum AbstractIntervalId {
  Unison,
  Second,
  Third,
  Fourth,
  Fifth,
  Sixth,
  Seventh,
  Octave,
  Ninth,
  Tenth,
  Eleventh,
  Twelfth,
  Thirteenth,
  Fourteenth,
  DoubleOctave
};

enum IntervalId {
  PerfectUnison,
  MinorSecond,
  MajorSecond,
  MinorThird,
  MajorThird,
  PerfectFourth,
  DiminishedFifth,
  PerfectFifth,
  MinorSixth,
  MajorSixth,
  MinorSeventh,
  MajorSeventh,
  PerfectOctave,
  MinorNinth,
  MajorNinth,
  MinorTenth,
  MajorTenth,
  PerfectEleventh,
  DiminishedTwelfth,
  PerfectTwelfth,
  MinorThirteenth,
  MajorThirteenth,
  MinorFourteenth,
  MajorFourteenth,
  PerfectDoubleOctave
};

/******************************************************************************
Chords
******************************************************************************/

namespace Chords {
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
  MinorSixthChord
};

vector<IntervalId> major_triad = { MajorThird, PerfectFifth };
vector<IntervalId> minor_triad = { MinorThird, PerfectFifth };
vector<IntervalId> major_sixth = { MajorThird, PerfectFifth, MajorSixth };
vector<IntervalId> minor_sixth = { MinorThird, PerfectFifth, MinorSixth };
// TODO (Martin): add chords

vector<IntervalId> _chordIntervals[] = {
  major_triad,
  minor_triad,
  major_sixth,
  minor_sixth
};

struct Chord {
  vector<IntervalId> intervals;

  Chord (ChordId id) {
    cout << "chord ";
    intervals = _chordIntervals[id];
    for (auto i : intervals) {
      cout << i << ", ";
    }
    cout << "!" << endl;
  }
};
};

using namespace Chords;

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

  AbstractNote operator +(IntervalId rhs) const {
    return *this + (int)rhs;
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

  Note operator +(IntervalId rhs) const {
    return *this + (int)rhs;
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

bool isLittleEndian() {
  // TODO store this at startup in config
  int x = 1;
  unsigned char *test_endian = (unsigned char*)&x;
  return test_endian[0] == 0;
}

void midiTest () {
  // http://www.music.mcgill.ca/~ich/classes/mumt306/midiformat.pdf

  {
    std::ofstream file("test.mid", std::ios::binary);
    file << "MThd";
    // <Header Chunk> = <chunk type><length><format><ntrks><division>

    // Write MIDI header
    int len = 6; // always 6
    short format = 0; // 0 / 1 / 2 // TODO (Martin): use format 1 instead
    short numTracks = 1;
    short bpm = 96;
    w(file, len, 4);
    w(file, format, 2);
    w(file, numTracks, 2);
    w(file, bpm, 2);

    // Write MIDI track chunks
    file << "MTrk";
    len = 15;
    w(file, len, 4);

    int dt = 0;
    int eventCode = 0xFF58; // time signature
    w(file, dt, 1);
    w(file, eventCode, 2);
    len = 4;
    w(file, len, 1);
    int timeSignatureTop = 4;
    int timeSignatureBottomPower = 2;
    w(file, timeSignatureTop, 1);
    w(file, timeSignatureBottomPower, 1);
    int clocksPerClick = 24;
    int thirtysecondNotesPerClick = 8;
    w(file, clocksPerClick, 1);
    w(file, thirtysecondNotesPerClick, 1);
    
    eventCode = 0xFF51; // tempo
    w(file, dt, 1);
    w(file, eventCode, 2);
    len = 3;
    int microsecondsPerQuarterNote = 500000;
    w(file, len, 1);
    w(file, microsecondsPerQuarterNote, 3);

    eventCode = 0xC0;
    w(file, dt, 1);
    w(file, eventCode, 1);
    int program = 5;
    w(file, program, 1);

    eventCode = 0x90; // Note on
    w(file, dt, 1);
    w(file, eventCode, 1);
    int note = 76; // E4
    int velocity = 32; // piano
    w(file, note, 1);
    w(file, velocity, 1);

    dt = 96;
    eventCode = 0x80; // Note off
    w(file, dt, 1);
    w(file, eventCode, 1);
    w(file, note, 1);
    velocity = 64;
    w(file, velocity, 1);

    dt = 0;
    eventCode = 0xFF2F; // Track end
    int value = 0;
    w(file, dt, 1);
    w(file, eventCode, 2);
    w(file, value, 1);
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
    Note m6 = note + MinorSixth;
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
