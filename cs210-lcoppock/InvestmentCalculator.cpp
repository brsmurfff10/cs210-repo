#include "InvestmentCalculator.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

InvestmentCalculator::InvestmentCalculator(double t_initialInvestmentAmount,
    double t_monthlyDepositAmount,
    double t_annualInterestRatePercent,
    int t_numberOfYears)
    : m_initialInvestmentAmount(t_initialInvestmentAmount),
    m_monthlyDepositAmount(t_monthlyDepositAmount),
    m_annualInterestRatePercent(t_annualInterestRatePercent),
    m_numberOfYears(t_numberOfYears) {
    if (m_initialInvestmentAmount < 0.0) {
        throw std::invalid_argument("Initial investment amount must be >= 0.");
    }
    if (m_monthlyDepositAmount < 0.0) {
        throw std::invalid_argument("Monthly deposit amount must be >= 0.");
    }
    if (m_annualInterestRatePercent < 0.0) {
        throw std::invalid_argument("Annual interest rate must be >= 0.");
    }
    if (m_numberOfYears <= 0) {
        throw std::invalid_argument("Number of years must be > 0.");
    }
}

double InvestmentCalculator::RoundToCents(double t_value) {
    return std::round(t_value * 100.0) / 100.0;
}

void InvestmentCalculator::PrintReportHeader(const char* t_title) {
    std::cout << "\n" << t_title << "\n";
    std::cout << std::string(65, '=') << "\n";
    std::cout << std::left
        << std::setw(8) << "Year"
        << std::setw(24) << "Year End Balance"
        << "Year End Earned Interest"
        << "\n";
    std::cout << std::string(65, '-') << "\n";
}

void InvestmentCalculator::PrintReportWithoutMonthlyDeposits() const {
    PrintReportHeader("Balance and Interest Without Additional Monthly Deposits");
    CalculateAndPrintWithoutDeposits();
}

void InvestmentCalculator::PrintReportWithMonthlyDeposits() const {
    PrintReportHeader("Balance and Interest With Additional Monthly Deposits");
    CalculateAndPrintWithDeposits();
}

void InvestmentCalculator::CalculateAndPrintWithoutDeposits() const {
    const double yearlyRate = m_annualInterestRatePercent / 100.0;

    double balance = m_initialInvestmentAmount;

    for (int year = 1; year <= m_numberOfYears; ++year) {
        const double startingBalance = balance;

        const double interestEarned = startingBalance * yearlyRate;
        balance = startingBalance + interestEarned;

        const double roundedBalance = RoundToCents(balance);
        const double roundedInterest = RoundToCents(interestEarned);

        std::cout << std::left
            << std::setw(8) << year
            << "$" << std::setw(23) << std::fixed << std::setprecision(2) << roundedBalance
            << "$" << std::fixed << std::setprecision(2) << roundedInterest
            << "\n";

        balance = roundedBalance;
    }
}

void InvestmentCalculator::CalculateAndPrintWithDeposits() const {
    const double monthlyRate = (m_annualInterestRatePercent / 100.0) / 12.0;

    double balance = m_initialInvestmentAmount;

    for (int year = 1; year <= m_numberOfYears; ++year) {
        double interestEarnedThisYear = 0.0;

        for (int month = 1; month <= 12; ++month) {
            balance += m_monthlyDepositAmount;

            const double monthlyInterest = balance * monthlyRate;
            balance += monthlyInterest;
            interestEarnedThisYear += monthlyInterest;
        }

        const double roundedBalance = RoundToCents(balance);
        const double roundedInterestYear = RoundToCents(interestEarnedThisYear);

        std::cout << std::left
            << std::setw(8) << year
            << "$" << std::setw(23) << std::fixed << std::setprecision(2) << roundedBalance
            << "$" << std::fixed << std::setprecision(2) << roundedInterestYear
            << "\n";

        balance = roundedBalance;
    }
}
