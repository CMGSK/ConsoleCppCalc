#include <cmath>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <limits>
#include <ostream>
#include <sys/types.h>

float parseOperation(char* line);
void removeSpc(char* &input);

int main() {
  float result;
  std::cout << "C++ :: Calc: " << std::endl << std::endl;
  char *line = new char[80]();

  while (true) {
    std::cout << "> ";
    std::cin.getline(line, 80);
    removeSpc(line);
    if (strcmp(line, "quit") == 0) break;

    try{
      float result = parseOperation(line);
      if (result == std::numeric_limits<float>::quiet_NaN()) throw std::exception();
      std::cout << line << " = " << result << std::endl;
    } catch (...) { std::cout << "Arithmetic ERR" << std::endl; }
  }
  return 0;
}

float parseOperation(char* line) {
  float nums[2] = {};
  char op = '\0';
  char *iter = line;
  // while (*iter != '\0' || *iter == '=') {
  //   if ((*iter >= '0'  && *iter <= '9') || *iter == '.'){
  //     ++iter;
  //   } 
  //   if (*iter < '0' && *iter > '9'){
  //     if(op == '\0'){
  //       op = *iter;
  //     } else throw "Multi-operations are not yet allowed in this version";
  //     char **ref = &iter;
  //     nums[0] = std::strtof(line, ref);
  //     nums[0] = std::strtof(, ref);
  //     iter++;
  //   }
  // }
  
  while ((*iter >= '0'  && *iter <= '9') || *iter == '.') 
    iter++;
  if(op == '\0')
    op = *iter;
  else throw "Inline multi-operations are not yet allowed in this version";
  nums[0] = std::strtof(line, &iter);
  line = ++iter;
  while ((*iter >= '0'  && *iter <= '9') || *iter == '.') 
    iter++;
  nums[1] = std::strtof(line, &iter);

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
  case 'e':
    return nums[0] * (pow(10, nums[1]));
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
    } else {
      iter++;
    }
  } 
  *saver = 0;
}
