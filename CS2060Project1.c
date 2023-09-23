#include <stdio.h>

// Constants for rental property information
int const SENTINEL_NEG1 = -1;
unsigned int const MIN_RENTAL_NIGHTS = 1;
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;
double const RENTAL_RATE = 400.00;
double const DISCOUNT = 50.00;

// Function prototypes
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max, int sentinel);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);

int main() {
    // Print rental property information
    printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

    // Get the number of nights from the user
    int nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1);

    if (nights != SENTINEL_NEG1) {
        // Calculate charges and print results
        double charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
        printNightsCharges(nights, charges);
    } else {
        printf("There were no rentals.\n");
    }

    return 0;
}

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {
    printf("Rental Property can be rented for %u to %u nights.\n", minNights, maxNights);
    printf("$%.2lf rate a night for the first %u nights\n", rate, interval1Nights);
    printf("$%.2lf discount rate a night for nights %u to %u\n", discount, interval1Nights + 1, interval2Nights);
    printf("$%.2lf discount rate a night for each remaining night over %u.\n", discount * 2, interval2Nights);
}

int getValidInt(int min, int max, int sentinel) {
    int input;
    while (1) {
        printf("Enter the number of nights you want to rent the property: ");
        if (scanf("%d", &input) != 1) {
            // Invalid input (non-integer)
            printf("Error: Not an integer number. Please enter the value again.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else if (input == sentinel) {
            // Check for sentinel value
            break;
        } else if (input < min || input > max) {
            // Input out of range
            printf("Error: Not within %d and %d. Please enter the value again.\n", min, max);
        } else {
            // Valid input, break out of the loop
            break;
        }
    }
    return input;
}

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {
    double totalCharge = 0.0;
    if (nights <= interval1Nights) {
        totalCharge = rate * nights;
    } else if (nights <= interval2Nights) {
        totalCharge = (rate * interval1Nights) + ((nights - interval1Nights) * (rate - discount));
    } else {
        totalCharge = (rate * interval1Nights) + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - discount * 2));
    }
    return totalCharge;
}

void printNightsCharges(unsigned int nights, double charges) {
    printf("\nRental Charges\n\n");
    printf("Nights          Charge\n");
    printf("%-5u          $%.2lf\n", nights, charges);
}