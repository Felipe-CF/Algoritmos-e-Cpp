#include <iostream>
#include <iomanip>
#include "array_list.hpp"
using namespace std;

int main(){
    array_list l1;
    for(int i = 1; i <= 10; ++i){
        l1.push_back(i);
    }
    cout << "l1 = [ ";
    l1.print_list();
    cout << "]" << endl;
    
     cout << "size = " << l1.size() << " capacity = " << l1.capacity() << endl;
     cout << "percent occupied = "  << fixed << setprecision(2) << l1.percent_occupied() << endl;
     cout << "sum = " << l1.sum() << endl;
     cout << "front = " << l1.front() << " back = " << l1.back() << endl;
     cout << "insert_at(3, 4)" << endl;
      l1.insert_at(3, 14);
      l1.print_list();
      cout << endl;
      cout << "get_at(3) = " << l1.get_at(3) << endl;

      cout << " remove_at(3)" << endl;
      l1.remove_at(3);
      l1.print_list();
      cout << endl;

     cout << "get_at(3) = " << l1.get_at(3) << endl;

     cout << "pop_front" << endl;
     l1.pop_front();
     l1.print_list();
     cout << endl;
     cout << "pop_back" << endl;
     l1.pop_back();
     l1.print_list();
     cout << endl;
     cout << "remove(5)" << endl;
     l1.remove(5);
     l1.print_list();
     cout << endl;
     cout << "find(7)" << endl;
     cout <<  l1.find(7) << endl;
     l1.insert_at(4, 17);
     l1.print_list();
     cout << "count(7)" << endl;
     cout <<  l1.count(17) << endl;
     l1.clear();
     l1.print_list();
    return 0;
}