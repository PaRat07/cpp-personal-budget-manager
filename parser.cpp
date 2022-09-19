#include "parser.h"

void ParseAndProcessQuery(BudgetManager &manager, std::string_view line) {
    std::string_view query_type = line.substr(0, line.find_first_of(' '));
    line.remove_prefix(query_type.size() + 1);
    if (query_type == "ComputeIncome") {
        Date beg, end;
        beg = Date::FromString(line.substr(0, line.find_first_of(' ')));
        end = Date::FromString(line.substr(line.find_first_of(' ') + 1, line.find_last_of(' ') - line.find_first_of(' ') - 1));
        ComputingIncome q{beg, end};
        std::cout << manager.ComputeIncome(q) << std::endl;
    }
    else if (query_type == "Earn") {
        Date beg, end;
        beg = Date::FromString(line.substr(0, line.find_first_of(' ')));
        end = Date::FromString(line.substr(line.find_first_of(' ') + 1, line.find_last_of(' ') - line.find_first_of(' ') - 1));
        double income = std::stod(std::string(line.substr(line.find_last_of(' ') + 1, line.size() - line.find_last_of(' ') - 1)));
        EarningQuery q{beg, end, income};
        manager.Earn(q);
    }
    else {
        Date beg, end;
        beg = Date::FromString(line.substr(0, line.find_first_of(' ')));
        end = Date::FromString(line.substr(line.find_first_of(' ') + 1, line.find_last_of(' ') - line.find_first_of(' ') - 1));
        PayingTaxQuery q{beg, end};
        manager.PayTax(q);
    }
}
