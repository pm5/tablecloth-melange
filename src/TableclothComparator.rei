/** */;
/** Comparator provide a way for custom data structures to be used with {!Map}s and {!Set}s.

    Say we have a module [Book] which we want to be able to create a {!Set} of

    {[
      module Book = {
        type t = {
          isbn: string,
          title: string,
        }

        let compare = (bookA, bookB) => String.compare(bookA.isbn, bookB.isbn)
      }
    ]}

    First we need to make our module conform to the {!S} signature.

    This can be done by using the {!Make} functor.

    {[
      module Book = {
        type t = {
          isbn: string,
          title: string,
        }

        let compare = (bookA, bookB) => String.compare(bookA.isbn, bookB.isbn)

        include Comparator.Make({
          type t = t

          let compare = compare
        })
      }
    ]}

    Now we can create a Set of books:

    {[
      Set.fromArray(module(Book),
       [
         {isbn: "9788460767923", title: "Moby Dick or The Whale"}
       ])
    ]}
*/;
module type T = {
  /** T represents the input for the {!Make} functor. */;
  type nonrec t;
  let compare: (t, t) => int;
};
type nonrec t('a, 'identity);
/** This just is an alias for {!t}.  */
type nonrec comparator('a, 'identity) = t('a, 'identity);
module type S = {
  /** The output type of {!Make}.  */;
  type nonrec t;
  type nonrec identity;
  let comparator: comparator(t, identity);
};
/** A type alias that is useful typing functions which accept first class modules like {!Map.empty} or {!Set.fromArray}. */
type nonrec s('a, 'identity) = (module S with
                                   type identity = 'identity and type t = 'a);
/** Create a new comparator by providing a module which satisifies {!T}.

    {2 Examples}

    {[
      module Book = {
        module T = {
          type t = {
            isbn: string,
            title: string,
          }
          let compare = (bookA, bookB) => String.compare(bookA.isbn, bookB.isbn)
        }

        include T
        include Comparator.Make(T)
      }

      let books = Set.empty(module(Book))
    ]}
*/
module Make: (M: T) => (S with type t := M.t)
