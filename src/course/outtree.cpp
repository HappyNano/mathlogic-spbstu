#include "course/outtree.hpp"
#include <iostream>
#include <cmath>
#include "course/vars.hpp"

static const int LOG_N = std::ceil(std::log2(N));
char var[VAR_NUM];

void print()
{
  for (unsigned i = 0; i < N; i++)
  {
    std::cout << i << ": ";
    for (unsigned j = 0; j < M; j++)
    {
      int J = i * M * LOG_N + j * LOG_N;
      int num = 0;
      for (unsigned k = 0; k < LOG_N; k++)
      {
        num += (unsigned)(var[J + k] << k);
      }
      std::cout << num << ' ';
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void build(char * varset, unsigned n, unsigned I)
{
  if (I == n - 1)
  {
    if (varset[I] >= 0)
    {
      var[I] = varset[I];
      print();
      return;
    }
    var[I] = 0;
    print();
    var[I] = 1;
    print();
    return;
  }
  if (varset[I] >= 0)
  {
    var[I] = varset[I];
    build(varset, n, I + 1);
    return;
  }
  var[I] = 0;
  build(varset, n, I + 1);
  var[I] = 1;
  build(varset, n, I + 1);
}

// Обработчик для bdd
void fun(char * varset, int size)
{
  build(varset, size, 0);
}