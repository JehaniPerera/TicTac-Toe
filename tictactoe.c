#include<stdio.h>
#include<stdlib.h>

char tictac[3][3]={
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'}
};

void tictacboard(){
	for(int i=0;i<3;i++){
		printf("%c |%c |%c \n", tictac[i][0],tictac[i][1],tictac[i][2]);
		if(i!=2){
			printf("--|--|--\n");
		}
	}

}
int check() {
	//rows
	for(int i=0;i<3;i++){
		if(tictac[i][0]==tictac[i][1] && tictac[i][1]==tictac[i][2]){
			return 0;
		}
	}
	//columns
	for (int i = 0; i < 3; i++) {
        if (tictac[0][i] == tictac[1][i] && tictac[1][i] == tictac[2][i]) {
            return 1;
        }
    }
    // diagonals
    if (tictac[0][0] == tictac[1][1] && tictac[1][1] == tictac[2][2]) {
        return 1;
    }
    if (tictac[2][0] == tictac[1][1] && tictac[1][1] == tictac[0][2]) {
        return 1;
    }

    // check draw
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tictac[i][j] != 'x' && tictac[i][j] != 'o') {
                count++;
            }
        }
    }
    if (count == 0) return 2;

    return 0;
}

int main() {
    int row, column, move, gamestatus;
    int player = 1;

    while (1) {
        system("clear"); 
        tictacboard();

        player = (player % 2) ? 1 : 2;
        printf("Player %d move (1-9): ", player);
        scanf("%d", &move);

        // input validation
        if (move < 1 || move > 9) {
            printf("Invalid input! Please enter 1-9.\n");
            player--;
            continue;
        }

        row = (move - 1) / 3;
        column = (move - 1) % 3;

        if (tictac[row][column] != 'x' && tictac[row][column] != 'o') {
            tictac[row][column] = (player == 1) ? 'x' : 'o';
        } else {
            printf("Warning! Cell already taken.\n");
            player--;
        }

        gamestatus = check();
        if (gamestatus == 1) {
            system("cls");
            tictacboard();
            printf("Player %d Wins!\n", player);
            break;
        } else if (gamestatus == 2) {
            system("cls");
            tictacboard();
            printf("Match Draw! Try again.\n");
            break;
        }
        player++;
    }
    return 0;
}




