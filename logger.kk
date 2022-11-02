linear effect fun log(s: string): ()

fun call_f(arg: a, f: a -> log b ): <console, log> b
  with fun log(s: string)
    println(s)
  log("# before call f()")
  val b = mask<log>(fn () f(arg))
  log("# after call f()")
  b

fun main()
  with fun log(s: string)
    ()
  call_f(1, fn (_) log("# do not print to console"))