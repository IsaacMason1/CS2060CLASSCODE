// Isaac Mason project iteration 2
// Profesor-Deb

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Constants for rental property information
unsigned int const MIN_RENTAL_NIGHTS = 1;
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;
double const RENTAL_RATE = 400.00;
double const DISCOUNT = 50.00;
// Maximum length of a string
#define STRING_LENGTH 80
// Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3
// Rental property login and sentinal values
#define CORRECT_PASSCODE "abcd"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1
// rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2
#define CORRECT_USER_ID "id1"
// Structures
struct Survey
{
    int checkInProcces;
    int cleanliness;
    int amentities;
};

struct Survey *createDynamicArray(int initialSize)
{
    return (struct Survey *)malloc(initialSize * sizeof(struct Survey));
}

void addSurvey(struct Survey **dynamicArray, int *size, int *capacity, struct Survey newSurvey) // my survey has 3 ints so it will take up 96 bits, the second * for dynamicArray is a pointer for a pointer
{
    if (*size >= *capacity)
    {
        *capacity = (*capacity == 0) ? 1 : (*capacity * 2);
        *dynamicArray = (struct Survey *)realloc(*dynamicArray, *capacity * sizeof(struct Survey));
    }

    (*dynamicArray)[*size] = newSurvey;
    (*size)++;
}
// Function prototypes
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount, struct Survey *surveys, int size);
int getValidInt(int min, int max);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);

// Function to perform the user login
bool performLogin()
{
    const int MAX_LOGIN_ATTEMPTS = 3;
    // const char* CORRECT_USER_ID = "id1";
    // const char* CORRECT_PASSCODE = "abcd";
    char inputUserId[20];
    char inputPasscode[20];

    printf("AirUCCS Rental Property Owner Login\n");

    for (int attempts = 1; attempts <= MAX_LOGIN_ATTEMPTS; attempts++)
    {
        printf("Enter your airUCCS id: ");
        scanf("%s", inputUserId);
        printf("Enter your airUCCS passcode: ");
        scanf("%s", inputPasscode);

        if (strcmp(inputUserId, CORRECT_USER_ID) == 0 && strcmp(inputPasscode, CORRECT_PASSCODE) == 0)
        {
            printf("Login successful\n");
            return true;
        }
        else
        {
            printf("Error: Incorrect id or passcode\n");
        }
    }

    printf("Exiting airUCCS\n");
    return false;
}

int main()
{
    unsigned int totalNights = 0;
    double totalCharges = 0.0;
    int isFirstInput = 1;
    bool shouldContinue = true;
    bool loggedIn = false;
    struct Survey *surveys = createDynamicArray(1);
    int size = 0;
    printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT, surveys, size);
    char buffer[80];

    int surveyResponses = 0;
    int capacity = 0;

    while (shouldContinue)
    {
        printf("Enter the number of nights you want to rent the property: ");
        int nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);

        if (isFirstInput && nights == -1)
        {
            printf("There were no rentals.\n");
            shouldContinue = false;
        }
        else
        {
            isFirstInput = 0;

            if (nights == -1 && !loggedIn)
            {
                // Ask for login only when entering -1 if not already logged in
                loggedIn = performLogin();
                if (!loggedIn)
                {
                    return 1;
                }
            }

            if (nights == -1)
            {
                printf("\nTotal Nights: %u\nTotal Charges: $%.2lf\n", totalNights, totalCharges);
                shouldContinue = false;
            }
            else
            {
                double charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
                printNightsCharges(nights, charges);
                totalNights += nights;
                totalCharges += charges;
                printf("check-in proccess 1-5 \n");

                int checkInProccess = getValidInt(1, 5);
                printf("cleanliness 1-5 \n");
                int cleanliness = getValidInt(1, 5);
                printf("amenities 1-5 \n");
                int amenities = getValidInt(1, 5);

                struct Survey response = {checkInProccess, cleanliness, amenities};
                addSurvey(&surveys, &size, &capacity, response);
                printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT, surveys, size);
            }
        }
    }

    return 0;
}

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount, struct Survey *surveys, int size)
{
    printf("Rental Property: Grin and Bear It Cabin. \n");
    printf("Location: Grand Lake,  Colorado. \n");
    printf("Rental Property can be rented for %u to %u nights.\n", minNights, maxNights);
    printf("$%.2lf rate a night for the first %u nights\n", rate, interval1Nights);
    printf("$%.2lf discount rate a night for nights %u to %u\n", discount, interval1Nights + 1, interval2Nights);
    printf("$%.2lf discount rate a night for each remaining night over %u.\n", discount * 2, interval2Nights);

    for (int i = 0; i < size; i++)
    {
        printf("Survey %d: checkInProcces=%d, cleanliness=%d, amentities=%d\n", i + 1, surveys[i].checkInProcces, surveys[i].cleanliness, surveys[i].amentities);
    }
}

int getValidInt(int min, int max)
{
    bool shouldContinue1 = true;
    int input;
    char buffer[256]; // Buffer to read input as a string
    while (shouldContinue1)
    {
        // printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            // if error reading input occurs print statement below
            printf("Error reading input. Please try again.\n");
            continue;
        }
        if (sscanf(buffer, "%d", &input) != 1)
        {
            // if invalid input (not an integer) is entered then print statement below
            printf("Error: Not an integer number. Please enter the value again.\n");
            continue;
        }

        if (input != -1 && (input < min || input > max))
        {
            // if input is out of range of the min and max nights then print this statement
            printf("Error: Not within %d and %d. Please enter the value again.\n", min, max);
        }
        else
        {
            // Valid input was entered, break out of the loop
            shouldContinue1 = false;
        }
    }
    return input;
}

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount)
{
    double totalCharge = 0.0;
    if (nights <= interval1Nights)
    {
        totalCharge = rate * nights; // this is the flat rate before getting to the 4th-night discount
    }
    else if (nights <= interval2Nights)
    {
        totalCharge = (rate * interval1Nights) + ((nights - interval1Nights) * (rate - discount));
        // this is for the night 4-6 50$ discount
    }
    else
    {
        totalCharge = (rate * interval1Nights) + ((interval2Nights - interval1Nights) * (rate - discount)) +
                      ((nights - interval2Nights) * (rate - discount * 2));
        // this is with all of the discounts after achieving 7 or more nights
    }
    return totalCharge;
}

void printNightsCharges(unsigned int nights, double charges)
{ // strings to show the final results
    printf("\nRental Charges\n\n");
    printf("Nights          Charge\n");
    printf("%-5u          $%.2lf\n", nights, charges);
}