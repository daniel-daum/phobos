#include <iostream>
using namespace std;

void showMenu() { 
cout << "1. Add\n2. View\n3. Exit\n"; 
} 

int main() { 
    
int option; 

do { 
       	showMenu(); 
       	cin >> option; 
    } while (option != 3); 
return 0; 

} 






