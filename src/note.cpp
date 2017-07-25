#include <string>
#include "interval.h"
#include "note.h"

AbstractNote::AbstractNote(const NoteId _noteId)
: noteId(_noteId)
{}

const AbstractNote AbstractNote::operator+(const int rhs) const {
  int nc = (int)noteId + rhs;
  int n = nc % 12;
  return AbstractNote((NoteId)n);
}

const AbstractNote AbstractNote::operator+(const Interval& rhs) const {
  return *this + rhs.getDistance();
}

Note::Note()
: noteId(C), octaveId(FirstLine)
{}

Note::Note(const NoteId _noteId)
: noteId(_noteId), octaveId(FirstLine)
{}

Note::Note(const NoteId _noteId, const OctaveId _octaveId)
: noteId(_noteId), octaveId(_octaveId)
{}

const std::string Note::toString () const {
  return std::string("C"); // TODO
}

const Note Note::operator+(const int rhs) const {
  int nc = (int)noteId + rhs;
  int n = nc % 12;
  int oc = nc / 12;
  int o = (int)octaveId + oc;
  return Note((NoteId)n, (OctaveId)o);
}

const Note Note::operator+(const Interval& rhs) const {
  return *this + rhs.getDistance();
}

