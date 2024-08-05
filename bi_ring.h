#ifndef RING

#include <assert.h>

#define RING

//This class represents a doubly linked list implemented as a Ring where the Last element Leads back to the start, and where it's possible to move directly from the start to the last element.
//This implementation of the linked lists uses a sentinel node at the beginning which is given default key and info values. The sentinel is in practice the first element in the list but can
//be treated as a non-existent element due to the methods of this class allowing for list manipulation and reading without accessing or interacting with this sentinel node.
template<typename Key, typename Info>
class Ring{

private:
    struct Node{
        Key label;
        Info value;
        Node* next;
        Node* prev;


        Node(const Key& ID = Key(), const Info& data = Info(), Node* consq = nullptr, Node* prec = nullptr) : label(ID), value(data), next(consq), prev(prec){}
    };

    Node* start = nullptr;
    unsigned int Size = 0;

public:

    //This class represents a smart pointer used for iterating through the Ring class. This iterator allows for editing of the Ring by directly
    //accessing the elements and their attributes. In other words, this iterator is used for both read and write operations.
    class Iterator{

    public:

        Node* pointer;


        //Constructor
        Iterator(Node* P) : pointer(P){}


        //This operator moves the iterator to the element after the element currently pointed to. It returns the iterator after incrementing it (postfix).
        Iterator& operator++(){
            assert(pointer);
            pointer = pointer->next;
            return *this;
        }


        //This operator moves the iterator to the element after the element currently pointed to. It returns the iterator before incrementing it (prefix).
        Iterator operator++(int){
            assert(pointer);
            Iterator ToBeReturned = *this;
            pointer = pointer->next;
            return ToBeReturned;
        }


        //This operator moves the iterator to the element previous to the element currently pointed to. It returns the iterator after decrementing it (postfix).
        Iterator& operator--(){
            assert(pointer);
            pointer = pointer->prev;
            return *this;
        }


        //This operator moves the iterator to the element previous to the element currently pointed to. It returns the iterator before decrementing it (prefix).
        Iterator operator--(int){
            assert(pointer);
            Iterator ToBeReturned = *this;
            pointer = pointer->prev;
            return ToBeReturned;
        }


        //This operator returns true if two iterators point to the same element and false otherwise.
        bool operator==(const Iterator& other) const{ return pointer == other.pointer; }


        //This operator returns false if two iterators point to the same element and true otherwise.
        bool operator!=(const Iterator& other) const{ return pointer != other.pointer; }



    };


    //This class represents a smart pointer used for iterating through the Ring class. This iterator allows only for reading of the elements and their attributes and does not allow for direct changes.
    // In other words, this iterator is used for read operations only.
    class ConstIterator{

    private:
        Node* cpointer;
        ConstIterator(Node* P) : cpointer(P){}
        friend class Ring;

    public:

        //Constructor
         ConstIterator(const Iterator& P) : cpointer(P.pointer){}


        //This operator moves the iterator to the element after the element currently pointed to. It returns the iterator after incrementing it (postfix).
         ConstIterator& operator++(){
            assert(cpointer);
            cpointer = cpointer->next;
            return *this;
        }


        //This operator moves the iterator to the element after the element currently pointed to. It returns the iterator before incrementing it (prefix).
        ConstIterator operator++(int){
            assert(cpointer);
            ConstIterator ToBeReturned(cpointer);
            cpointer = cpointer->next;
            return ToBeReturned;
        }


        //This operator moves the iterator to the element previous to the element currently pointed to. It returns the iterator after decrementing it (postfix).
        ConstIterator& operator--(){
            assert(cpointer);
            cpointer = cpointer->prev;
            return *this;
        }


        //This operator moves the iterator to the element previous to the element currently pointed to. It returns the iterator before decrementing it (prefix).
        ConstIterator operator--(int){
            assert(cpointer);
            ConstIterator ToBeReturned = *this;
            cpointer = cpointer->prev;
            return ToBeReturned;
        }


        //This operator returns true if two iterators point to the same element and false otherwise.
        bool operator==(const ConstIterator& other) const{ return cpointer == other.cpointer; }


        //This operator returns false if two iterators point to the same element and true otherwise.
        bool operator!=(const ConstIterator& other) const{ return cpointer != other.cpointer; }


        //This operator returns the key of the element the iterator points to.
        Info operator*() const{
            return cpointer->value;
        }


        //This operator returns the info of the element the iterator points to.
        Key operator&() const{
            return cpointer->label;
        }


        //This function Returns true if the iterator is null and false otherwise.
        bool IsNull(){ return cpointer == nullptr; }

    };


    //Constructor
    Ring(){
        start = new Node();
        start->next = start;
        start->prev = start;
    }


    //Copy constructor
    Ring(const Ring& src){ *this = src; }


    //Destructor
    ~Ring(){
        this->Clear();
        delete start;
    }


    //This function returns an iterator pointing to the first element in the Ring (the element after the sentinel.
    Iterator GetFirst() const{
        assert(start);
        return start->next;
    }


    //This function returns an iterator pointing to the last element in the Ring (the element before the sentinel.
    Iterator GetLast() const{
        assert(start);
        return start->prev;
    }


    //This function returns the number of elements currently present in the Ring.
    unsigned int Length() const{ return Size; }


    //This function returns true if the Ring is empty (if the only existing element is the sentinel), and false otherwise.
    bool IsEmpty() const{ return start->next == start; }


    //This function inserts an element with a given key and info to the beginning of the Ring.
    Iterator PushFront(const Key& ID, const Info& Data){
        start->next = start->next->prev = new Node(ID,Data,start->next,start);
        Size++;
        return this->GetFirst();
    }


    //This function removes the first element in the Ring, unless the Ring is empty.
    Iterator PopFront(){
        if(!this->IsEmpty()){
            Iterator temp = start->next;
            start->next = start->next->next;
            start->next->prev = start;
            delete temp.pointer;
            Size--;
        }
        return this->GetFirst();
    }


    //This function inserts an element with a given key and info to the end of the Ring.
    Iterator PushBack(const Key& ID, const Info& Data){
        start->prev = start->prev->next = new Node(ID,Data,start,start->prev);
        Size++;
        return this->GetLast();
    }


    //This function removes the last element in the Ring, unless the Ring is empty.
    Iterator PopBack(){
        if(!this->IsEmpty()){
            Iterator temp = start->prev;
            start->prev = start->prev->prev;
            start->prev->next = start;
            delete temp.pointer;
            Size--;
        }
        return this->GetLast();
    }



    Iterator LookFor(const Key& item) const;



    Iterator LookThrough(const Key& item, const Iterator& Begin, const Iterator& End) const;



    Iterator Insert(const Iterator& item, const Key& ID, const Info& Data);



    Iterator Erase(const Iterator& item);



    void Clear();



    void Print() const;



    Ring& operator+(const Ring& other);



    Ring& operator=(const Ring& other);



    bool operator==(const Ring& other);



    bool operator!=(const Ring& other);

};


//This function searches the whole ring for an element with a given key. If the element is found then an iterator to it is returned, otherwise nullptr is returned.
template<typename Key, typename Info>
typename Ring<Key,Info>::Iterator Ring<Key,Info>::LookFor(const Key& item) const{
    Iterator temp = start;

    do{
        if(temp.pointer->label == item) return temp;
        ++temp;
    }while(temp != start);

    return nullptr;
}

//This function searches within a given range for a given key in the Ring. If the element is found then an iterator to it is returned, otherwise nullptr is returned.
template<typename Key, typename Info>
typename Ring<Key,Info>::Iterator Ring<Key,Info>::LookThrough(const Key& item, const Iterator& Begin, const Iterator& End) const{
    Iterator temp = Begin;
    if( Begin != nullptr && End != nullptr){

    do{
        if(temp.pointer->label == item) return temp;
        ++temp;
    }while(temp != End);

    }

    return nullptr;
}


//This function inserts a new element with a given key and info before the element in the list which the iterator passed points to, and returns a pointer to it.
// It does nothing if the pointer passed is nullptr besides returning nullptr.
template<typename Key, typename Info>
typename Ring<Key,Info>::Iterator Ring<Key,Info>::Insert(const Iterator& item, const Key& ID, const Info& Data){
    if(item.pointer){
        Iterator NewNode = new Node(ID,Data,item.pointer,item.pointer->prev);
        item.pointer->prev->next = NewNode.pointer;
        item.pointer->prev = NewNode.pointer;
        Size++;
        return NewNode;
    }
    return nullptr;
}


//This function removes the element that the iterator passed to it points to, unless that element is the sentinel, and returns an iterator to the element that's now taking it's place (the sentinel
//if it as the only one). It returns nullptr if the passed iterator is null or if it points to the sentinel.
template<typename Key, typename Info>
typename Ring<Key,Info>::Iterator Ring<Key,Info>::Erase(const Iterator& item){
    if(item.pointer != nullptr && item != start){
        Iterator temp = item;
        Iterator ToBeReturned = temp.pointer->prev;
        item.pointer->prev->next = item.pointer->next;
        item.pointer->next->prev = item.pointer->prev;
        delete temp.pointer;
        Size--;
        return ToBeReturned;
    }
    return nullptr;
}


//This function removes all the elements from the Ring, keeping only the sentinel.
template<typename Key, typename Info>
void Ring<Key,Info>::Clear(){
    while(!this->IsEmpty()) this->PopFront();;
}


//This function prints the Ring.
template<typename Key, typename Info>
void Ring<Key,Info>::Print() const{

    std::cout << "start<=>";
    for(ConstIterator temp(start->next); temp != start ;++temp){
    std::cout << '(' << *temp << ','<< &temp << ')' << "<=>";
    }
    std::cout << "start" << std::endl;

}


//This operator concatenates two Rings by adding one Ring to the end of another. It returns a reference to the generated Ring to allow for chaining of this operator.
template<typename Key, typename Info>
Ring<Key,Info>& Ring<Key,Info>::operator+(const Ring& other){
    ConstIterator temp = other.GetFirst();
    unsigned int Count = other.Length();

    while(Count > 0){
        this->PushBack(&temp,*temp);
        ++temp;
        --Count;
    }
    return *this;
}


//This operator assigns one Ring to another. i.e: it overwrites one Ring with another. It returns a reference to the generated Ring to allow for chaining of this operator.
template<typename Key, typename Info>
Ring<Key,Info>& Ring<Key,Info>::operator=(const Ring& other){
    if(this->GetFirst() != other.GetFirst()){
        this->Clear();
        (*this) + other;
    }
    return *this;
}


//This operator returns true if two Rings are equal, and false otherwise.
template<typename Key, typename Info>
bool Ring<Key,Info>::operator==(const Ring& other){
    if(Size != other.Size) return false;
    ConstIterator temp1 = this->GetFirst();
    ConstIterator temp2 = other.GetFirst();

    while(temp1 != start){
        if(&temp1 != &temp2 || *temp1 != *temp2) return false;
        ++temp1;
        ++temp2;
    }

    return true;
}


//This operator returns true if two Rings are unequal, and false otherwise.
template<typename Key, typename Info>
bool Ring<Key,Info>::operator!=(const Ring& other){
    return !(*this == other);
}


//This function adds to a new Ring the elements of the passed Ring which pass a given condition. The new Ring is then returned at the end.
template<typename Key, typename Info>
Ring<Key, Info> Filter(const Ring<Key, Info>& source, bool(pred)(const Key&)){
    Ring<Key,Info> NewRing;
    typename Ring<Key,Info>::ConstIterator temp = source.GetFirst();
    for(unsigned i=0; i<source.Length() ;i++){
        if(pred(&temp)) NewRing.PushBack(&temp,*temp);
        ++temp;
    }

    return NewRing;
}


//This function removes repeated instances of any key by reducing all the elements with the same key to a single element with that key and info equivalent to the aggregate of all their infos.
//The process for aggregation is given by the user. These new reduced elements are then added to a new Ring. If an element is already unique, it's simply copied to the new Ring. The new
//Ring is returned at the end.
template<typename Key, typename Info>
Ring<Key, Info> Unique(const Ring<Key, Info>& source, Info(aggregate)(const Key&, const Info&, const Info&)){
    Ring<Key,Info> NewRing;
    typename Ring<Key,Info>::ConstIterator temp = source.GetFirst();
    typename Ring<Key,Info>::Iterator it = NewRing.GetFirst();

    for(unsigned i=0; i<source.Length(); i++){
        it = NewRing.LookFor(&temp);
        if(!it.pointer) NewRing.PushBack(&temp,*temp);
        else it.pointer->value = aggregate(&temp,it.pointer->value,*temp);
        ++temp;
    }

    return NewRing;
}


//This function iterates through the first Ring, and with each step it searches for an element with an equivalent key in the second Ring. If such element is found, the info from
//both elements is added together and then an element with the equivalent key and the sum of infos is added to a new Ring. If no such element is found, the element from the first
//Ring is simply copied to the new Ring. Both lists are reduced to their unique form before this process begins by Using the function Unique. The new Ring is returned at the end.
template<typename Key, typename Info>
Ring<Key, Info> Join(const Ring<Key, Info>& first, const Ring<Key, Info>& second){
    Ring<Key,Info> Unique1 = Unique<Key,Info>(first,[](const Key&, const Info& arg1, const Info& arg2){ return arg1 + arg2; });
    Ring<Key,Info> Unique2 = Unique<Key,Info>(second,[](const Key&, const Info& arg1, const Info& arg2){ return arg1 + arg2; });
    Ring<Key,Info> NewRing;
    typename Ring<Key,Info>::ConstIterator temp1 = Unique1.GetFirst();
    typename Ring<Key,Info>::ConstIterator temp2 = Unique2.GetFirst();

    for(unsigned i=0; i<Unique1.Length(); i++){
        temp2 = Unique2.LookFor(&temp1);
        if(temp2.IsNull()) NewRing.PushBack(&temp1,*temp1);
        else NewRing.PushBack(&temp1,*temp1 + *temp2);
        ++temp1;
    }

    return NewRing;
}


//This function adds fcnt many items from the first Ring, then adds scnt many items from the second Ring to a new Ring. It does this reps many times. It iterates in both Rings
//starting from the beginning of each Ring and resets to the beginning of the Ring if the end is reached when iterating in either Ring. The new Ring is then returned at the end.
template<typename Key, typename Info>
Ring<Key, Info> Shuffle(const Ring<Key, Info>& first, unsigned int fcnt,const Ring<Key, Info>& second, unsigned int scnt,unsigned int reps){
    Ring<Key,Info> NewRing;
    typename Ring<Key,Info>::ConstIterator temp1 = first.GetFirst();
    typename Ring<Key,Info>::ConstIterator temp2 = second.GetFirst();

    unsigned i=0;
    while(i++ < reps){
        for(unsigned m=0; m<fcnt ;m++){
            NewRing.PushBack(&temp1,*temp1);
            if(temp1++ == first.GetLast()) temp1 = first.GetFirst();
        }

        for(unsigned n=0; n<scnt ;n++){
            NewRing.PushBack(&temp2,*temp2);
            if(temp2++ == second.GetLast()) temp2 = second.GetFirst();
        }
    }

    return NewRing;
}




#endif // RING

