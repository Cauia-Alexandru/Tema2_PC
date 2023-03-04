#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./util/scrabble.h"
#include "./util/print_board.h"
#define BOARD_SIZE 15
#define WORDS_SIZE 100
char game_board[BOARD_SIZE][BOARD_SIZE];
 
void fill_game_board()
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			game_board[i][j] = '.';
		}
	}
}
 
char *readScrabbleLine(char Number[])
{
	fgets(Number, 100, stdin);
	return strtok(Number, " ");
}
 
void task_1()
{
	char Number[100];
	fgets(Number, 100, stdin);
	int num = atoi(Number);
	for (int i = 0; i < num; i++)
	{
		char *string = readScrabbleLine(Number);
 
		char Y[4];
		strcpy(Y, string);
		int Y_integer = atoi(Y);
		string = strtok(NULL, " ");
 
		char X[4];
		strcpy(X, string);
		int X_integer = atoi(X);
		string = strtok(NULL, " ");
 
		char D[4];
		strcpy(D, string);
		int D_integer = atoi(D);
		string = strtok(NULL, " ");
 
		char given_word[100];
		strcpy(given_word, string);
 
		if (D_integer == 0)
		{
			for (int i = 0; i < (int)strlen(given_word) - 1; ++i)
			{
				game_board[Y_integer][X_integer + i] = given_word[i];
			}
		}
		else
			for (int i = 0; i < (int)strlen(given_word) - 1; ++i)
			{
				game_board[Y_integer + i][X_integer] = given_word[i];
			}
	}
}
 
void task_2()
{
	int player1_score = 0;
	int player2_score = 0;
	char Number[100];
	int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	fgets(Number, 100, stdin);
	int num = atoi(Number);
 
	for (int i = 0; i < num; i++)
	{
 
		char *string = readScrabbleLine(Number);
 
		
		string = strtok(NULL, " ");
 
		
		string = strtok(NULL, " ");
 
		
		string = strtok(NULL, " ");
 
		char given_word[100];
		strcpy(given_word, string);
		int lenght = strlen(given_word);
		if (i % 2 == 0)
		{
 
			for (int i = 0; i < lenght; i++)
			{
				player1_score += scores[(int)(given_word[i] - 'A')]; 
			}
		}
		else
		{
			for (int i = 0; i < lenght; i++)
			{
				player2_score += scores[(int)(given_word[i] - 'A')];
			}
		}
	}
 
	printf("Player 1: %d Points", player1_score);
	printf("\nPlayer 2: %d Points", player2_score);
}
 

 int calculateWordPoint(char given_word[], int letter_score[26])
{
	int returned_word_points = 0;
	int given_word_length = strlen(given_word);
	for (int i = 0; i < given_word_length - 1; i++)
	{
		returned_word_points += letter_score[(int)(given_word[i] - 'A')];
	}
 
	return returned_word_points;
}


int checkGivenWordMatchTriple(char given_word[], char YY[])
{
	int given_word_length = strlen(given_word);
	if (given_word[given_word_length - 3] == YY[0] &&
		given_word[given_word_length - 2] == YY[1])
		return 1;
	return 0;
}

int checkGivenWordMatchDouble(char given_word[], char XX[])
{
	if (strstr(given_word, XX) != NULL)
		return 1;
	return 0;
}

int calculateMultiplier(int D_integer, int Y_integer, int X_integer, int canBeDoubled, int canBeTripled, int given_word_length)
{
	int multiplier = 1;
	for (int i = 0; i < given_word_length - 1; ++i)
	{
		int bonus_board_value;
		if (D_integer == 1)
			bonus_board_value = bonus_board[Y_integer + i][X_integer];
		if (D_integer == 0)
			bonus_board_value = bonus_board[Y_integer][X_integer + i];
 
		if (canBeDoubled && bonus_board_value == 1)
		{
			multiplier = multiplier * 2;
		}
		if (canBeTripled && bonus_board_value == 2)
		{
			multiplier = multiplier * 3;
		}
	}
 
	return multiplier;
}

void task_3()
{
	char XX[10], YY[10];
	fgets(XX, 10, stdin); 
	XX[strlen(XX) - 1] = '\0';
	fgets(YY, 10, stdin); 
	YY[strlen(YY) - 1] = '\0';
 
	int letter_score[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	char nr_words[100];
	fgets(nr_words, 100, stdin);
	int nr_words_int = atoi(nr_words);
	int score_player1 = 0, score_player2 = 0; 
 
	for (int i = 0; i < nr_words_int; i++)
	{
		int multiplier = 1;
		int word_point1 = 0, word_point2 = 0;
		char word_info[100];
 
		char *token_string = readScrabbleLine(word_info);
 
		char Y[5];
		strcpy(Y, token_string);
		int Y_integer = atoi(Y);
		token_string = strtok(NULL, " ");
 
		char X[5];
		strcpy(X, token_string);
		int X_integer = atoi(X);
		token_string = strtok(NULL, " ");
 
		char D[5];
		strcpy(D, token_string);
		int D_integer = atoi(D);
		token_string = strtok(NULL, " ");
 
		char given_word[100];
		strcpy(given_word, token_string);
 
		int canBeTripled = checkGivenWordMatchTriple(given_word, YY);
		int canBeDoubled = checkGivenWordMatchDouble(given_word, XX);
 
		int given_word_length = strlen(given_word);
 
		multiplier = calculateMultiplier(D_integer, Y_integer, X_integer, canBeDoubled, canBeTripled, given_word_length);
 
		if (i % 2 == 0)
		{
			word_point1 = calculateWordPoint(given_word, letter_score);
 
			score_player1 = score_player1 + word_point1 * multiplier;
		}
		else
		{
 
			word_point2 = calculateWordPoint(given_word, letter_score);
			score_player2 = score_player2 + word_point2 * multiplier;
		}
	}
	printf("Player 1: %d Points", score_player1);
	printf("\nPlayer 2: %d Points\n", score_player2);
}
 

void initArray(int *array, int n)
{
	for (int i = 0; i < n; i++)
	{
		*(array + i) = 0;
	}
}

int findWordInArray(char given_word[])
{
	for (int i = 0; i < WORDS_SIZE; i++)
	{
 
		int isFound = 1;
		for (int j = 0; j < WORDS_SIZE; j++)
		{
			if (words[i][j] == '\0' || given_word[j] == '\0')
				break;
			if (words[i][j] != given_word[j])
			{
				isFound = 0;
				break;
			}
		}
		if (isFound == 1)
			return i;
	}
	return -1;
}

void fillGameBoardWithWord(int D_integer, int Y_integer, int X_integer, char given_word[])
{
	int length = strlen(given_word);
	for (int i = 0; i < length-1; ++i)
	{
		if (D_integer == 0)
			game_board[Y_integer][X_integer+i] = given_word[i];
		if (D_integer == 1)
			game_board[Y_integer+i][X_integer] = given_word[i];
	}
}
void getPositionsOfWordsWordInMatrix(char firstCharacterOfWord, int returnedMatrix[2][225], int *positionsFoundNumber)
{
	int ROWS = 2;
	int COLUMNS = 225;
 
	*(positionsFoundNumber) = 0;
 
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			returnedMatrix[i][j] = -1;
 
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (game_board[i][j] == firstCharacterOfWord)
			{
				returnedMatrix[0][*positionsFoundNumber] = i;
				returnedMatrix[1][*positionsFoundNumber] = j;
				(*positionsFoundNumber)++;
			}
		}
	}
}
int getDirection(int line, int column, int word_length)
{
	int canGoHorizontal = 1, canGoVertical = 1;
 
	if (column + word_length > BOARD_SIZE)
		canGoHorizontal = 0;
	if (line + word_length > BOARD_SIZE)
		canGoVertical = 0;
	for (int i = 1; i < word_length && canGoHorizontal == 1; i++)
	{
		if (game_board[line][column + i] != '.')
		{
			canGoHorizontal = 0;
			break;
		}
	}
 
	for (int i = 1; i < word_length && canGoVertical == 1; i++)
	{
		if (game_board[line + i][column] != '.')
		{
			canGoVertical = 0;
			break;
		}
	}
	if (canGoHorizontal == 1)
		return 0;
	if (canGoVertical == 1)
		return 1;
	return -1;
}

void task_4()
{
	int foundWord = 0;
	const int FIRST_CHAR = 0;
	int foundInArray[100];
	initArray(&foundInArray[0], 100);
 
	char XX[10], YY[10];
	fgets(XX, 10, stdin); 
	XX[strlen(XX) - 1] = '\0';
	fgets(YY, 10, stdin); 
	YY[strlen(YY) - 1] = '\0';
	char nr_words[100];
	fgets(nr_words, 100, stdin);
	int nr_words_int = atoi(nr_words); 
 
	for (int i = 0; i < nr_words_int; i++)
	{
		char word_info[100];
 
		char *token_string = readScrabbleLine(word_info);
 
		char Y[5];
		strcpy(Y, token_string);
		int Y_integer = atoi(Y);
		token_string = strtok(NULL, " ");
 
		char X[5];
		strcpy(X, token_string);
		int X_integer = atoi(X);
		token_string = strtok(NULL, " ");
 
		char D[5];
		strcpy(D, token_string);
		int D_integer = atoi(D);
		token_string = strtok(NULL, " ");
 
		char given_word[100];
		strcpy(given_word, token_string);
 
		int position = findWordInArray(given_word);
		if (position != -1)
			foundInArray[position] = 1;
 
		fillGameBoardWithWord(D_integer, Y_integer, X_integer, given_word);
	}
 
 
	for (int i = 0; i < WORDS_SIZE && foundWord == 0; i++)
	{
		char currentWord[100];
		int currentWordLength = 0;
		int charPositionsMatrix[2][225];
		int positionsFound;
 
		if(foundInArray[i] == 1)
			continue;
 
 
		getPositionsOfWordsWordInMatrix(words[i][FIRST_CHAR], charPositionsMatrix, &positionsFound);
		if (positionsFound == 0)
			continue;
 
		for (int j = 0; words[i][j] != '\0' && j < WORDS_SIZE; j++)
		{
			currentWord[j] = words[i][j];
			currentWordLength++;
		}
 
		currentWord[currentWordLength+1] = '\0'; 
 
		for (int j = 0; j < positionsFound && foundWord == 0; j++)
		{
			int direction = getDirection(charPositionsMatrix[0][j], charPositionsMatrix[1][j], currentWordLength);
			if(direction == -1) continue;
 
			fillGameBoardWithWord(direction,charPositionsMatrix[0][j], charPositionsMatrix[1][j],currentWord);
			foundWord = 1;
		}
	}
}
 

int isExceedingMatrixLimit(char wordFromWordsLength, int D_integer, int Y_integer, int X_integer)
{
	if (D_integer == 0 && wordFromWordsLength + X_integer > BOARD_SIZE)
	{
		return 1;
	}
	if (D_integer == 1 && wordFromWordsLength + Y_integer > BOARD_SIZE)
	{
		return 1;
	}
	return 0;
}
 
int main()
{
	char input_char[3];
	fgets(input_char, 3, stdin);
	int verify = atoi(input_char);
 
	if (verify == 0)
	{
		fill_game_board();
		print_board(game_board);
	}
 
	if (verify == 1)
	{
		fill_game_board();
		task_1();
		print_board(game_board);
	}
	if (verify == 2)
	{
		task_2();
	}
	if (verify == 3)
	{
		fill_game_board();
		task_3();
	}
	if (verify == 4)
	{
		fill_game_board();
		task_4();
		print_board(game_board);
	}
 
	return 0;
}