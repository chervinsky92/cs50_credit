#include <stdio.h>
#include <cs50.h>

int check_length(long cc_num);
int get_checksum(long cc_num);
int find_first_digit(long cc_num);
int find_second_digit(long cc_num);

int main(void)
{
    // Ask user for credit card number
    long n = get_long("Number: ");

    int cc_length = check_length(n);
    // printf("Credit card length: %i\n", cc_length);
    int checksum = get_checksum(n);
    // printf("Checksum: %i\n", checksum);
    int first_digit = find_first_digit(n);
    // printf("First digit: %i\n", first_digit);
    int second_digit = find_second_digit(n);
    // printf("Second digit: %i\n", second_digit);

    // If checksum is valid, determine type of credit card
    if (checksum == 0)
    {
        // American Express 15 digits, start with 34 or 37
        if ((cc_length == 15) & (first_digit == 3) && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
        }
        // Mastercard 16 digits, start with 51 - 55
        else if ((cc_length == 16) && (first_digit == 5) && (second_digit == 1 || second_digit == 2 || second_digit == 3
                 || second_digit == 4 || second_digit == 5))
        {
            printf("MASTERCARD\n");
        }
        // Visa 13 or 16 digits, start with 4
        else if ((cc_length == 13 || cc_length == 16) && (first_digit == 4))
        {
            printf("VISA\n");
        }
        // Not AMEX, MASTERCARD, or VISA
        else
        {
            printf("INVALID\n");
        }
    }
    // Fails the checksum
    else
    {
        printf("INVALID\n");
    }
}

// Returns amount of digits in credit card number
int check_length(long cc_num)
{
    int n_digits = 0;
    while (cc_num > 0)
    {
        cc_num = cc_num / 10;
        n_digits++;
    }
    return n_digits;
}

// Algorithm to check if credit card number is legit
// Final sum needs to be divisible by 10 in order to pass
int get_checksum(long cc_num)
{
    int sum = 0;
    int count = 0;
    int special_digits = 0;

    // Count digits backwards, starting from the last digit
    while (cc_num > 0)
    {
        // For even counts, add digit to sum
        if (count % 2 == 0)
        {
            sum += (cc_num % 10);
        }
        // For odd counts, multiply digit by 2 and then add each digit of resulting number to sum (ex: 6 * 2 = 12 -> sum + 1 + 2)
        else if (count % 2 == 1)
        {
            special_digits = (cc_num % 10) * 2;
            while (special_digits > 0)
            {
                sum += special_digits % 10;
                special_digits = (special_digits - (special_digits % 10)) / 10;
            }
        }
        cc_num = (cc_num - (cc_num % 10)) / 10;
        count++;
    }
    // A return value of 0 means the number has passed the checksum
    return sum % 10;
}

// Returns first digit of credit card number
int find_first_digit(long cc_num)
{
    while (cc_num >= 10)
    {
        cc_num = (cc_num - (cc_num % 10)) / 10;
    }
    return cc_num;
}

// Returns second digit of credit card number
int find_second_digit(long cc_num)
{
    while (cc_num >= 100)
    {
        cc_num = (cc_num - (cc_num % 10)) / 10;
    }
    return cc_num % 10;
}
