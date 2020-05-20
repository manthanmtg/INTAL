/*
 * 	Author:   Manthan B Y
 *  SRN: PES1201701498
 * 	Language: C
 *  Date: 20-05-2020
 * 	
 * 	Problem Statement: INTAL Implementation
 *  #### Implementation File ####
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
// ------------------------------------------------------------------

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