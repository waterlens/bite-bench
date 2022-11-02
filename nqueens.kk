effect search
  ctl choose(n: int): int
  ctl fail(): ()

fun safe(queen: int, diag: int, solution: list<int>): bool
  match solution
    Nil -> True
    Cons(q, qs) -> queen != q &&
                   queen != q + diag &&
                   queen != q - diag &&
                   safe (queen, diag + 1, qs)

fun find_solutions(n: int, col: int): <div, search> list<int>
  if col == 0 then
    Nil
  else
    val sol = find_solutions(n, col - 1)
    val queen = choose(n)
    if safe(queen, 1, sol) then
      Cons(queen, sol)
    else
      fail()
      Nil

fun count_solutions(n: int): div int
  with handler
    ctl fail() 0
    ctl choose(n1) {
      fun loop(i: int, acc: int): div int {
        if i == n1 then
          resume(i) + acc
        else
          loop(i+1, resume(i) + acc)
      }
      loop(1, 0)
    }
  find_solutions(n, n)
  1

fun main()
  count_solutions(8).println