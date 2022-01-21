#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();
  int client_socket = server_connect(listen_socket);
  subserver(client_socket);
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];
  int player = 1;
  char board[6][7];//create board
  clear_board(board);//clear it
  print_board(board);//print clean board
  while (1){
  	if (player == 1){
  		read(client_socket, buffer, sizeof(buffer));//read opponent move
  		int move = convert_int(buffer);//convert to int
  		place_piece(board, player, move);//place piece
  		print_board(board);
  		player = 2;
  	}
  	else{
  		int move = get_int(buffer, player);//get input to write
  		int fail = place_piece(board, player, move-1);//see if move fails
  		if (fail){
  			continue;//start over, new move
  		}
  		print_board(board);
    		write(client_socket, buffer, sizeof(buffer));//give input to opponent
  		player = 1;
  	}
  }
  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
