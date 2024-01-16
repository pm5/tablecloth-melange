open Jest;
open Expect;
open Tablecloth.Float;
test("zero", () =>
  expect(zero)->(toEqual(0.))
);
test("one", () =>
  expect(one)->(toEqual(1.))
);
test("nan", () =>
  expect(nan == nan)->(toEqual(false))
);
test("infinity", () =>
  expect(infinity *. 2. == infinity)->(toEqual(true))
);
test("negativeInfinity", () =>
  expect(negativeInfinity *. 2. == negativeInfinity)->(toEqual(true))
);
describe("equals", () =>
  test("zero", () =>
    expect(0. == (-0.))->(toEqual(true))
  )
);
describe("fromString", () => {
  [@ns.braces]
  {
    test("NaN", () =>
      expect(fromString("NaN"))->(toEqual(Some(Js.Float._NaN)))
    );
    test("nan", () =>
      expect(fromString("nan"))->(toEqual(Some(Js.Float._NaN)))
    );
    test("Infinity", () =>
      expect(fromString("Infinity"))->(toEqual(Some(infinity)))
    );
    test("infinity", () =>
      expect(fromString("infinity"))->(toEqual(None))
    );
    test("infinity", () =>
      expect(fromString("infinity"))->(toEqual(None))
    );
    test("55", () =>
      expect(fromString("55"))->(toEqual(Some(55.)))
    );
    test("-100", () =>
      expect(fromString("-100"))->(toEqual(Some(-100.)))
    );
    test("not number", () =>
      expect(fromString("not number"))->(toEqual(None))
    );
  }
});
describe("add", () =>
  test("add", () =>
    expect(add(3.14, 3.14))->(toEqual(6.28))
  )
);
describe("subtract", () =>
  test("subtract", () =>
    expect(subtract(4., 3.))->(toEqual(1.))
  )
);
describe("multiply", () =>
  test("multiply", () =>
    expect(multiply(2., 7.))->(toEqual(14.))
  )
);
describe("divide", () => {
  [@ns.braces]
  {
    test("divide", () =>
      expect(divide(3.14, ~by=[@ns.namedArgLoc] 2.))->(toEqual(1.57))
    );
    test("divide by zero", () =>
      expect(divide(3.14, ~by=[@ns.namedArgLoc] 0.) == infinity)
      ->(toEqual(true))
    );
    test("divide by negative zero", () =>
      expect(divide(3.14, ~by=[@ns.namedArgLoc] -0.) == negativeInfinity)
      ->(toEqual(true))
    );
  }
});
describe("power", () => {
  [@ns.braces]
  {
    test("power", () =>
      expect(
        power(~base=[@ns.namedArgLoc] 7., ~exponent=[@ns.namedArgLoc] 3.),
      )
      ->(toEqual(343.))
    );
    test("0 base", () =>
      expect(
        power(~base=[@ns.namedArgLoc] 0., ~exponent=[@ns.namedArgLoc] 3.),
      )
      ->(toEqual(0.))
    );
    test("0 exponent", () =>
      expect(
        power(~base=[@ns.namedArgLoc] 7., ~exponent=[@ns.namedArgLoc] 0.),
      )
      ->(toEqual(1.))
    );
  }
});
describe("negate", () => {
  [@ns.braces]
  {
    test("positive number", () =>
      expect(negate(8.))->(toEqual(-8.))
    );
    test("negative number", () =>
      expect(negate(-7.))->(toEqual(7.))
    );
    test("zero", () =>
      expect(negate(0.))->(toEqual(-0.))
    );
  }
});
describe("absolute", () => {
  [@ns.braces]
  {
    test("positive number", () =>
      expect(absolute(8.))->(toEqual(8.))
    );
    test("negative number", () =>
      expect(absolute(-7.))->(toEqual(7.))
    );
    test("zero", () =>
      expect(absolute(0.))->(toEqual(0.))
    );
  }
});
describe("maximum", () => {
  [@ns.braces]
  {
    test("positive numbers", () =>
      expect(maximum(7., 9.))->(toEqual(9.))
    );
    test("negative numbers", () =>
      expect(maximum(-4., -1.))->(toEqual(-1.))
    );
    test("nan", () =>
      expect(isNaN(maximum(7., nan)))->(toEqual(true))
    );
    test("infinity", () =>
      expect(maximum(7., infinity) == infinity)->(toEqual(true))
    );
    test("negativeInfinity", () =>
      expect(maximum(7., negativeInfinity))->(toEqual(7.))
    );
  }
});
describe("minimum", () => {
  [@ns.braces]
  {
    test("positive numbers", () =>
      expect(minimum(7., 9.))->(toEqual(7.))
    );
    test("negative numbers", () =>
      expect(minimum(-4., -1.))->(toEqual(-4.))
    );
    test("nan", () =>
      expect(isNaN(minimum(7., nan)))->(toEqual(true))
    );
    test("infinity", () =>
      expect(minimum(7., infinity))->(toEqual(7.))
    );
    test("negativeInfinity", () =>
      expect(minimum(7., negativeInfinity) == negativeInfinity)
      ->(toEqual(true))
    );
  }
});
describe("clamp", () => {
  [@ns.braces]
  {
    test("in range", () =>
      expect(
        clamp(~lower=[@ns.namedArgLoc] 0., ~upper=[@ns.namedArgLoc] 8., 5.),
      )
      ->(toEqual(5.))
    );
    test("above range", () =>
      expect(
        clamp(~lower=[@ns.namedArgLoc] 0., ~upper=[@ns.namedArgLoc] 8., 9.),
      )
      ->(toEqual(8.))
    );
    test("below range", () =>
      expect(
        clamp(~lower=[@ns.namedArgLoc] 2., ~upper=[@ns.namedArgLoc] 8., 1.),
      )
      ->(toEqual(2.))
    );
    test("above negative range", () =>
      expect(
        clamp(
          ~lower=[@ns.namedArgLoc] -10.,
          ~upper=[@ns.namedArgLoc] -5.,
          5.,
        ),
      )
      ->(toEqual(-5.))
    );
    test("below negative range", () =>
      expect(
        clamp(
          ~lower=[@ns.namedArgLoc] -10.,
          ~upper=[@ns.namedArgLoc] -5.,
          -15.,
        ),
      )
      ->(toEqual(-10.))
    );
    test("nan upper bound", () =>
      expect(
        isNaN(
          clamp(
            ~lower=[@ns.namedArgLoc] -7.9,
            ~upper=[@ns.namedArgLoc] nan,
            -6.6,
          ),
        ),
      )
      ->(toEqual(true))
    );
    test("nan lower bound", () =>
      expect(
        isNaN(
          clamp(
            ~lower=[@ns.namedArgLoc] nan,
            ~upper=[@ns.namedArgLoc] 0.,
            -6.6,
          ),
        ),
      )
      ->(toEqual(true))
    );
    test("nan value", () =>
      expect(
        isNaN(
          clamp(
            ~lower=[@ns.namedArgLoc] 2.,
            ~upper=[@ns.namedArgLoc] 8.,
            nan,
          ),
        ),
      )
      ->(toEqual(true))
    );
    test("invalid arguments", () =>
      toThrow(
        expect(() =>
          clamp(~lower=[@ns.namedArgLoc] 7., ~upper=[@ns.namedArgLoc] 1., 3.)
        ),
      )
    );
  }
});
describe("squareRoot", () => {
  [@ns.braces]
  {
    test("whole numbers", () =>
      expect(squareRoot(4.))->(toEqual(2.))
    );
    test("decimal numbers", () =>
      expect(squareRoot(20.25))->(toEqual(4.5))
    );
    test("negative number", () =>
      expect(isNaN(squareRoot(-1.)))->(toEqual(true))
    );
  }
});
describe("log", () => {
  [@ns.braces]
  {
    test("base 10", () =>
      expect(log(~base=[@ns.namedArgLoc] 10., 100.))->(toEqual(2.))
    );
    test("base 2", () =>
      expect(log(~base=[@ns.namedArgLoc] 2., 256.))->(toEqual(8.))
    );
    test("of zero", () =>
      expect(log(~base=[@ns.namedArgLoc] 10., 0.) == negativeInfinity)
      ->(toEqual(true))
    );
  }
});
describe("isNaN", () => {
  [@ns.braces]
  {
    test("nan", () =>
      expect(isNaN(nan))->(toEqual(true))
    );
    test("non-nan", () =>
      expect(isNaN(91.4))->(toEqual(false))
    );
  }
});
describe("isFinite", () => {
  [@ns.braces]
  {
    test("infinity", () =>
      expect(isFinite(infinity))->(toEqual(false))
    );
    test("negative infinity", () =>
      expect(isFinite(negativeInfinity))->(toEqual(false))
    );
    test("NaN", () =>
      expect(isFinite(nan))->(toEqual(false))
    );
    testAll("regular numbers", [(-5.), (-0.314), 0., 3.14], n =>
      expect(isFinite(n))->(toEqual(true))
    );
  }
});
describe("isInfinite", () => {
  [@ns.braces]
  {
    test("infinity", () =>
      expect(isInfinite(infinity))->(toEqual(true))
    );
    test("negative infinity", () =>
      expect(isInfinite(negativeInfinity))->(toEqual(true))
    );
    test("NaN", () =>
      expect(isInfinite(nan))->(toEqual(false))
    );
    testAll("regular numbers", [(-5.), (-0.314), 0., 3.14], n =>
      expect(isInfinite(n))->(toEqual(false))
    );
  }
});
describe("inRange", () => {
  [@ns.braces]
  {
    test("in range", () =>
      expect(
        inRange(~lower=[@ns.namedArgLoc] 2., ~upper=[@ns.namedArgLoc] 4., 3.),
      )
      ->(toEqual(true))
    );
    test("above range", () =>
      expect(
        inRange(~lower=[@ns.namedArgLoc] 2., ~upper=[@ns.namedArgLoc] 4., 8.),
      )
      ->(toEqual(false))
    );
    test("below range", () =>
      expect(
        inRange(~lower=[@ns.namedArgLoc] 2., ~upper=[@ns.namedArgLoc] 4., 1.),
      )
      ->(toEqual(false))
    );
    test("equal to ~upper", () =>
      expect(
        inRange(~lower=[@ns.namedArgLoc] 1., ~upper=[@ns.namedArgLoc] 2., 2.),
      )
      ->(toEqual(false))
    );
    test("negative range", () =>
      expect(
        inRange(
          ~lower=[@ns.namedArgLoc] -7.9,
          ~upper=[@ns.namedArgLoc] -5.2,
          -6.6,
        ),
      )
      ->(toEqual(true))
    );
    test("nan upper bound", () =>
      expect(
        inRange(
          ~lower=[@ns.namedArgLoc] -7.9,
          ~upper=[@ns.namedArgLoc] nan,
          -6.6,
        ),
      )
      ->(toEqual(false))
    );
    test("nan lower bound", () =>
      expect(
        inRange(
          ~lower=[@ns.namedArgLoc] nan,
          ~upper=[@ns.namedArgLoc] 0.,
          -6.6,
        ),
      )
      ->(toEqual(false))
    );
    test("nan value", () =>
      expect(
        inRange(
          ~lower=[@ns.namedArgLoc] 2.,
          ~upper=[@ns.namedArgLoc] 8.,
          nan,
        ),
      )
      ->(toEqual(false))
    );
    test("invalid arguments", () =>
      toThrow(
        expect(() =>
          inRange(
            ~lower=[@ns.namedArgLoc] 7.,
            ~upper=[@ns.namedArgLoc] 1.,
            3.,
          )
        ),
      )
    );
  }
});
test("hypotenuse", () =>
  expect(hypotenuse(3., 4.))->(toEqual(5.))
);
test("degrees", () =>
  expect(degrees(180.))->(toEqual(pi))
);
test("radians", () =>
  expect(radians(pi))->(toEqual(pi))
);
test("turns", () =>
  expect(turns(1.))->(toEqual(2. *. pi))
);
describe("ofPolar", () =>
  [@ns.braces]
  {
    let (x, y) = fromPolar((squareRoot(2.), degrees(45.)));
    test("x", () =>
      expect(x)->(toBeCloseTo(1.))
    );
    test("y", () =>
      expect(y)->(toEqual(1.))
    );
  }
);
describe("toPolar", () => {
  [@ns.braces]
  {
    test("toPolar", () =>
      expect(toPolar((3.0, 4.0)))->(toEqual((5.0, 0.9272952180016122)))
    );
    let (r, theta) = toPolar((5.0, 12.0));
    testAll(
      "toPolar", [(r, 13.0), (theta, 1.17601)], ((actual, expected)) =>
      expect(actual)->(toBeCloseTo(expected))
    );
  }
});
describe("cos", () => {
  [@ns.braces]
  {
    test("cos", () =>
      expect(cos(degrees(60.)))->(toBeCloseTo(0.5))
    );
    test("cos", () =>
      expect(cos(radians(pi /. 3.)))->(toBeCloseTo(0.5))
    );
  }
});
describe("acos", () =>
  test("1 / 2", () =>
    expect(acos(1. /. 2.))->(toBeCloseTo(1.0472))
  )
);
describe("sin", () => {
  [@ns.braces]
  {
    test("30 degrees", () =>
      expect(sin(degrees(30.)))->(toBeCloseTo(0.5))
    );
    test("pi / 6", () =>
      expect(sin(radians(pi /. 6.)))->(toBeCloseTo(0.5))
    );
  }
});
describe("asin", () =>
  test("asin", () =>
    expect(asin(1. /. 2.))->(toBeCloseTo(0.523599))
  )
);
describe("tan", () => {
  [@ns.braces]
  {
    test("45 degrees", () =>
      expect(tan(degrees(45.)))->(toEqual(0.9999999999999999))
    );
    test("pi / 4", () =>
      expect(tan(radians(pi /. 4.)))->(toEqual(0.9999999999999999))
    );
    test("0", () =>
      expect(tan(0.))->(toEqual(0.))
    );
  }
});
describe("atan", () => {
  [@ns.braces]
  {
    test("0", () =>
      expect(atan(0.))->(toEqual(0.))
    );
    test("1 / 1", () =>
      expect(atan(1. /. 1.))->(toEqual(0.7853981633974483))
    );
    test("1 / -1", () =>
      expect(atan(1. /. (-1.)))->(toEqual(-0.7853981633974483))
    );
    test("-1 / -1", () =>
      expect(atan((-1.) /. (-1.)))->(toEqual(0.7853981633974483))
    );
    test("-1 / -1", () =>
      expect(atan((-1.) /. 1.))->(toEqual(-0.7853981633974483))
    );
  }
});
describe("atan2", () => {
  [@ns.braces]
  {
    test("0", () =>
      expect(atan2(~y=[@ns.namedArgLoc] 0., ~x=[@ns.namedArgLoc] 0.))
      ->(toEqual(0.))
    );
    test("(1, 1)", () =>
      expect(atan2(~y=[@ns.namedArgLoc] 1., ~x=[@ns.namedArgLoc] 1.))
      ->(toEqual(0.7853981633974483))
    );
    test("(-1, 1)", () =>
      expect(atan2(~y=[@ns.namedArgLoc] 1., ~x=[@ns.namedArgLoc] -1.))
      ->(toEqual(2.3561944901923449))
    );
    test("(-1 -1)", () =>
      expect(atan2(~y=[@ns.namedArgLoc] -1., ~x=[@ns.namedArgLoc] -1.))
      ->(toEqual(-2.3561944901923449))
    );
    test("(1, -1)", () =>
      expect(atan2(~y=[@ns.namedArgLoc] -1., ~x=[@ns.namedArgLoc] 1.))
      ->(toEqual(-0.7853981633974483))
    );
  }
});
describe("round", () => {
  [@ns.braces]
  {
    test("`Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Zero, 1.2))->(toEqual(1.))
    );
    test("`Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Zero, 1.5))->(toEqual(1.))
    );
    test("`Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Zero, 1.8))->(toEqual(1.))
    );
    test("`Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Zero, -1.2))
      ->(toEqual(-1.))
    );
    test("`Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Zero, -1.5))
      ->(toEqual(-1.))
    );
    test("`Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Zero, -1.8))
      ->(toEqual(-1.))
    );
    test("`AwayFromZero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `AwayFromZero, 1.2))
      ->(toEqual(2.))
    );
    test("`AwayFromZero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `AwayFromZero, 1.5))
      ->(toEqual(2.))
    );
    test("`AwayFromZero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `AwayFromZero, 1.8))
      ->(toEqual(2.))
    );
    test("`AwayFromZero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `AwayFromZero, -1.2))
      ->(toEqual(-2.))
    );
    test("`AwayFromZero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `AwayFromZero, -1.5))
      ->(toEqual(-2.))
    );
    test("`AwayFromZero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `AwayFromZero, -1.8))
      ->(toEqual(-2.))
    );
    test("`Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Up, 1.2))->(toEqual(2.))
    );
    test("`Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Up, 1.5))->(toEqual(2.))
    );
    test("`Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Up, 1.8))->(toEqual(2.))
    );
    test("`Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Up, -1.2))->(toEqual(-1.))
    );
    test("`Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Up, -1.5))->(toEqual(-1.))
    );
    test("`Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Up, -1.8))->(toEqual(-1.))
    );
    test("`Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Down, 1.2))->(toEqual(1.))
    );
    test("`Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Down, 1.5))->(toEqual(1.))
    );
    test("`Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Down, 1.8))->(toEqual(1.))
    );
    test("`Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Down, -1.2))
      ->(toEqual(-2.))
    );
    test("`Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Down, -1.5))
      ->(toEqual(-2.))
    );
    test("`Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Down, -1.8))
      ->(toEqual(-2.))
    );
    test("`Closest `Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Zero), 1.2))
      ->(toEqual(1.))
    );
    test("`Closest `Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Zero), 1.5))
      ->(toEqual(1.))
    );
    test("`Closest `Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Zero), 1.8))
      ->(toEqual(2.))
    );
    test("`Closest `Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Zero), -1.2))
      ->(toEqual(-1.))
    );
    test("`Closest `Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Zero), -1.5))
      ->(toEqual(-1.))
    );
    test("`Closest `Zero", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Zero), -1.8))
      ->(toEqual(-2.))
    );
    test("`Closest `AwayFromZero", () =>
      expect(
        round(~direction=[@ns.namedArgLoc] `Closest(`AwayFromZero), 1.2),
      )
      ->(toEqual(1.))
    );
    test("`Closest `AwayFromZero", () =>
      expect(
        round(~direction=[@ns.namedArgLoc] `Closest(`AwayFromZero), 1.5),
      )
      ->(toEqual(2.))
    );
    test("`Closest `AwayFromZero", () =>
      expect(
        round(~direction=[@ns.namedArgLoc] `Closest(`AwayFromZero), 1.8),
      )
      ->(toEqual(2.))
    );
    test("`Closest `AwayFromZero", () =>
      expect(
        round(~direction=[@ns.namedArgLoc] `Closest(`AwayFromZero), -1.2),
      )
      ->(toEqual(-1.))
    );
    test("`Closest `AwayFromZero", () =>
      expect(
        round(~direction=[@ns.namedArgLoc] `Closest(`AwayFromZero), -1.5),
      )
      ->(toEqual(-2.))
    );
    test("`Closest `AwayFromZero", () =>
      expect(
        round(~direction=[@ns.namedArgLoc] `Closest(`AwayFromZero), -1.8),
      )
      ->(toEqual(-2.))
    );
    test("`Closest `Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Up), 1.2))
      ->(toEqual(1.))
    );
    test("`Closest `Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Up), 1.5))
      ->(toEqual(2.))
    );
    test("`Closest `Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Up), 1.8))
      ->(toEqual(2.))
    );
    test("`Closest `Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Up), -1.2))
      ->(toEqual(-1.))
    );
    test("`Closest `Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Up), -1.5))
      ->(toEqual(-1.))
    );
    test("`Closest `Up", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Up), -1.8))
      ->(toEqual(-2.))
    );
    test("`Closest `Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Down), 1.2))
      ->(toEqual(1.))
    );
    test("`Closest `Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Down), 1.5))
      ->(toEqual(1.))
    );
    test("`Closest `Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Down), 1.8))
      ->(toEqual(2.))
    );
    test("`Closest `Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Down), -1.2))
      ->(toEqual(-1.))
    );
    test("`Closest `Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Down), -1.5))
      ->(toEqual(-2.))
    );
    test("`Closest `Down", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`Down), -1.8))
      ->(toEqual(-2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), 1.2))
      ->(toEqual(1.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), 1.5))
      ->(toEqual(2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), 1.8))
      ->(toEqual(2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), 2.2))
      ->(toEqual(2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), 2.5))
      ->(toEqual(2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), 2.8))
      ->(toEqual(3.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), -1.2))
      ->(toEqual(-1.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), -1.5))
      ->(toEqual(-2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), -1.8))
      ->(toEqual(-2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), -2.2))
      ->(toEqual(-2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), -2.5))
      ->(toEqual(-2.))
    );
    test("`Closest `ToEven", () =>
      expect(round(~direction=[@ns.namedArgLoc] `Closest(`ToEven), -2.8))
      ->(toEqual(-3.))
    );
  }
});
describe("floor", () => {
  [@ns.braces]
  {
    test("floor", () =>
      expect(floor(1.2))->(toEqual(1.))
    );
    test("floor", () =>
      expect(floor(1.5))->(toEqual(1.))
    );
    test("floor", () =>
      expect(floor(1.8))->(toEqual(1.))
    );
    test("floor", () =>
      expect(floor(-1.2))->(toEqual(-2.))
    );
    test("floor", () =>
      expect(floor(-1.5))->(toEqual(-2.))
    );
    test("floor", () =>
      expect(floor(-1.8))->(toEqual(-2.))
    );
  }
});
describe("ceiling", () => {
  [@ns.braces]
  {
    test("ceiling", () =>
      expect(ceiling(1.2))->(toEqual(2.))
    );
    test("ceiling", () =>
      expect(ceiling(1.5))->(toEqual(2.))
    );
    test("ceiling", () =>
      expect(ceiling(1.8))->(toEqual(2.))
    );
    test("ceiling", () =>
      expect(ceiling(-1.2))->(toEqual(-1.))
    );
    test("ceiling", () =>
      expect(ceiling(-1.5))->(toEqual(-1.))
    );
    test("ceiling", () =>
      expect(ceiling(-1.8))->(toEqual(-1.))
    );
  }
});
describe("truncate", () => {
  [@ns.braces]
  {
    test("truncate", () =>
      expect(truncate(1.2))->(toEqual(1.))
    );
    test("truncate", () =>
      expect(truncate(1.5))->(toEqual(1.))
    );
    test("truncate", () =>
      expect(truncate(1.8))->(toEqual(1.))
    );
    test("truncate", () =>
      expect(truncate(-1.2))->(toEqual(-1.))
    );
    test("truncate", () =>
      expect(truncate(-1.5))->(toEqual(-1.))
    );
    test("truncate", () =>
      expect(truncate(-1.8))->(toEqual(-1.))
    );
  }
});
describe("fromInt", () => {
  [@ns.braces]
  {
    test("5", () =>
      expect(fromInt(5))->(toEqual(5.0))
    );
    test("0", () =>
      expect(zero)->(toEqual(0.0))
    );
    test("-7", () =>
      expect(fromInt(-7))->(toEqual(-7.0))
    );
  }
});
describe("toInt", () => {
  [@ns.braces]
  {
    test("5.", () =>
      expect(toInt(5.))->(toEqual(Some(5)))
    );
    test("5.3", () =>
      expect(toInt(5.3))->(toEqual(Some(5)))
    );
    test("0.", () =>
      expect(toInt(0.))->(toEqual(Some(0)))
    );
    test("-7.", () =>
      expect(toInt(-7.))->(toEqual(Some(-7)))
    );
    test("nan", () =>
      expect(toInt(nan))->(toEqual(None))
    );
    test("infinity", () =>
      expect(toInt(infinity))->(toEqual(None))
    );
    test("negativeInfinity", () =>
      expect(toInt(negativeInfinity))->(toEqual(None))
    );
  }
});
describe("isInteger", () => {
  [@ns.braces]
  {
    test("true", () =>
      expect(isInteger(5.0))->(toEqual(true))
    );
    test("false", () =>
      expect(isInteger(pi))->(toEqual(false))
    );
  }
});
