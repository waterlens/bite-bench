import std/num/int32

effect val ask : int

linear effect st 
  fun get() : int32
  fun put(i : int32)  : ()

fun state( i : int32, action : () -> <st|e> a ) : e a 
  var s := i
  handle action
    fun get()  s
    fun put(x) s := x    

fun reader( init : int, action ) 
  println("enter reader " ++ init.show)
  with finally { println("leave reader " ++ init.show) }
  with val ask = init
  action()

fun counter( c : int32 ) : _ int 
  val i = get()
  if i==zero then c.int else 
    put(i.dec)
    counter(c.inc)

pub fun main() 
  with state(100100100.int32)
  with reader(0)
  with reader(1)
  with reader(2)
  with reader(3)
  with reader(4)
  counter(zero).println