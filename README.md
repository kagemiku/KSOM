# KSOM
KSOM is a simple header for SOM.  
You can use this very easily.

# Usage
1. Include KSOM.h in your code.  

2. Create array of input vector.  
For example, if you want to use some input vector with 3-dimension...   
```cpp
const int length = 100;
const int dimension = 3;
Node<int>* src = new Node<int>[length];
for (int i = 0; i < length; i++ ) {
    src[i] = Node<int>(dimension);
    for ( int j = 0; j < dimension; j++ ) {
        src[i][j] = some_integer_value;
    }
}
```

3. Create matrix of model vector.   
In mane cases, we use input vecor at random to initialize matrix of model vector.  

4. Create instance of KSOM.  
KSOM's constructor requires the following values.    

| name | description |
|:-----: |:----- |
| src | array of input vector |
| length | length of src |
| map | matrix of model vector |
| rows | number of row in map |
| cols | number of column in map |
| maxIterate | number of iteration |
| alpha0 | initial value of alpha |
| sigma0 | initial value of sigma |

5. Call KSOM::calcIterate() method.  

# Example
Please look at the source file **Main.cpp** in examples.  

# Upcoming update
* Interface change.  

* Writing README.md more properly.  
    
# License
MIT License  
