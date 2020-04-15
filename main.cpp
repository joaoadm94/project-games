#include <iostream>
using namespace std;

int main () {

  bool finish;
  int turn;
  char board[3][3];
  int i, j;

  turn = 1;
  finish = false;

  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      board[i][j] = ' ';
    }
  }

  while (!finish) {
    for(i = 0; i < 3; i++) {
      for(j = 0; j < 3; j++) {
        cout << board[i][j];
        if (j < 2) {
          cout << " | ";
        }
      }
      if (i < 2) {
        cout << endl;
        cout << "_________";
      }
      cout << endl;
    }
    finish = true;
  }

  return 0;
}
