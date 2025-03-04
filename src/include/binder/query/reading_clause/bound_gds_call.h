#pragma once

#include "binder/query/reading_clause/bound_reading_clause.h"
#include "function/gds_function.h"

namespace kuzu {
namespace binder {

struct BoundGDSCallInfo {
    function::GDSFunction func;
    expression_vector outExprs;

    BoundGDSCallInfo(function::GDSFunction func, expression_vector outExprs)
        : func{std::move(func)}, outExprs{std::move(outExprs)} {}
    EXPLICIT_COPY_DEFAULT_MOVE(BoundGDSCallInfo);

    const function::GDSAlgorithm* getGDS() const;
    const function::GDSBindData* getBindData() const;

private:
    BoundGDSCallInfo(const BoundGDSCallInfo& other)
        : func{other.func.copy()}, outExprs{other.outExprs} {}
};

class BoundGDSCall final : public BoundReadingClause {
    static constexpr common::ClauseType clauseType_ = common::ClauseType::GDS_CALL;

public:
    explicit BoundGDSCall(BoundGDSCallInfo info)
        : BoundReadingClause{clauseType_}, info{std::move(info)} {}

    const BoundGDSCallInfo& getInfo() const { return info; }

private:
    BoundGDSCallInfo info;
};

} // namespace binder
} // namespace kuzu
