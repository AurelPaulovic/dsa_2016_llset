#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <assert.h>
#include "set.h"

#define assertListElements(expectedListElements, expectedSize, list) (assert(_assertListElements((expectedListElements), (expectedSize), (list))))

int _assertListElements(int expectedListElements[], int expectedSize, Element * list);

#endif
