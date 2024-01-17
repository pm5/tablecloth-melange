/** */;
/** A [Map] represents a unique mapping from keys to values.

    [Map] is an immutable data structure which means operations like {!Map.add} and {!Map.remove} do not modify the data structure, but return a new map with the desired changes.

    Since maps of [int]s and [string]s are so common the specialized {!Map.Int} and {!Map.String} modules are available, which offer a convenient way to construct new maps.

    Custom data types can be used with maps as long as the module satisfies the {!Comparator.S} interface.

    {[
      module Point = {
        type t = (int, int)
        let compare = Tuple2.compare(~f=Int.compare, ~g=Int.compare)
        include Comparator.Make({
          type t = t
          let compare = compare
        })
      }

      type animal
        | Cow
        | Pig
        | Alpacca

      let pointToAnimal = Map.fromArray(
        module(Point),
        [((0, 0), Alpacca), ((3, 4), Cow), ((6, 7), Pig)],
      )
     ]}

    See the {!Comparator} module for a more details.
*/;
type nonrec t('key, 'value, 'cmp) = Belt.Map.t('key, 'value, 'cmp);
/** {1 Create}

    You can create sets of modules types which conform to the {!Comparator.S} signature by using {!empty}, {!singleton}, {!fromList} or {!fromArray}.

    Specialised versions of the {!empty}, {!singleton}, {!fromList} and {!fromArray} functions available in the {!Set.Int} and {!Set.String} sub-modules.
*/;
/** A map with nothing in it.

    Often used as an intial value for functions like {!Array.fold}.

    {2 Examples}

    {[
      Array.fold(["Pear", "Orange", "Grapefruit"], ~initial=Map.empty(module(Int)), ~f=(
        lengthToFruit,
        fruit,
      ) => Map.add(lengthToFruit, ~key=String.length(fruit), ~value=fruit))->Map.toArray ==
      [(4, "Pear"), (6, "Orange"), (10, "Grapefruit")]
     ]}

    In this particular case you might want to use {!Array.groupBy}
*/
external empty:
  TableclothComparator.s('key, 'identity) => t('key, 'value, 'identity)
  ;
/** Create a map from a key and value.

    {2 Examples}

    {[
      Map.singleton(module(Int), ~key=1, ~value="Ant")->Map.toArray == [(1, "Ant")]
    ]}
*/
external singleton:
  (
    TableclothComparator.s('key, 'identity),
    ~key: [@ns.namedArgLoc] 'key,
    ~value: [@ns.namedArgLoc] 'value
  ) =>
  t('key, 'value, 'identity)
  ;
/** Create a map from an {!Array} of key-value tuples. */
external fromArray:
  (TableclothComparator.s('key, 'identity), array(('key, 'value))) =>
  t('key, 'value, 'identity)
  ;
/** Create a map of a {!List} of key-value tuples. */
external fromList:
  (TableclothComparator.s('key, 'identity), list(('key, 'value))) =>
  t('key, 'value, 'identity)
  ;
/** {1 Basic operations} */;
/** Adds a new entry to a map. If [key] is allready present, its previous value is replaced with [value].

    {2 Examples}

    {[
      Map.add(
        Map.Int.fromArray([(1, "Ant"), (2, "Bat")]),
        ~key=3,
        ~value="Cat",
      )->Map.toArray == [(1, "Ant"), (2, "Bat"), (3, "Cat")]

      Map.add(
        Map.Int.fromArray([(1, "Ant"), (2, "Bat")]),
        ~key=2,
        ~value="Bug",
      )->Map.toArray == [(1, "Ant"), (2, "Bug")]
     ]}
*/
external add:
  (
    t('key, 'value, 'id),
    ~key: [@ns.namedArgLoc] 'key,
    ~value: [@ns.namedArgLoc] 'value
  ) =>
  t('key, 'value, 'id)
  ;
/** Removes a key-value pair from a map based on they provided key.

    {2 Examples}

    {[
      let animalPopulations = Map.String.fromArray([
        ("Elephant", 3_156),
        ("Mosquito", 56_123_156),
        ("Rhino", 3),
        ("Shrew", 56_423),
      ])
      Map.remove(animalPopulations, "Mosquito")->Map.toArray
      == [("Elephant", 3_156), ("Rhino", 3), ("Shrew", 56_423)]
     ]}
*/
external remove: (t('key, 'value, 'id), 'key) => t('key, 'value, 'id);
/** Get the value associated with a key. If the key is not present in the map, returns [None].

    {2 Examples}

    {[
      let animalPopulations = Map.String.fromArray([
        ("Elephant", 3_156),
        ("Mosquito", 56_123_156),
        ("Rhino", 3),
        ("Shrew", 56_423),
      ])
      Map.get(animalPopulations, "Shrew") == Some(56_423)
     ]}
*/
external get: (t('key, 'value, 'id), 'key) => option('value);
/** Update the value for a specific key using [f]. If [key] is not present in the map [f] will be called with [None].

    {2 Examples}

    {[
      let animalPopulations = Map.String.fromArray([
        ("Elephant", 3_156),
        ("Mosquito", 56_123_156),
        ("Rhino", 3),
        ("Shrew", 56_423),
      ])

      Map.update(animalPopulations, ~key="Hedgehog", ~f=population =>
        switch population {
        | None => Some(1)
        | Some(count) => Some(count + 1)
        }
      )->Map.toArray ==
        [
          ("Elephant", 3_156),
          ("Hedgehog", 1),
          ("Mosquito", 56_123_156),
          ("Rhino", 3),
          ("Shrew", 56_423),
        ]
     ]}
*/
external update:
  (
    t('key, 'value, 'id),
    ~key: [@ns.namedArgLoc] 'key,
    ~f: [@ns.namedArgLoc] (option('value) => option('value))
  ) =>
  t('key, 'value, 'id)
  ;
/** {1 Query} */;
/** Determine if a map is empty. */ external isEmpty: t(_, _, _) => bool;
/** Returns the number of key-value pairs present in the map.

    {2 Examples}

    {[
      Map.Int.fromArray([(1, "Hornet"), (3, "Marmot")])->Map.length == 2
     ]}
*/
external length: t(_, _, _) => int;
/** Determine if [f] returns [true] for [any] values in a map. */
external any:
  (t(_, 'value, _), ~f: [@ns.namedArgLoc] ('value => bool)) => bool
  ;
/** Determine if [f] returns [true] for [all] values in a map. */
external all:
  (t(_, 'value, _), ~f: [@ns.namedArgLoc] ('value => bool)) => bool
  ;
/** Returns, as an {!Option} the first key-value pair for which [f] evaluates to [true].

    If [f] doesn't return [true] for any of the elements [find] will return [None].

    Searches starting from the smallest {b key}

    {2 Examples}

    {[
      Map.String.fromArray([
        ("Elephant", 3_156),
        ("Mosquito", 56_123_156),
        ("Rhino", 3),
        ("Shrew", 56_423),
      ])->Map.find(~f=(~key, ~value) => value > 10_000)
      == Some("Mosquito", 56_123_156)
     ]}
*/
external find:
  (
    t('key, 'value, _),
    ~f: [@ns.namedArgLoc] (
          (~key: [@ns.namedArgLoc] 'key, ~value: [@ns.namedArgLoc] 'value) =>
          bool
        )
  ) =>
  option(('key, 'value))
  ;
/** Determine if a map includes [key].  */
external includes: (t('key, _, _), 'key) => bool;
/** Returns, as an {!Option}, the smallest {b key } in the map.

    Returns [None] if the map is empty.

    {2 Examples}

    {[
      Map.Int.fromArray([(8, "Pigeon"), (1, "Hornet"), (3, "Marmot")])
      ->Map.minimum == Some(1)
     ]}
*/
external minimum: t('key, _, _) => option('key);
/** Returns the largest {b key } in the map.

    Returns [None] if the map is empty.

    {2 Examples}

    {[
      Map.Int.fromArray([(8, "Pigeon"), (1, "Hornet"), (3, "Marmot")])
      ->Map.maximum == Some(8)
     ]}
*/
external maximum: t('key, _, _) => option('key);
/** Returns, as an {!Option}, a {!Tuple2} of the [(minimum, maximum)] {b key}s in the map.

    Returns [None] if the map is empty.

    {2 Examples}

    {[
      Map.Int.fromArray([(8, "Pigeon"), (1, "Hornet"), (3, "Marmot")])
      ->Map.extent == Some(1, 8)
     ]}
*/
external extent: t('key, _, _) => option(('key, 'key));
/** {1 Combine} */;
/** Combine two maps.

    You provide a function [f] which is provided the key and the optional
    value from each map and needs to account for the three possibilities:

    - Only the 'left' map includes a value for the key.
    - Both maps contain a value for the key.
    - Only the 'right' map includes a value for the key.

    You then traverse all the keys, building up whatever you want.

    {2 Examples}

    {[
      let animalToPopulation = Map.String.fromArray([("Elephant", 3_156), ("Shrew", 56_423)])

      let animalToPopulationGrowthRate = Map.String.fromArray([
        ("Elephant", 0.88),
        ("Squirrel", 1.2),
        ("Python", 4.0),
      ])

      Map.merge(animalToPopulation, animalToPopulationGrowthRate, ~f=(_animal, population, growth) =>
        switch Option.both(population, growth) {
        | Some(population, growth) => Some(Float.fromInt(population) *. growth)
        | None => None
        }
      )->Map.toArray
      == [("Elephant", 2777.28)]
     ]}
*/
external merge:
  (
    t('key, 'v1, 'id),
    t('key, 'v2, 'id),
    ~f: [@ns.namedArgLoc] (('key, option('v1), option('v2)) => option('v3))
  ) =>
  t('key, 'v3, 'id)
  ;
/** {1 Transform} */;
/** Apply a function to all values in a dictionary.

    {2 Examples}

    {[
      Map.String.fromArray([("Elephant", 3_156), ("Shrew", 56_423)])
      ->Map.map(~f=Int.toString)
      ->Map.toArray == [("Elephant", "3156"), ("Shrew", "56423")]
     ]}
*/
external map:
  (t('key, 'value, 'id), ~f: [@ns.namedArgLoc] ('value => 'b)) =>
  t('key, 'b, 'id)
  ;
/** Like {!map} but [f] is also called with each values corresponding key. */
external mapWithIndex:
  (t('key, 'value, 'id), ~f: [@ns.namedArgLoc] (('key, 'value) => 'b)) =>
  t('key, 'b, 'id)
  ;
/** Keep elements that [f] returns [true] for.

    {2 Examples}

    {[
      Map.String.fromArray([("Elephant", 3_156), ("Shrew", 56_423)])
      ->Map.filter(~f=population => population > 10_000)
      ->Map.toArray
      == [("Shrew", 56423)]
     ]}
*/
external filter:
  (t('key, 'value, 'id), ~f: [@ns.namedArgLoc] ('value => bool)) =>
  t('key, 'value, 'id)
  ;
/** Mombine {!map} and {!filter} into a single pass.

    The output list only contains elements for which [f] returns [Some].
*/
external filterMap:
  (
    t('key, 'value, 'id),
    ~f: [@ns.namedArgLoc] (
          (~key: [@ns.namedArgLoc] 'key, ~value: [@ns.namedArgLoc] 'value) =>
          option('b)
        )
  ) =>
  t('key, 'b, 'id)
  ;
/** Divide a map into two, the first map will contain the key-value pairs that [f] returns [true] for, pairs that [f] returns [false] for will end up in the second.

    {2 Examples}

    {[
      let (endangered, notEndangered)
        Map.String.fromArray([
          ("Elephant", 3_156),
          ("Mosquito", 56_123_156),
          ("Rhino", 3),
          ("Shrew", 56_423),
        ])->Map.partition(~f=(~key as _, ~value as population) => population < 10_000)

      endangered->Map.toArray == [("Elephant", 3_156), ("Rhino", 3)]

      notEndangered->Map.toArray == [("Mosquito", 56_123_156), ("Shrew", 56_423)]
     ]}
*/
external partition:
  (
    t('key, 'value, 'id),
    ~f: [@ns.namedArgLoc] (
          (~key: [@ns.namedArgLoc] 'key, ~value: [@ns.namedArgLoc] 'value) =>
          bool
        )
  ) =>
  (t('key, 'value, 'id), t('key, 'value, 'id))
  ;
/** Like {!Array.fold} but [f] is also called with both the [key] and [value]. */
external fold:
  (
    t('key, 'value, _),
    ~initial: [@ns.namedArgLoc] 'a,
    ~f: [@ns.namedArgLoc] (
          (
            'a,
            ~key: [@ns.namedArgLoc] 'key,
            ~value: [@ns.namedArgLoc] 'value
          ) =>
          'a
        )
  ) =>
  'a
  ;
/** {1 Iterate} */;
/** Runs a function [f] against each {b value} in the map. */
external forEach:
  (t(_, 'value, _), ~f: [@ns.namedArgLoc] ('value => unit)) => unit
  ;
/** Like {!Map.forEach} except [~f] is also called with the corresponding key. */
external forEachWithIndex:
  (
    t('key, 'value, _),
    ~f: [@ns.namedArgLoc] (
          (~key: [@ns.namedArgLoc] 'key, ~value: [@ns.namedArgLoc] 'value) =>
          unit
        )
  ) =>
  unit
  ;
/** {1 Convert} */;
/** Get a {!List} of all of the keys in a map.

    {2 Examples}

    {[
      Map.String.fromArray([
        ("Elephant", 3_156),
        ("Mosquito", 56_123_156),
        ("Rhino", 3),
        ("Shrew", 56_423),
      ])->Map.keys
      == list{"Elephant", "Mosquito", "Rhino", "Shrew"}
     ]}
*/
external keys: t('key, _, _) => list('key);
/** Get a {!List} of all of the values in a map.

    {2 Examples}

    {[
      Map.String.fromArray([
        ("Elephant", 3_156),
        ("Mosquito", 56_123_156),
        ("Rhino", 3),
        ("Shrew", 56_423),
      ])->Map.values
      == list{3_156, 56_123_156, 3, 56_423}
     ]}
*/
external values: t(_, 'value, _) => list('value);
/** Get an {!Array} of all of the key-value pairs in a map. */
external toArray: t('key, 'value, _) => array(('key, 'value));
/** Get a {!List} of all of the key-value pairs in a map. */
external toList: t('key, 'value, _) => list(('key, 'value));
/** Construct a Map which can be keyed by any data type using the polymorphic [compare] function. */
module Poly: {
  type identity;

  type t('key, 'value) = t('key, 'value, identity);

  /** A map with nothing in it. */
  external empty: unit => t('key, 'value);

  /** Create a map from a key and value.

      {2 Examples}

      {[
      Map.Poly.singleton(~key=false, ~value=1)->Map.toArray == [(false, 1)]
    ]}
  */
  external singleton: (~key: 'key, ~value: 'value) => t('key, 'value);

  /** Create a map from an {!Array} of key-value tuples. */
  external fromArray: array(('key, 'value)) => t('key, 'value);

  /** Create a map from a {!List} of key-value tuples. */
  external fromList: list(('key, 'value)) => t('key, 'value);
}
/** Construct a Map with {!Int}s for keys. */
module Int: {
  type identity;

  type t('value) = t(TableclothInt.t, 'value, identity);

  /** A map with nothing in it. */
  external empty: t('value);

  /** Create a map from a key and value.

      {2 Examples}

      {[
      Map.Int.singleton(~key=1, ~value="Ant")->Map.toArray == [(1, "Ant")]
    ]}
  */
  external singleton: (~key: int, ~value: 'value) => t('value);

  /** Create a map from an {!Array} of key-value tuples. */
  external fromArray: array((int, 'value)) => t('value);

  /** Create a map of a {!List} of key-value tuples. */
  external fromList: list((int, 'value)) => t('value);
}
