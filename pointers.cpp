#include <iostream>
#include <string>
using namespace std;

struct Item {
  int id;
  string name;
};

int binarySearch(Item *items, int size, int targetId) {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    // the middle
    int mid = left + (right - left) / 2;

    if (items[mid].id == targetId) {
      return mid;
    }

    if (items[mid].id < targetId) {
      left = mid + 1;
    }

    else {
      right = mid - 1;
    }
  }

  return -1;
}

int main() {
  const int arraySize = 5;

  Item *items = new Item[5];

  items[0] = {1, "Dog"};
  items[1] = {2, "Cat"};
  items[2] = {3, "Fish"};
  items[3] = {4, "Rabbit"};
  items[4] = {5, "Parrot"};

  cout << "Items in the array:" << endl;

  for (int i = 0; i < arraySize; i++) {
    cout << "ID: " << items[i].id << ", Name: " << items[i].name << endl;
  }

  cout << endl;

  int searchId;
  cout << "Enter an ID to search for: ";
  cin >> searchId;

  int result = binarySearch(items, arraySize, searchId);

  if (result != -1) {

    cout << "Item found at index " << result << endl;
    cout << "Name: " << items[result].name << ", ID: " << items[result].id
         << endl;

  } else {
    cout << "Item with ID " << searchId << " not found." << endl;
  }

  delete[] items;

  return 0;
}
