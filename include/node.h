#pragma once

#include "date.h"

#include <string>
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& event) const override;
private:
    bool eval_res_;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    Comparison cmp_;
    Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const string& event);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    Comparison cmp_;
    string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    LogicalOperation op_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};

template <typename T>
bool EvalComparison(Comparison cmp, T lhs, T rhs);