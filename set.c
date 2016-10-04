#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "test.h"

int main(int argc, const char* argv[]) {
	test_insertFirstElement();
	test_insertMultipleElementsInOrder();
	test_insertMultipleElementsInDifferentOrders();
	test_insertSameValueMultipleTimesPreservesUniqueForFirst();
	test_insertSameValueMultipleTimesPreservesUnique();

	test_removeElementFromEmptyList();
	test_removeElementFromListWithOneElement();
	test_removeFirstElementFromListWithMultipleElements();
	test_removeLastElementFromListWithMultipleElements();
	test_removeElementFromList();
	test_removeNonExistingElementFromList();
	test_removeElementWithExistingValueButBadPointer();

	return 0;
}

Element * removeElement(Element * list, Element * ele) {
	if (ele == NULL || list == NULL) {
		return list;
	}
	
	if (list == ele) {
		return list->next;
	}

	Element * previousElement = list;
	while (previousElement->next != NULL && previousElement->next != ele) {
		previousElement = previousElement->next;
	}

	if (previousElement->next == ele) {
		previousElement->next = previousElement->next->next;
	}

	return list;
}

Element * insertElement(Element * list, Element * newEle) {
	if (newEle == NULL) {
		return list;
	}

	Element * predecessor = findPredecessor(list, newEle->value);

	if (predecessor == NULL) {
		// newEle is first element in list
		newEle->next = list;
		return newEle;
	} else if (predecessor->value != newEle->value) {
		newEle->next = predecessor->next;
		predecessor->next = newEle;
		return list;
	} else {
		// predecessor has the same value as the new element
		// return original list as we do not insert duplicates
		return list;
	}
}

Element * findPredecessor(Element * list, int value) {
	// list is empty -> predecessor does not exist
	if (list == NULL) {
		return NULL;
	}

	Element * currentEle = list;

	// check if the value is smaller than the first element -> predecessor does not exist
	if (value < currentEle->value) {
		return NULL;
	}

	// peek into next element and check if it is still smaller or equal and if it is, advance to the next element
	// -> we will stop at the predecessor
	while (currentEle->next != NULL && currentEle->next->value <= value) {
		currentEle = currentEle->next;
	}

	return currentEle;
}

void printList(Element * ele) {
	while (ele != NULL) {
		printElement(ele);
		ele = ele->next;
	}
}

void printElement(Element * ele) {
	printf("%d\n", ele->value);
}

void freeElement(Element * ele) {
	free(ele);
}

Element * allocNewElement() {
	Element * ele = (Element *) malloc(sizeof(Element));

	if (ele == NULL) {
		perror("Could not allocate memory for new element");
		exit(1);
	}

	return ele;
}
