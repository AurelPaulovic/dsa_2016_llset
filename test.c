#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

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
		perror("Could not allocate memory for string reprsentation of an array");
		return 0;
	}
	strcat(result,"[");

	for (int i = 0; i < length; i++) {
		if (i != 0) {
			strcat(result, ", ");
		}

		strcat(result, arrayAsStrings[i]); 
	}

	strcat(result, "]");

	return result;
}

int _assertListElements(int expectedListElements[], int expectedSize, Element * list) {
	if (list == NULL && (expectedListElements == NULL || expectedSize == 0)) {
		return 1;
	}

	Element * currentEle = list;

	for (int i = 0; i < expectedSize ; i++, currentEle = currentEle->next) {
		if (currentEle == NULL || expectedListElements[i] != currentEle->value) {
			char * expectedAsString = _intArrayToString(expectedListElements, expectedSize);
			fprintf(stderr, "The list does not have expected elements.\nExpected elements: %s\nActual elements: %s\n", 
					expectedAsString, 
					"abc" //_intListToString(list)
			       );
			free(expectedAsString);
			return 0;
		}
	}

	if (currentEle != NULL && currentEle->next != NULL) {
		char * expectedAsString = _intArrayToString(expectedListElements, expectedSize);
		fprintf(stderr, "The list does not have expected elements.\nExpected elements: %s\nActual elements: %s\n", 
				expectedAsString, 
				"abc" //_intListToString(list)
		       );
		free(expectedAsString);
		return 0;
	}

	return 1;
}


