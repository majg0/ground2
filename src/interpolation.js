function flat () {
  return (a, b, t) => a
}

function step (when) {
  return (a, b, t) => t > when ? b : a
}

function lerp () {
  return (a, b, t) => a * (1 - t) + b * t
}

function cerp () {
  return (a, b, t) => {
    const t2 = 0.5 * (1 - Math.cos(t * Math.PI))
    return a * (1 - t2) + b * t2
  }
}

module.exports = {
  flat,
  step,
  lerp,
  cerp
}
