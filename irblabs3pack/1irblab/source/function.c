

errorCodes decimalToOther(int number, int power, int* result) {
    int countOfConquctions = 0;
    int mask = (1 << power) - 1;
    while (number > 0) {
        result[countOfConquctions] = number & mask;
        number = number >> power;
        countOfConquctions++;
    }

}