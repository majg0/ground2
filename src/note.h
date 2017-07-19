#ifndef GROUND2_NOTE_H
#define GROUND2_NOTE_H

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
  NoteId_NUM
};

enum OctaveId {
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

  AbstractNote (NoteId);

  AbstractNote operator +(int rhs) const;
  AbstractNote operator +(const Interval& rhs) const;
};

struct Note {
  NoteId noteId;
  OctaveId octaveId;

  Note (NoteId nid);
  Note (NoteId nid, OctaveId oid);

  const std::string toString () const; // TODO rename to reflect type of string?

  Note operator +(int rhs) const;
  Note operator +(const Interval& rhs) const;
};

#endif
