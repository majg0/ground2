
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "interval.h"
#include "chord.h"

using namespace std;

const std::vector<AbstractIntervalId> triad = { Third, Fifth };
const std::vector<AbstractIntervalId> sixth = { Third, Fifth, Sixth };
const std::vector<AbstractIntervalId> seventh = { Third, Fifth, Seventh };
const std::vector<AbstractIntervalId> ninth = { Third, Fifth, Seventh, Ninth };
const std::vector<AbstractIntervalId> eleventh = { Third, Fifth, Seventh, Ninth, Eleventh };
const std::vector<AbstractIntervalId> thirteenth = { Third, Fifth, Seventh, Ninth, Eleventh, Thirteenth };
// TODO (Martin): add abstract chords

const std::vector<AbstractIntervalId> _abstractChordIntervals[] = {
  triad,
  sixth,
  seventh,
  ninth,
  eleventh,
  thirteenth
};

const std::vector<Interval> major_triad = { Interval(Third, Major), Interval(Fifth, Perfect) };
const std::vector<Interval> minor_triad = { Interval(Third, Minor), Interval(Fifth, Perfect) };
const std::vector<Interval> major_sixth = { Interval(Third, Major), Interval(Fifth, Perfect), Interval(Sixth, Major) };
const std::vector<Interval> minor_sixth = { Interval(Third, Minor), Interval(Fifth, Perfect), Interval(Sixth, Minor) };
const std::vector<Interval> dominant_seventh_sharp_ninth = { Interval(Third, Major), Interval(Fifth, Perfect), Interval(Seventh, Minor), Interval(Ninth, Augmented) };
// TODO (Martin): add chords

const std::vector<Interval> _chordIntervals[] = {
  major_triad,
  minor_triad,
  major_sixth,
  minor_sixth
};


Chord::Chord(ChordId id) : intervals(_chordIntervals[id]) {
  cout << "chord " << getIntervalsNotation() << endl;
}

std::string Chord::getIntervalsNotation () {
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


AbstractChord::AbstractChord (AbstractChordId id) {
  cout << "abstract chord ";
  intervals = _abstractChordIntervals[id];
  for (auto i : intervals) {
    cout << i << ", ";
  }
  cout << "!" << endl;
}
