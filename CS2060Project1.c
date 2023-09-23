#include <stdio.h>

// Constants for rental property information 
int const SENTINEL_NEG1 = -1;
unsigned int const MIN_RENTAL_NIGHTS = 1;/*The difference between unsigned int const and signed int 
const lies in the range of values they can represent and how they handle negative and positive numbers:
    Unsigned int is an integer data type that represents non-negative whole numbers.It cannot represent negative numbers.
        Signed int is an integer data type that can represent both positive and negative whole numbers.
*/
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;
double const RENTAL_RATE = 400.00;
double const DISCOUNT = 50.00;

// Function prototypes - they kind of act as an interface from java
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max, int sentinel);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);

int main() {
    /*Print rental property information - printRentalPropertyInfo() under main will be used to
    print out the desired strings */
    printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

    /* Get the number of nights from the user - getValidInt() under main will be used to find a vaild int
     that fits the assaignment details, this is also where i will make sure that the code will not 
     stop running fro some random reason such as a -1 or 000 being entered. */
    int nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1);

    //-1 is used as a sentinel value to signal that there were no rentals when input by the user.
    if (nights != SENTINEL_NEG1) {
        // Calculate charges and print results
        double charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
        printNightsCharges(nights, charges);
   //more info about calc charges down bellow
    } else {
        printf("There were no rentals.\n");//should only ever print this is -1 is entered
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
    if (nights <= interval1Nights) { //this is the base pay without any discounts being added
        totalCharge = rate * nights;
    } else if (nights <= interval2Nights) { // this is for the 50$ disount for nights 4 to 6
        totalCharge = (rate * interval1Nights) + ((nights - interval1Nights) * (rate - discount));
    } else { //and this is with the 100$ discount after night 6
        totalCharge = (rate * interval1Nights) + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - discount * 2));
    }
    return totalCharge;
}

void printNightsCharges(unsigned int nights, double charges) {
    printf("\nRental Charges\n\n");
    printf("Nights          Charge\n");
    printf("%-5u          $%.2lf\n", nights, charges);
}