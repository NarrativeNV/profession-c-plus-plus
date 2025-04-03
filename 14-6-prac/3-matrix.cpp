#include <iostream>
#include <limits>

bool matrix_match(int matrixA[][4], int matrixB[][4])
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (matrixA[i][j] != matrixB[i][j])
        return false;
    }
  }
  return true;
}

void matrix_output(int matrix[][4])
{
  std::cout << std::endl;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

int main()
{
  srand(time(NULL));
  int matrixA[4][4];
  int matrixB[4][4];

  std::cout << "Input matrix A values(a b c d)\n";
  for (int i = 0; i < 4; i++)
  {
    std::cout << i + 1 << " line: ";
    std::cin >> matrixA[i][0] >> matrixA[i][1] >> matrixA[i][2] >> matrixA[i][3];
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Input error. Please enter 4 integers.\n";
      i--;
      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::cout << "\nMatrix A";
  matrix_output(matrixA);

  std::cout << "Input matrix B values(a b c d)\n";
  for (int i = 0; i < 4; i++)
  {
    std::cout << i + 1 << " line: ";
    std::cin >> matrixB[i][0] >> matrixB[i][1] >> matrixB[i][2] >> matrixB[i][3];
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Input error. Please enter 4 integers.\n";
      i--;
      continue;
    }
  }

  std::cout << "\nMatrix B";
  matrix_output(matrixB);

  if (matrix_match(matrixA, matrixB))
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (j != i)
          matrixA[i][j] = 0;
      }
    }
    std::cout << "Matrices is Equal. Diagonal matrice";
    matrix_output(matrixA);
  }
  else
    std::cout << "The matrices are not equal";
}