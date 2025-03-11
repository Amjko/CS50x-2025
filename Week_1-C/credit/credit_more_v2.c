#include <stdio.h>
#include <cs50.h>

//* Function prototypes
int luhns_algorithm(long card_number, int total_sum);
int card_type_check(long card_number, int card_length);
int invalid(void);

//* Main function
int main(void)
{
    //* Prompt for credit card number
    // Long for holding card number
    long card_number;

    // No other symbols beside digits
    do
    {
        card_number = get_long("Number: ");
    } while (card_number <= 1);

    //* Count card number length
    // Temp variable for counting
    long counting_temp = card_number;
    int card_length = 0;

    // Counts card number length
    while (counting_temp > 0)
    {
        counting_temp /= 10;
        card_length++;
    }

    //* Check if card number is valid using Luhn's Algorithm
    // Variable for initial sum before total sum of digits
    int initial_sum = 0;
    int total_sum = luhns_algorithm(card_number, initial_sum);

    //* Check type of card based on number
    // If product is divisible by 10 = 0
    if (total_sum % 10 == 0)
    {
        card_type_check(card_number, card_length);
    }
    else
    {
        invalid();
    }

    return 0;
}

//* Function for calculating card number check sum
int luhns_algorithm(long card_number, int total_sum)
{
    // Variable for current position in card number
    long digit_pos = card_number;
    bool multiply = false;

    // Process each digit
    while (digit_pos > 0)
    {
        int digit = digit_pos % 10;

        // Multiply every odd places digits by 2
        if (multiply)
        {
            digit *= 2;

            if (digit > 9)
            {
                digit = (digit % 10) + (digit / 10);
            }
        }

        total_sum += digit;

        // Switch between false and true
        multiply = !multiply;

        // Move to next digit from right to left
        digit_pos /= 10;
    }

    return total_sum;
}

//* Function for checking type of card
int card_type_check(long card_number, int card_length)
{
    // Get first two digits from card number
    while (card_number > 99)
    {
        card_number /= 10;
    }

    // AMERICAN EXPRESS Requirements
    if (card_length == 15 && (card_number == 34 || card_number == 37))
    {
        printf("AMEX\n");
    }

    // MASTERCARD Requirements
    else if (card_length == 16 && card_number >= 51 && card_number <= 55)
    {
        printf("MASTERCARD\n");
    }

    // VISA Requirements
    else if ((card_length == 13 || card_length == 16) && ((card_number / 10) % 10 == 4))
    {
        printf("VISA\n");
    }

    else
    {
        invalid();
    }


    return 0;
}

//* Function for printing invalid and file termination
int invalid(void)
{
    printf("INVALID\n");
    return 0;
}
