#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../sources/node.h"
#include "../sources/ksom.h"


class KSOMTest : public ::testing::Test {
protected:
    const size_t validDimension;
    const size_t invalidDimension;
    const size_t validSourceLength;
    const size_t invalidSourceLength;
    std::vector<kg::Node<int>> validSource;
    std::vector<kg::Node<int>> invalidSource;


protected:
    KSOMTest()
        :validDimension(2)
        ,invalidDimension(3)
        ,validSourceLength(2)
        ,invalidSourceLength(2)
    {
    }

    ~KSOMTest()
    {
    }

    virtual auto SetUp() -> void
    {
        validSource = std::vector<kg::Node<int>>(validSourceLength);
        validSource[0] = kg::Node<int>(validDimension);
        validSource[1] = kg::Node<int>(validDimension);

        invalidSource = std::vector<kg::Node<int>>(invalidSourceLength);
        invalidSource[0] = kg::Node<int>(validDimension);
        invalidSource[1] = kg::Node<int>(invalidDimension);
    }

    virtual auto TearDown() -> void
    {
    }

    static auto SetUpTestCase() -> void
    {
    }

    static auto TearDownTestCase() -> void
    {
    }
};

TEST_F(KSOMTest, Initialization1)
{
    std::vector<std::vector<kg::Node<int>>> invalidMap(1, invalidSource);

    ASSERT_THROW(kg::KSOM<int>(invalidSource, invalidMap, 1, 1.0, 1.0), std::string);
}

TEST_F(KSOMTest, Initialization2)
{
    std::vector<kg::Node<int>> validSource2(validSource);
    validSource2.emplace_back(validDimension);

    std::vector<std::vector<kg::Node<int>>> invalidMap(2);
    invalidMap[0] = validSource;
    invalidMap[1] = validSource2;

    ASSERT_THROW(kg::KSOM<int>(validSource, invalidMap, 1, 1.0, 1.0), std::string);
}

TEST_F(KSOMTest, Initialization3)
{
    std::vector<std::vector<kg::Node<int>>> invalidMap(1, validSource);
    invalidMap[0][0] = kg::Node<int>(invalidDimension);

    ASSERT_THROW(kg::KSOM<int>(validSource, invalidMap, 1, 1.0, 1.0), std::string);
}

TEST_F(KSOMTest, Computation)
{
    std::vector<kg::Node<int>> validSource2(validSource);

    std::vector<std::vector<kg::Node<int>>> validMap(2);
    validMap[0] = validSource;
    validMap[1] = validSource2;
    auto ksom = kg::KSOM<int>(validSource, validMap, 1, 1.0, 1.0);

    ASSERT_TRUE(ksom.computeOnes());
    ASSERT_FALSE(ksom.computeOnes());
}

TEST_F(KSOMTest, GettingTime)
{
    std::vector<kg::Node<int>> validSource2(validSource);

    std::vector<std::vector<kg::Node<int>>> validMap(2);
    validMap[0] = validSource;
    validMap[1] = validSource2;
    auto ksom = kg::KSOM<int>(validSource, validMap, 1, 1.0, 1.0);
    ksom.computeOnes();

    ASSERT_EQ(1, ksom.time());
}

TEST_F(KSOMTest, GettingMap)
{
    std::vector<kg::Node<int>> validSource2(validSource);

    std::vector<std::vector<kg::Node<int>>> validMap(2);
    validMap[0] = validSource;
    validMap[1] = validSource2;
    auto ksom = kg::KSOM<int>(validSource, validMap, 1, 1.0, 1.0);

    auto clonedMap = ksom.map();
    for ( auto r = 0; r < clonedMap.size(); r++ ) {
        for ( auto c = 0; c < clonedMap[r].size(); c++ ) {
            for ( auto i = 0; i < clonedMap[r][c].size(); i++ ) {
                ASSERT_EQ(validMap[r][c][i], clonedMap[r][c][i]);
            }
        }
    }
}

