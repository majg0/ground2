#ifndef GROUND2_CHORD_H
#define GROUND2_CHORD_H
#include <vector>
#include <string>

struct Interval;
enum AbstractIntervalId : int;

enum ChordId : int {
  MajorTriadChord,
  MinorTriadChord,
  MajorSixthChord,
  MinorSixthChord,
  DominantSeventhSharpNinth
};

enum AbstractChordId : int {
  TriadChord,
  SixthChord,
  SeventhChord,
  NinthChord,
  EleventhChord,
  ThirteenthChord
};

struct Chord {
  std::vector<Interval> intervals;

  Chord (ChordId);
  Chord(const std::vector<Interval>& _intervals);

  const std::string getIntervalsNotation () const;
};

struct AbstractChord {
  std::vector<AbstractIntervalId> intervals;
  AbstractChord (const AbstractChordId id);
};

// TODO implement famouschord lookups for notation etc.
// TODO upgrade famouschord to use murmurhash and hashtable, as lookups will be much faster.

#endif
