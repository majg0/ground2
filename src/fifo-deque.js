class FifoDequeNode {
  constructor (value) {
    this.next = null
    this.previous = null
    this.value = value
  }

  prepend (node) {
    if (this.previous) {
      node.previous = this.previous
      this.previous.next = node
    }
    this.previous = node
    node.next = this
    return node
  }

  cut () {
    const prev = this.previous
    if (prev) {
      prev.next = null
      this.previous = null
    }
    return [prev, this]
  }
}

class FifoDeque {
  constructor (capacity, value) {
    this.last = this.head = new FifoDequeNode(value)
    this.length = 1
    this.capacity = capacity
  }

  prepend (value) {
    this.head = this.head.prepend(new FifoDequeNode(value))
    if (++this.length > this.capacity) {
      return this.cut()
    }
  }

  cut () {
    const [last, { value }] = this.last.cut()
    this.last = last
    --this.length
    return value
  }
}

module.exports = FifoDeque
