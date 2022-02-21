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
#include <string.h>
#include "questions.h"

// Initializes game questions, answers, and point values
void initialize_game(void)
{
    // Instantiate questions array with each question struct
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        strcpy(questions[i].category, categories[i % 3]);
        questions[i].answered = false;
        strcpy(questions[i].question, "Question");
        strcpy(questions[i].answer, "Answer");
    }

    // Initialize questions, answers, and point values
    questions[0].value = 100;
    strcpy(questions[0].question, "This is rolled out to the airplane stairs when visiting foreign dignitaries arrive");
    strcpy(questions[0].answer, "a red carpet");

    questions[1].value = 100;
    strcpy(questions[1].question, "Some men who may have never turned on an oven in the kitchen routinely perform this outdoor cooking activity");
    strcpy(questions[1].answer, "grilling");

    questions[2].value = 100;
    strcpy(questions[2].question, "Born on October 20, 1882, this Hungarian actor is best remembered for his role as the most famous vampire of all time");
    strcpy(questions[2].answer, "Bela Lugosi");

    questions[3].value = 200;
    strcpy(questions[3].question, "These red berries are a Thanksgiving favorite");
    strcpy(questions[3].answer, "a cranberry");

    questions[4].value = 200;
    strcpy(questions[4].question, "This compartment in a commercial or military aircraft was once the exclusive domain of men");
    strcpy(questions[4].answer, "a cockpit");

    questions[5].value = 200;
    strcpy(questions[5].question, "Born October 14, 1890, he was the last general to serve as U.S. president");
    strcpy(questions[5].answer, "Dwight D. Eisenhower");

    questions[6].value = 400;
    strcpy(questions[6].question, "This adorable bug is red with black dots");
    strcpy(questions[6].answer, "a ladybug");

    questions[7].value = 400;
    strcpy(questions[7].question, "Women are from Venus, and men are from this planet");
    strcpy(questions[7].answer, "Mars");

    questions[8].value = 400;
    strcpy(questions[8].question, "Born October 16, 1925, this grand dame of TV mysteries plays Jessica Fletcher in Murder, She Wrote");
    strcpy(questions[8].answer, "Angela Lansbury");
}

// Displays remaining categories and point values in an ASCII table
void display_categories(void)
{
    // Width of table in characters
    int width = 40;

    for (int i = 0; i < 3; i++) {
        // Left Corner
        putchar('+');
        for (int j = 0; j < width; j++) {
            // Top Horizontal Line
            putchar('-');
        }
    }

    // Right Corner
    printf("+\n");

    for (int i = 0; i < 3; i++) {
        // Display Category Name
        printf("| %-*s", width - 1, categories[i]);
    }

    // Right Border
    printf("|\n");

    for (int i = 0; i < 3; i++) {
        // Left Corner
        putchar('+');
        for (int j = 0; j < width; j++) {
            // Horizontal Line
            putchar('-');
        }
    }

    printf("\n");

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (questions[i].answered == false) {
            // Display Question Value
            printf("| $%-*d", width - 2, questions[i].value);
        } else {
            // Display Answered Question
            printf("|  %-*s", width - 2, " -   ");
        }

        if (i % 3 == 2) {
            // Left Border
            printf("|\n");
        }
    }

    for (int i = 0; i < 3; i++) {
        // Right Corner
        putchar('+');
        for (int j = 0; j < width; j++) {
            // Bottom Horizontal Line
            putchar('-');
        }
    }
}

// Display the question, category, and point value
void display_question(char *category, int value)
{
    // Display category and point value
    printf("Question (%s for $%d):\n", category, value);

    // Get question index
    int num = get_question(category, value);
    if (num == -1) {
        // Question not found
        printf("Error: Question %s not found, %d\n", category, value);
        return;
    }

    // Display question
    printf("\t%s.\n", questions[num].question);
}

// Returns true if the answer is correct from the category and point value
bool valid_answer(char *category, int value, char *answer)
{
    // Get question index
    int num = get_question(category, value);
    if (num == -1) {
        // Question not found
        printf("Error: Question %s not found, %d\n", category, value);
        return false;
    }

    // Check answer to question
    return (strcasecmp(answer, questions[num].answer) == 0);
}

// Set question as answered from the category and point value
void set_answered(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (questions[i].value == value && strcasecmp(questions[i].category, category) == 0) {
            questions[i].answered = true;
        }
    }
}

// Return the question index from the category and point value
int get_question(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++)
        if (strcasecmp(questions[i].category, category) == 0 && questions[i].value == value)
            return i;

    return -1;
}

// Return true if there are unanswered questions remaining
bool running() {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (questions[i].answered == false) {
            return true;
        }
    }

    return false;
}