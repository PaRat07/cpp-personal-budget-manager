// разработайте менеджер личного бюджета самостоятельно
#include "budget_manager.h"

EarningQuery::EarningQuery(Date b, Date e, double inc)
        : ChangingQuery(b, e)
        , income(inc)
{}

Query::Query(Date b, Date e)
        : beg(b)
        , end(e)
{}

double BudgetManager::ComputeIncome(ComputingIncome query) const {
    int time_until_beg = Date::ComputeDistance(START_DATE, query.beg);
    int time_until_end = std::min(Date::ComputeDistance(START_DATE, query.end), static_cast<int>(days_.size() - 1));
    double sum = 0.0;
    for (int i = time_until_beg; i <= time_until_end; ++i) {
        sum += days_[i].income - days_[i].expense;
    }
    return sum;
}

void BudgetManager::Earn(EarningQuery query) {
    int time_until_beg = Date::ComputeDistance(START_DATE, query.beg);
    int time_until_end = Date::ComputeDistance(START_DATE, query.end);
    if (days_.size() <= time_until_end) {
        days_.resize(time_until_end + 1);
    }
    double inc_per_day = query.income / (time_until_end - time_until_beg + 1);
    for (int i = time_until_beg; i <= time_until_end; ++i) {
        days_[i].income += inc_per_day;
    }
}

void BudgetManager::PayTax(PayingTaxQuery query) {
    int time_until_beg = Date::ComputeDistance(START_DATE, query.beg);
    int time_until_end = std::min(Date::ComputeDistance(START_DATE, query.end), static_cast<int>(days_.size() - 1));
    for (int i = time_until_beg; i <= time_until_end; ++i) {
        days_[i].income *= 1 - query.percent / 100.;
    }
}

void BudgetManager::Spend(SpendingQuery query) {
    int time_until_beg = Date::ComputeDistance(START_DATE, query.beg);
    int time_until_end = Date::ComputeDistance(START_DATE, query.end);
    if (days_.size() <= time_until_end) {
        days_.resize(time_until_end + 1);
    }
    double exp_per_day = query.expense / (time_until_end - time_until_beg + 1);
    for (int i = time_until_beg; i <= time_until_end; ++i) {
        days_[i].expense += exp_per_day;
    }
}

PayingTaxQuery::PayingTaxQuery(Date b, Date e, int perc)
        : ChangingQuery(b, e)
        , percent(perc)
{}
