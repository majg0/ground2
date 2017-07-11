const FifoDeque = require('./fifo-deque')
const { NOTES } = require('./notes')
const { OCTAVES } = require('./octaves')
const { SCALES } = require('./scales')
const { ABSTRACT_CHORDS, CHORDS } = require('./chords')

const root = NOTES.C
const octave = OCTAVES.FirstLine
const scale = SCALES.Standard
const mode = 0 // ionian if using major scale

function bar (numBeats, numSubdivisions, events) {
  return {
    numBeats,
    numSubdivisions,
    events: events.sort((a, b) => {
      const [beatA, divA] = a.when
      const [beatB, divB] = b.when
      return (beatA / divA) - (beatB / divB) // might need reversing
    })
  }
}

// const bar1 = bar(5, 4, [
//   event(EVENTS.CHORD(CHORDS.MAJOR_TRIAD, NOTES.C), [0, 4]),
//   event(EVENTS.CHORD(CHORDS.MINOR_TRIAD, NOTES.A), [2, 4])
// ])

function instrument (timbre, bottomNote, topNote) {
  return {
    timbre,
    range: [bottomNote, topNote]
  }
}

function generatePart (song, partNumber) {
  // part
  /*
  bars: [bar...],
  instrumentPool: [[id, num]...],
  intensity: 0..1,
  tempo: bpm,
  interpolator: function (a, b, t) => [0..1] // TODO flat, step, lerp, cerp, curve
    // TODO remember motifs in parts
  */

  // const target = {
  //   intensity: 0.5,
  //   tempo: 120
  // }

  // 1. initialize
  if (partNumber === 0) {
    // there is no history yet, make something up
  } else {
    // set my initial data from previous part's target data
  }

  // 2. make up target

  // Compose part
    // Select tempo

    // Create chord progression with time signature info

  //

  // Arrange part
    // Select instruments (timbre, range) (from instrument pool?)

    // Choose who should play when

    // Let each instrument generate something it can play
    // Pass all previous events to current generator
  //

  return {
    partNumber,
    target: {},
    events: [] // event array
  }
}

function createSong (configuration) {
  if (!configuration.numParts) {
    configuration.numParts = Number.POSITIVE_INFINITY
  }

  const {
    numParts,
    numPartsMemorized
  } = configuration

  const song = {
    configuration,
    history: null
  }

  // TODO select generator
  const part = generatePart(song, 0)
  console.log(part)
  song.history = new FifoDeque(numPartsMemorized, part)

  for (let i = 1; i < numParts; ++i) {
    console.log()
    // fill current part
    const part = generatePart(song, i)
    console.log(part)
    const old = song.history.prepend(part)
    if (old) {
      console.log('old', old)
    }

    // play current part

    // |>-----|>-----
    //  play   fill
  }

  console.log('\nend')
  while (song.history.length) {
    console.log('dump', song.history.cut())
  }
}

createSong({
  numParts: 4,
  numPartsMemorized: 2,
  seed: 1337
})

// TODO math: how does lerping tempo affect other timings?
