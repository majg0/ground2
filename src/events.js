function event (what, when) {
  return { what, when }
}

// TODO make module
const EVENTS = {
  CHORD: (chord, root) => ({ chord, root })
}

module.exports = {
  event,
  EVENTS
}
