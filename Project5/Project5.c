/*
 * This program implements a selection sort algorithm in C and inline assembly language for an array of small int values.
 *
 * Spencer Peace
 * CSC 362-001
 * Dr. Richard Fox
 * 11/14/19
 * Project 5
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int nums[] = { 100, 99, 97, 95, 90, 87, 86, 83, 81, 77, 74, 69, 63, 50, 44, 43, 39, 31, 29, 12 }; // Hardcode array of ints for run #1
	// int nums[] = { 8, -1, 7, -8, 6, 3, -4, 4, 1, -2, 9, -5, 0, 2 }; // Hardcode array of ints for run #2

	int min, minposition, temp, /*n = 14*/ n = 20; // Declare int variables for use within the algorithm
	
	/* Write program in C first, test functionality, then convert to assembly
	for (int i = 0; i < n - 1; i++) {
		min = nums[i];
		minposition = i;
		for (int j = i + 1; j < n; j++) {
			if (nums[j] < nums[minposition]) {
				min = nums[j];
				minposition = j;
			}
		}
		temp = nums[i];
		nums[i] = nums[minposition];
		nums[minposition] = temp;
		printf("%d ", nums[i]); // Print out in sorted order
	}
	*/

	// Begin main assembly code
	__asm {

	}

	// Print values in sorted order
	for (int i = 0; i < n - 1; i++) {
		printf("%d ", nums[i]);
	}
}