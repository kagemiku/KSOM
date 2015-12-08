# KSOM
KSOM is a simple header for SOM.  
You can use this very easily.

# Usage
#### 1. Include KSOM.h in your code.  

#### 2. Create array of input vector.  
For example, if you want to use some input vector with 3-dimension...   
```cpp
const int length = 100;
const int dimension = 3;
vector<Node<int>> src(length, kg::Node<int>(dimension));
```

#### 3. Create matrix of model vector.   
In mane cases, we use input vecor at random to initialize matrix of model vector.  

#### 4. Create instance of KSOM.  
KSOM's constructor requires the following values.    

| name | description |
|:-----: |:----- |
| src | array of input vector |
| map | matrix of model vector |
| maxIterate | number of iteration |
| alpha0 | initial value of alpha |
| sigma0 | initial value of sigma |

#### 5. Call kg::KSOM::compute() method or kg::KSOM::computeOnes() method.

# Example
Please look at the source file **Main.cpp** in examples.

# Author
KAGE
    
# License
MIT License  
