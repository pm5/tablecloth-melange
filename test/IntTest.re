open Tablecloth;
open Jest;
open Expect;
test("zero", () =>
  expect(Int.zero)->(toEqual(0))
);
test("one", () =>
  expect(Int.one)->(toEqual(1))
);
test("minimumValue", () =>
  expect(Int.minimumValue - 1)->(toEqual(Int.maximumValue))
);
test("maximumValue", () =>
  expect(Int.maximumValue + 1)->(toEqual(Int.minimumValue))
);
describe("add", () =>
  test("add", () =>
    expect(Int.add(3002, 4004))->(toEqual(7006))
  )
);
describe("subtract", () =>
  test("subtract", () =>
    expect(Int.subtract(4, 3))->(toEqual(1))
  )
);
describe("multiply", () =>
  test("multiply", () =>
    expect(Int.multiply(2, 7))->(toEqual(14))
  )
);
describe("divide", () => {
  [@ns.braces]
  {
    test("divide", () =>
      expect(Int.divide(3, ~by=[@ns.namedArgLoc] 2))->(toEqual(1))
    );
    test("division by zero", () =>
      toThrow(expect(() =>
                Int.divide(3, ~by=[@ns.namedArgLoc] 0)
              ))
    );
    test("divide", () =>
      expect([@ns.braces] Int.(divide(27, ~by=[@ns.namedArgLoc] 5)))
      ->(toEqual(5))
    );
    test("divideFloat", () =>
      expect([@ns.braces] Int.(divideFloat(3, ~by=[@ns.namedArgLoc] 2)))
      ->(toEqual(1.5))
    );
    test("divideFloat", () =>
      expect([@ns.braces] Int.(divideFloat(27, ~by=[@ns.namedArgLoc] 5)))
      ->(toEqual(5.4))
    );
    test("divideFloat", () =>
      expect([@ns.braces] Int.(divideFloat(8, ~by=[@ns.namedArgLoc] 4)))
      ->(toEqual(2.0))
    );
    test("divideFloat by 0", () =>
      expect(
        [@ns.braces] Int.(divideFloat(8, ~by=[@ns.namedArgLoc] 0))
        == Float.infinity,
      )
      ->(toEqual(true))
    );
    test("divideFloat 0", () =>
      expect(
        [@ns.braces] Int.(divideFloat(-8, ~by=[@ns.namedArgLoc] 0))
        == Float.negativeInfinity,
      )
      ->(toEqual(true))
    );
  }
});
describe("power", () => {
  [@ns.braces]
  {
    test("power", () =>
      expect(
        Int.power(~base=[@ns.namedArgLoc] 7, ~exponent=[@ns.namedArgLoc] 3),
      )
      ->(toEqual(343))
    );
    test("0 base", () =>
      expect(
        Int.power(~base=[@ns.namedArgLoc] 0, ~exponent=[@ns.namedArgLoc] 3),
      )
      ->(toEqual(0))
    );
    test("0 exponent", () =>
      expect(
        Int.power(~base=[@ns.namedArgLoc] 7, ~exponent=[@ns.namedArgLoc] 0),
      )
      ->(toEqual(1))
    );
  }
});
describe("negate", () => {
  [@ns.braces]
  {
    test("positive number", () =>
      expect(Int.negate(8))->(toEqual(-8))
    );
    test("negative number", () =>
      expect(Int.negate(-7))->(toEqual(7))
    );
    test("zero", () =>
      expect(Int.negate(0))->(toEqual(-0))
    );
  }
});
describe("modulo", () =>
  test("documentation examples", () =>
    expect(
      Array.map(
        [|(-4), (-3), (-2), (-1), 0, 1, 2, 3, 4|], ~f=[@ns.namedArgLoc] a =>
        Int.modulo(a, ~by=[@ns.namedArgLoc] 3)
      ),
    )
    ->(toEqual([|2, 0, 1, 2, 0, 1, 2, 0, 1|]))
  )
);
describe("remainder", () =>
  test("documentation examples", () =>
    expect(
      Array.map([|(-4), (-2), (-1), 0, 1, 2, 3, 4|], ~f=[@ns.namedArgLoc] a =>
        Int.remainder(a, ~by=[@ns.namedArgLoc] 3)
      ),
    )
    ->(toEqual([|(-1), (-2), (-1), 0, 1, 2, 0, 1|]))
  )
);
describe("absolute", () => {
  [@ns.braces]
  {
    test("positive number", () =>
      expect(Int.absolute(8))->(toEqual(8))
    );
    test("negative number", () =>
      expect(Int.absolute(-7))->(toEqual(7))
    );
    test("zero", () =>
      expect(Int.absolute(0))->(toEqual(0))
    );
  }
});
describe("minimum", () => {
  [@ns.braces]
  {
    test("positive numbers", () =>
      expect(Int.minimum(8, 18))->(toEqual(8))
    );
    test("with zero", () =>
      expect(Int.minimum(5, 0))->(toEqual(0))
    );
    test("negative numbers", () =>
      expect(Int.minimum(-4, -1))->(toEqual(-4))
    );
  }
});
describe("maximum", () => {
  [@ns.braces]
  {
    test("positive numbers", () =>
      expect(Int.maximum(8, 18))->(toEqual(18))
    );
    test("with zero", () =>
      expect(Int.maximum(5, 0))->(toEqual(5))
    );
    test("negative numbers", () =>
      expect(Int.maximum(-4, -1))->(toEqual(-1))
    );
  }
});
describe("isEven", () => {
  [@ns.braces]
  {
    test("even number", () =>
      expect(Int.isEven(8))->(toEqual(true))
    );
    test("odd number", () =>
      expect(Int.isEven(9))->(toEqual(false))
    );
    test("zero even", () =>
      expect(Int.isEven(0))->(toEqual(true))
    );
  }
});
describe("isOdd", () => {
  [@ns.braces]
  {
    test("even number", () =>
      expect(Int.isOdd(8))->(toEqual(false))
    );
    test("odd number", () =>
      expect(Int.isOdd(9))->(toEqual(true))
    );
    test("zero even", () =>
      expect(Int.isOdd(0))->(toEqual(false))
    );
  }
});
describe("clamp", () => {
  [@ns.braces]
  {
    test("in range", () =>
      expect(
        Int.clamp(~lower=[@ns.namedArgLoc] 0, ~upper=[@ns.namedArgLoc] 8, 5),
      )
      ->(toEqual(5))
    );
    test("above range", () =>
      expect(
        Int.clamp(~lower=[@ns.namedArgLoc] 0, ~upper=[@ns.namedArgLoc] 8, 9),
      )
      ->(toEqual(8))
    );
    test("below range", () =>
      expect(
        Int.clamp(~lower=[@ns.namedArgLoc] 2, ~upper=[@ns.namedArgLoc] 8, 1),
      )
      ->(toEqual(2))
    );
    test("above negative range", () =>
      expect(
        Int.clamp(
          ~lower=[@ns.namedArgLoc] -10,
          ~upper=[@ns.namedArgLoc] -5,
          5,
        ),
      )
      ->(toEqual(-5))
    );
    test("below negative range", () =>
      expect(
        Int.clamp(
          ~lower=[@ns.namedArgLoc] -10,
          ~upper=[@ns.namedArgLoc] -5,
          -15,
        ),
      )
      ->(toEqual(-10))
    );
    test("invalid arguments", () =>
      toThrow(
        expect(() =>
          Int.clamp(~lower=[@ns.namedArgLoc] 7, ~upper=[@ns.namedArgLoc] 1, 3)
        ),
      )
    );
  }
});
describe("inRange", () => {
  [@ns.braces]
  {
    test("in range", () =>
      expect(
        Int.inRange(
          ~lower=[@ns.namedArgLoc] 2,
          ~upper=[@ns.namedArgLoc] 4,
          3,
        ),
      )
      ->(toEqual(true))
    );
    test("above range", () =>
      expect(
        Int.inRange(
          ~lower=[@ns.namedArgLoc] 2,
          ~upper=[@ns.namedArgLoc] 4,
          8,
        ),
      )
      ->(toEqual(false))
    );
    test("below range", () =>
      expect(
        Int.inRange(
          ~lower=[@ns.namedArgLoc] 2,
          ~upper=[@ns.namedArgLoc] 4,
          1,
        ),
      )
      ->(toEqual(false))
    );
    test("equal to ~upper", () =>
      expect(
        Int.inRange(
          ~lower=[@ns.namedArgLoc] 1,
          ~upper=[@ns.namedArgLoc] 2,
          2,
        ),
      )
      ->(toEqual(false))
    );
    test("negative range", () =>
      expect(
        Int.inRange(
          ~lower=[@ns.namedArgLoc] -7,
          ~upper=[@ns.namedArgLoc] -5,
          -6,
        ),
      )
      ->(toEqual(true))
    );
    test("invalid arguments", () =>
      toThrow(
        expect(() =>
          Int.inRange(
            ~lower=[@ns.namedArgLoc] 7,
            ~upper=[@ns.namedArgLoc] 1,
            3,
          )
        ),
      )
    );
  }
});
describe("toFloat", () => {
  [@ns.braces]
  {
    test("5", () =>
      expect(Int.toFloat(5))->(toEqual(5.))
    );
    test("0", () =>
      expect(Int.toFloat(0))->(toEqual(0.))
    );
    test("-7", () =>
      expect(Int.toFloat(-7))->(toEqual(-7.))
    );
  }
});
describe("fromString", () => {
  [@ns.braces]
  {
    test("0", () =>
      expect(Int.fromString("0"))->(toEqual(Some(0)))
    );
    test("-0", () =>
      expect(Int.fromString("-0"))->(toEqual(Some(-0)))
    );
    test("42", () =>
      expect(Int.fromString("42"))->(toEqual(Some(42)))
    );
    test("123_456", () =>
      expect(Int.fromString("123_456"))->(toEqual(Some(123_456)))
    );
    test("-42", () =>
      expect(Int.fromString("-42"))->(toEqual(Some(-42)))
    );
    test("0XFF", () =>
      expect(Int.fromString("0XFF"))->(toEqual(Some(255)))
    );
    test("0X000A", () =>
      expect(Int.fromString("0X000A"))->(toEqual(Some(10)))
    );
    test("Infinity", () =>
      expect(Int.fromString("Infinity"))->(toEqual(None))
    );
    test("-Infinity", () =>
      expect(Int.fromString("-Infinity"))->(toEqual(None))
    );
    test("NaN", () =>
      expect(Int.fromString("NaN"))->(toEqual(None))
    );
    test("abc", () =>
      expect(Int.fromString("abc"))->(toEqual(None))
    );
    test("--4", () =>
      expect(Int.fromString("--4"))->(toEqual(None))
    );
    test("empty string", () =>
      expect(Int.fromString(" "))->(toEqual(None))
    );
  }
});
describe("toString", () => {
  [@ns.braces]
  {
    test("positive number", () =>
      expect(Int.toString(1))->(toEqual("1"))
    );
    test("negative number", () =>
      expect(Int.toString(-1))->(toEqual("-1"))
    );
  }
});
