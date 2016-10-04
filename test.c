#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "test.h"

static char * _intArrayToString(int array[], int length) {
	char * arrayAsStrings[length];
	char intAsStringBuffer[20];
	int totalLength = 0;
	int intStringLength;

	// convert int[] to char * [] where each entry in array is a string representation of the respective integer
	for (int i = 0; i < length; i++) {
		intStringLength = snprintf(intAsStringBuffer, 20, "%d", array[i]);
		if (intStringLength <= 0) {
			perror("Could not encode int to string");
			return 0;
		}

		totalLength += intStringLength;
		arrayAsStrings[i] = strdup(intAsStringBuffer);
	}

	char * result = (char *) malloc(sizeof(char) * totalLength + length*2 + 1 + 2);
	if (result == NULL) {
		perror("Could not allocate memory for string representation of an array");
		return 0;
	}
	
	strcpy(result,"[");

	for (int i = 0; i < length; i++) {
		if (i != 0) {
			strcat(result, ", ");
		}

		strcat(result, arrayAsStrings[i]); 
	}

	strcat(result, "]");

	return result;
}

static char * _intListToString(Element * list) {
	int listLength = 0;
	Element * currentEle = NULL;

	currentEle = list;
	while (currentEle != NULL) {
		listLength++;
		currentEle = currentEle->next;
	}
	
	int listAsStrings[listLength];

	currentEle = list;
	int currentIdx = 0;

	while (currentEle != NULL) {
		listAsStrings[currentIdx] = currentEle->value;
		currentEle = currentEle->next;
		currentIdx++;
	}

	return _intArrayToString(listAsStrings, listLength);
}

int _assertListElements(int expectedListElements[], int expectedSize, Element * list) {
	if (list == NULL && (expectedListElements == NULL || expectedSize == 0)) {
		return 1;
	}

	Element * currentEle = list;

	for (int i = 0; i < expectedSize ; i++, currentEle = currentEle->next) {
		if (currentEle == NULL || expectedListElements[i] != currentEle->value) {
			char * expectedAsString = _intArrayToString(expectedListElements, expectedSize);
			char * actualAsString = _intListToString(list);
			fprintf(stderr, "The list does not have expected elements.\nExpected elements: %s\nActual elements: %s\n", 
					expectedAsString, 
					actualAsString
			       );
			free(expectedAsString);
			free(actualAsString);
			return 0;
		}
	}

	if (currentEle != NULL && currentEle->next != NULL) {
		char * expectedAsString = _intArrayToString(expectedListElements, expectedSize);
		char * actualAsString = _intListToString(list);
		fprintf(stderr, "The list does not have expected elements.\nExpected elements: %s\nActual elements: %s\n", 
				expectedAsString, 
				actualAsString
		       );
		free(expectedAsString);
		free(actualAsString);
		return 0;
	}

	return 1;
}

void test_insertFirstElement() {
	printf("Running test: insert first element in empty list\n");

	Element * ele = allocNewElement();
	ele->value = 1;

	Element * list = insertElement(NULL, ele);

	assertListElements(((int[]){1}), 1, list);
	freeElement(ele);
}

void test_insertMultipleElementsInOrder() {
	printf("Running test: insert multiple elements into list in correct order\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * ele4 = allocNewElement();
	ele4->value = 4;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);
	list = insertElement(list, ele4);

	assertListElements(((int[]){1, 2, 3, 4}), 4, list);
	
	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
	freeElement(ele4);
}

void test_insertMultipleElementsInDifferentOrders() {
	printf("Running test: insert multiple elements into list in different order\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * ele4 = allocNewElement();
	ele4->value = 4;

	Element * list1 = NULL;
	list1 = insertElement(list1, ele4);
	list1 = insertElement(list1, ele3);
	list1 = insertElement(list1, ele2);
	list1 = insertElement(list1, ele1);

	Element * list2 = NULL;
	list2 = insertElement(list2, ele2);
	list2 = insertElement(list2, ele4);
	list2 = insertElement(list2, ele1);
	list2 = insertElement(list2, ele3);

	int expected[] = {1, 2, 3, 4};

	assertListElements(expected, 4, list1);
	assertListElements(expected, 4, list2);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
	freeElement(ele4);
}

void test_insertSameValueMultipleTimesPreservesUniqueForFirst() {
	printf("Running test: insert single element into empty list multiple times\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele1_dup = allocNewElement();
	ele1_dup->value = 1;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele1_dup);

	assertListElements(((int[]){1}), 1, list);

	freeElement(ele1);
	freeElement(ele1_dup);
}

void test_insertSameValueMultipleTimesPreservesUnique() {
	printf("Running test: insert multiple elements into list multiple times\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * ele1_dup = allocNewElement();
	ele1_dup->value = 1;

	Element * ele2_dup = allocNewElement();
	ele2_dup->value = 2;

	Element * ele3_dup = allocNewElement();
	ele3_dup->value = 3;

	int expected[] = {1, 2, 3};

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	assertListElements(expected, 3, list);

	list = insertElement(list, ele1_dup);
	assertListElements(expected, 3, list);

	list = insertElement(list, ele2_dup);
	assertListElements(expected, 3, list);

	list = insertElement(list, ele3_dup);
	assertListElements(expected, 3, list);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
	freeElement(ele1_dup);
	freeElement(ele2_dup);
	freeElement(ele3_dup);
}

void test_removeElementFromEmptyList() {
	printf("Running test: remove element from empty list\n");

	Element * ele = allocNewElement();
	ele->value = 1;

	Element * list = NULL;
	list = removeElement(list, ele);

	assert(NULL == list);
}

void test_removeElementFromListWithOneElement() {
	printf("Running test: remove element from list with single element\n");

	Element * ele = allocNewElement();
	ele->value = 1;

	Element * list = NULL;
	list = insertElement(list, ele);

	assertListElements(((int[]){1}), 1, list);

	removeElement(list, ele);

	assertListElements(((int[]){}), 0, list);
}

void test_removeFirstElementFromListWithMultipleElements() {
	printf("Running test: remove first element from list\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	list = removeElement(list, ele1);
	assertListElements(((int[]){2, 3}), 2, list);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
}

void test_removeLastElementFromListWithMultipleElements() {
	printf("Running test: remove last element from list with multiple elements\n");
	
	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	list = removeElement(list, ele3);
	assertListElements(((int[]){1, 2}), 2, list);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
}

void test_removeElementFromList() {
	printf("Running test: remove element from list\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	list = removeElement(list, ele2);
	assertListElements(((int[]){1, 3}), 2, list);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
}

void test_removeNonExistingElementFromList() {
	printf("Running test: remove non-existing element from list\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	Element * nonExistingEle = allocNewElement();
	nonExistingEle->value = 4;
	list = removeElement(list, nonExistingEle);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
	freeElement(nonExistingEle);
}

void test_removeElementWithExistingValueButBadPointer() {
	printf("Running test: remove element with existing value but bad pointer\n");

	Element * ele1 = allocNewElement();
	ele1->value = 1;

	Element * ele2 = allocNewElement();
	ele2->value = 2;

	Element * ele3 = allocNewElement();
	ele3->value = 3;

	Element * list = NULL;
	list = insertElement(list, ele1);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	Element * eleWithBadPointer = allocNewElement();
	eleWithBadPointer->value = 2;

	list = removeElement(list, eleWithBadPointer);

	assertListElements(((int[]){1, 2, 3}), 3, list);

	freeElement(ele1);
	freeElement(ele2);
	freeElement(ele3);
	freeElement(eleWithBadPointer);
}
