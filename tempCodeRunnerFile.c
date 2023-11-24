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

// Function prototypes
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);

// Function to perform the user login
bool performLogin() {
    const int MAX_LOGIN_ATTEMPTS = 3;
    const char* CORRECT_USER_ID = "id1";
    const char* CORRECT_PASSCODE = "abcd";
    char inputUserId[20];
    char inputPasscode[20];
    
    printf("AirUCCS Rental Property Owner Login\n");
    
    for (int attempts = 1; attempts <= MAX_LOGIN_ATTEMPTS; attempts++) {
        printf("Enter your airUCCS id: ");
        scanf("%s", inputUserId);
        printf("Enter your airUCCS passcode: ");
        scanf("%s", inputPasscode);
        
        if (strcmp(inputUserId, CORRECT_USER_ID) == 0 && strcmp(inputPasscode, CORRECT_PASSCODE) == 0) {
            printf("Login successful\n");
            return true;
        } else {
            printf("Error: Incorrect id or passcode\n");
        }
    }
    
    printf("Exiting airUCCS\n");
    return false;
}

int main() { 
    if (!performLogin()) {
        return 1; // Exit the program if login fails
    }

    unsigned int totalNights = 0;
    double totalCharges = 0.0;
    int isFirstInput = 1;
    bool shouldContinue = true;

    printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

    while (shouldContinue) {
        int nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);

        if (isFirstInput && nights == -1) {
            printf("There were no rentals.\n");
            shouldContinue = false;
        }
        else {
            isFirstInput = 0;

            if (nights == -1) {
                
                printf("\nTotal Nights: %u\nTotal Charges: $%.2lf\n", totalNights, totalCharges);
                shouldContinue = false;
            }
            else {
                double charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
                printNightsCharges(nights, charges);
                totalNights += nights;
                totalCharges += charges;
            }
        }
    }

    return 0;
}