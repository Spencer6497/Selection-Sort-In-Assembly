/*
 * This program implements a selection sort algorithm in C and inline assembly language for an array of small int values.
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int nums[] = { 100, 99, 97, 95, 90, 87, 86, 83, 81, 77, 74, 69, 63, 50, 44, 43, 39, 31, 29, 12 }; // Hardcode array of ints for run #1
	// int nums[] = { 8, -1, 7, -8, 6, 3, -4, 4, 1, -2, 9, -5, 0, 2 }; // Hardcode array of ints for run #2

	int min, minposition, i, j, temp, /*n = 14*/ n = 20; // Declare int variables for use within the algorithm
	
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
		ecx = data register
		eax = running calculations
		edx = data register

	*/

	// Begin main assembly code
	__asm {
					mov i, 0 // set our loop counter (i) to zero for the outer loop
		outer:		mov eax, n
					dec eax // eax <- n - 1
					cmp i, eax
					jge print // if i >= n - 1, exit the outer loop and end the algorithm, printing the results
					mov eax, 4 // Store byte offset in the eax to calculate offset into array
					mul i // eax = 4 * i
					mov ebx, eax // offset (ebx) = 4 * i
					mov edx, nums[ebx] // edx (temporary) = nums[i]
					mov min, edx // min <- nums[i]
					mov edx, i // edx <- i (temporary)
					mov minposition, edx // minposition = i
					mov eax, i
					inc eax // eax = i + 1
					mov j, eax // j = i + 1
		inner:		mov edx, j // edx <- j (temporarily)
					cmp edx, n
					jge swap // if j >= n, skip the inner loop and go down to the swapping portion
					mov eax, 4 // store byte offset in eax to calculate offset into array
					mul j // eax = 4 * j
					mov ebx, eax // ebx = 4 * j
					mov ecx, nums[ebx] // store nums[j] in ecx temporarily for comparison
					mov eax, 4 // store byte offset in eax
					mul minposition // eax = 4 * minposition
					mov ebx, eax // ebx = 4 * minposition
					mov eax, nums[ebx] // store nums[minposition] in eax temporarily for comparison
					cmp ecx, eax
					jge xelse // if nums[j] >= nums[minposition], skip the if block and go to the else block
					mov min, ecx // min <- nums[j]
					mov edx, j // move j to edx temporarily to store in minposition
					mov minposition, edx // minposition = j
		xelse:		inc j // j + 1
					jmp inner // jump back to the top of the inner loop unconditionally
		swap:		mov eax, 4
					mul i
					mov ebx, eax // ebx = 4 * i
					mov edx, nums[ebx] // edx = nums[i] temporarily
					mov temp, edx // temp = nums[i] for the swap
					mov eax, 4
					mul minposition
					mov ebx, eax // ebx = 4 * minposition
					mov ecx, nums[ebx] // ecx = nums[minposition]
					mov eax, 4
					mul i
					mov ebx, eax // ebx = 4 * i
					mov nums[ebx], ecx // nums[i] = nums[minposition]
					mov eax, 4
					mul minposition
					mov ebx, eax // ebx = 4 * minposition
					mov edx, temp // edx = temp = nums[i]
					mov nums[ebx], edx // nums[minposition] = temp
					inc i // increment i for the next iteration
					jmp outer // Unconditionally jump to the top of the outer loop
		print:		nop // Algorithm complete, print results
	}

	// Print values in sorted order
	for (int i = 0; i < n; i++) {
		printf("%d ", nums[i]);
	}
}

/*
	Output 1: 
	12 29 31 39 43 44 50 63 69 74 77 81 83 86 87 90 95 97 99 100 
	Press any key to continue . . .

	C:\WINDOWS\system32\cmd.exe (process 6292) exited with code 0.
	Press any key to close this window . . .

	Output 2:
	-8 -5 -4 -2 -1 0 1 2 3 4 6 7 8 9 
	Press any key to continue . . .

	C:\WINDOWS\system32\cmd.exe (process 2576) exited with code 0.
	Press any key to close this window . . .
*/
