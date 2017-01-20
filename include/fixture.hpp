#ifndef FIXTURE_HPP_
# define FIXTURE_HPP_

# include "vect.hpp"

struct FixtureInfo // 4 * 8 -> 32 YAY!
{
  float inverseMass; // 4
  float rotationInertia; // 4 TODO: badly namaed (1 / x)
  // MUST BE COUNTERCLOCKWISE!
  Vect<3u, Vect<2u, float>> corners; // 4 * 2 * 3
};

class FixtureCacheData // 4 * 8 = 32 YAY!
{
public:
  Vect<2u, float> rotationVectCache;
  // note the 32 byte offset to the Vect from which it will be calculated.
  Vect<3u, Vect<2u, float>> cornerCache; // true position after rotation & translation
};

struct FixtureState // 4 * 7 = 28 -> 4 left
{
  Vect<2u, float> center; // 4 * 2 <- center of mass too.
  Vect<2u, float> speed; // 4 * 2
  float angle; // 4
  float rotation; // 4
  struct
  {
    unsigned int hit : 1;
    unsigned int : 31;
  };
};

struct FixtureData // 36 left...
  : public FixtureInfo,
    public FixtureCacheData,
    public FixtureState
{
  float __a[36]; // padding XD

  FixtureData(FixtureInfo fixtureInfo, FixtureState fixtureState)
    : FixtureInfo(fixtureInfo),
      FixtureState(fixtureState)
  {}

  FixtureData()
  {}
};

#endif // !FIXTURE_HPP_
