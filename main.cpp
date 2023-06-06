
#include <iostream>

using namespace std;

void ShowBinaryForm( int Number, short unsigned int AmountOfRanks ) {
	for (int i = AmountOfRanks - 1; i >= 0; i--) {
		if (Number & (1 << i)) {
			cout << '1';
		}
		else {
			cout << '0';
		}
	}
}

inline int abs( int Number ) {
	return Number < 0 ? -Number : Number;
}

void ShowLetter( unsigned char Letter, short unsigned int AmountOfTimes ) {
	for ( size_t i = 0; i < AmountOfTimes; i++ ) {
		cout << Letter;
	}
}

int GetMeaningRankOfNumber( int Number ) {
	for ( int i = 31; i >= 0; i-- ) {
		if (Number & (1 << i)) {
			return i + 1;
		}
	}
	return 1;
}

int GetMaskOfNumber( int AmountRanks ) {
	int Number = 0;
	for (size_t i = 0; i < AmountRanks; i++) {
		Number |= (1 << i);
	}
	return Number;
}

int main() {
	int Dividend, Divisor;
	cout << "Enter dividend and divisor: ";
	cin >> Dividend >> Divisor;
	if (Divisor > Dividend) {
		cout << "divisor overs dividend!";
		return 0;
	}
	cout << "Task: \n" << Dividend << " / " << Divisor << " = ?\n";
	ShowBinaryForm(Dividend, 32);
	cout << "  /  ";
	ShowBinaryForm(Divisor, 32);
	cout << " = ?\n\n";

	bool NumberSign = (Dividend & (1 << 31)) ^ (Divisor & (1 << 31));
	Dividend = abs(Dividend);
	Divisor = abs(Divisor);
	short unsigned int MeaningRankOfDividend = GetMeaningRankOfNumber(Dividend);
	short unsigned int MeaningRankOfDivisor = GetMeaningRankOfNumber(Divisor);
	
	short int Subtrahend = GetMaskOfNumber(MeaningRankOfDivisor) << (MeaningRankOfDividend - MeaningRankOfDivisor);
	Subtrahend = (Dividend & Subtrahend) >> (MeaningRankOfDividend - MeaningRankOfDivisor);

	int Result = 0;
	for (int i = 0, NextRank = MeaningRankOfDividend - MeaningRankOfDivisor - 1; i < MeaningRankOfDividend; i++, NextRank--) {
		cout << "\n_ ";
		ShowBinaryForm(Subtrahend, MeaningRankOfDivisor + 1);
		cout << "\n  ";
		ShowBinaryForm(Divisor, MeaningRankOfDivisor + 1);
		cout << "\n  ";
		ShowLetter('-', MeaningRankOfDivisor + 1);
		cout << "\n  ";
		
		Subtrahend -= Divisor;
		ShowBinaryForm(Subtrahend, MeaningRankOfDivisor + 1);
		if (Subtrahend < 0) {
			Subtrahend += Divisor;
			Result <<= 1;
		} else {
			Result <<= 1;
			Result |= 1;
		}
		
		cout << "\n\nResult: ";
		ShowBinaryForm(Result, i + 1);
		cout << "\n\n";
		
		Subtrahend <<= 1;
		Subtrahend &= ~(1 << MeaningRankOfDivisor + 1);
		Subtrahend |= (Dividend & (1 << NextRank));
		if (NextRank < 0 ) {
			break;
		}
	}
	if (NumberSign) {
		Result = ~(Result) + 1;
	}
	cout << "Result:\n(Decimal) " << Result << "\n(Binary)";	
	ShowBinaryForm(Result, GetMeaningRankOfNumber(Result));
	char StopLetter = 0;
	cout << "\nPress letter...";
	cin >> StopLetter;
	return 0;
}