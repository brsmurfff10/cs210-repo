#ifndef INVESTMENTCALCULATOR_H_
#define INVESTMENTCALCULATOR_H_

#include <cstddef>

class InvestmentCalculator {
public:
    InvestmentCalculator(double t_initialInvestmentAmount,
        double t_monthlyDepositAmount,
        double t_annualInterestRatePercent,
        int t_numberOfYears);

    void PrintReportWithoutMonthlyDeposits() const;
    void PrintReportWithMonthlyDeposits() const;

private:
    double m_initialInvestmentAmount;
    double m_monthlyDepositAmount;
    double m_annualInterestRatePercent;
    int m_numberOfYears;

    static double RoundToCents(double t_value);
    static void PrintReportHeader(const char* t_title);

    void CalculateAndPrintWithoutDeposits() const;
    void CalculateAndPrintWithDeposits() const;
};

#endif