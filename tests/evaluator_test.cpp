#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../sources/node.hpp"
#include "../sources/ksom.hpp"
#include "../sources/evaluator.hpp"


class EvaluatorTest : public ::testing::Test {
protected:
    const int length;
    const int rows;
    const int cols;
    const int dimension;
    std::vector<kg::Node<int>> validSource1;
    std::vector<kg::Node<int>> validSource2;
    std::vector<kg::Node<int>> invalidSource1;
    std::vector<kg::Node<int>> invalidSource2;
    kg::Matrix<kg::Node<int>> validMap1;
    kg::Matrix<kg::Node<int>> validMap2;
    kg::Matrix<kg::Node<int>> invalidMap;

protected:
    EvaluatorTest()
        :length(2)
        ,rows(2)
        ,cols(2)
        ,dimension(1)
    {
    }

    ~EvaluatorTest()
    {
    }

    virtual auto SetUp() -> void
    {
        kg::Node<int> node1(dimension);
        kg::Node<int> node2(dimension);
        node1[0] = 0;
        node2[0] = 1;

        kg::Node<int> invalidNode(dimension + 1);

        validSource1    = std::vector<kg::Node<int>>(length);
        validSource1[0] = node1;
        validSource1[1] = node1;

        validSource2    = std::vector<kg::Node<int>>(length);
        validSource2[0] = node2;
        validSource2[1] = node2;

        invalidSource1      = std::vector<kg::Node<int>>(length);
        invalidSource1[0]   = node1;
        invalidSource1[1]   = invalidNode;

        invalidSource2      = std::vector<kg::Node<int>>(length);
        invalidSource2[0]   = invalidNode;
        invalidSource2[1]   = invalidNode;

        validMap1       = kg::Matrix<kg::Node<int>>(rows, std::vector<kg::Node<int>>(cols));
        validMap1[0][0] = node1;
        validMap1[0][1] = node1;
        validMap1[1][0] = node1;
        validMap1[1][1] = node1;

        validMap2       = kg::Matrix<kg::Node<int>>(rows, std::vector<kg::Node<int>>(cols));
        validMap2[0][0] = node1;
        validMap2[0][1] = node2;
        validMap2[1][0] = node2;
        validMap2[1][1] = node1;

        invalidMap          = kg::Matrix<kg::Node<int>>(rows, std::vector<kg::Node<int>>(cols));
        invalidMap[0][0]    = node1;
        invalidMap[0][1]    = node1;
        invalidMap[1][0]    = node1;
        invalidMap[1][1]    = invalidNode;
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

TEST_F(EvaluatorTest, CheckingArguments)
{
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(invalidSource1, validMap1), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(invalidSource2, validMap1), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(invalidSource1, validMap2), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(invalidSource2, validMap2), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(validSource1, invalidMap), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(validSource2, invalidMap), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(invalidSource1, invalidMap), std::string);
    ASSERT_THROW(kg::Evaluator<int>::evaluateMap(invalidSource2, invalidMap), std::string);

    ASSERT_NO_THROW(kg::Evaluator<int>::evaluateMap(validSource1, validMap1));
    ASSERT_NO_THROW(kg::Evaluator<int>::evaluateMap(validSource2, validMap1));
    ASSERT_NO_THROW(kg::Evaluator<int>::evaluateMap(validSource1, validMap2));
    ASSERT_NO_THROW(kg::Evaluator<int>::evaluateMap(validSource2, validMap2));
}

TEST_F(EvaluatorTest, EvaluationMap)
{
    ASSERT_DOUBLE_EQ(0.0, kg::Evaluator<int>::evaluateMap(validSource1, validMap1));
    ASSERT_DOUBLE_EQ(2.0, kg::Evaluator<int>::evaluateMap(validSource2, validMap1));

    ASSERT_DOUBLE_EQ(0.0, kg::Evaluator<int>::evaluateMap(validSource1, validMap2));
    ASSERT_DOUBLE_EQ(0.0, kg::Evaluator<int>::evaluateMap(validSource2, validMap2));
}

