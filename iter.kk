type mlist<h, a>
  MNil
  MCons(x: ref<h, a>, y: ref<h, mlist<h, a>>)

effect fun replace(v: int): ()
effect fun behead(): ()
effect ctl yield(v: int): (() -> <replace, behead> ())


fun iter(l: mlist<h, int>, i: int): <yield, behead, read<h>, write<h>, alloc<h>, div> ()
  match l
    MCons(hd, tl) ->
      with fun replace(x)
        hd := x
      yield(!hd)()
      if (!tl).is-mcons then
        with fun behead()
          match !tl
            MCons(_, tl') -> tl := !tl'
            _ -> ()
        iter(!tl, i + 1)
    _ -> ()

fun mlist_to_list(m: mlist<h, a>): <read<h>, div> list<a>
  match m
    MCons(hd, tl) -> Cons(!hd, mlist_to_list(!tl))
    MNil -> Nil

fun list_to_mlist(l: list<a>): <write<h>, alloc<h>, div> mlist<h, a>
  match l
    Cons(hd, tl) -> MCons(ref(hd), ref(list_to_mlist(tl)))
    Nil -> MNil

fun main()
  var ls := [0, 1, 3, -2, -8, 9]
  var mls := list_to_mlist(ls)

  with ctl yield(x)
    resume ({ if x < 0 then behead()
              else replace(x * 2) })
  with fun behead()
    match mls
      MCons(_, tl) -> mls := !tl
      _ -> ()
  iter(mls, 0)

  println(mls.mlist_to_list.show-list(show))