#ifndef GROUND2_CHORD_H
#define GROUND2_CHORD_H
#include <vector>
#include <string>

enum AbstractChordId {
  TriadChord,
  SixthChord,
  SeventhChord,
  NinthChord,
  EleventhChord,
  ThirteenthChord
};

enum ChordId {
  MajorTriadChord,
  MinorTriadChord,
  MajorSixthChord,
  MinorSixthChord,
  DominantSeventhSharpNinth
};

struct Interval;
struct Chord {
  Chord (ChordId);

  std::vector<Interval> intervals;
  std::string getIntervalsNotation ();
  };

enum AbstractIntervalId : int;

struct AbstractChord {
  std::vector<AbstractIntervalId> intervals;
  AbstractChord (AbstractChordId id);
  };


#endif
