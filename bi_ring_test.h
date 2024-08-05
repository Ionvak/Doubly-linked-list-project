#ifndef TEST


#define TEST


#include <iostream>
#include "bi_ring.h"
#include <string>


//This function tests if two values are equal and returns false along a message if they are not, and true otherwise.
template<typename T>
bool TestEqual(const T& arg1, const T& arg2, std::string message){
    if(arg1 != arg2){
        std::cout << "Test Failed: " << message << std::endl;
        return false;
    }
    return true;
}

//This function tests if two values are unequal and returns false along a message if they are not, and true otherwise.
template<typename T>
bool TestDifference(const T& arg1, const T& arg2, std::string message){
    if(arg1 == arg2){
        std::cout << "Test Failed: " << message << std::endl;
        return false;
    }
    return true;
}

//This function goes through the whole Ring in both directions and returns true only if:
//1- in an empty Ring, the sentinel does not point to itself from both directions.
//2- in a single element Ring, the sentinel points to the single element from both directions, and the single element points to the sentinel from both directions.
//3- in a multi-element Ring: there is one link forward and one link back between each of the nodes including the sentinel.
//it returns false if any of these conditions are not met.
template<typename Key, typename Info>
bool ImproperConnect(const Ring<Key, Info>& src){

    typename Ring<Key, Info>::ConstIterator it = src.GetFirst();
    typename Ring<Key, Info>::ConstIterator it2 = src.GetLast();

    if(!(--it == ++it2 && (++it == src.GetFirst() && --it2 == src.GetLast()) )) return true;

    if(src.Length() > 0){
        unsigned int Count = 1;
        while(Count != src.Length()+1){
            if(it.IsNull() || (it == src.GetLast() && Count != src.Length()) || (it != src.GetLast() && Count == src.Length()) ) return true;
            ++it;
            ++Count;
        }

        while(Count != 0){
            if(it.IsNull() || (it == src.GetFirst() && Count != 1) || (it != src.GetFirst() && Count == 1)) return true;
            --it;
            --Count;
        }
    }
    return false;
}


//This function tests if a given argument passes a given condition and returns false alongside a message if it does not, and true otherwise.
template<typename T>
bool TestIf(const T& arg, bool (Check)(const T&), std::string message){
    if(!Check(arg)){
        std::cout << "Test Failed: " << message << std::endl;
        return false;
    }
    return true;
}


//This function artificially fills the list with n many default values.
template<typename Key, typename Info>
void FillRing(Ring<Key, Info>& src,const int& n){
    for(int i=0; i<n ;i++) src.PushBack(Key(),Info());
}



#endif // TEST
