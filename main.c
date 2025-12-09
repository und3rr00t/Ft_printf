/* ************************************************************************** */
/* */
/* MY ULTIMATE FT_PRINTF DESTRUCTION SUITE                                  */
/* */
/* I wrote this to absolutely break my code. If it survives this,           */
/* it survives anything.                                                    */
/* */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

// Visualizing the output to easily identify failures.
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"

int g_tests_failed = 0;
int g_tests_total = 0;

/* MY TEST MACRO
   This runs the original printf and my ft_printf side-by-side.
   I'm comparing the output visually and the return value strictly.
   If the return values don't match, I count it as a fail.
*/
#define TEST(category, fmt, ...) \
    do { \
        g_tests_total++; \
        int ret_orig, ret_mine; \
        /* FIX: I used "%s" here so printf doesn't try to interpret 'fmt' inside the debug msg */ \
        printf(BLUE "\n[%s] Testing: \"%s\"" RESET "\n", category, fmt); \
        \
        /* 1. Run the OG printf to see what it should look like */ \
        printf("   [ORIG]: "); \
        fflush(stdout); \
        ret_orig = printf(fmt, ##__VA_ARGS__); \
        printf("\n"); \
        \
        /* 2. Run my version */ \
        printf("   [MINE]: "); \
        fflush(stdout); \
        ret_mine = ft_printf(fmt, ##__VA_ARGS__); \
        printf("\n"); \
        \
        /* 3. The moment of truth: Compare return values */ \
        if (ret_orig == ret_mine) { \
            printf(GREEN "   [PASS] Return Value Match (%d)" RESET "\n", ret_orig); \
        } else { \
            printf(RED "   [FAIL] Return Value Mismatch! ORIG: %d vs MINE: %d" RESET "\n", ret_orig, ret_mine); \
            g_tests_failed++; \
        } \
    } while(0)

int main(void)
{
    printf(YELLOW "==================================================\n");
    printf("         TIME TO DESTROY MY FT_PRINTF\n");
    printf("==================================================" RESET "\n");

    int a = 42;
    int *ptr = &a;

    // --- 1. Warming up with basic Chars & Strings ---
    TEST("CHAR", "Char: %c", 'A');
    TEST("STRING", "String: %s", "Hello World");
    TEST("EMPTY STR", "Empty: %s", "");
    
    // --- 2. The NULL Tests ---
    // I need to make sure I handle NULLs exactly like the system does.
    // If I crash here, I failed the project.
    TEST("NULL STRING", "This is NULL: %s", (char *)NULL); 
    TEST("NULL POINTER", "This is NULL: %p", (void *)NULL);

    // --- 3. Integers (The Limit Tests) ---
    // Checking if my logic holds up against edge cases.
    TEST("INT NORMAL", "Value: %d", 12345);
    TEST("INT NEG", "Value: %d", -9876);
    TEST("INT ZERO", "Value: %d", 0);
    TEST("INT MAX", "Max: %d", INT_MAX);
    // This INT_MIN test usually breaks if I messed up the casting
    TEST("INT MIN", "Min: %d", INT_MIN); 

    // --- 4. Unsigned & Hex ---
    // Testing my base conversion logic here.
    TEST("UNSIGNED", "U: %u", 4294967295U);
    TEST("HEX LOWER", "Hex: %x", 255);
    TEST("HEX UPPER", "Hex: %X", 255);
    TEST("HEX ZERO", "Hex: %x", 0);
    
    // --- 5. Pointers ---
    TEST("PTR ADDR", "Address: %p", ptr);
    // Passing -1 is a dirty trick to check if I'm using unsigned long properly
    TEST("PTR WEIRD", "Address: %p", (void *)-1); 

    // --- 6. The Percent Sign ---
    // Edge cases for %% are annoying, better test them.
    TEST("PERCENT", "100%% sure");
    TEST("PERCENT SEQ", "%% %% %%");

    // --- 7. The Combo (The Boss Fight) ---
    // This is where I mix everything. If my va_list logic is bad, this will segfault.
    TEST("COMBO 1", "%c %s %p %d %i %u %x %X %%", 'Z', "Mix", ptr, INT_MAX, INT_MIN, UINT_MAX, INT_MAX, INT_MAX);
    TEST("COMBO 2", "Test %s %d", "string", 0);

    // --- 8. The Impossible Test (FD 1 Closed) ---
    // This simulates a write error. Real printf returns -1.
    // If I didn't check write() return values, I will fail this.
    g_tests_total++;
    printf(BLUE "\n[FD CLOSED] Testing: Write to closed stdout" RESET "\n");
    
    int saved_stdout = dup(1); // Backup stdout
    close(1); // DESTROY STDOUT
    
    int ret_orig = printf("This should fail");
    int ret_mine = ft_printf("This should fail");
    
    dup2(saved_stdout, 1); // Restore stdout to print results
    close(saved_stdout);

    if (ret_orig == ret_mine) {
        printf(GREEN "   [PASS] Return Value Match (%d)" RESET "\n", ret_orig);
    } else {
        printf(RED "   [FAIL] Return Value Mismatch! ORIG: %d vs MINE: %d" RESET "\n", ret_orig, ret_mine);
        g_tests_failed++;
    }

    // --- Final Verdict ---
    printf(YELLOW "\n==================================================\n" RESET);
    if (g_tests_failed == 0)
        printf(GREEN "SUMMARY: ALL %d TESTS PASSED! MY CODE IS SOLID.\n" RESET, g_tests_total);
    else
        printf(RED "SUMMARY: %d OF %d TESTS FAILED. TIME TO DEBUG.\n" RESET, g_tests_failed, g_tests_total);

    return (g_tests_failed);
}