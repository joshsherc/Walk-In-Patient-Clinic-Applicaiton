/*
 * List.cpp
 *
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - (What other characteristic does our List have?)
 *
 * Last modified: May 27 2017
 * Author: Hakeem Wewala, Josh Shercliffe
 */

#include <iostream>
#include <string>
#include "Patient.h"
#include "List.h"


// Default Constructor
List::List()
{
    for(int i = 0; i < 10; ++i)
    {
        elementCount[i] = 0;
        capacity[i] = MAX_ELEMENTS;
        elementsZeroToNine[i] = new Patient[MAX_ELEMENTS];
    }
}

//Destructor
List::~List()
{
    cout << "Destructor called\n";
    for(int i = 0; i < 10; ++i)
    {
        delete[] elementsZeroToNine[i];
        elementsZeroToNine[i] = NULL;
    }

    delete[] elementsZeroToNine;
    elementsZeroToNine == NULL;

    return;
}

//Description: Returns the integer value of the first digit of the patients care card number
int List::getFirstDigit(const Patient& thePatient) const
{
   string careCardTemp = thePatient.getCareCard();
   char firstDigitChar = careCardTemp[0]; //get the first digit of the new Patient's care card number
   int firstDigitInt = firstDigitChar - '0'; //convert the character to an integer

   return firstDigitInt;
}
//Description: Used for expanding a section of the list when it is full
void List::expand(const int firstDigit)
{
        capacity[firstDigit] *= 2; //multiply the capacity of the array by 2
        Patient* newArray = new Patient[(capacity[firstDigit])];//create new temporary list double the size of the old one
        for (int i=0; i<elementCount[firstDigit]; i++)
       {
            newArray[i] = elementsZeroToNine[firstDigit][i]; //copy elements of full list into newArray variable
       }
        delete[] elementsZeroToNine[firstDigit]; //delete the full array

       elementsZeroToNine[firstDigit] = new Patient[(capacity[firstDigit])]; //re-create it as a bigger array

        for (int i=0; i<elementCount[firstDigit]; i++)
        {
            elementsZeroToNine[firstDigit][i] = newArray[i]; //copy elements from old array into new array
        }
        delete[] newArray; //delete the temporary list
}

// Description: Returns the current number of elements in the List.
int  List::getElementCount() const
{
    int totalElementCount = 0;
    for (int i = 0; i<10; i++)
    {
        totalElementCount += elementCount[i];
    }
    return totalElementCount;
}


	// Description: Insert an element.
	// Precondition: newElement must not already be in data collection.
	// Postcondition: newElement inserted and elementCount has been incremented.
bool List::insert(const Patient& newElement)
{
   Patient temp;

   int firstDigitInt = getFirstDigit(newElement);

   bool ableToInsert = (elementCount[firstDigitInt] < capacity[firstDigitInt]); //check if the array corresponding to care card numbers that start with the new patient's first digit is full
   bool listFull  = !ableToInsert; //the array is full if we are not able to insert

    if (listFull)
   {
        expand(firstDigitInt);//expand the list
        ableToInsert = true;
   }
   if (ableToInsert)
   {
       for(int ii=0;ii<elementCount[firstDigitInt];ii++)
       {
           if (elementsZeroToNine[firstDigitInt][ii] == newElement)
           {
               cout << "element not added to list, care card number already exists" << endl;
               return false; //do not insert newElement if it is already in the list
           }

       }
      if(elementCount[firstDigitInt] == 0)
      {
          elementsZeroToNine[firstDigitInt][(elementCount[firstDigitInt])] = newElement;
          elementCount[firstDigitInt]++;
          return true;
      }
     else if(elementCount[firstDigitInt] == 1)
      {
          if(!(elementsZeroToNine[firstDigitInt][0] > newElement)) //compare care card numbers
          {
                elementsZeroToNine[firstDigitInt][(elementCount[firstDigitInt])] = newElement;
                elementCount[firstDigitInt]++;
                return true;
          }
          else
          {
              elementsZeroToNine[firstDigitInt][1] = elementsZeroToNine[firstDigitInt][0];
              elementsZeroToNine[firstDigitInt][0] = newElement;
              elementCount[firstDigitInt]++;
              return true;
          }
      }
      //if the list has more than 2 elements, insert it at the end of the list and then sort
      elementsZeroToNine[firstDigitInt][(elementCount[firstDigitInt])] = newElement;
      elementCount[firstDigitInt]++;

      for(int i=0; i<elementCount[firstDigitInt]-1;i++)
        {
            for(int j=0;j<elementCount[firstDigitInt]-1-i;j++)
            {
                if(elementsZeroToNine[firstDigitInt][j] > elementsZeroToNine[firstDigitInt][j+1])
                {
                    temp=elementsZeroToNine[firstDigitInt][j];
                    elementsZeroToNine[firstDigitInt][j]=elementsZeroToNine[firstDigitInt][j+1];
                    elementsZeroToNine[firstDigitInt][j+1]=temp;
                }
            }
        }

        return true;
   }

}  // end insert


	// Description: Remove an element.
	// Postcondition: toBeRemoved is removed and elementCount has been decremented.
bool List::remove( const Patient& toBeRemoved ) // not sure about this one
{
    int arrayIndex;

   int firstDigitInt = getFirstDigit(toBeRemoved);

    for(int jj=0;jj<elementCount[firstDigitInt];jj++) //go through every element in the list
    {
        if(elementsZeroToNine[firstDigitInt][jj] == toBeRemoved) //until you find the one that matches the one to be removed
        {
            arrayIndex = jj; //index of element to be removed

            if(arrayIndex == elementCount[firstDigitInt]-1)//if it is the last element in the list
            {
                elementCount[firstDigitInt]--;
                return true;
            }
            for (int fromIndex = arrayIndex + 1, toIndex = arrayIndex ; fromIndex < elementCount[firstDigitInt]; fromIndex++, toIndex++)
            {
                    elementsZeroToNine[firstDigitInt][toIndex] = elementsZeroToNine[firstDigitInt][fromIndex];
            }
            elementCount[firstDigitInt]--;  // Decrease count of elements
            return true;
        }
    }
    cout << "Patient to be removed is not in the list" << endl;
    return false;


} //end remove

// Description: Search for target element.
	//              Returns a pointer to the element if found,
	//              otherwise, returns NULL.
Patient* List::search(const Patient& target)
{
    int i;
    Patient *element;

    int firstDigit = getFirstDigit(target);

    for (i=0; i<elementCount[firstDigit]; i++)
    {
        if (elementsZeroToNine[firstDigit][i] == target)
        {
            element = &elementsZeroToNine[firstDigit][i];
            return element;
        }
    }
    cout << "target is not in list" << endl;
    return NULL;
}
// Description: Removes all elements from the List.
// Postconditions: List contains no elements and the element count is 0.
void List::removeAll()
{
    for (int i=0; i<10; i++)
   elementCount[i] = 0;
} // end removeAll


// Description: Prints all elements in the List.
void List::printList()
{
    int totalElementCount = getElementCount();

    for (int j=0; j<10; j++) //cycles through the big array
    {

        for (int i = 0; i<elementCount[j]; i++) //cycles through through each array within the big array
        {
            cout << elementsZeroToNine[j][i].getCareCard() << ", Patient: " << elementsZeroToNine[j][i].getName()
            << ", " << elementsZeroToNine[j][i].getAddress() << ", " << elementsZeroToNine[j][i].getPhone() << ", " << elementsZeroToNine[j][i].getEmail() << endl;
        }


    }

} // end of printList

//  End of implementation file
