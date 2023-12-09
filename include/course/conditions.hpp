#ifndef CONDITIONS_HPP
#define CONDITIONS_HPP

#include <bdd.h>
#include "course/vars.hpp"

enum class NeighbourType
{
  LEFT, TOPLEFT
};

struct PropertyOfObject
{
  PropertyOfObject(int objectNumber, int propertyNumber, int propertyValue):
    objectNumber(objectNumber), propertyNumber(propertyNumber), propertyValue(propertyValue)
  {}

  int objectNumber;
  int propertyNumber;
  int propertyValue;
};

bdd restriction_1(const bdd p[M][N][N], const PropertyOfObject propertyOfObject);
bdd restriction_2(const bdd p[M][N][N], const PropertyOfObject propertyOfObject1, const PropertyOfObject propertyOfObject2);
bdd restriction_3(const bdd p[M][N][N], const NeighbourType neighbour, const PropertyOfObject currentProperty,
          PropertyOfObject neihbourProperty);

bdd restriction_4(const bdd p[M][N][N], const PropertyOfObject currentProperty, const PropertyOfObject neihbourProperty);
void restriction_5(bdd& tree, const bdd p[M][N][N]);
bdd restriction_6(const bdd p[M][N][N]);

#endif
