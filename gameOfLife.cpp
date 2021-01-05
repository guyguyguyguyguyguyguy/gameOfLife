// Could be interesting to give nodes a value of more than 1, and introduce some sort of entropy
// Don't actually need a bool value, but does allow extension if I want to include varying 'fitness'

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Game.h"
#include "datastructs.h"
#include "Visual.h"


int main() {
  srand(0);
  char randConfig;
  Visual *a; 
  do {
    std::cout << "Random starting configuration? [y/n] \n";
    std::cin >> randConfig;
  } while (!std::cin.fail() && randConfig != 'y' && randConfig != 'n');
  
  if (randConfig == 'y') {
    a = new Visual(true);
  } else {
    a = new Visual(false);
  }
  a->run();
  
  delete a;
  return 1;
}



