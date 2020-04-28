#include <iostream>
using namespace std;

int position;
char board[9], player;

// Imprime board na tela
void draw() {
  int i;
  for(i = 0; i < 9; i++) {
    cout << board[i];
    if (i == 8) {
      break;
    }
    if ((i + 1) % 3 == 0 ) {
      cout << endl;
      cout << "_________";
      cout << endl;
    } else {
      cout << " | ";
    }
  }
  cout << endl;
}

// Prepara a jogada e recebe a posição desejada
void input() {
  while (1) {
    cout << "Jogador " << player << ": " << endl;
    cout << "Escolha uma posição de 1 a 9" << endl;
    cin >> position;
    if (board[position - 1] != 'X' && board[position - 1] != '0') {
      board[position - 1] = player;
      break;
    }
  }
}

// Alterna o jogador
void togglePlayer() {
  if (player == 'X') {
    player  = 'O';
  } else {
    player = 'X';
  }
}

char checkWin() {
    if (board[0] == board[1] && board[1] == board[2]) {
      return board[0];
    }
    if (board[3] == board[4] && board[3] == board[5]) {
      return board[3];
    }
    if (board[6] == board[7] && board[7] == board[8]) {
      return board[6];
    }
    if (board[0] == board[3] && board[3] == board[6]) {
      return board[0];
    }
    if (board[1] == board[4] && board[4] == board[7]) {
      return board[1];
    }
    if (board[2] == board[5] && board[5] == board[8]) {
      return board[2];
    }
    if (board[0] == board[4] && board[4] == board[8]) {
      return board[0];
    }
    if (board[2] == board[4] && board[4] == board[6]) {
      return board[0];
    }
    return 0;
}

int checkEnd() {
  int i;
  for (i = 0; i < 9; i++) {
    if (board[i] >= '1' && board[i] <= '9') {
      return 0;
    }
  }
  return 1;
}

int main () {

  player = 'X';
  int i;

  for(i = 1; i < 10; i++) {
      board[i - 1] = '0' + i;
  }

  while (1) {
    system("clear");
    draw();
    if (checkWin()) {
      cout << "Vencedor: jogador " << checkWin() << endl;
      break;
    }
    if (checkEnd()) {
      cout << endl << "V E L H A" << endl;
      break;
    }
    input();
    togglePlayer();
  }

  return 0;
}
