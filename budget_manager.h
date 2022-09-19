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
    PayingTaxQuery(Date b, Date e, int perc);

    int percent;
};

class SpendingQuery : public ChangingQuery {
public:
    SpendingQuery(Date b, Date e, double exp)
        : ChangingQuery(b, e)
        , expense(exp)
    {}

    double expense;
};

struct Day {
    Day() = default;
    explicit Day(double inc, double exp)
        : income(inc)
        , expense(exp)
    {}

    double income;
    double expense;
};

class BudgetManager {
public:
    inline static const Date START_DATE{2000, 1, 1};
    inline static const Date END_DATE{2100, 1, 1};

    double ComputeIncome(ComputingIncome query) const;

    void Earn(EarningQuery query);

    void PayTax(PayingTaxQuery query);

    void Spend(SpendingQuery query);
private:
    std::vector<Day> days_;
};
