#ifndef GROUND2_INTERVAL_H
#define GROUND2_INTERVAL_H

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

enum IntervalModifierId {
  Diminished,
  Minor,
  Perfect,
  Major,
  Augmented,
  Unspecified_NUM,
};

struct Interval {
  AbstractIntervalId intervalId;
  IntervalModifierId modifierId;
  
  Interval (AbstractIntervalId, IntervalModifierId);

  const int getDistance () const;
  const std::string getNotation () const;
};

#endif
