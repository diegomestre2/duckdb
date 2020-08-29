#include "duckdb/planner/expression/bound_unnest_expression.hpp"

#include "duckdb/common/types/hash.hpp"
#include "duckdb/common/string_util.hpp"

namespace duckdb {
using namespace std;

BoundUnnestExpression::BoundUnnestExpression(LogicalType return_type)
    : Expression(ExpressionType::BOUND_UNNEST, ExpressionClass::BOUND_UNNEST, move(return_type)) {
}

bool BoundUnnestExpression::IsFoldable() const {
	return false;
}

string BoundUnnestExpression::ToString() const {
	return "UNNEST(" + child->ToString() + ")";
}

hash_t BoundUnnestExpression::Hash() const {
	hash_t result = Expression::Hash();
	return CombineHash(result, duckdb::Hash("unnest"));
}

bool BoundUnnestExpression::Equals(const BaseExpression *other_) const {
	if (!Expression::Equals(other_)) {
		return false;
	}
	auto other = (BoundUnnestExpression *)other_;
	if (!Expression::Equals(child.get(), other->child.get())) {
		return false;
	}
	return true;
}

unique_ptr<Expression> BoundUnnestExpression::Copy() {
	auto copy = make_unique<BoundUnnestExpression>(return_type);
	copy->child = child->Copy();
	return move(copy);
}

} // namespace duckdb
