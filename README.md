# KSOM
[![Build Status](https://travis-ci.org/kagemiku/KSOM.svg?branch=master)](https://travis-ci.org/kagemiku/KSOM)

KSOM is a simple header for SOM.
You can use this very easily.

# Usage
#### 1. Include KSOM.hpp in your code.

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
|:-----: |:-----: |
| src | Array of input vector |
| map | Matrix of model vector |
| maxIterate | Number of iteration |
| alpha0 | Initial value of alpha |
| sigma0 | Initial value of sigma |
| randomly(**optional**) | Whether SOM randomly compute map or not (default value is **true**)|

#### 5. Call kg::KSOM::compute() method or kg::KSOM::computeOnes() method.

# Example
Please look at the source file **Main.cpp** in examples.

# Author
KAGE

# License
MIT License
