#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(void)
{
  std::string originalFileName, modifiedFileName;
  size_t num;

  std::cout << "input original file name:";
  std::cin >> originalFileName;

  std::cout << "input modified file name:";
  std::cin >> modifiedFileName;

  std::cout << "What is the number of the file?:";
  std::cin >> num;

  std::ifstream originalFile(originalFileName, std::ios::binary);

  originalFile.seekg(0, std::ios::end);
  size_t originalFileSize = originalFile.tellg();
  originalFile.seekg(0);

  char *originalData = new char[originalFileSize];
  originalFile.read(originalData, originalFileSize);

  std::ifstream modifiedFile(modifiedFileName, std::ios::binary);

  modifiedFile.seekg(0, std::ios::end);
  size_t modifiedFileSize = modifiedFile.tellg();
  modifiedFile.seekg(0);

  char *modifiedData = new char[modifiedFileSize];
  modifiedFile.read(modifiedData, modifiedFileSize);

  std::ofstream newFile("_" + originalFileName, std::ios::trunc | std::ios::binary);

  size_t files = 1;

  for (size_t i = 0; i < originalFileSize; i++)
  {
    char data2[4] = {0x50, 0x4B, 0x03, 0x04};
    if (!memcmp(&originalData[i], data2, 4))
    {
      if (num == files++)
      {
        newFile.write((char *)&modifiedData[0], modifiedFileSize);
        i += 10;
        while (memcmp(&originalData[i++], data2, 4))
          ;
        newFile.write((char *)&originalData[i], originalFileSize - i);
        break;
      }
      else
        newFile.write((char *)&originalData[i], 1);
    }
    else
      newFile.write((char *)&originalData[i], 1);
  }
  delete[] originalData;
  delete[] modifiedData;
  originalFile.close();
  modifiedFile.close();
  newFile.close();

  return 0;
}
