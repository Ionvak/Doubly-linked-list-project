#include <iostream>
#include <string>
#include "bi_ring.h"
#include "bi_ring_test.h"

int main(){
    Ring<int,std::string> TestRing;

    //****************************** test zone 1 ****************************  (Testing following functions: GetFirst, GetLast, PushFront, PopFront, Print.)

    std::cout << "-Test Zone 1-\n" << std::endl;

    if(ImproperConnect(TestRing)) std::cout << "Empty list does not have sentinel node pointing to itself" << std::endl;
    TestRing.Print();

    TestRing.PushFront(1,"ABC");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after PushFront on empty list." << std::endl;
    TestRing.Print();

    TestRing.PushFront(2,"DEF");
    TestRing.PushFront(2,"GHI");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements list after PushFront on non-empty list." << std::endl;
    TestRing.Print();

    TestRing.PopFront();
    TestRing.PopFront();
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after PopFront on multi-element list." << std::endl;
    TestRing.Print();

    TestRing.PopFront();
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after clearing list with PopFront." << std::endl;
    TestRing.Print();

    TestRing.PopFront();
    if(ImproperConnect(TestRing)) std::cout << "List changed after using PopFront on empty list." << std::endl;
    TestRing.Print();


    std::cout << '\n' << std::endl;


    //****************************** test zone 2 ****************************  (Testing following functions: IsEmpty, Length, PushBack, PopBack.)
    std::cout << "-Test Zone 2-\n" << std::endl;
    unsigned int iTest = 0;

    if(!TestRing.IsEmpty()) std::cout << "IsEmpty returns false for empty list." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of single element list returned by Length is not 1.");
    TestRing.Print();

    TestRing.PushBack(11,"M");
    ++iTest;
    TestEqual(TestRing.Length(),iTest,"Size of single element list returned by Length is not 1.");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after PushBack on non-empty list." << std::endl;
    if(TestRing.IsEmpty()) std::cout << "IsEmpty returns true for non-empty list." << std::endl;
    TestRing.Print();

    TestRing.PushBack(22,"N");
    TestRing.PushBack(33,"O");
    iTest += 2;
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after PushBack on non-empty list" << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct for multi-element list.");
    TestRing.Print();

    TestRing.PopBack();
    --iTest;
    TestEqual(TestRing.Length(),iTest,"Size of single element list returned by Length is not correct after PopBack on multi-element list.");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after PopBack on multi-element list." << std::endl;
    TestRing.Print();

    TestRing.PopBack();
    TestRing.PopBack();
    iTest -= 2;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after clearing list with PopBack.");
    if(ImproperConnect(TestRing)) std::cout << "Sentinel node does not point to itself after clearing list with PopBack." << std::endl;
    TestRing.Print();

    TestRing.PopBack();
    if(ImproperConnect(TestRing)) std::cout << "List changed after PopBack on empty list." << std::endl;
    TestRing.Print();

    std::cout << '\n' << std::endl;


    //****************************** test zone 3 ****************************  (Testing following functions: LookFor, Insert, Remove, , Clear, LookThrough.)
    std::cout << "-Test Zone 3-\n" << std::endl;
    Ring<int,std::string>::Iterator it(TestRing.GetFirst());

    it = TestRing.LookFor(5);
    if(it.pointer) std::cout << "Non-existent element returned by LookFor." << std::endl;

    TestRing.Insert(it, 1, "A");
    if(!TestRing.IsEmpty()) std::cout << "Element inserted in list despite iterator passed being nullptr." << std::endl;

    TestRing.PushBack(1,"A");
    TestRing.PushBack(2,"B");
    TestRing.PushBack(4,"C");
    TestRing.Print();

    it = TestRing.LookFor(4);
    TestEqual(it.pointer->label,4,"Key of element found by LookFor is not the correct one.");

    TestRing.Insert(it, 3, "D");
    iTest += 4;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using Insert.");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after using Insert." << std::endl;
    TestRing.Print();

    iTest = 0;
    TestRing.Clear();
    if(!TestRing.IsEmpty()) std::cout << "List is not empty after using Clear." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using Clear.");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections between elements after using Clear." << std::endl;
    TestRing.Print();

    TestRing.Clear();
    if(ImproperConnect(TestRing)) std::cout << "List changed after using Clear on empty List." << std::endl;
    TestRing.Print();

    it = nullptr;
    TestRing.Erase(it);
    if(ImproperConnect(TestRing)) std::cout << "List changed after using Erase on empty List." << std::endl;
    TestRing.Print();

    TestRing.PushFront(0,"-");
    ++iTest;
    TestRing.Erase(it);
    if(ImproperConnect(TestRing)) std::cout << "Element removed from List with Erase despite iterator passed being nullptr." << std::endl;
    TestRing.Print();

    it = TestRing.GetFirst();
    TestRing.Erase(it);
    if(ImproperConnect(TestRing)) std::cout << "Improper connection between elements after clearing list with Erase." << std::endl;
    --iTest;
    it = TestRing.GetFirst();
    TestRing.Print();

    TestRing.Insert(it, 1, "A");
    TestRing.Insert(it, 2, "B");
    TestRing.Insert(it, 3, "C");
    if(ImproperConnect(TestRing)) std::cout << "Improper connection between elements after filling list with Insert." << std::endl;
    iTest = 3;
    TestRing.Print();

    TestRing.Erase(it);
    if(ImproperConnect(TestRing)) std::cout << "Sentinel node removed by Erase." << std::endl;

    ++it;
    TestRing.Erase(it);
    --iTest;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using Erase.");
    if(ImproperConnect(TestRing)) std::cout << "Improper connection between elements after using Erase." << std::endl;
    TestRing.Print();

    TestRing.PushFront(1,"A");
    ++iTest;
    it = TestRing.LookFor(2);
    TestEqual(TestRing.LookFor(2),TestRing.LookThrough(2,TestRing.GetFirst(),TestRing.GetLast()),"LookThrough does not return correct Iterator when End is after Begin.");
    TestEqual(TestRing.LookFor(3),TestRing.LookThrough(3,it,it),"LookThrough does not return correct Iterator when End is equal to Begin.");
    TestEqual(TestRing.LookFor(3),TestRing.LookThrough(3,it,TestRing.GetFirst()),"LookThrough does not return correct Iterator when End is before Begin.");
    TestRing.Print();

    it = nullptr;
    TestEqual(it,TestRing.LookThrough(4,TestRing.GetFirst(),TestRing.GetFirst()),"LookThrough returns iterator to non-existent element.");
    TestEqual(it,TestRing.LookThrough(1,TestRing.GetFirst(),it),"LookThrough returns iterator when End is nullptr.");
    TestEqual(it,TestRing.LookThrough(1,it,TestRing.GetLast()),"LookThrough returns iterator when Begin is nullptr.");
    TestRing.Print();

    std::cout << '\n' << std::endl;


    //****************************** test zone 4 ****************************  (Testing following functions: operator==, operator!=, operator=, operator+.)
    std::cout << "-Test Zone 4-\n" << std::endl;

    Ring<int,std::string> TestRing2;
    TestRing2.PushFront(12,"Z");
    TestRing2.PushBack(34,"X");
    it = TestRing2.GetFirst();
    TestRing2.Insert(it,56,"Y");
    TestRing.Print();
    TestRing2.Print();

    if(!(TestRing == TestRing)) std::cout << "Operator== returns false for equal lists." << std::endl;
    if(TestRing == TestRing2) std::cout << "Operator== returns true for unequal lists." << std::endl;

    if(TestRing != TestRing) std::cout << "Operator!= returns true for equal lists." << std::endl;
    if(!(TestRing != TestRing2)) std::cout << "Operator!= returns false for unequal lists." << std::endl;

    TestRing = TestRing;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using operator= to assign list to itself.");
    if(ImproperConnect(TestRing)) std::cout << "List changed when assigned itself." << std::endl;
    TestRing.Print();

    TestRing = TestRing2;
    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using operator=." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using operator= to assign one list to another.");
    if(TestRing != TestRing2) std::cout << "Operator= does not result in list equal to it's assigned value." << std::endl;
    TestRing.Print();
    TestRing2.Print();

    TestRing.Clear();
    TestRing2 = TestRing = TestRing2;
    if(ImproperConnect(TestRing2)) std::cout << "Improper connections after using operator= several times in single line." << std::endl;
    TestEqual(TestRing2.Length(),iTest,"Size of list returned by Length is not correct after using operator= multiple times on the same line.");
    if(TestRing != TestRing2) std::cout << "Result of using operator= on same line more than once is not as expected." << std::endl;
    TestRing.Print();
    TestRing2.Print();

    iTest *= 2;
    TestRing = TestRing + TestRing;
    TestRing2.PushBack(56,"Y");
    TestRing2.PushBack(12,"Z");
    TestRing2.PushBack(34,"X");
    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using operator+ to add list to itself." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using operator+ to add list to itself.");
    if(TestRing2 != TestRing) std::cout << "Resulting list is not as expected after adding list to itself" << std::endl;
    TestRing.Print();
    TestRing2.Print();

    iTest *= 2;
    TestRing2 = TestRing2 + TestRing;
    TestRing = TestRing + TestRing;
    if(TestRing != TestRing2) std::cout << "Result From adding two non-empty lists with operator+ is not as expected." << std::endl;
    if(ImproperConnect(TestRing2)) std::cout << "Improper connections after using operator+ to add two non-empty lists." << std::endl;
    TestEqual(TestRing2.Length(),iTest,"Size of list returned by Length is not correct after using operator+ to add two lists.");
    TestRing.Print();
    TestRing2.Print();

    TestRing.Clear();
    TestRing2.Clear();
    iTest = 0;
    TestRing = TestRing + TestRing2;
    if(!TestRing.IsEmpty()) std::cout << "Result From adding two empty lists with operator+ is not empty." << std::endl;
    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using operator+ to add two empty lists." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using operator+ to add two empty lists.");
    TestRing.Print();
    TestRing2.Print();

    TestRing2.PushBack(0,"WUT");
    TestRing = TestRing + TestRing2 + TestRing2 + TestRing2 ;
    TestRing2.PushBack(0,"WUT");
    TestRing2.PushBack(0,"WUT");
    iTest = 3;
    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using operator+ several times in single line." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list returned by Length is not correct after using operator+ multiple times on the same line.");
    if(TestRing != TestRing2) std::cout << "Result of using operator+ on same line more than once is not as expected." << std::endl;
    TestRing.Print();
    TestRing2.Print();


    std::cout << '\n' << std::endl;


    //****************************** test zone 6 ****************************  (Testing following functions: Filter, Unique, Join, Shuffle.)
    std::cout << "-Test Zone 5-\n" << std::endl;

    TestRing.Clear();
    iTest = 10;
    for(unsigned i=1; i<=iTest ;i++) TestRing.PushBack(i,"test");
    TestRing.Print();

    iTest = 5;
    TestRing2 = Filter<int,std::string>(TestRing,[](const int& x){ return x > 5; });
    for(unsigned i=0; i<iTest ;i++) TestRing.PopFront();
    if(ImproperConnect(TestRing2)) std::cout << "Improper connections after using Filter." << std::endl;
    TestEqual(TestRing2.Length(),iTest,"Size of list is not correct after using Filter.");
    if(TestRing != TestRing2) std::cout << "Result of using Filter is not as expected." << std::endl;
    TestRing.Print();
    TestRing2.Print();

    TestRing = TestRing + TestRing2;
    TestRing2.Clear();
    iTest = 10;
    for(unsigned i=6; i<=iTest ;i++) TestRing2.PushBack(i,"[test,test]");
    iTest = 5;
    TestRing.Print();
    TestRing2.Print();

    TestRing = Unique<int,std::string>(TestRing,[](const int& x, const std::string& arg1, const std::string& arg2){ return "[" + arg1 + "," + arg2 + "]"; } );
    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using Unique." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list is not correct after using Unique.");
    if(TestRing != TestRing2) std::cout << "Result of using Unique is not as expected." << std::endl;
    TestRing.Print();
    TestRing2.Print();

    iTest = 5;
    TestRing.Clear();
    TestRing2.Clear();
    for(unsigned i=1; i<=iTest ;i++) TestRing.PushBack(i,"comp");
    for(unsigned i=1; i<=iTest ;i++) TestRing2.PushBack(i,"lete");
    TestRing.Print();
    TestRing2.Print();

    TestRing = Join(TestRing,TestRing2);
    it = TestRing2.GetFirst();
    for(unsigned i=1; i<=iTest ;i++){
        it.pointer->value = "complete";
        it++;
    }

    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using Join." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list is not correct after using Join.");
    if(TestRing != TestRing2) std::cout << "Result of using Join is not as expected." << std::endl;
    TestRing.Print();
    TestRing2.Print();

    TestRing.Clear();
    TestRing2.Clear();
    for(unsigned i=1; i<=5 ;i++) TestRing.PushBack(i,std::to_string(i));
    for(unsigned i=6; i<=10 ;i++) TestRing2.PushBack(i,std::to_string(i));
    TestRing.Print();
    TestRing2.Print();

    iTest = 12;
    TestRing = Shuffle(TestRing,1,TestRing2,3,3);
    TestRing2.Clear();
    TestRing2.PushBack(1,"1");
    TestRing2.PushBack(6,"6");
    TestRing2.PushBack(7,"7");
    TestRing2.PushBack(8,"8");
    TestRing2.PushBack(2,"2");
    TestRing2.PushBack(9,"9");
    TestRing2.PushBack(10,"10");
    TestRing2.PushBack(6,"6");
    TestRing2.PushBack(3,"3");
    TestRing2.PushBack(7,"7");
    TestRing2.PushBack(8,"8");
    TestRing2.PushBack(9,"9");

    if(ImproperConnect(TestRing)) std::cout << "Improper connections after using Shuffle." << std::endl;
    TestEqual(TestRing.Length(),iTest,"Size of list is not correct after using Shuffle.");
    if(TestRing != TestRing2) std::cout << "Result of using Shuffle is not as expected." << std::endl;
    TestRing.Print();
    TestRing2.Print();


    std::cout << "\nEnd of Tests (^w^)" << std::endl;


return 0;
}
