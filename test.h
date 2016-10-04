#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <assert.h>
#include "set.h"

#define assertListElements(expectedListElements, expectedSize, list) (assert(_assertListElements((expectedListElements), (expectedSize), (list))))

int _assertListElements(int expectedListElements[], int expectedSize, Element * list);

void test_insertFirstElement();
void test_insertMultipleElementsInOrder();
void test_insertMultipleElementsInDifferentOrders();
void test_insertSameValueMultipleTimesPreservesUniqueForFirst();
void test_insertSameValueMultipleTimesPreservesUnique();

void test_removeElementFromEmptyList();
void test_removeElementFromListWithOneElement();
void test_removeFirstElementFromListWithMultipleElements();
void test_removeLastElementFromListWithMultipleElements();
void test_removeElementFromList();
void test_removeNonExistingElementFromList();
void test_removeElementWithExistingValueButBadPointer();

#endif
