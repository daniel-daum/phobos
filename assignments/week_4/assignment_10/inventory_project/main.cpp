#include "item.h"

using namespace std;

int main() {
  Item item1("Notebook", 10);
  Item item2("Pencil", 50);
  Item item3("dog", 1);

  item1.display();
  item2.display();
  item3.display();

  return 0;
}
