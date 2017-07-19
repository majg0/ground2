#include <string>
#include "interval.h"
#include "note.h"

AbstractNote::AbstractNote(NoteId _noteId)
: noteId(_noteId)
{}

AbstractNote AbstractNote::operator+(int rhs) const {
  int nc = (int)noteId + rhs;
  int n = nc % 12;
  return AbstractNote((NoteId)n);
}

AbstractNote AbstractNote::operator+(const Interval& rhs) const {
  return *this + rhs.getDistance();
}

Note::Note(NoteId _noteId)
: noteId(_noteId), octaveId(FirstLine)
{}

Note::Note(NoteId _noteId, OctaveId _octaveId)
: noteId(_noteId), octaveId(_octaveId)
{}

const std::string Note::toString () const {
  return std::string("C"); // TODO
}

Note Note::operator+(int rhs) const {
  int nc = (int)noteId + rhs;
  int n = nc % 12;
  int oc = nc / 12;
  int o = (int)octaveId + oc;
  return Note((NoteId)n, (OctaveId)o);
}

Note Note::operator+(const Interval& rhs) const {
  return *this + rhs.getDistance();
}

