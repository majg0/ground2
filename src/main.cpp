#include <iostream>
#include "interval.h"
#include "note.h"
#include "chord.h"
#include "midi.h"

using namespace std;

int main (int argc, char *argv[]) {
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
