#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

bool charCmp(char *data1, char *data2, size_t size)
{
  for (size_t i = 0; i < size; i++)
    if (data1[i] != data2[i])
      return false;
  return true;
}

int main(void)
{
  std::string fileName;

  std::cout << "input file name:";
  std::cin >> fileName;

  std::ifstream ifs(fileName, std::ios::binary);

  ifs.seekg(0, std::ios::end);
  size_t size = ifs.tellg();
  ifs.seekg(0);

  char *data = new char[size];
  ifs.read(data, size);

  size_t files = 1;

  for (size_t i = 0; i < size - 4; i++)
  {
    char data2[4] = {0x50, 0x4B, 0x03, 0x04};
    if (charCmp(&data[i], data2, 4))
    {
      std::ofstream newZip(std::to_string(files++) + ".zip", std::ios::trunc | std::ios::binary);
      char data2[4] = {0x50, 0x4B, 0x05, 0x06};
      while (i < size - 4)
      {
        if (charCmp(&data[i], data2, 4))
        {
          for (size_t j = 0; j < 22; j++)
            newZip.write((char *)&data[i++], 1);
          break;
        }
        newZip.write((char *)&data[i++], 1);
      }
      newZip.close();
    }
  }
  delete []data;
  ifs.close();

  return 0;
}