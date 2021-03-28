#include <stdio.h>
#include <cs50.h>

int check_length(long cc_num);
int get_checksum(long cc_num);

// 1. Check if valid number

// 2. If valid, determine what kind of credit card
// American Express 15 digits, start with 34 or 37
// Mastercard 16 digits, start with 51 - 55
// Visa 13 or 16 digits, start with 4

int main(void)
{
    long n = get_long("Number: ");

    int cc_length = check_length(n);
    printf("Credit card length: %i\n", cc_length);
    int checksum = get_checksum(n);
    printf("Checksum: %i\n", checksum);
}

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

int get_checksum(long cc_num)
{
    int sum = 0;
    int count = 0;
    int special_digits = 0;

    while (cc_num > 0)
    {
        if (count % 2 == 0)
        {
            sum += (cc_num % 10);
        }
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
    return sum % 10;
}
