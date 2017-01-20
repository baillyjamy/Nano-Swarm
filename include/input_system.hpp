#ifndef INPUT_SYSTEM_HPP_
# define INPUT_SYSTEM_HPP_

# include <stdio.h>
# include <string>

class FileInput
{
private:
  FILE *file;
public:
  FileInput(char const *);
  ~FileInput();
  std::string toString();
};

#endif // !TMP_INPUT_SYSTEM
