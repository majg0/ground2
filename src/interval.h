#ifndef GROUND2_INTERVAL_H
#define GROUND2_INTERVAL_H

#include <vector>

enum AbstractIntervalId : int {
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
  DoubleOctave,
  AbstractIntervalId_NUM
};

enum IntervalModifierId {
  Diminished,
  Minor,
  Perfect,
  Major,
  Augmented,
  IntervalModifierId_NUM,
};

struct Interval {
  AbstractIntervalId intervalId;
  IntervalModifierId modifierId;

  Interval (AbstractIntervalId, IntervalModifierId);

  const int getDistance () const;
  const std::string getNotation () const;
};


#endif
