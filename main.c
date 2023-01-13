#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define SPADE 0
#define HEART 1
#define DIAMOND 2
#define CLUB 3
#define JOKER 4


char player1[100], player2[100], gameMode[100];
int nowMode = 0;
int card[54];
int player1Card[54] = {0}, player2Card[54] = {0}, deskCard[54] = {0};
int nowNumberISay = 0;
int carzyModePlusMinusNumber = 0;
int nowshouldDrop = 0;
int player1Foul = 0, player2Foul = 0;

void enterName() {
	char choice[100];
	while(1) {
		printf("\n\n\nEnter player 1 name : ");
		scanf("%s",player1);fflush(stdin);
		printf("\n\n\nEnter player 2 name : ");
		scanf("%s",player2);fflush(stdin);
		printf("\n\n%s  v.s.  %s\n\nsure?(y/n) : ",player1, player2);
		scanf("%s",choice);fflush(stdin);
		// printf("\nchoice : %s",choice);
		if(!strcmp(choice,"y")) {
			printf("\n\nOK, Let's start!\n\n");
			system("pause");
			break;
		}else if(!strcmp(choice,"n")) {
			printf("\n\nRetype your names...\n\n");
			system("pause");
		}else {
			printf("\n\n%s..?\n\nWhat are you talking about?\n\n",choice);
			system("pause");
		}
		system("cls");
	}
}

void gameModeSetting() {
	char choice[100];
	system("cls");
	printf("\n\nHi \'%s\' and \'%s\'",player1,player2);
	printf("\n\nNow you guys choose the game mode : ");
	while(1) {
		printf("\n\n1. normal game\n\tWhen the player says the same number as the card number->\'hit\'\n");
		printf("\n2. crazy mode\n\tWhen the player says the number after +x or -x as the card number->\'hit\'\n\nMode : ");
		scanf("%s",gameMode);fflush(stdin);
		if(!strcmp(gameMode,"1")) {
			printf("\n\nOK, game mode 1. normal game\n\nsure?(y/n) : ");
			scanf("%s",choice);fflush(stdin);
			if(!strcmp(choice,"y")) {
				printf("\n\nsetting game mode \'normal game\'\n\n");
				nowMode = 0;
				system("pause");
				break;
			}else if(!strcmp(choice,"n")) {
				printf("\n\n.....\n\n");
				system("pause");
			}else {
				printf("\n\n%s..?\n\nWhat are you talking about?\n\n",choice);
				system("pause");
			}
		}else if(!strcmp(gameMode,"2")) {
			printf("\n\nOK, game mode 2. crazy mode\n\nsure?(y/n) : ");
			scanf("%s",choice);fflush(stdin);
			if(!strcmp(choice,"y")) {
				printf("\n\nOK, game mode 2. crazy mode\n\n");
				printf("\n\nWhat number would you like to + -?(at most 3) : \n\n");
				scanf("%d",&carzyModePlusMinusNumber);
				if(carzyModePlusMinusNumber>3) {
					printf("\nToo large....Default set to hardest mode +-3\n\n");
					carzyModePlusMinusNumber = 3;
				}else if(carzyModePlusMinusNumber<=0) {
					printf("\nToo small....Default set to smallest mode +-1\n\n");
					carzyModePlusMinusNumber = 1;
				}
				nowMode = carzyModePlusMinusNumber;
				system("pause");
				break;
			}else if(!strcmp(choice,"n")) {
				printf("\n\n.....\n\n");
				system("pause");
			}else {
				printf("\n\n%s..?\n\nWhat are you talking about?\n\n",choice);
				system("pause");
			}
		}else {
			printf("\n\n%s..?\n\nFun?\n\n",gameMode);
			system("pause");
		}
		system("cls");
	}
}

void setCard() {
	for(int i = 0; i<54; ++i)
		card[i] = i+1;
}

void shuffleCard(int *a,int len,int time) {
	if(len > 54) {
		printf("Warning : out of array range <shuffleCard()>\n");
	}
    int change_position;
    int temp;
    for(int t=0; t <= time; ++t)
    {
        for(int change=len-1; change >= 0; --change)
        {
            change_position=rand()%(change+1);
            temp=a[change];
            a[change]=a[change_position];
            a[change_position]=temp;
        }
    }
}

void printCard(int *a, int position) {
	if(position >= 54 || position < 0) {
		printf("Warning : out of array range <printCard()>\n");
		exit(0);
	}
	if(a[position] == 0) {
		printf("No card\n");
		return;
	}
	int suit = (a[position]-1)/13, number = (a[position]-1)%13+1;
	switch(suit){
		case SPADE:
		printf("Spade   %2d\n",number);
		break;
		case HEART:
		printf("Heart   %2d\n",number);
		break;
		case DIAMOND:
		printf("Diamond %2d\n",number);
		break;
		case CLUB:
		printf("Club    %2d\n",number);
		break;
		case JOKER:
		printf("Joker\n");
		break;
	}
}

void printCardGraphic(int *a, int position) {
	if(position >= 54 || position < 0) {
		printf("Warning : out of array range <printCard()>\n");
		exit(0);
	}
	if(a[position] == 0) {
		printf("No card\n");
		return;
	}
	int suit = (a[position]-1)/13, number = (a[position]-1)%13+1;
	printf("--------------\n");
	printf("\t|            |\n");
	switch(suit){
		case SPADE:
		printf("\t|    Spade   |\n");
		break;
		case HEART:
		printf("\t|    Heart   |\n");
		break;
		case DIAMOND:
		printf("\t|   Diamond  |\n");
		break;
		case CLUB:
		printf("\t|    CLUB    |\n");
		break;
		case JOKER:
		printf("\t|            |\n");
		printf("\t|            |\n");
		printf("\t|            |\n");
		printf("\t|    JOKER   |\n");
		printf("\t|            |\n");
		printf("\t|            |\n");
		printf("\t|            |\n");
		printf("\t|            |\n");
		printf("\t|            |\n");
		printf("\t--------------\n");
		return;
	}
	switch(number){
		case 1:
		printf("\t|            |\n");
		printf("\t|      |     |\n");
		printf("\t|     | |    |\n");
		printf("\t|    |   |   |\n");
		printf("\t|   |-----|  |\n");
		printf("\t|  |       | |\n");
		printf("\t| |         ||\n");
		printf("\t|            |\n");
		printf("\t--------------\n");
		break;
		case 2:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |         |\n");
		printf("\t|  |         |\n");
		printf("\t|  --------  |\n");
		printf("\t--------------\n");
		break;
		case 3:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|  --------  |\n");
		printf("\t--------------\n");
		break;
		case 4:
		printf("\t|            |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t--------------\n");
		break;
		case 5:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |         |\n");
		printf("\t|  |         |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|  --------  |\n");
		printf("\t--------------\n");
		break;
		case 6:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |         |\n");
		printf("\t|  |         |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  --------  |\n");
		printf("\t--------------\n");
		break;
		case 7:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|            |\n");
		printf("\t--------------\n");
		break;
		case 8:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  --------  |\n");
		printf("\t--------------\n");
		break;
		case 9:
		printf("\t|            |\n");
		printf("\t|  --------  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  |      |  |\n");
		printf("\t|  --------  |\n");
		printf("\t|         |  |\n");
		printf("\t|         |  |\n");
		printf("\t|            |\n");
		printf("\t--------------\n");
		break;
		case 10:
		printf("\t|            |\n");
		printf("\t| |  ------- |\n");
		printf("\t| |  |     | |\n");
		printf("\t| |  |     | |\n");
		printf("\t| |  |     | |\n");
		printf("\t| |  |     | |\n");
		printf("\t| |  ------- |\n");
		printf("\t|            |\n");
		printf("\t--------------\n");
		break;
		case 11:
		printf("\t|            |\n");
		printf("\t| ---------- |\n");
		printf("\t|       |    |\n");
		printf("\t|       |    |\n");
		printf("\t|       |    |\n");
		printf("\t|  |    |    |\n");
		printf("\t|   ----     |\n");
		printf("\t|            |\n");
		printf("\t--------------\n");
		break;
		case 12:
		printf("\t|            |\n");
		printf("\t|   ------   |\n");
		printf("\t|  |      |  |\n");
		printf("\t| |        | |\n");
		printf("\t| |        | |\n");
		printf("\t|  |   |  |  |\n");
		printf("\t|   ----|-   |\n");
		printf("\t|        |   |\n");
		printf("\t--------------\n");
		break;
		case 13:
		printf("\t|            |\n");
		printf("\t| |       |  |\n");
		printf("\t| |      |   |\n");
		printf("\t| |     |    |\n");
		printf("\t| |----|     |\n");
		printf("\t| |     |    |\n");
		printf("\t| |      |   |\n");
		printf("\t| |       |  |\n");
		printf("\t--------------\n");
		break;
	}
}

void shareCard() {
	for(int i = 0; i<54; ++i)
		if(i<27)
            player1Card[i] = card[i];
        else
            player2Card[i-27] = card[i];
}

void dropCard(int player) {
	for(int i = 53; i>0; --i) {
		deskCard[i] = deskCard[i-1];
	}
	if(player == 1) {
		deskCard[0] = player1Card[0];
		for(int i = 0; i<54; ++i) {
			player1Card[i] = player1Card[i+1];
		}
	}else if(player == 2) {
		deskCard[0] = player2Card[0];
		for(int i = 0; i<54; ++i) {
			player2Card[i] = player2Card[i+1];
		}
	}
	++nowNumberISay;
	if(nowNumberISay>13)
		nowNumberISay = 1;
}

int isWin(int *a) {
	if(*a == 0)
		return 1;
	return 0;
}

int hitDesk() {
	if((nowNumberISay+nowMode+13)%13 == (deskCard[0]-1)%13+1 || (nowNumberISay-nowMode+13)%13 == (deskCard[0]-1)%13+1 || (deskCard[0]-1)/13 == JOKER)
		return 1;
	return 0;
}

void addCardFromDeskToPlayer(int player) {
	int playerCardNum, deskCardNum = 0;
	for(playerCardNum = 0; player==1?player1Card[playerCardNum]:player2Card[playerCardNum] != 0; ++playerCardNum);
	for(deskCardNum = 0; deskCard[deskCardNum] != 0; ++deskCardNum);
	if(player == 1) {
		for(int i = playerCardNum; i<deskCardNum+playerCardNum; ++i) {
			player1Card[i] = deskCard[i-playerCardNum];
			deskCard[i-playerCardNum] = 0;
		}
	}else {
		for(int i = playerCardNum; i<deskCardNum+playerCardNum; ++i) {
			player2Card[i] = deskCard[i-playerCardNum];
			deskCard[i-playerCardNum] = 0;
		}
	}
}

void printUI() {
	int player1CardNum, player2CardNum, deskCardNum;
	system("cls");
	printf("\n%s\tv.s.\t%s\n",player1,player2);
	printf("%d foul\t\t%d foul\n\n",player1Foul,player2Foul);
	if(!nowMode) {
		printf("Normal Mode\n\n");
	}else {
		printf("Crazy Mode Now +- %d\n\n",nowMode);
	}
	for(player1CardNum = 0; player1Card[player1CardNum] != 0; ++player1CardNum);
	for(player2CardNum = 0; player2Card[player2CardNum] != 0; ++player2CardNum);
	for(deskCardNum = 0; deskCard[deskCardNum] != 0; ++deskCardNum);
	printf("%s has %d cards\t %s has %d cards\n\n\n",player1,player1CardNum,player2,player2CardNum);
	printf("    %s's turn\n\n\n",nowshouldDrop == 1?player1:player2);
	printf("    Now number is : %d\n\n\n",nowNumberISay);
	printf("\t");
	printCardGraphic(deskCard,0);
	printf("\n\n    Cards on desks : %d\n\n\n",deskCardNum);
}

void play() {
	char press;
	int i = 0;
	printf("\n\nDecide who drop first(1/2) : ");
	scanf("%d",&nowshouldDrop);
	if(nowshouldDrop != 1 && nowshouldDrop != 2) {
		printf("\n\n = = I decide %s drop first",player1);
		nowshouldDrop = 1;
	}
	printf("\n\nFor %s :\n\t\'a\' key for dropping cards, \'s\' key for hitting the desk",player1);
	printf("\n\nFor %s :\n\t\'k\' key for dropping cards, \'l\' key for hitting the desk\n\n\n",player2);
	printf("You should receive a foul :\n\t1. if you skip the turn you should hit the desk");
	printf("\n\t2. drop the card on opponent turn");
	printf("\n\t3. anyone receive 3 fouls will lose the game\n\n\n");
	system("pause");
	while(1) {
		printUI();
		if(player1Foul == 3) {
			printf("\n\n%s receives 3 fouls\n\n",player1);
			printf("\n\'%s\' You Win!!!\n\n",player2);
			system("pause");
			break;
		}else if(player2Foul == 3) {
			printf("\n\n%s receives 3 fouls\n\n",player2);
			printf("\n\'%s\' You Win!!!\n\n",player1);
			system("pause");
			break;
		}
		press = getch();
		if(press == 'a') {
			// player 1 drop
			// printf("a pressed\n");
			if(nowshouldDrop == 1) {
				if(nowNumberISay!=0 && ((nowNumberISay+nowMode+13)%13 == (deskCard[0]-1)%13+1 || (nowNumberISay-nowMode+13)%13 == (deskCard[0]-1)%13+1 || (deskCard[0]-1)/13==JOKER)) {
					printf("\n\n%s you need to hit !!\n\n",player1);
					++player1Foul;
					system("pause");
				}else {
					dropCard(1);
					nowshouldDrop = 2;
				}
			}else {
				printf("\n\nNot %s turn~ foul %d",player1,++player1Foul);
				system("pause");
			}
			if(isWin(player1Card)) {
				system("cls");
				printf("\n\n\'%s\' You Win!!!\n\n",player1);
				printf("\n\n\'%s\' You Lose!!!\n\n",player2);
				system("pause");
				return;
			}
		}else if(press == 's') {
			// player 1 hit
            // printf("s pressed\n");
            if(hitDesk()) {
            	addCardFromDeskToPlayer(2);
            	nowshouldDrop = 2;
            	printf("\n\'%s\'' hit the right card, add all the cards on desk to \'%s\'\n",player1,player2);
            }else {
            	addCardFromDeskToPlayer(1);
            	nowshouldDrop = 1;
            	printf("\n\'%s\'' hit the wrong card, add all the cards on desk to \'%s\'\n",player1,player1);
            }
            nowNumberISay = 0;
            system("pause");
            system("pause");
		}else if(press == 'k') {
			// player 2 drop
            // printf("k pressed\n");
            if(nowshouldDrop == 2) {
				if(nowNumberISay!=0 && ((nowNumberISay+nowMode+13)%13 == (deskCard[0]-1)%13+1 || (nowNumberISay-nowMode+13)%13 == (deskCard[0]-1)%13+1 || (deskCard[0]-1)/13==JOKER)) {
					printf("\n\n%s you need to hit !!\n\n",player2);
					++player2Foul;
					system("pause");
				}else {
					dropCard(2);
					nowshouldDrop = 1;
				}
			}else {
				printf("\n\nNot %s turn~ foul %d",player2,++player2Foul);
				system("pause");
			}
            if(isWin(player2Card)) {
				system("cls");
				printf("\n\n\'%s\' You Win!!!\n\n",player2);
				printf("\n\n\'%s\' You Lose!!!\n\n",player1);
				system("pause");
				return;
			}
		}else if(press == 'l') {
			// player 2 hit
            // printf("l pressed\n");
            if(hitDesk()) {
            	addCardFromDeskToPlayer(1);
            	nowshouldDrop = 1;
            	printf("\n\'%s\'' hit the right card, add all the cards on desk to \'%s\'\n",player2,player1);
            }else {
            	addCardFromDeskToPlayer(2);
            	nowshouldDrop = 2;
            	printf("\n\'%s\'' hit the wrong card, add all the cards on desk to \'%s\'\n",player2,player2);
            }
            nowNumberISay = 0;
            system("pause");
            system("pause");
		}else {
            printf("\n\n\nStop typing wrong key\n");
            system("pause");
		}
	}
}

int main() {
	srand(time(NULL));
	setCard();
    printf("welcome to SlapJack");
	enterName();
	gameModeSetting();
	shuffleCard(card,54,1);
	shareCard();
	system("cls");
	play();
    return 0;
}

