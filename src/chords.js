const ABSTRACT_CHORDS = {
  Triad: [2, 4],
  Sixth: [2, 4, 5],
  Seventh: [2, 4, 6],
  Ninth: [1, 2, 4, 6],
  Eleventh: [1, 2, 3, 4, 6],
  Thirteenth: [1, 2, 3, 4, 5, 6]
}

const CHORDS = {
  MAJOR_TRIAD: [4, 7],
  MINOR_TRIAD: [3, 7],
  MAJOR_SIXTH: [4, 7, 9],
  MINOR_SIXTH: [3, 7, 8]
}

module.exports = {
  ABSTRACT_CHORDS,
  CHORDS
}
