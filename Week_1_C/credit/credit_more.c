#include <stdio.h>
#include <cs50.h>

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

    // Loop counts card number length
    while (card_number > 0)
    {
        counting_temp /= 10;
        card_length++;
    }

    //* Check if card number is valid using Luhn's Algorithm
    // Temp variable
    long luhns_temp = card_number;
    int sum = 0;
    bool multiply = false;

    // Process each digit
    while (luhns_temp > 0)
    {
        int digit = luhns_temp % 10;

        if (multiply)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = (digit % 10) + (digit / 10);
            }
        }

        sum += digit;
        multiply = !multiply;   // Switch between false and true
        luhns_temp /= 10;
    }

    // Check if credit card is valid
    bool valid = false;
    if (sum % 10 == 0)
    {
        valid = true;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

    // *Check type of card based on number
    if (valid)
    {
        // AMERICAN EXPRESS card requirements
        if (card_length == 15)
        {
            long amex_number = card_number;

            // Get last two digits
            for (int i = 0; i < card_length - 2; i++)
            {
                amex_number /= 10;
            }

            if ((amex_number == 34) || (amex_number == 37))
            {
                printf("AMEX\n");
                return 0;
            }

            printf("INVALID\n");
        }

        // VISA/MASTERCARD card requirements
        else if ((card_length == 13) || (card_length == 16))
        {
            long visa_master_number = card_number;

            // Get last two digits
            for (int i = 0; i < card_length - 2; i++)
            {
                visa_master_number /= 10;
            }

            // If met mastercard requirements
            if ((visa_master_number >= 51 && visa_master_number <= 55) && card_length == 16)
            {
                printf("MASTERCARD\n");
                return 0;
            }

            // If met visa requirements
            else if ((visa_master_number / 10) % 10 == 4)
            {
                printf("VISA\n");
                return 0;
            }

            printf("INVALID\n");
        }
    }

    return 0;
}
