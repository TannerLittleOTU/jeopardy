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
#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdbool.h>

#define MAX_LEN 256
#define NUM_CATEGORIES 3
// The number of questions, you can use this in your functions in
// questions.c, this can be accessed in questions.c
#define NUM_QUESTIONS 9

// List of 3 categories as array of strings
static char categories[NUM_CATEGORIES][MAX_LEN] = {
    "Simply Red",
    "Male Order",
    "October Baby"
};

// Questions struct for each question
typedef struct {
    char category[MAX_LEN];
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
} question;

// An array of 12 questions (4 for each category), initialized in initialize_game
// this may need to be a pointer if you want it set dynamically
question questions[NUM_QUESTIONS];

// Initializes game questions, answers, and point values
extern void initialize_game(void);

// Displays remaining categories and point values in an ASCII table
extern void display_categories(void);

// Display the question, category, and point value
extern void display_question(char *category, int value);

// Returns true if the answer is correct from the category and point value
extern bool valid_answer(char *category, int value, char *answer);

// Set question as answered from the category and point value
extern void set_answered(char *category, int value);

// Return the question index from the category and point value
extern int get_question(char *category, int value);

// Return true if there are unanswered questions remaining
extern bool running();

#endif /* QUESTIONS_H_ */