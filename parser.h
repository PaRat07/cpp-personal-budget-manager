#pragma once

#include <iostream>
#include "date.h"
#include "budget_manager.h"


void ParseAndProcessQuery(BudgetManager& manager, std::string_view line);