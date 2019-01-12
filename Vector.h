/** @file Vector.h - Vector class definition
    @author Keo Tom-Shaw
    @date 10/04/2018
    @version 1
*/

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

template <class Type>
///Manages a dynamic array with methods for inserting, deleting and accessing elements.
class Vector{
public:
    ///Default Constructor
    Vector();

    /** Copy Constructor
        @param vec The Vector object which is to be copied.
    */
    Vector(const Vector & vec);

    ///Destructor
    ~Vector();

    /** Overloaded assignment operator.
        @param vec Vector object to be copied into the left operand.
        @return A constant reference to a Vector object.
    */
    const Vector & operator =(const Vector & vec);

    /** Overloaded constant array access operator.
        @pre The parameter i should not be greater than GetSize() - 1.
        @param i The number of the array position to be accessed, starts at 0.
        @return A constant reference to a Type parameter object stored in the array.
    */
    const Type & operator [](unsigned i) const;

    /** Inserts the given Type into the array at position i.
        @pre If the parameter i is greater than GetMaxSize() - 1, the array will be expanded to accommodate the addition to the array.
        @post If the parameter i is greater than GetSize() - 1, the parameter type will be placed at the value GetSize() in the array.
        @param i The number of the array position to be accessed, starts at 0.
        @param type Type variable to be inserted into the array.
        @return void
    */
    void InsertAt(unsigned i, const Type & type);

    /** Deletes a variable at position i in the array.
        @pre The parameter i should not be greater than GetSize() - 1.
        @param i The number of the array position to be accessed, starts at 0.
        @return void
    */
    void DeleteAt(unsigned i);

    /** Returns the used size of the array (not maximum size).
        @return The used size of the array (unsigned).
    */
    unsigned GetSize() const;

    /** Returns the maximum size of the array in memory.
        @return The maximum size of the array.
    */
    unsigned GetMaxSize() const;

    /** Adds a Type to the end of the array, allocates space if necessary.
        @param type a Type variable to be added to the end of the array.
        @return void
    */
    void Add(const Type & type);


private:
    ///Amount of elements stored in the array.
    unsigned size;
    ///Maximum size of array currently.
    unsigned maxSize;
    ///Variable size array.
    Type *array;

    /** Checks if array is full, or too empty, and de/allocates memory accordingly (helper method).
        @return void
    */
    void MemCheck();
};

template <class Type>
Vector<Type>::Vector(){
    size=0;
    maxSize = 10;
    array = new Type[10];
}

template <class Type>
Vector<Type>::Vector(const Vector<Type> & vec){
    size = vec.size;
    maxSize = vec.maxSize;
    array = new Type[maxSize];
    unsigned i;
    for(i=0;i<maxSize;i++){
        array[i] = vec.array[i];
    }
}

template <class Type>
Vector<Type>::~Vector(){
    delete [] array;
}

template <class Type>
const Vector<Type> & Vector<Type>::operator =(const Vector<Type> & vec){
    if(this!=&vec){
        delete [] array;
        size = vec.GetSize();
        maxSize = vec.GetMaxSize();
        array = new Type[maxSize];
        for(unsigned i = 0;i<maxSize;i++){
            array[i] = vec.array[i];
        }
    }

    return *this;
}

template <class Type>
const Type & Vector<Type>::operator[](unsigned i) const{
    if(i>=size){ //Can't access elements that don't exist.
        return array[size-1];
    }
    return array[i];
}

template <class Type>
void Vector<Type>::InsertAt(unsigned i, const Type & type){

    MemCheck(); //Creates space if needed.
    if(i>=size){ //Adds to the end of the array.
        array[size] = type;
    }else{
        for(unsigned j = size;j>i;j--){
            array[j] = array[j-1]; //Goes from the end of the array, shuffling elements up by one until it reaches insertion location.
        }
        array[i] = type; //Element inserted.
    }
    size++;
}

template <class Type>
void Vector<Type>::DeleteAt(unsigned i){

    if(i>=size) return; //Can't delete objects which don't exist.

    for(unsigned j=i;j<size-1;j++){
        array[j] = array[j+1];
    }
    size--;
    MemCheck();
}

template <class Type>
unsigned Vector<Type>::GetSize() const{
    return size;
}

template <class Type>
unsigned Vector<Type>::GetMaxSize() const{
    return maxSize;
}

template <class Type>
void Vector<Type>::Add(const Type & type){
    MemCheck();
    array[size] = type;
    size++;
}

template <class Type>
void Vector<Type>::MemCheck(){

    if(size==maxSize){

        maxSize = (int) (maxSize * 1.5);
        Type *newArray = new Type[maxSize]; // Increases new array size by 1.5 times previous.

        for(unsigned i = 0;i<size;i++){ //Copies old array into new.
            newArray[i] = array[i];
        }
        delete [] array;
        array = newArray;

    }else{
        if(size <= maxSize/1.5 && size>=10){
            maxSize = size;
            Type *newArray = new Type[size]; //Decreases array size by roughly 1.5.

            for(unsigned i = 0;i<size;i++){
                newArray[i] = array[i];
            }
            delete [] array;
            array = newArray;
        }
    }
}

#endif // VECTOR_H_INCLUDED
