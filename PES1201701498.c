/*
 * 	Author: Manthan B Y
 *  SRN   : PES1201701498
 * 	Language: C
 *  Date: 20-05-2020
 * 	
 * 	Problem Statement: INTAL Implementation
 *  ############## Implementation File ##############
*/

#include <stdlib.h>
#include <string.h>

// -------------------- Helper Functions -------------------------------

char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

short int to_num(const char ch)
{
    return ch - '0';
}

char to_char(const int num)
{
    return num + '0';
}

void rstrip_zero(char *str)
{
    // zeros will be in right
    short int i = strlen(str) - 1;
    while (str[i] == '0')
        --i;
    str[i + 1] = '\0';
}

void lstrip_zero(char *num)
{
    short int zeros = 0;
    while (num[zeros] == '0')
        ++zeros;
    strcpy(num, num + zeros);
    if (strlen(num) == 0)
        strcpy(num, "0");
}

short int isZero(const char *num)
{
    if (0 == strcmp(num, "0"))
        return 1;
    return 0;
}

void append_zeros(char *str, short int n)
{
    short int i = strlen(str);
    while (n != 0)
    {
        str[i++] = '0';
        --n;
    }
    str[i] = '\0';
}

char *int_to_string(int num)
{
    char *str = (char *)malloc(1001 * sizeof(char));
    short int k = 0;
    while (num != 0)
    {
        str[k++] = to_char(num % 10);
        num /= 10;
    }
    str[k] = '\0';
    strrev(str);
    return str;
}

// ---------------------------------------------------------------------

// Returns the sum of two intals.
char *intal_add(const char *intal1, const char *intal2)
{
    short int carry = 0; // Variable to hold the carry
    short int i = strlen(intal1) - 1;
    short int j = strlen(intal2) - 1;
    short int k = 0;
    short int temp_num = 0;

    char *final_num = (char *)malloc(1001 * sizeof(char));

    while (i != -1 && j != -1)
    {
        temp_num = carry + to_num(intal1[i--]) + to_num(intal2[j--]);
        carry = temp_num / 10;
        temp_num = temp_num % 10;
        final_num[k++] = to_char(temp_num);
    }
    while (i != -1)
    {
        temp_num = carry + to_num(intal1[i--]);
        carry = temp_num / 10;
        temp_num = temp_num % 10;
        final_num[k++] = to_char(temp_num);
    }
    while (j != -1)
    {
        temp_num = carry + to_num(intal2[j--]);
        carry = temp_num / 10;
        temp_num = temp_num % 10;
        final_num[k++] = to_char(temp_num);
    }
    if (carry == 1)
        final_num[k++] = '1';
    final_num[k] = '\0';
    strrev(final_num); // big-endian
    return final_num;
}

// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char *intal1, const char *intal2)
{
    short int i = strlen(intal1) - 1;
    short int j = strlen(intal2) - 1;

    if (i > j)
        return 1; // length of intal1 is greater than length of intal2
    if (i < j)
        return -1; // length of intal2 is greater than length of intal1

    // same length : go from 0 index to high
    i = 0;
    while (intal1[i] != '\0')
    {
        if (intal1[i] > intal2[i])
            return 1;
        if (intal2[i] > intal1[i])
            return -1;
        ++i;
    }
    return 0;
}

// Returns the difference (obviously, nonnegative) of two intals.
char *intal_diff(const char *intal1, const char *intal2)
{
    short int cmp = intal_compare(intal1, intal2);
    char *diff = (char *)malloc(1001 * sizeof(char));
    if (cmp == 0)
        return "0";
    if (cmp == -1) // if intal2 is greater : swap intal1 and intal2 (pointers)
    {
        const char *temp = intal1;
        intal1 = intal2;
        intal2 = temp;
    }

    char *intal1t = (char *)malloc(1001 * sizeof(char));
    strcpy(intal1t, intal1);

    short int i = strlen(intal1t) - 1;
    short int j = strlen(intal2) - 1;
    short int k = 0;
    short int num1 = 0;
    short int num2 = 0;
    while (j != -1)
    {
        num1 = to_num(intal1t[i]);
        num2 = to_num(intal2[j]);
        if (num1 >= num2)
        {
            diff[k++] = to_char(num1 - num2);
        }
        else
        {
            intal1t[i - 1] -= 1;
            num1 += 10;
            diff[k++] = to_char(num1 - num2);
        }
        --i;
        --j;
    }
    while (i != -1)
    {
        diff[k++] = intal1t[i];
        --i;
    }
    diff[k] = '\0';

    // rstrip_zero(diff);  // zeros which are not required will be in the right of the string

    strrev(diff); // big-endian
    lstrip_zero(diff);
    free(intal1t); // freeing the temporary string
    return diff;
}

// Returns the product of two intals.
char *intal_multiply(const char *intal1, const char *intal2)
{
    char *intal1t = (char *)malloc(1001 * sizeof(char));
    strcpy(intal1t, intal1);
    char *intal2t = (char *)malloc(1001 * sizeof(char));
    strcpy(intal2t, intal2);

    lstrip_zero(intal1t);
    lstrip_zero(intal2t);

    if (isZero(intal1t) || isZero(intal2t))
        return "0";

    if (strlen(intal1t) < strlen(intal2t))
    {
        char *temp = intal1t;
        intal1t = intal2t;
        intal2t = temp;
    } // 1 X 2

    char *temp = (char *)malloc(1001 * sizeof(char));
    char *final = (char *)malloc(1001 * sizeof(char));
    strcpy(final, "0");

    short int i = strlen(intal2t) - 1; // intal2
    short int j;                       // intal1
    short int k;                       // temp

    short int num1;
    short int num2;
    short int res;
    short int carry;
    while (i != -1)
    {
        num1 = to_num(intal2t[i]);
        j = strlen(intal1t) - 1;
        carry = 0;
        k = 0;
        while (j != -1)
        {
            num2 = to_num(intal1t[j]);
            res = carry + (num1 * num2);
            temp[k++] = to_char(res % 10);
            carry = res / 10;
            --j;
        }
        temp[k++] = to_char(carry);
        temp[k] = '\0';
        strrev(temp);
        lstrip_zero(temp);
        append_zeros(temp, strlen(intal2t) - (i + 1));

        char *t = final; // this will be freed : just temporary
        final = intal_add(temp, final);
        free(t);
        --i;
    }
    free(temp);
    return final;
}

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char *intal_fibonacci(unsigned int n)
{
    if (n == 0)
        return "0";
    if (n == 1)
        return "1";
    char *first = (char *)malloc(1001 * sizeof(char));
    char *second = (char *)malloc(1001 * sizeof(char));
    strcpy(first, "0");
    strcpy(second, "1");
    char *third;
    char *first_temp;
    for (short int i = 2; i <= n; ++i)
    {
        third = intal_add(first, second);
        first_temp = first;
        first = second;
        second = third;
        free(first_temp);
    }
    return third;
}

// Returns the factorial of n.
char *intal_factorial(unsigned int n)
{
    if (n == 0)
        return "1";
    char *final = (char *)malloc(1001 * sizeof(char));
    strcpy(final, "1");
    char *final_temp;
    char *str_num;
    for (int i = 2; i <= n; ++i)
    {
        final_temp = final;
        str_num = int_to_string(i);
        final = intal_multiply(final, str_num);
        free(final_temp);
        free(str_num);
    }
    return final;
}