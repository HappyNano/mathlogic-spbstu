#include "course/conditions.hpp"
#include <vector>
#include <cmath>

static const int LOG_N = std::ceil(std::log2(N));

bdd restriction_1(const bdd p[M][N][N], const PropertyOfObject propertyOfObject)
{
  return p[propertyOfObject.propertyNumber][propertyOfObject.objectNumber][propertyOfObject.propertyValue];
}

bdd restriction_2(const bdd p[M][N][N], const PropertyOfObject propertyOfObject1, const PropertyOfObject propertyOfObject2)
{
  bdd tree = bddtrue;
  for (int i = 0; i < N; ++i)
  {
    tree &= !(p[propertyOfObject1.propertyNumber][i][propertyOfObject1.propertyValue] ^
              p[propertyOfObject2.propertyNumber][i][propertyOfObject2.propertyValue]);
  }
  return tree;
}

bdd restriction_3(const bdd p[M][N][N],
 const NeighbourType neighbour,
 const PropertyOfObject currentProperty,
 PropertyOfObject neihbourProperty)
{
  bdd tree = bddtrue;
  switch (neighbour)
  {
  case NeighbourType::TOPLEFT: {
    for (int i = 0; i < N - ROW_LENGTH; ++i)
    {
      if (i % ROW_LENGTH != 0 && i > 2)
      {
        tree &= !(p[currentProperty.propertyNumber][i][currentProperty.propertyValue] ^
                  p[neihbourProperty.propertyNumber][i - ROW_LENGTH - 1][neihbourProperty.propertyValue]);
      }
      else if (i % ROW_LENGTH == 0 && i > 2)
      {
        tree &= !(p[currentProperty.propertyNumber][i][currentProperty.propertyValue] ^
                  p[neihbourProperty.propertyNumber][i - ROW_LENGTH + 2][neihbourProperty.propertyValue]);
      }
    }
    break;
  }
  case NeighbourType::LEFT: {
    for (int i = 0; i < N; ++i)
    {
      if (i % ROW_LENGTH != 0)
      {
        tree &= !(p[currentProperty.propertyNumber][i][currentProperty.propertyValue] ^
                  p[neihbourProperty.propertyNumber][i - 1][neihbourProperty.propertyValue]);
      }
      else
      {
        tree &= !(p[currentProperty.propertyNumber][i][currentProperty.propertyValue] ^
                  p[neihbourProperty.propertyNumber][i + 2][neihbourProperty.propertyValue]);
      }
    }
    break;
  }
  }
  return tree;
}

bdd restriction_4(const bdd p[M][N][N], const PropertyOfObject currentProperty, const PropertyOfObject neihbourProperty)
{
  bdd treeTmp = bddfalse;
  std::vector< NeighbourType > neighbours = { NeighbourType::LEFT, NeighbourType::TOPLEFT };
  for (NeighbourType neighbour: neighbours)
  {
    treeTmp |= restriction_3(p, neighbour, currentProperty, neihbourProperty);
  }
  return treeTmp;
}

void restriction_5(bdd & tree, const bdd p[M][N][N])
{

  for (unsigned j = 0; j < N; ++j)
  {
    for (unsigned i = 0; i < N - 1; ++i)
    {
      for (unsigned k = i + 1; k < N; ++k)
      {
        for (unsigned m = 0; m < M; ++m)
        {
          tree &= p[m][i][j] >> !p[m][k][j];
        }
      }
    }
  }
}

bdd restriction_6(const bdd p[M][N][N])
{
  bdd tree = bddtrue;
  for (int i = 0; i < N; ++i)
  {
    for (int k = 0; k < M; ++k)
    {
      bdd temp0 = bddfalse;
      for (int j = 0; j < N; ++j)
      {
        temp0 |= p[k][i][j];
      }
      tree &= temp0;
    }
  }
  return tree;
}
