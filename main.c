// /* ************************************************************************** */
// /* */
// /* MY ULTIMATE FT_PRINTF DESTRUCTION SUITE                                  */
// /* */
// /* I wrote this to absolutely break my code. If it survives this,           */
// /* it survives anything.                                                    */
// /* */
// /* ************************************************************************** */

// #include <stdio.h>
// #include <limits.h>
// #include <unistd.h> // Needed for close, dup, dup2
// #include "ft_printf.h"

// // Formatting the output to make errors easier to spot
// #define RESET   "\033[0m"
// #define RED     "\033[1;31m"
// #define GREEN   "\033[1;32m"
// #define YELLOW  "\033[1;33m"
// #define BLUE    "\033[1;34m"

// int g_tests_failed = 0;
// int g_tests_total = 0;

// /* MY TEST MACRO
//    This runs the original printf and my ft_printf side-by-side.
//    I'm comparing the output visually and the return value strictly.
//    If the return values don't match, I count it as a fail.
// */
// #define TEST(category, fmt, ...) \
//     do { \
//         g_tests_total++; \
//         int ret_orig, ret_mine; \
//         /* FIX: I used "%s" here so printf doesn't try to interpret 'fmt' inside the debug msg */ \
//         printf(BLUE "\n[%s] Testing: \"%s\"" RESET "\n", category, fmt); \
//         \
//         /* 1. Run the OG printf to see what it should look like */ \
//         printf("   [ORIG]: "); \
//         fflush(stdout); \
//         ret_orig = printf(fmt, ##__VA_ARGS__); \
//         printf("\n"); \
//         \
//         /* 2. Run my version */ \
//         printf("   [MINE]: "); \
//         fflush(stdout); \
//         ret_mine = ft_printf(fmt, ##__VA_ARGS__); \
//         printf("\n"); \
//         \
//         /* 3. The moment of truth: Compare return values */ \
//         if (ret_orig == ret_mine) { \
//             printf(GREEN "   [PASS] Return Value Match (%d)" RESET "\n", ret_orig); \
//         } else { \
//             printf(RED "   [FAIL] Return Value Mismatch! ORIG: %d vs MINE: %d" RESET "\n", ret_orig, ret_mine); \
//             g_tests_failed++; \
//         } \
//     } while(0)

// int main(void)
// {
//     printf(YELLOW "==================================================\n");
//     printf("         TIME TO DESTROY MY FT_PRINTF\n");
//     printf("==================================================" RESET "\n");

//     int a = 42;
//     int *ptr = &a;

//     // --- 1. Warming up with basic Chars & Strings ---
//     TEST("CHAR", "Char: %c", 'A');
//     TEST("STRING", "String: %s", "Hello World");
//     TEST("EMPTY STR", "Empty: %s", "");
    
//     // --- 2. The NULL Tests ---
//     // I need to make sure I handle NULLs exactly like the system does.
//     // If I crash here, I failed the project.
//     TEST("NULL STRING", "This is NULL: %s", (char *)NULL); 
//     TEST("NULL POINTER", "This is NULL: %p", (void *)NULL);

//     // --- 3. Integers (The Limit Tests) ---
//     // Checking if my logic holds up against edge cases.
//     TEST("INT NORMAL", "Value: %d", 12345);
//     TEST("INT NEG", "Value: %d", -9876);
//     TEST("INT ZERO", "Value: %d", 0);
//     TEST("INT MAX", "Max: %d", INT_MAX);
//     // This INT_MIN test usually breaks if I messed up the casting
//     TEST("INT MIN", "Min: %d", INT_MIN); 

//     // --- 4. Unsigned & Hex ---
//     // Testing my base conversion logic here.
//     TEST("UNSIGNED", "U: %u", 4294967295U);
//     TEST("HEX LOWER", "Hex: %x", 255);
//     TEST("HEX UPPER", "Hex: %X", 255);
//     TEST("HEX ZERO", "Hex: %x", 0);
    
//     // --- 5. Pointers ---
//     TEST("PTR ADDR", "Address: %p", ptr);
//     // Passing -1 is a dirty trick to check if I'm using unsigned long properly
//     TEST("PTR WEIRD", "Address: %p", (void *)-1); 

//     // --- 6. The Percent Sign ---
//     // Edge cases for %% are annoying, better test them.
//     TEST("PERCENT", "100%% sure");
//     TEST("PERCENT SEQ", "%% %% %%");

//     // --- 7. The Combo (The Boss Fight) ---
//     // This is where I mix everything. If my va_list logic is bad, this will segfault.
//     TEST("COMBO 1", "%c %s %p %d %i %u %x %X %%", 'Z', "Mix", ptr, INT_MAX, INT_MIN, UINT_MAX, INT_MAX, INT_MAX);
//     TEST("COMBO 2", "Test %s %d", "string", 0);

//     // --- 8. Invalid Format Specifiers (Undefined Behavior) ---
//     // Standard printf usually prints "%k", but my code might just swallow it.
//     // This mismatch is expected unless I specifically handled unknown flags.
//     TEST("INVALID 1", "This is invalid: %k");
//     TEST("INVALID 2", "Multiple invalid: %w %r %y");

//     // --- 9. The Impossible Test (FD 1 Closed) ---
//     // This simulates a write error. Real printf returns -1.
//     // If I didn't check write() return values, I will fail this.
//     g_tests_total++;
//     printf(BLUE "\n[FD CLOSED] Testing: Write to closed stdout" RESET "\n");
    
//     int saved_stdout = dup(1); // Backup stdout
//     close(1); // DESTROY STDOUT
    
//     int ret_orig = printf("This should fail");
//     int ret_mine = ft_printf("This should fail");
    
//     dup2(saved_stdout, 1); // Restore stdout to print results
//     close(saved_stdout);

//     if (ret_orig == ret_mine) {
//         printf(GREEN "   [PASS] Return Value Match (%d)" RESET "\n", ret_orig);
//     } else {
//         printf(RED "   [FAIL] Return Value Mismatch! ORIG: %d vs MINE: %d" RESET "\n", ret_orig, ret_mine);
//         g_tests_failed++;
//     }

//     // --- Final Verdict ---
//     printf(YELLOW "\n==================================================\n" RESET);
//     if (g_tests_failed == 0)
//         printf(GREEN "SUMMARY: ALL %d TESTS PASSED! MY CODE IS SOLID.\n" RESET, g_tests_total);
//     else
//         printf(RED "SUMMARY: %d OF %d TESTS FAILED. TIME TO DEBUG.\n" RESET, g_tests_failed, g_tests_total);

//     return (g_tests_failed);
// }





#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TEST_COUNT 1000
#define STR_COUNT 5

int main(void)
{
	int ret_std, ret_ft;
	srand(time(NULL));

	const char *samples[STR_COUNT] = {"", "hello", "world", "ft_printf", NULL};

	printf("===== SUPER MULTI-STRING STRESS TEST =====\n\n");

	for (int i = 0; i < TEST_COUNT; i++) {
		int di = rand() % (INT_MAX / 2) - (INT_MAX / 4);
		unsigned int u = rand();
		char c = (char)(rand() % 128);
		const char *s1 = samples[rand() % STR_COUNT];
		const char *s2 = samples[rand() % STR_COUNT];
		const char *s3 = samples[rand() % STR_COUNT];
		void *p = (i % 10 == 0) ? NULL : (void *)(uintptr_t)(rand() % 0xFFFFF);
		unsigned int x = rand();
		unsigned int X = rand();

		ret_std = printf(
			"std %%d %%u %%c %%s %%s %%s %%p %%x %%X: |%d|%u|%c|%s|%s|%s|%p|%x|%X|\n",
			di, u, c,
			s1 ? s1 : "(null)",
			s2 ? s2 : "(null)",
			s3 ? s3 : "(null)",
			p, x, X
		);

		ret_ft = ft_printf(
			"ft  %%d %%u %%c %%s %%s %%s %%p %%x %%X: |%d|%u|%c|%s|%s|%s|%p|%x|%X|\n",
			di, u, c, s1, s2, s3, p, x, X
		);

		if (ret_std != ret_ft) {
			int fd = open("error.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
			if (fd == -1)
				return 1;

			int save = dup(1);
			dup2(fd, 1);
			printf("std  %%d %%u %%c %%s %%s %%s %%p %%x %%X: |%d|%u|%c|%s|%s|%s|%p|%x|%X|\n", di, u, c, s1, s2, s3, p, x, X);
			ft_printf("ft   %%d %%u %%c %%s %%s %%s %%p %%x %%X: |%d|%u|%c|%s|%s|%s|%p|%x|%X|\n", di, u, c, s1, s2, s3, p, x, X);
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! RET MISMATCH at iteration %d !!!\n", i);
			printf("ft:%d\nstd:%d\n", ret_ft, ret_std);

			fflush(stdout);
			dup2(save, 1);
			close(fd);
			close(save);
		}
	}

	printf("===== MULTI-STRING STRESS TEST COMPLETE =====\n");
	return 0;
}