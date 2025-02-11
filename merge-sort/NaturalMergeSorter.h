#ifndef NATURALMERGESORTER_H
#define NATURALMERGESORTER_H

class NaturalMergeSorter {
public:
      virtual int GetSortedRunLength(int* array, int arrayLength, int startIndex) {
      // Return 0 if startIndex is out of bounds
      if (startIndex < 0 || startIndex >= arrayLength) {
         return 0;
      }

      int runLength = 1; // At minimum, the run includes the start element

      // Stop at the first non-increasing element
      while ((startIndex + runLength) < arrayLength && 
            array[startIndex + runLength - 1] <= array[startIndex + runLength]) { 
         runLength++;
      }

      return runLength;
   }


   virtual void NaturalMergeSort(int* array, int arrayLength) {
      // Your code here
      if(arrayLength <= 1){
         return;
      }

      bool sorted = false;

       while (!sorted) {
         int i = 0;
         sorted = true;
         
         while (i < arrayLength) {
            int firstRunLength = GetSortedRunLength(array, arrayLength, i);
            if (firstRunLength == arrayLength) {
               return;
            }
            
            int firstRunEnd = i + firstRunLength;
            if (firstRunEnd >= arrayLength) {
               i = 0;
               break;
            }
            
            int secondRunLength = GetSortedRunLength(array, arrayLength, firstRunEnd);
            int secondRunEnd = firstRunEnd + secondRunLength;
            
            Merge(array, i, firstRunEnd - 1, secondRunEnd - 1);
            
            if (secondRunEnd < arrayLength) {
               i = secondRunEnd;
            } else {
               i = 0;
            }
            
            sorted = false;
         }
      }
   }
   
   virtual void Merge(int* numbers, int leftFirst, int leftLast,
      int rightLast) {
      int mergedSize = rightLast - leftFirst + 1;
      int* mergedNumbers = new int[mergedSize];
      int mergePos = 0;
      int leftPos = leftFirst;
      int rightPos = leftLast + 1;
         
      // Add smallest element from left or right partition to merged numbers
      while (leftPos <= leftLast && rightPos <= rightLast) {
         if (numbers[leftPos] <= numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            leftPos++;
         }
         else {
            mergedNumbers[mergePos] = numbers[rightPos];
            rightPos++;
         }
         mergePos++;
      }
         
      // If left partition isn't empty, add remaining elements to mergedNumbers
      while (leftPos <= leftLast) {
         mergedNumbers[mergePos] = numbers[leftPos];
         leftPos++;
         mergePos++;
      }
      
      // If right partition isn't empty, add remaining elements to mergedNumbers
      while (rightPos <= rightLast) {
         mergedNumbers[mergePos] = numbers[rightPos];
         rightPos++;
         mergePos++;
      }
      
      // Copy merged numbers back to numbers
      for (mergePos = 0; mergePos < mergedSize; mergePos++) {
         numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
      }
      
      // Free temporary array
      delete[] mergedNumbers;
   }
};

#endif