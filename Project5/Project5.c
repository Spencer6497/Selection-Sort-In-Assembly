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
		// printf("%d ", nums[i]); // Print out in sorted order
	}
	*/

	/*
		Notes about this program for reference:

		Each int is a 32-bit unsigned int, 4 bytes each (4 is offset)
		ebx = base offset
		ecx = i
		eax = running calculations
		edx = temporary storage

	*/

	// Begin main assembly code
	__asm {
		mov ecx, 0 // set our loop counter (ecx = i) to zero for the outer loop
		outer:		mov eax, n
					dec eax // eax <- n - 1
					cmp ecx, eax
					jge print // if i >= n - 1, exit the outer loop and end the algorithm, printing the results
					mov eax, 4 // Store byte offset in the eax to calculate offset into array
					mul ecx // eax = 4 * i
					mov ebx, eax // offset (ebx) = 4 * i
					mov edx, nums[ebx] // edx (temporary) = nums[i]
					mov min, edx // min <- nums[i]
					mov minposition, ecx // minposition = i
					mov eax, ecx
					inc eax // eax = i + 1
					mov temp, eax // temp (j) = i + 1
		inner:		mov edx, temp // edx <- temp (temporarily)
					cmp edx, n
					jge swap // if j >= n, skip the inner loop and go down to the swapping portion
					mov eax, 4 // store byte offset in eax to calculate offset into array
					mul temp // eax = 4 * j
					mov ebx, eax // ebx = 4 * j
					mov ecx, nums[ebx] // store nums[j] in ecx temporarily for comparison
					mov eax, 4 // store byte offset in eax
					mul minposition // eax = 4 * minposition
					mov ebx, eax // ebx = 4 * minposition
					mov eax, nums[ebx] // store nums[minposition] in eax temporarily for comparison
					cmp ecx, eax
					jge xelse // if nums[j] >= nums[minposition], skip the if block and go to the else block
					mov min, ecx // min <- nums[j]
					mov edx, temp
					mov minposition, edx // minposition = j
		xelse:		mov ecx, temp // ecx <- j (i + 1) 
					dec ecx // reset value of ecx to i		
					inc temp // j + 1
					jmp inner // jump back to the top of the inner loop unconditionally
		swap:		mov eax, 4
					mul ecx
					mov ebx, eax // ebx = 4 * i
					mov eax, nums[ebx] // eax = nums [i] temporarily
					mov temp, eax // temp = nums[i] for the swap
					mov eax, 4
					mul minposition
					mov ebx, eax // ebx = 4 * minposition
					mov edx, nums[ebx] // edx = nums[minposition]
					mov eax, 4
					mul ecx
					mov ebx, eax // ebx = 4 * i
					mov nums[ebx], edx // nums[i] = nums[minposition]
					mov eax, 4
					mul minposition
					mov ebx, eax // ebx = 4 * minposition
					mov edx, temp // edx = temp = nums[i]
					mov nums[ebx], edx // nums[minposition] = temp
					inc ecx // increment the ecx (i) for the next iteration
					jmp outer // Unconditionally jump to the top of the outer loop
		print:		nop // Algorithm complete, print results
	}

	// Print values in sorted order
	for (int i = 0; i < n; i++) {
		printf("%d ", nums[i]);
	}
}

/*
	I wasn't able to complete this program. My current outputs are 

	100 99 97 95 90 87 86 83 81 77 74 69 63 50 44 43 39 31 0 29
	C:\Users\Spencer\source\repos\Project5\Debug\Project5.exe (process 15724) exited with code 20.
	Press any key to close this window . . .

	and 

	8 -1 7 0 6 3 -4 4 1 -2 9 -5 0 2
	C:\Users\Spencer\source\repos\Project5\Debug\Project5.exe (process 22452) exited with code 14.
	Press any key to close this window . . .

	respectively.

	I believe I have most of the logic worked out, other than the logic in the swap portion. This is 
	because I couldn't figure out how to set nums[i] equal nums[minposition] without erasing or overwriting
	one of the data registers. Ultimately I should have started on this much sooner.
*/