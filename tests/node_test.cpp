#include <gtest/gtest.h>
#include <string>
#include "../sources/node.hpp"


class NodeTest : public ::testing::Test {
protected:
    const size_t size;
    const size_t invalidSize;
    kg::Node<int> node1;
    kg::Node<int> node2;
    kg::Node<int> invalidNode;

protected:
    NodeTest()
        :size(3)
        ,invalidSize(2)
    {
    }

    ~NodeTest()
    {
    }

    virtual auto SetUp() -> void
    {
        node1 = kg::Node<int>(size);
        node1[0] = 1;
        node1[1] = 10;
        node1[2] = 100;

        node2 = kg::Node<int>(size);
        node2[0] = 2;
        node2[1] = 20;
        node2[2] = 200;

        invalidNode = kg::Node<int>(invalidSize);
        invalidNode[0] = 3;
        invalidNode[1] = 30;
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


TEST_F(NodeTest, Initialization)
{
    kg::Node<int> node(size);
    ASSERT_EQ(size, node.size());
}

TEST_F(NodeTest, Copying)
{
    kg::Node<int> node(node1);
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i], node[i]);
    }
}

TEST_F(NodeTest, 1OperatorPlus)
{
    kg::Node<int> node(+node1);
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i], node[i]);
    }
}

TEST_F(NodeTest, 1OperatorMinus)
{
    kg::Node<int> node(-node1);
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(-node1[i], node[i]);
    }
}

TEST_F(NodeTest, AddingNode)
{
    kg::Node<int> node = node1 + node2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] + node2[i], node[i]);
    }

    ASSERT_THROW(node1 + invalidNode, std::string);
}

TEST_F(NodeTest, AddingValue)
{
    constexpr auto val = 10;
    kg::Node<int> node = node1 + val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] + val, node[i]);
    }
}

TEST_F(NodeTest, SubtractionNode)
{
    kg::Node<int> node = node1 - node2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] - node2[i], node[i]);
    }

    ASSERT_THROW(node1 - invalidNode, std::string);
}

TEST_F(NodeTest, SubtractionValue)
{
    constexpr auto val = 10;
    kg::Node<int> node = node1 - val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] - val, node[i]);
    }
}

TEST_F(NodeTest, MultiplicationNode)
{
    kg::Node<int> node = node1 * node2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] * node2[i], node[i]);
    }

    ASSERT_THROW(node1 * invalidNode, std::string);
}

TEST_F(NodeTest, MultiplicationValue)
{
    constexpr auto val = 10;
    kg::Node<int> node = node1 * val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] * val, node[i]);
    }
}

TEST_F(NodeTest, DivisionNode)
{
    constexpr auto dSize = 3;
    kg::Node<double> dNode1(dSize);
    dNode1[0] = 1.0;
    dNode1[1] = 10.0;
    dNode1[2] = 100.0;

    kg::Node<double> dNode2(dSize);
    dNode2[0] = 2.0;
    dNode2[1] = 20.0;
    dNode2[2] = 200.0;

    kg::Node<double> dNode = dNode1 / dNode2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_DOUBLE_EQ(dNode1[i] / dNode2[i], dNode[i]);
    }

    constexpr auto dInvalidSize = 2;
    kg::Node<double> dInvalidNode(dInvalidSize);
    dInvalidNode[0] = 3.0;
    dInvalidNode[1] = 30.0;
    ASSERT_THROW(dNode1 / dInvalidNode, std::string);

    kg::Node<double> dNode3(dSize);
    dNode3[0] = 0.0;
    dNode3[1] = 30.0;
    dNode3[2] = 300.0;
    ASSERT_THROW(dNode1 / dNode3, std::string);
}

TEST_F(NodeTest, DivisionValue)
{
    constexpr auto dSize = 3;
    kg::Node<double> dNode1(dSize);
    dNode1[0] = 1.0;
    dNode1[1] = 10.0;
    dNode1[2] = 100.0;

    constexpr auto val = 10.0;
    kg::Node<double> dNode = dNode1 / val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_DOUBLE_EQ(dNode1[i] / val, dNode[i]);
    }

    ASSERT_THROW(dNode1 / 0.0, std::string);
}

TEST_F(NodeTest, Assignment)
{
    kg::Node<int> node;
    node = node1;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i], node[i]);
    }
}

TEST_F(NodeTest, AddingAndAssignmentNode)
{
    kg::Node<int> node(node1);
    node += node2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] + node2[i], node[i]);
    }

    ASSERT_THROW(node1 += invalidNode, std::string);
}

TEST_F(NodeTest, AddingAndAssignmentValue)
{
    constexpr auto val = 10;
    kg::Node<int> node(node1);
    node += val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] + val, node[i]);
    }
}

TEST_F(NodeTest, SubtractionAndAssignmentNode)
{
    kg::Node<int> node(node1);
    node -= node2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] - node2[i], node[i]);
    }

    ASSERT_THROW(node1 -= invalidNode, std::string);
}

TEST_F(NodeTest, SubtractionAndAssignmentValue)
{
    constexpr auto val = 10;
    kg::Node<int> node(node1);
    node -= val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] - val, node[i]);
    }
}

TEST_F(NodeTest, MultiplicationAndAssignmentNode)
{
    kg::Node<int> node(node1);
    node *= node2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] * node2[i], node[i]);
    }

    ASSERT_THROW(node1 *= invalidNode, std::string);
}

TEST_F(NodeTest, MultiplicationAndAssignmentValue)
{
    constexpr auto val = 10;
    kg::Node<int> node(node1);
    node *= val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_EQ(node1[i] * val, node[i]);
    }
}

TEST_F(NodeTest, DivisionAndAssignmentNode)
{
    constexpr auto dSize = 3;
    kg::Node<double> dNode1(dSize);
    dNode1[0] = 1.0;
    dNode1[1] = 10.0;
    dNode1[2] = 100.0;

    kg::Node<double> dNode2(dSize);
    dNode2[0] = 2.0;
    dNode2[1] = 20.0;
    dNode2[2] = 200.0;

    kg::Node<double> dNode(dNode1);
    dNode /= dNode2;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_DOUBLE_EQ(dNode1[i] / dNode2[i], dNode[i]);
    }

    constexpr auto dInvalidSize = 2;
    kg::Node<double> dInvalidNode(dInvalidSize);
    dInvalidNode[0] = 3.0;
    dInvalidNode[1] = 30.0;
    ASSERT_THROW(dNode1 /= dInvalidNode, std::string);

    kg::Node<double> dNode3(dSize);
    dNode3[0] = 0.0;
    dNode3[1] = 30.0;
    dNode3[2] = 300.0;
    ASSERT_THROW(dNode1 /= dNode3, std::string);
}

TEST_F(NodeTest, DivisionAndAssignmentValue)
{
    constexpr auto dSize = 3;
    kg::Node<double> dNode1(dSize);
    dNode1[0] = 1.0;
    dNode1[1] = 10.0;
    dNode1[2] = 100.0;

    constexpr auto val = 10.0;
    kg::Node<double> dNode(dNode1);
    dNode /= val;
    for ( auto i = 0; i < size; i++ ) {
        ASSERT_DOUBLE_EQ(dNode1[i] / val, dNode[i]);
    }
}

TEST_F(NodeTest, OperatorBrackets)
{
    constexpr auto val = 10;
    kg::Node<int> node(node1);
    node[0] = val;
    ASSERT_EQ(val, node[0]);

    ASSERT_THROW(node[size], std::string);
}

TEST_F(NodeTest, SettingAndGettingElement)
{
    constexpr auto val = 10;
    constexpr auto idx = 0;
    kg::Node<int> node(node1);
    node.setElem(val, idx);
    ASSERT_EQ(val, node.elem(idx));

    ASSERT_THROW(node.setElem(val, size), std::string);
    ASSERT_THROW(node.elem(size), std::string);

}

TEST_F(NodeTest, GettingSize)
{
    ASSERT_EQ(size, node1.size());
}

