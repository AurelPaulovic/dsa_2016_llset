#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

typedef struct Element {
	int value;
	struct Element * next;
} Element;

Element * insertElement(Element * list, Element * newEle);

Element * findPredecessor(Element * list, int value);

Element * allocNewElement();

void printList(Element * ele);

void printElement(Element * ele);

#endif
