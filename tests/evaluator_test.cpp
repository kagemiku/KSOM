#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../sources/node.hpp"
#include "../sources/ksom.hpp"
#include "../sources/evaluator.hpp"


class EvaluatorTest : public ::testing::Test {
protected:
    template <typename T>
    using Matrix = std::vector<std::vector<T>>;

    const int rows;
    const int cols;
    const int dimension;
    kg::Node<int> node1;
    kg::Node<int> node2;
    Matrix<kg::Node<int>> validMap;
    Matrix<kg::Node<int>> invalidMap;

protected:
    EvaluatorTest()
        :rows(2)
        ,cols(2)
        ,dimension(1)
    {
    }

    ~EvaluatorTest()
    {
    }

    virtual auto SetUp() -> void
    {
        node1 = kg::Node<int>(dimension);
        node2 = kg::Node<int>(dimension);
        node1[0] = 0;
        node2[0] = 1;

        validMap        = Matrix<kg::Node<int>>(rows, std::vector<kg::Node<int>>(cols));
        validMap[0][0]  = node1;
        validMap[0][1]  = node1;
        validMap[1][0]  = node1;
        validMap[1][1]  = node1;

        invalidMap          = Matrix<kg::Node<int>>(rows, std::vector<kg::Node<int>>(cols));
        invalidMap[0][0]    = node1;
        invalidMap[0][1]    = node1;
        invalidMap[1][0]    = node1;
        invalidMap[1][1]    = kg::Node<int>(dimension + 1);
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

TEST_F(EvaluatorTest, Initialization)
{
    ASSERT_THROW(std::move(kg::Evaluator<int>(invalidMap)), std::string);

    Matrix<kg::Node<int>> invalidMap2(rows);
    invalidMap2[0]      = std::vector<kg::Node<int>>(cols);
    invalidMap2[1]      = std::vector<kg::Node<int>>(cols - 1);
    invalidMap2[0][0]   = node1;
    invalidMap2[0][1]   = node1;
    invalidMap2[1][0]   = node1;
    ASSERT_THROW(std::move(kg::Evaluator<int>(invalidMap2)), std::string);

    auto invalidMap3    = Matrix<kg::Node<int>>(rows, std::vector<kg::Node<int>>(cols));
    invalidMap3[0][0]   = node1;
    invalidMap3[0][1]   = node1;
    invalidMap3[1][0]   = node1;
    invalidMap3[1][1]   = kg::Node<int>(dimension + 1);
    ASSERT_THROW(std::move(kg::Evaluator<int>(invalidMap3)), std::string);

    ASSERT_NO_THROW(std::move(kg::Evaluator<int>(validMap)));
}

TEST_F(EvaluatorTest, EvaluationMap)
{
    kg::Evaluator<int> evaluator1(validMap);
    ASSERT_DOUBLE_EQ(0.0, evaluator1.evaluateMap());

    Matrix<kg::Node<int>> validMap2(rows, std::vector<kg::Node<int>>(cols));
    validMap2[0][0] = node1;
    validMap2[0][1] = node2;
    validMap2[1][0] = node2;
    validMap2[1][1] = node1;

    kg::Evaluator<int> evaluator2(validMap2);
    ASSERT_DOUBLE_EQ(4.0, evaluator2.evaluateMap());
}

