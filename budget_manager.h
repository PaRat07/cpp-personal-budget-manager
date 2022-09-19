#pragma once

#include <algorithm>
#include <numeric>

#include "date.h"

class Query {
public:
    Date beg;
    Date end;
    Query(Date b, Date e);
};

class ReadingQuery : public Query {
public:
    using Query::Query;
};

class ChangingQuery : public Query {
public:
    using Query::Query;
};

class ComputingIncome : public ReadingQuery {
public:
    using ReadingQuery::ReadingQuery;
};

class EarningQuery: public ChangingQuery {
public:
    EarningQuery(Date b, Date e, double inc);
    double income;
};

class PayingTaxQuery : public ChangingQuery {
public:
    using ChangingQuery::ChangingQuery;
};

struct Day {
    Day() = default;
    explicit Day(double inc)
        : income(inc)
    {}

    double income;
};

class BudgetManager {
public:
    inline static const Date START_DATE{2000, 1, 1};
    inline static const Date END_DATE{2100, 1, 1};

    double ComputeIncome(ComputingIncome query);

    void Earn(EarningQuery query);

    void PayTax(PayingTaxQuery query);
private:
    std::vector<Day> days_;
};
