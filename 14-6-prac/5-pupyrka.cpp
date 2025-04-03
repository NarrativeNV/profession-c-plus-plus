#include <iostream>
#include <vector>

void pupyrka_output(std::vector<std::vector<bool>> pupyrka)
{
  std::cout << std::endl;
  std::cout << "Pupyrka field\n\n";
  for (int i = 0; i < pupyrka.size(); i++)
  {
    for (int j = 0; j < pupyrka.size(); j++)
    {
      if (pupyrka[i][j] == true)
        std::cout << "O" << " ";
      else
        std::cout << "X" << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::vector<std::vector<bool>> pupyrka_field(std::vector<std::vector<bool>> pupyrka)
{
  for (int i = 0; i < pupyrka.size(); i++)
  {
    for (int j = 0; j < pupyrka.size(); j++)
    {
      pupyrka[i][j] = true;
    }
  }

  return pupyrka;
}

std::vector<std::vector<bool>> pupyrka_burst(std::vector<std::vector<bool>> pupyrka)
{
  std::cout << "Bubble burst(x y): ";
  int x, y;
  std::cin >> x >> y;
  if (x > 0 && y > 0 && x < pupyrka.size() + 1 && y < pupyrka.size() + 1)
  {
    if (pupyrka[x - 1][y - 1] == true)
    {
      pupyrka[x - 1][y - 1] = false;
      std::cout << "Succesfull\n";
    }
    else
      std::cout << "\nThe bubble has already burst";
  }
  else
    std::cout << "\nInvalid coordinates";

  return pupyrka;
}

bool field_check(std::vector<std::vector<bool>> pupyrka)
{
  for (int i = 0; i < pupyrka.size(); i++)
  {
    for (int j = 0; j < pupyrka.size(); j++)
    {
      if (pupyrka[i][j] == true)
        return true;
    }
  }
  return false;
}

int main()
{
  const int size = 2;
  std::vector<std::vector<bool>> pupyrka(size, std::vector<bool>(size));
  pupyrka = pupyrka_field(pupyrka);
  while (field_check(pupyrka))
  {
    pupyrka_output(pupyrka);
    pupyrka = pupyrka_burst(pupyrka);
  }
  std::cout << "\nGame Over\n";
  pupyrka_output(pupyrka);
}