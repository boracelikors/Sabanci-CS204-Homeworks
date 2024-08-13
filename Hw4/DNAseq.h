#ifndef DNASEQ_H
#define DNASEQ_H

#include <iostream>

using namespace std;

enum Nucleotide { A, C, G, T };

class DNAseq {
private:
    int length;
    Nucleotide* sequence;

public:
    DNAseq();
    DNAseq(const string& nucleotides);
    DNAseq(const DNAseq& other);
    ~DNAseq();
    const Nucleotide* getSequence() const;
    int getLength() const;
    DNAseq& operator=(const DNAseq& rhs);
    DNAseq operator!() const;
    bool operator<=(const DNAseq& rhs) const;
    DNAseq operator*(int n);
    int operator%(Nucleotide n) const;
    DNAseq& operator+=(const DNAseq& rhs);
};

DNAseq operator+(const DNAseq& lhs, const DNAseq& rhs);
DNAseq operator+(Nucleotide n, const DNAseq& rhs);
DNAseq operator-(const DNAseq& lhs, const DNAseq& rhs);
ostream& operator<<(ostream& os, const DNAseq& obj);

#endif // DNASEQ_H
