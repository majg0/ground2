#include <string>
#include <vector>
#include "interval.h"
using namespace std;

const int baseIntervalDistances[] = { 0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24};
const int minorMajorModifierValues[] = { -2, -1, 0, 0, 1, 0 };
const int perfectModifierValues[] = { -1, 0, 0, 0, 1, 0 };
const char modifierNotations[] = {
  'd',
  'm',
  'P',
  'M',
  'A'
};

Interval::Interval(const AbstractIntervalId _intervalId, const IntervalModifierId _modifierId)
: intervalId(_intervalId), modifierId(_modifierId)
{}

const int Interval::getDistance () const {
  int baseDistance = baseIntervalDistances[(int)intervalId];
  int d = baseDistance % 12;
  const int* modifierValues = (d == 0 || d == 5 || d == 7)
    ? perfectModifierValues
    : minorMajorModifierValues;
  return baseDistance + modifierValues[(int)modifierId];
}

const std::string Interval::getNotation () const {
  std::string i = std::to_string(1 + (int)intervalId);
  char n(modifierNotations[(int)modifierId]);
  return n + i;
}
