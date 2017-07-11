function stringify (hour, minute, second, frame) {
  return `${hour}:${minute}:${second}:${frame}`
}

function parse (string) {
  const [ hour, minute, second, frame ] = string.split(':')
  return { hour, minute, second, frame }
}

module.exports = {
  stringify,
  parse
}
