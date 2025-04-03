#include <iostream>
#include <limits>

int main()
{

  while (true)
  {
    const int size = 4;
    float vector[size];
    float matrix[size][size];
    std::cout << "\nInput matrix values(a b c d)\n";
    for (int i = 0; i < 4; i++)
    {
      std::cout << i + 1 << " line: ";
      std::cin >> matrix[i][0] >> matrix[i][1] >> matrix[i][2] >> matrix[i][3];
    }

    std::cout << "Input vector values(a b c d): ";
    std::cin >> vector[0] >> vector[1] >> vector[2] >> vector[3];

    float multiply_vector[size] = {};

    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        multiply_vector[i] += matrix[i][j] * vector[j];
      }
    }

    std::cout << "Final vector: ";
    for (int i = 0; i < 4; i++)
    {
      std::cout << multiply_vector[i] << " ";
    }
    std::cout << std::endl;
  }
}