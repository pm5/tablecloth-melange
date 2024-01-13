type nonrec t('a, 'b) = ('a, 'b);
let make = (a, b) => (a, b);
let fromArray = array =>
  switch (array) {
  | [||]
  | [|_|] => None
  | [|a, b|] => Some((a, b))
  | _ => Some((array[0], array[1]))
  };
let fromList = list =>
  switch (list) {
  | []
  | [_] => None
  | [a, b, ..._rest] => Some((a, b))
  };
let first = ((a, _)) => a;
let second = ((_, b)) => b;
let mapFirst = ((a, b), ~f as [@ns.namedArgLoc] f) => (f(a), b);
let mapSecond = ((a, b), ~f as [@ns.namedArgLoc] f) => (a, f(b));
let mapEach = ((a, b), ~f as [@ns.namedArgLoc] f, ~g as [@ns.namedArgLoc] g) => (
  f(a),
  g(b),
);
let mapAll = ((a1, a2), ~f as [@ns.namedArgLoc] f) => (f(a1), f(a2));
let swap = ((a, b)) => (b, a);
let toArray = ((a, b)) => [|a, b|];
let toList = ((a, b)) => [a, b];
let equal = ((a, b), (a', b'), equalFirst, equalSecond) =>
  equalFirst(a, a') && equalSecond(b, b');
let compare =
    (
      (a, b),
      (a', b'),
      ~f as [@ns.namedArgLoc] compareFirst,
      ~g as [@ns.namedArgLoc] compareSecond,
    ) =>
  switch (compareFirst(a, a')) {
  | 0 => compareSecond(b, b')
  | result => result
  };
