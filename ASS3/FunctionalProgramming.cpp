#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>

typedef bool (*compFunction)(int, int);

bool isLessThan(int i, int j)
{
  return i < j;
}

bool isGreaterThan(int i, int j)
{
  return i > j;
}

std::function<bool(int,int)> generateNearestTo(int center)
{
  return [center](int i, int j){return abs(center - i) < abs(center - j);};
}

class IComparer
{
public:
  virtual ~IComparer(){}
  virtual bool isBefore(int i, int j) = 0;
};

class LessThanComparer : public IComparer
{
  ~LessThanComparer(){}
  virtual bool isBefore(int i, int j)
  {
    return i < j;
  }
};

class GreaterThanComparer : public IComparer
{
  ~GreaterThanComparer(){}
  virtual bool isBefore(int i, int j)
  {
    return i > j;
  }
};

class IsClosestToComparer : public IComparer
{
private:
  int center;

public:
  IsClosestToComparer(int c) : center(c){}
  ~IsClosestToComparer(){}
  virtual bool isBefore(int i, int j)
  {
    return (abs(center - i) < abs(center - j));
  }
};

void merge(int left, int right, int middle, int* p, std::function<bool(int, int)>& func)
{
  int i = left;
  int j = middle + 1;
  std::vector<int> merged;
  while (i <= middle && j <= right)
  {
    if (func(p[i], p[j]))
    {
      merged.push_back(p[i]);
      i++;
    }
    else
    {
      merged.push_back(p[j]);
      j++;
    }
  }

  while (i <= middle)
  {
    merged.push_back(p[i]);
    i++;
  }

  while (j <= right)
  {
    merged.push_back(p[j]);
    j++;
  }

  i = left;
  for (int v : merged)
  {
    p[i] = v;
    ++i;
  }
}

void merge(int left, int right, int middle, int* p, IComparer& comp)
{
  int i = left;
  int j = middle + 1;
  std::vector<int> merged;
  while (i <= middle && j <= right)
  {
    if (comp.isBefore(p[i], p[j]))
    {
      merged.push_back(p[i]);
      i++;
    }
    else
    {
      merged.push_back(p[j]);
      j++;
    }
  }

  while (i <= middle)
  {
    merged.push_back(p[i]);
    i++;
  }

  while (j <= right)
  {
    merged.push_back(p[j]);
    j++;
  }

  i = left;
  for (int v : merged)
  {
    p[i] = v;
    ++i;
  }
}

void merge(int left, int right, int middle, int* p, compFunction f)
{
  int i = left;
  int j = middle + 1;
  std::vector<int> merged;
  while (i <= middle && j <= right)
  {
    if ((*f)(p[i], p[j]))
    {
      merged.push_back(p[i]);
      i++;
    }
    else
    {
      merged.push_back(p[j]);
      j++;
    }
  }

  while (i <= middle)
  {
    merged.push_back(p[i]);
    i++;
  }

  while (j <= right)
  {
    merged.push_back(p[j]);
    j++;
  }

  i = left;
  for (int v : merged)
  {
    p[i] = v;
    ++i;
  }
}

void sortWithPointers(int* p, int left, int right, compFunction f)
{
  // Merge sort with pointer to comp function
  if (left < right)
  {
    /* divide length into two array length1 and length2 */
    int middle = left + (right - left) / 2; /* declare the number of elements in p1 */

    /*recursive call mergeSort*/
    sortWithPointers(p, left, middle, f);
    sortWithPointers(p, middle + 1, right, f);

    /* Finish putting it to together */
    merge(left, right, middle, p, f);
  } 
  else
  {
    return; /*return array when length is less than 2*/
  }
}

void sortWithInterfaces(int* p, int left, int right, IComparer& comp)
{
  // Merge sort with pointer to comp function
  if (left < right)
  {
    /* divide length into two array length1 and length2 */
    int middle = left + (right - left) / 2; /* declare the number of elements in p1 */

    /*recursive call mergeSort*/
    sortWithInterfaces(p, left, middle, comp);
    sortWithInterfaces(p, middle + 1, right, comp);

    /* Finish putting it to together */
    merge(left, right, middle, p, comp);
  } 
  else
  {
    return; /*return array when length is less than 2*/
  }
}

void sortWithStandardFunction(int* p, int left, int right, std::function<bool(int, int)>& func)
{
  // Merge sort with pointer to comp function
  if (left < right)
  {
    /* divide length into two array length1 and length2 */
    int middle = left + (right - left) / 2; /* declare the number of elements in p1 */

    /*recursive call mergeSort*/
    sortWithStandardFunction(p, left, middle, func);
    sortWithStandardFunction(p, middle + 1, right, func);

    /* Finish putting it to together */
    merge(left, right, middle, p, func);
  } 
  else
  {
    return; /*return array when length is less than 2*/
  }
}

void testSortWithPointers(compFunction f)
{
  const int length = 10;
  int* A = new int[length];

  for (int i = 0; i < length; ++i) 
  {
    A[i] = rand() % 100 + 1;
  } 

  printf("Before merge sort: ");
  for (int i = 0; i < length; ++i)
  {
    printf ("%i ", A[i]);
  }
  printf("\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  
  sortWithPointers(A , 0, length - 1, f);

  printf("After merge sort: ");
  for (int i = 0; i < length; ++i)
  {
    printf ("%i ", A[i]);
  }
  printf("\n");
  printf("---------------------------------------------------------------------------------------------\n" );
}

void testSortWithInterfaces(IComparer& comp)
{
  const int length = 10;
  int* A = new int[length];

  for (int i = 0; i < length; ++i) 
  {
    A[i] = rand() % 100 + 1;
  } 

  printf("Before merge sort: ");
  for (int i = 0; i < length; ++i)
  {
    printf ("%i ", A[i]);
  }
  printf("\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  
  sortWithInterfaces(A , 0, length - 1, comp);

  printf("After merge sort: ");
  for (int i = 0; i < length; ++i)
  {
    printf ("%i ", A[i]);
  }
  printf("\n");
  printf("---------------------------------------------------------------------------------------------\n" );
}

void testSortWithLambdas(std::function<bool(int, int)>& func)
{
  const int length = 10;
  int* A = new int[length];

  for (int i = 0; i < length; ++i) 
  {
    A[i] = rand() % 100 + 1;
  } 

  printf("Before merge sort: ");
  for (int i = 0; i < length; ++i)
  {
    printf ("%i ", A[i]);
  }
  printf("\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  
  sortWithStandardFunction(A , 0, length - 1, func);

  printf("After merge sort: ");
  for (int i = 0; i < length; ++i)
  {
    printf ("%i ", A[i]);
  }
  printf("\n");
  printf("---------------------------------------------------------------------------------------------\n" );
}

int main()
{
  printf("Testing Sort with isLessThan function pointers\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  compFunction f = &isLessThan;
  testSortWithPointers(f);

  printf("Testing Sort with isGreaterThan function pointer \n");
  printf("---------------------------------------------------------------------------------------------\n" );
  f = &isGreaterThan;
  testSortWithPointers(f);

  printf("\n");
  printf("Testing Sort with LessThanComparer intefarface\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  IComparer* comp = new LessThanComparer();
  testSortWithInterfaces(*comp);

  printf("Testing Sort with GreaterThanComparer intefarface\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  comp = new GreaterThanComparer();
  testSortWithInterfaces(*comp);

  int center = 10;
  printf("Testing Sort with IsClosestToComparer intefarface with %i as the center value\n", center);
  printf("---------------------------------------------------------------------------------------------\n" );
  comp = new IsClosestToComparer(center);
  testSortWithInterfaces(*comp);

  printf("\n");
  printf("Testing Sort with Lambdas\n");
  printf("---------------------------------------------------------------------------------------------\n" );
  auto func = generateNearestTo(center);
  testSortWithLambdas(func);
  
  delete comp;
}