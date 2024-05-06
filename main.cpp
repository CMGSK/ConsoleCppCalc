#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <sys/types.h>

float parseOperation(char* line);
void removeSpc(char* &input);

int main() {
  float result;
  std::cout << "C++ :: Calc: " << std::endl << std::endl;
  std::cout << std::setprecision(6);
  char *line = new char[80]();

  while (true) {
    std::cout << "> ";
    std::cin.getline(line, 80);
    removeSpc(line);
    if (strcmp(line, "quit") == 0) break;

    try{
      float result = parseOperation(line);
      if (result != result){
        std::cout << "Arithmetic ERR" << std::endl; 
        continue;
      }
      std::cout << "\t" << line << " = " << result << std::endl;
    } catch (...) { std::cout << "Internal ERR" << std::endl; }
  }
  return 0;
}

float parseOperation(char* line) {
  float nums[2] = {};
  char op = '\0';
  char *iter = line;
  // 10 lines of dark magic
  if (*iter == '-') iter++;
  while ((*iter >= '0'  && *iter <= '9') || *iter == '.') 
    iter++;
  op = *iter;
  nums[0] = std::strtof(line, &iter);
  line = ++iter;
  if (*iter == '-') iter++;
  while ((*iter >= '0'  && *iter <= '9') || *iter == '.') 
    iter++;
  nums[1] = std::strtof(line, &iter);

  if (op == '\0') throw "Inline multi-operators are not allowed on this version";
  if(iter != line && op=='\0') return nums[0];

  switch (op) {
  case '+':
    return nums[0] + nums[1];
  case '-':
    return nums[0] - nums[1];
  case '*':
    return nums[0] * nums[1];
  case '/':
    return nums[0] / nums[1];
  case '%':
    return nums[0] * (nums[1]/100);
  case 'e': {
    float result =  nums[0] * ((float) pow(10, nums[1]));
    return result;
  }
  case 'r':
    return std::sqrt(nums[0]);
  case '^':{
    float result = 1;
    for (int i=0; i<nums[1]; ++i)
      result *= nums[0];
    return result;
  }
  default:
    return std::numeric_limits<float>::quiet_NaN();
  }
    return std::numeric_limits<float>::quiet_NaN();
}

void removeSpc(char* &input){
  char* saver = input;
  char* iter = input;
  while (*iter != '\0') {
    if (*iter != ' ' && *iter != '='){
      *saver = *iter;
      iter++;
      saver++;
    } else iter++;
  } 
  *saver = 0;
}
