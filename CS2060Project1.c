#include <stdio.h>

int main() {
    int nights;
    double rate = 400.00;
    double totalCharge = 0.0;

    printf("Rental Property can be rented for 1 to 14 nights.\n");
    printf("$%.2lf rate a night for the first 3 nights\n", rate);
    printf("$50.00 discount rate a night for nights 4 to 6\n");
    printf("$100.00 discount rate a night for each remaining night over 6.\n");

    printf("Enter the number of nights you want to rent the property: ");
    scanf("%d", &nights);

    if (nights >= 1 && nights <= 3) {
        totalCharge = rate * nights;
    } else if (nights >= 4 && nights <= 6) {
        totalCharge = (rate * 3) + ((nights - 3) * (rate - 50.00));
    } else if (nights >= 7 && nights <= 14) {
        totalCharge = (rate * 3) + (3 * (rate - 50.00)) + ((nights - 6) * (rate - 100.00));
    } else {
        printf("Invalid number of nights entered. Please choose between 1 and 14 nights.\n");
        return 1; // Exit with an error code
    }

    printf("\nRental Charges\n\n");
    printf("Nights          Charge\n");
    printf("%-5d          $%.2lf\n", nights, totalCharge);

    return 0;
}

   

