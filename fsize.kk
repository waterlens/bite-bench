effect ctl yield(elem: a): unit

type tree<a>
  Empty
  Node(left: tree<a>, right: tree<a>, value: a)

fun tree_filter_iterate(tr: tree<a>, f: a -> bool): yield ()
  match tr
    Empty -> ()
    Node(l, r, v) ->
      tree_filter_iterate(l, f)
      tree_filter_iterate(r, f)
      if f(v) then yield(v)

fun tree_filter_size_direct(tr: tree<a>, f: a -> e bool): e int
  match tr
    Empty -> 0
    Node(l, r, v) ->
      val ls = tree_filter_size_direct(l, f)
      val rs = tree_filter_size_direct(r, f)
      val cur = if f(v) then 1 else 0
      ls + rs + cur

fun tree_filter_size_indirect(tr: tree<a>, f: a -> bool): int
  var num := 0
  with ctl yield(_)
    num := num + 1
    resume()
  tree_filter_iterate(tr, f)
  num

fun generate_tree(d: int, n: int): div tree<int>
  if d == 0 then
    Empty
  else
    val lt = generate_tree(d - 1, n - 1)
    val rt = generate_tree(d - 1, n + 1)
    Node(lt, rt, n)

fun main()
  val tree = generate_tree(10, 3)
  val n1 =
    with ctl yield(_)
      resume()
    tree_filter_size_direct(tree,
      fn (n) {
        yield(n)
        n > 0
      })
  val n2 =
    with ctl yield(_)
      resume()
    tree_filter_size_indirect(tree,
      fn (n) {
        yield(n)
        n > 0
      })
  n1.println
  n2.println