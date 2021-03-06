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

// -------------------- <Helper Functions> -------------------------------

static char *strrev(char *str)
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

static short int to_num(const char ch)
{
    return ch - '0';
}

static char to_char(const int num)
{
    return num + '0';
}

static void rstrip_zero(char *str)
{
    // zeros will be in right
    short int i = strlen(str) - 1;
    while (str[i] == '0')
        --i;
    str[i + 1] = '\0';
}

static void lstrip_zero(char *num)
{
    short int zeros = 0;
    while (num[zeros] == '0')
        ++zeros;
    char *temp = (char *)malloc(1001 * sizeof(char));
    strcpy(temp, num + zeros);
    strcpy(num, temp);
    free(temp);
    if (strlen(num) == 0)
        strcpy(num, "0");
}

static short int isZero(const char *num)
{
    if (0 == strcmp(num, "0"))
        return 1;
    return 0;
}

static void append_zeros(char *str, short int n)
{
    short int i = strlen(str);
    while (n != 0)
    {
        str[i++] = '0';
        --n;
    }
    str[i] = '\0';
}

static char *int_to_string(int num)
{
    char *str = (char *)malloc(1001 * sizeof(char));
    if (num == 0)
    {
        strcpy(str, "0");
        return str;
    }
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

/*
    Returns str[a:b]   (Python sematic)
*/
static char *getSubString(const char *str, short int a, short int b)
{
    char *substr = (char *)malloc(1001 * sizeof(char));
    short int k = 0;
    for (short int i = a; i < b; ++i)
        substr[k++] = str[i];
    substr[k] = '\0';
    return substr;
}

// ----------------------- </Helper Functions> ------------------------------

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

// ------------------------ <Merge Sort> ---------------------------------

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
static void merge(char **arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    short int cmp;
    while (i < n1 && j < n2)
    {
        cmp = intal_compare(L[i], R[j]);
        if (cmp == -1 || cmp == 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
static void mergeSort(char **arr, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// ------------------ </Merge Sort> ----------------------------------

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

// Returns the difference (obviously, nonnegative) of two intals.
char *intal_diff(const char *intal1, const char *intal2)
{
    short int cmp = intal_compare(intal1, intal2);
    char *diff = (char *)malloc(1001 * sizeof(char));
    if (cmp == 0)
    {
        strcpy(diff, "0");
        return diff;
    }
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
    short int ti;
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
            ti = i - 1;
            while (intal1t[ti] == '0')
            {
                intal1t[ti] = '9';
                --ti;
            }
            intal1t[ti] -= 1;
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

// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
// intal2 > 1
// Implement a O(log intal1) time taking algorithm.
// O(intal1 / intal2) time taking algorithm may exceed time limit.
// O(intal1 / intal2) algorithm may repeatedly subtract intal2 from intal1.
// That will take intal1/intal2 iterations.
// You need to design a O(log intal1) time taking algorithm.
// Generate your own testcases at https://www.omnicalculator.com/math/modulo
char *intal_mod(const char *intal1, const char *intal2)
{
    char *current = (char *)malloc(1001 * sizeof(char));
    short int cmp = intal_compare(intal1, intal2);
    if (cmp == 0)
    {
        strcpy(current, "0");
        return current;
    }

    if (cmp == -1)
    {
        strcpy(current, intal1);
        return current;
    }

    short int l1 = strlen(intal1);
    short int l2 = strlen(intal2);
    short int temp;

    short int i;
    short int curr_index = 0;
    char *up;
    current[0] = '\0';
    char *curr_temp;
    char *down = (char *)malloc(1001 * sizeof(char));
    char *down_temp;

    while (curr_index < l1)
    {
        up = getSubString(intal1, curr_index, curr_index + l2);
        current = strcat(current, up);
        lstrip_zero(current);
        curr_index += l2;
        cmp = intal_compare(current, intal2);
        if (cmp == -1)
        {
            temp = strlen(current);
            while (cmp == -1 && curr_index < l1)
            {
                current[temp++] = intal1[curr_index++];
                lstrip_zero(current);
                cmp = intal_compare(current, intal2);
            }
            current[temp] = '\0';
        }

        strcpy(down, intal2);

        i = 1;
        cmp = intal_compare(down, current);
        while (cmp == -1 || cmp == 0) // down < current
        {
            down_temp = down;
            down = intal_multiply(intal2, int_to_string(i));
            ++i;
            free(down_temp);
            cmp = intal_compare(down, current);
        }

        down_temp = down;
        down = intal_diff(down, intal2);
        free(down_temp);

        if (strcmp(down, "0") != 0)
        {
            curr_temp = current;
            current = intal_diff(current, down);
            free(curr_temp);
        }
    }

    if (strlen(current) == 0)
        strcpy(current, "0");

    return current;
}

static char *pow_helper(const char *num, unsigned int exp)
{
    if (exp == 1)
    {
        char *left = (char *)malloc(1001 * sizeof(char));
        strcpy(left, num);
        return left;
    }
    char *left;
    char *right = pow_helper(num, exp / 2);
    short int isEven = (exp % 2 == 0);
    if (isEven)
    {
        left = intal_multiply(right, right);
        free(right);
    }
    else
    {
        char *temp = intal_multiply(right, right);
        left = intal_multiply(temp, num);
        free(right);
        free(temp);
    }
    return left;
}
// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
// Implement a O(log n) intal multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit.
char *intal_pow(const char *intal1, unsigned int n)
{
    return pow_helper(intal1, n);
}

static void gcd_helper(const char *intal1, const char *intal2, char *res)
{
    if (strcmp(intal1, "0") == 0)
    {
        strcpy(res, intal2);
        return;
    }
    char *temp = intal_mod(intal2, intal1);
    gcd_helper(temp, intal1, res);
    free(temp);
    return;
}
// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if both intal1 and intal2 are "0" even though it is undefined, mathematically.
// Use Euclid's theorem to not exceed the time limit.
char *intal_gcd(const char *intal1, const char *intal2)
{
    // char *intal1t = (char *)malloc(1001 * sizeof(char));
    // char *intal2t = (char *)malloc(1001 * sizeof(char));
    // strcpy(intal1t, intal1);
    // strcpy(intal2t, intal2);
    char *res = (char *)malloc(1001 * sizeof(char));
    gcd_helper(intal1, intal2, res);
    return res;
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

// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n,k).
// Use Dynamic Programming. Use extra space of not more than O(k) number of intals. Do not allocate the whole O(nk) memo table.
// Don't let C(1000,900) take more time than C(1000,500). Time limit may exceed otherwise.
char *intal_bincoeff(unsigned int n, unsigned int k)
{
    char **memo = (char **)malloc((k + 1) * sizeof(char *));
    for (int i = 0; i <= k; ++i)
    {
        memo[i] = (char *)malloc(1001 * sizeof(char));
        memo[i][0] = '0';
        memo[i][1] = '\0';
    }
    memo[0][0] = '1';
    char *current;
    char *previous;
    char *temp;
    for (short int i = 1; i <= n; ++i)
    {
        current = (char *)malloc(1001 * sizeof(char));
        strcpy(current, memo[0]);

        for (short int j = 1; j <= i && j <= k; ++j)
        {

            previous = (char *)malloc(1001 * sizeof(char));
            strcpy(previous, current);
            free(current);
            current = (char *)malloc(1001 * sizeof(char));
            strcpy(current, memo[j]);

            temp = intal_add(previous, current);

            free(memo[j]);

            memo[j] = (char *)malloc(1001 * sizeof(char));
            strcpy(memo[j], temp);
            free(temp);
            if (i % 2 == 1 && j + 1 == (i + 1) / 2)
                break;
            if (i % 2 == 0 && j + 1 == (i / 2))
            {
                temp = intal_multiply(current, "2");
                free(memo[j + 1]);
                memo[j + 1] = (char *)malloc(1001 * sizeof(char));
                strcpy(memo[j + 1], temp);
                free(temp);
                break;
            }
            free(previous);
        }
        free(current);
    }

    int mid = k + 1;

    if (n % 2 == 0 && k > (n / 2) + 1)
    {
        mid = n / 2 + 1;
        mid -= ((k - ((n / 2) + 1)) + 1);
    }

    if (n % 2 == 1 && k > (n + 1) / 2)
    {
        mid = (n + 1) / 2;
        mid -= (k - (n + 1) / 2) + 1;
    }

    char *coeff = (char *)malloc(1001 * sizeof(char));

    strcpy(coeff, memo[mid - 1]);
    for (int i = 0; i <= k; ++i)
    {
        free(memo[i]);
    }

    free(memo);
    return coeff;
}

// Returns the offset of the largest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n)
{
    char *max = arr[0];
    int max_off = 0;
    for (short int i = 1; i < n; ++i)
    {
        if (intal_compare(max, arr[i]) == -1)
        {
            max = arr[i];
            max_off = i;
        }
    }
    return max_off;
}

// Returns the offset of the smallest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n)
{
    char *min = arr[0];
    int min_off = 0;
    for (short int i = 1; i < n; ++i)
    {
        if (intal_compare(min, arr[i]) == 1)
        {
            min = arr[i];
            min_off = i;
        }
    }
    return min_off;
}

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char *key)
{
    for (short int i = 0; i < n; ++i)
    {
        if (intal_compare(arr[i], key) == 0)
            return i;
    }
    return -1;
}

// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
int intal_binsearch(char **arr, int n, const char *key)
{
    short int left = 0;
    short int right = n - 1;
    short int mid;
    short int cmp = 0;
    while (left <= right)
    {
        mid = (left + right) / 2;
        cmp = intal_compare(key, arr[mid]);
        if (cmp == 0)
            return mid;
        else if (cmp == 1)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
void intal_sort(char **arr, int n)
{
    mergeSort(arr, 0, n - 1);
}

// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space even though the DP table may be of O(n) size.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char *coin_row_problem(char **arr, int n)
{
    char *previous = (char *)malloc(1001 * sizeof(char));
    strcpy(previous, "0");
    char *current = (char *)malloc(1001 * sizeof(char));
    strcpy(current, arr[0]);

    for (int i = 1; i < n; ++i)
    {
        char *temp = intal_add(previous, arr[i]);
        short int cmp = intal_compare(temp, current);
        if (cmp == 1)
        {
            strcpy(previous, current);
            strcpy(current, temp);
        }
        else
        {
            strcpy(previous, current);
        }
        free(temp);
    }

    free(previous);

    return current;
}