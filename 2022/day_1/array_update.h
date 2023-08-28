#ifndef ARRAY_UPDATE_H
#define ARRAY_UPDATE_H

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> array_update( int sum, std::vector<int> array, int index ) {
    if ( index > 0 ) {
        if ( sum > array[index] ) {
            if ( sum > array[index-1] ) {
                array[index] = array[index-1];
            }
            else {
                array[index] = sum;
            }
        }
        array = array_update(sum, array, index-1);
    }
    else if ( sum > array[index] ) {
        array[index] = sum;
    }
    return array;
}

#endif // ARRAY_UPDATE_H
