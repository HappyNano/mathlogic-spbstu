#include <bdd.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "course/outtree.hpp"
#include "course/vars.hpp"
#include "course/conditions.hpp"

static const int LOG_N = std::ceil(std::log2(N));

void init(bdd p[M][N][N])
{
  for (int i = 0; i < M; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      for (int k = 0; k < N; ++k)
      {
        p[i][j][k] = bddtrue;
        for (int l = 0; l < LOG_N; ++l)
        {
          p[i][j][k] &= ((k >> l) & 1) ? bdd_ithvar((j * LOG_N * M) + l + LOG_N * i) : bdd_nithvar((j * LOG_N * M) + l + LOG_N * i);
        }
      }
    }
  }
}

int main()
{
  bdd_init(5000000, 7000000);
  bdd_setvarnum(VAR_NUM);
  bdd p[M][N][N];
  init(p);
  bdd tree = bddtrue;

  tree &= restriction_6(p);

  // 7
  tree &= restriction_1(p, PropertyOfObject(0, 0, 1));
  tree &= restriction_1(p, PropertyOfObject(1, 1, 3));
  tree &= restriction_1(p, PropertyOfObject(2, 2, 5));
  tree &= restriction_1(p, PropertyOfObject(3, 2, 2));
  tree &= restriction_1(p, PropertyOfObject(4, 3, 4));
  tree &= restriction_1(p, PropertyOfObject(5, 3, 0));
  tree &= restriction_1(p, PropertyOfObject(6, 2, 3));
  // Доп ограничения
  tree &= restriction_1(p, PropertyOfObject(3, 3, 3));
  tree &= restriction_1(p, PropertyOfObject(7, 3, 1));
  tree &= restriction_1(p, PropertyOfObject(0, 3, 5));
  tree &= restriction_1(p, PropertyOfObject(2, 3, 7));
  tree &= restriction_1(p, PropertyOfObject(5, 1, 4));
  tree &= restriction_1(p, PropertyOfObject(4, 1, 8));
  tree &= restriction_1(p, PropertyOfObject(6, 3, 6));

  // 4
  tree &= restriction_2(p, PropertyOfObject(-1, 3, 0), PropertyOfObject(-1, 0, 2));
  tree &= restriction_2(p, PropertyOfObject(-1, 2, 1), PropertyOfObject(-1, 0, 0));
  tree &= restriction_2(p, PropertyOfObject(-1, 2, 2), PropertyOfObject(-1, 0, 3));
  tree &= restriction_2(p, PropertyOfObject(-1, 2, 3), PropertyOfObject(-1, 0, 4));
  // Доп ограничения
  tree &= restriction_2(p, PropertyOfObject(-1, 2, 5), PropertyOfObject(-1, 0, 7));
  tree &= restriction_2(p, PropertyOfObject(-1, 1, 7), PropertyOfObject(-1, 0, 1));
  tree &= restriction_2(p, PropertyOfObject(-1, 1, 3), PropertyOfObject(-1, 0, 5));
  tree &= restriction_2(p, PropertyOfObject(-1, 3, 4), PropertyOfObject(-1, 0, 6));
  tree &= restriction_2(p, PropertyOfObject(-1, 0, 2), PropertyOfObject(-1, 2, 6));

  // 2
  tree &= restriction_3(p, NeighbourType::TOPLEFT, PropertyOfObject(-1, 3, 4), PropertyOfObject(-1, 2, 8));
  tree &= restriction_3(p, NeighbourType::LEFT, PropertyOfObject(-1, 0, 0), PropertyOfObject(-1, 2, 4));
  // Доп ограничения
  tree &= restriction_3(p, NeighbourType::LEFT, PropertyOfObject(-1, 1, 1), PropertyOfObject(-1, 2, 7));
  tree &= restriction_3(p, NeighbourType::TOPLEFT, PropertyOfObject(-1, 3, 2), PropertyOfObject(-1, 2, 0));
  tree &= restriction_3(p, NeighbourType::LEFT, PropertyOfObject(-1, 1, 5), PropertyOfObject(-1, 1, 6));

  // 6
  tree &= restriction_4(p, PropertyOfObject(-1, 0, 2), PropertyOfObject(-1, 0, 5));
  tree &= restriction_4(p, PropertyOfObject(-1, 2, 1), PropertyOfObject(-1, 2, 0));
  tree &= restriction_4(p, PropertyOfObject(-1, 0, 8), PropertyOfObject(-1, 3, 3));
  tree &= restriction_4(p, PropertyOfObject(-1, 3, 4), PropertyOfObject(-1, 1, 2));
  tree &= restriction_4(p, PropertyOfObject(-1, 1, 3), PropertyOfObject(-1, 1, 7));
  tree &= restriction_4(p, PropertyOfObject(-1, 2, 5), PropertyOfObject(-1, 3, 8));
  // Доп ограничения
  tree &= restriction_4(p, PropertyOfObject(-1, 2, 4), PropertyOfObject(-1, 1, 2));

  restriction_5(tree, p);

  std::cout << bdd_satcount(tree) << " solution(s):\n";
  bdd_allsat(tree, fun);
  bdd_done();

  return 0;
}
