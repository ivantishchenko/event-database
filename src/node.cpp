#include "node.h"

EmptyNode::EmptyNode() : eval_res_(true) {}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    // HACK: to get rid of not used var:
    (void)date;
    (void)event;
    return eval_res_;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) 
    : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    // HACK: to get rid of not used var:
    (void)event;
    return EvalComparison(cmp_, date, date_);
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event) 
    : cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    // HACK: to get rid of not used var:
    (void)date;
    return EvalComparison(cmp_, event, event_);
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) 
    : op_(op), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (op_) {
        case LogicalOperation::And:
            return left_->Evaluate(date, event) && right_->Evaluate(date, event);
        case LogicalOperation::Or:
            return left_->Evaluate(date, event) || right_->Evaluate(date, event);
        default:
            throw invalid_argument("Not supported logical operation");
    }
}

template <typename T>
bool EvalComparison(Comparison cmp, T lhs, T rhs) {
    switch (cmp) {
        case Comparison::Less:
            return lhs < rhs;
        case Comparison::LessOrEqual:
            return lhs <= rhs;
        case Comparison::Greater:
            return lhs > rhs;
        case Comparison::GreaterOrEqual:
            return lhs >= rhs;
        case Comparison::Equal:
            return lhs == rhs;
        case Comparison::NotEqual:
            return lhs != rhs;
        default:
            throw invalid_argument("Not supported comparison");
    }
}