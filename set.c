#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "test.h"

int main(int argc, const char* argv[]) {
	Element * ele = allocNewElement();
	ele->value = 1;
	
	Element * ele2 = allocNewElement();
	ele2->value = 4;

	Element * ele3 = allocNewElement();
	ele3->value = 2;

	Element * list = insertElement(NULL, ele);
	list = insertElement(list, ele2);
	list = insertElement(list, ele3);

	printList(list);

	assertListElements(((int[]){1, 2, 4}), 3, list);
	
	free(ele);
	free(ele2);
	free(ele3);

	return 0;
}

Element * insertElement(Element * list, Element * newEle) {
	if (newEle == NULL) {
		return list;
	}

	Element * predecessor = findPredecessor(list, newEle->value);
	// predecessor is the last smaller or equal element in the list

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

Element * allocNewElement() {
	Element * ele = (Element *) malloc(sizeof(Element));

	if (ele == NULL) {
		perror("Could not allocate memory for new element");
		exit(1);
	}

	return ele;
}
