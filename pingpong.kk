rec effect fun cping(): (() -> <cping, cpong, console, div> ())
rec effect fun cpong(): (() -> <cping, cpong, console, div> ())

fun pinger(i: int, n): <cping, console, div> () {
  println("pinger")
  println(i)
  with fun cpong()
    println("pong handler")
    ({ pinger(i + 1, n) })
  if i < n then cping()() else ()
}

fun ponger(): <cpong, console, div> () {
  println("ponger")
  with fun cping()
    println("ping handler")
    ({ ponger() })
  cpong()()
}

fun main()
  with fun cping()
    println("ping handler@main")
    ({ ponger() })
  pinger(0, 10)
