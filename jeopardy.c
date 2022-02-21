/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Group 18
 * Laith Hasan
 * Hamza Zahid
 * Tanner Little
 *
 * Copyright (C) 2020
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

int main(int argc, char *argv[])
{
    // Display the game introduction and initialize the questions
    initialize_game();

    printf("This is Jeopardy\n");

    // Prompt for number of players
    int num_players = 0;

    printf("Number of players: ");
    scanf("%d", (int *) &num_players);

    player players[num_players];

    // Prompt for players names
    for (int i = 0; i < num_players; i++) {
        players[i].score = 0;

        printf("Enter player %i's name: ", (i+1));
        scanf("%s", (char *) &players[i].name);
    }

    system("clear");

    // Infinite loop until all questions have been answered
    while (running()) {
        char selected_player[MAX_LEN] = "";
        char selected_category[MAX_LEN] = "";
        int selected_val = 0;

        // Prompt for next player until a valid player is provided
        do {
            if (strcasecmp(selected_player, "") != 0) {
                printf("Unable to find the player: %s\n", selected_player);
            }

            printf("Enter next player's name: ");
            scanf("%s", (char *) &selected_player);
        } while (!player_exists(players, num_players, selected_player));

        // Prompt for category and value until a valid category and value is provided
        do {
            if (selected_val != 0) {
                system("clear");
            }

            display_categories();

            if (selected_val != 0) {
                printf("\nInvalid category, please try again.\n");
            }

            printf("\nEnter category: ");
            getchar();
            fgets((char *) selected_category, MAX_LEN, stdin);
            strtok(selected_category, "\n");

            printf("Enter Value: ");
            scanf("%d", (int *) &selected_val);
        } while(questions[get_question(selected_category, selected_val)].answered);

        // Prompt for answer until a valid answer is provided
        bool answered = false;

        do {
            if (selected_val != 0) {
                system("clear");
            }

            if (answered) {
                printf("Make sure to begin answers with \"what is\" or \"who is\".\n\n");
            }

            display_question(selected_category, selected_val);

            char *answer[MAX_LEN] = {0};
            printf("\nAnswer: ");
            if (!answered) getchar();
            fgets((char *) answer, MAX_LEN, stdin);

            char *tokenize_answer;
            tokenize((char *) answer, &tokenize_answer);

            answered = true;

            if (tokenize_answer == NULL) {
                continue;
            }

            if (valid_answer(selected_category, selected_val, tokenize_answer)) {
                printf("Correct Answer!\n");
                printf("Player %s gained %d points!\n\n", selected_player, selected_val);
                update_score(players, 4, selected_player, selected_val);
            } else {
                printf("Wrong Answer!\n");
                int num = get_question(selected_category, selected_val);
                printf("The correct answer is: [Who/What] is %s?\n\n", questions[num].answer);
            }

            set_answered(selected_category, selected_val);
        } while (!questions[get_question(selected_category, selected_val)].answered);
    }

    // No more questions available, display final results
    show_results(players, num_players);
    getchar();

    // Exit
    return EXIT_SUCCESS;
}

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char *str;

    // Isolate first word of answer
    if ((str = strtok(input, " ")) != NULL) {
        // Verify the first word is "who" or "what", otherwise return NULL
        if (strcasecmp(str, "who") != 0 && strcasecmp(str, "what") != 0) {
            *tokens = NULL;
            return;
        }
    }

    // Isolate second word of answer
    if ((str = strtok(NULL, " ")) != NULL) {
        // Verify the second word is "is", otherwise return NULL
        if (strcasecmp(str, "is") != 0) {
            *tokens = NULL;
            return;
        }
    }

    // Return tokenized answer
    *tokens = strtok(NULL, "\n");
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // Initialize local variables
    int player = 0;
    int score = 0;
    int winner = 0;

    // Sort players by points and determine winnder
    for (int i = 0; i < num_players; i++) {
        if ((int) strlen(players[i].name) > player) {
            player = strlen(players[i].name);
        }

        if (players[i].score > score) {
            score = players[i].score;
            winner = i;
        }
    }

    // Display final results
    system("clear");

    printf("Game Over!\n\nScores: \n");
    for (int i = 0; i < num_players; i++) {
        printf("%*s: %d\n", player + 1, players[i].name, players[i].score);
    }

    printf("Winner: %s with a score of %d!", players[winner].name, players[winner].score);
}
