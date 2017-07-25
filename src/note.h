#ifndef GROUND2_NOTE_H
#define GROUND2_NOTE_H

enum NoteId : int {
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
  NoteId_NUM
};

enum OctaveId : int {
  DoubleContra,
  SubContra,
  Contra,
  Great,
  Small,
  FirstLine,
  SecondLine,
  ThirdLine,
  FourthLine,
  FifthLine,
  SixthLine,
  OctaveId_NUM
};

struct Interval;

struct AbstractNote {
  NoteId noteId;

  AbstractNote (const NoteId);

  const AbstractNote operator +(const int rhs) const;
  const AbstractNote operator +(const Interval& rhs) const;
};

struct Note {
  NoteId noteId;
  OctaveId octaveId;

  Note ();
  Note (const NoteId nid);
  Note (const NoteId nid, const OctaveId oid);

  const std::string toString () const; // TODO rename to reflect type of string?

  const Note operator +(int rhs) const;
  const Note operator +(const Interval& rhs) const;
};

#endif
