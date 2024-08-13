
#include "DNAseq.h"
#include "string"


// Default constructor
DNAseq::DNAseq() {
    length = 0;
    sequence = nullptr;
}

// Parametric constructor
DNAseq::DNAseq(const string& s) {
    length = s.length();
    if(length == 0){
        sequence = nullptr;
    }else{
        sequence = new Nucleotide[length];
        for(int i =0;i < length; i++){
            char c = s[i];
            if(c == 'A') {
                sequence[i] = A;

            }
            else if(c == 'C') {
                sequence[i] = C;

            }
            else if(c == 'G') {
                sequence[i] = G;

            }
            else if(c == 'T') {
                sequence[i] = T;

            }

        }
    }


}

// Deep copy constructor
DNAseq::DNAseq(const DNAseq& copy) {
    length = copy.length;
    sequence = new Nucleotide[length];
    for (int i = 0; i < length; ++i) {
        sequence[i] = copy.sequence[i];
    }
}

// Destructor
DNAseq::~DNAseq() {
    delete[] sequence;
}

// Accessor functions for sequence and lenght
// Returns the length of the DNA sequence
int DNAseq::getLength() const {
    return length;
}

// Returns a constant pointer to the DNA sequence
const Nucleotide* DNAseq::getSequence() const {
    return sequence;
}

// Assignment operator
DNAseq& DNAseq::operator=(const DNAseq& rhs) {
    if (this != &rhs) { // check self-assignment

        delete[] sequence; // delete lhs



        // create new lhs, also i could use deep copy constructor here, like lecture slides.
        // however it would be inefficient, because same block of code would run with extra constructor call

        length = rhs.length;
        sequence = new Nucleotide[length];
        for (int i = 0; i < length; ++i) {
            sequence[i] = rhs.sequence[i];
        }
    }
    return *this;
}

int DNAseq::operator%(Nucleotide n) const {
    int count = 0;
    for (int i = 0; i < this->length; ++i) { // basic counting here
        if (this->sequence[i] == n) {
            ++count;
        }
    }
    return count;
}

// Complement operator
DNAseq DNAseq::operator!() const {
    DNAseq ters;

    ters.sequence = new Nucleotide[length];
    ters.length = length;

// I convert nucleotides to their complement with this loop
    for (int i = 0; i < length; ++i) {
        if (sequence[i] == A) {
            ters.sequence[i] = T;
        } else if (sequence[i] == T) {
            ters.sequence[i] = A;
        } else if (sequence[i] == G) {
            ters.sequence[i] = C;
        } else if (sequence[i] == C) {
            ters.sequence[i] = G;
        }
    }

    return ters;
}

DNAseq DNAseq::operator*( int rhs) {
    if (rhs <= 0) {
        return DNAseq(); // returns an empty sequence by default constructor
    }
    int totalLength = this->length * rhs;
    DNAseq p;
    p.sequence = new Nucleotide[totalLength];
    p.length = totalLength;
    for (int i = 0; i < rhs; ++i) {
        for (int j = 0; j < this->length; ++j) { // create same sequence of DNA, rhs times
            p.sequence[i * this->length + j] = this->sequence[j];
        }
    }
    return p;
}

// <= operator
bool DNAseq::operator<=(const DNAseq& rhs) const {

    if (this->length == rhs.length) { // if they have same size, easier to check
        for (int i = 0; i < this->length; i++) {
            if (this->sequence[i] != rhs.sequence[i]) {
                return false;
            }
        }
        return true;
    }else{ // if they have different sizes, we have to iterate through both lhs and rhs at the same time.
        int j = 0;

        for (int i = 0; i < rhs.length && j < this->length; i++) {
            if (this->sequence[j] == rhs.sequence[i]) {
                j++;
            }
        }

        bool is_equal = j == this->length; // if these numbers are equal, we got that

        return is_equal;
    }



}

// Helper function, converts nucleotide to char
char nucleotideToChar(Nucleotide n) {
    char result;
    if (n == A) {
        result = 'A';
    } else if (n == C) {
        result = 'C';
    } else if (n == G) {
        result = 'G';
    } else if (n == T) {
        result = 'T';
    }
    return result;
}


// Another helper function, nucleotide to string
string nucleotideToString(const Nucleotide* nucleotides, int length) {
    string result;
    for (int i = 0; i < length; ++i) {
        result += nucleotideToChar(nucleotides[i]);
    }
    return result;
}

// Addition for two DNA's
DNAseq operator+(const DNAseq& lhs, const DNAseq& rhs) {
    if (rhs.getLength() == 0) return lhs;
    if (lhs.getLength() == 0) return rhs;

    // I converted sequences into string by helper function, since it is easier to manipulate for me
    string lhsStr = nucleotideToString(lhs.getSequence(), lhs.getLength());
    string rhsStr = nucleotideToString(rhs.getSequence(), rhs.getLength());
    int index = lhsStr.find(rhsStr[0]);

    if (index != string::npos) {
        // this is case a
        lhsStr.insert(index + 1, rhsStr);
    } else {
        // and this is case b
        lhsStr += rhsStr;
    }
    // when my operations done, convert string to DNA again by parametric constructor
    return DNAseq(lhsStr); //
}

// Addition for nucleotide to DNA
DNAseq operator+(Nucleotide n, const DNAseq& rhs) {
    // likewise previous + implementation, i converted that into string to manipulate easier
    string rhsStr = nucleotideToString(rhs.getSequence(), rhs.getLength());
    string combined = nucleotideToChar(n) + rhsStr; // add nucleotide to beginning
    return DNAseq(combined); // convert to DNA again
}

DNAseq& DNAseq::operator+=(const DNAseq& rhs) {
    if (rhs.getLength() == 0) return *this;  // If rhs is empty, return lhs without any change

    int index = -1;
    for (int i = 0; (i < this->getLength()) && (index == -1); ++i) {
        if (this->getSequence()[i] == rhs.getSequence()[0]) {
            index = i + 1;  // insert after the found nucleotide
        }
    }

    int newLength = this->getLength() + rhs.getLength();
    Nucleotide* newSequence = new Nucleotide[newLength];

    if (index != -1) {  // find the position
        for (int i = 0; i < index; ++i) {
            newSequence[i] = this->getSequence()[i];  // copy lhs to index
        }
        for (int j = 0; j < rhs.getLength(); ++j) {
            newSequence[index + j] = rhs.getSequence()[j];  // Insert rhs
        }
        for (int k = index; k < this->getLength(); ++k) {
            newSequence[rhs.getLength() + k] = this->getSequence()[k];  // copy the rest of lhs
        }
    } else {  // Not found, simply append
        for (int i = 0; i < this->getLength(); ++i) {
            newSequence[i] = this->getSequence()[i];  // Copy lhs
        }
        for (int j = 0; j < rhs.getLength(); ++j) {
            newSequence[this->getLength() + j] = rhs.getSequence()[j];  // Append rhs
        }
    }

    // delete old sequence
    delete[] this->sequence;

    // create new one
    this->sequence = newSequence;
    this->length = newLength;

    return *this;
}

// removes the first occurrence of rhs from lhs
DNAseq operator-(const DNAseq& lhs, const DNAseq& rhs) {
    // also I converted it into string there
    string lhsStr = nucleotideToString(lhs.getSequence(), lhs.getLength());
    string rhsStr = nucleotideToString(rhs.getSequence(), rhs.getLength());

    int startPos = lhsStr.find(rhsStr); // first occurrence of rhs

    if (startPos != string::npos) {
        // remove the rhs from lhs
        lhsStr.erase(startPos, rhsStr.length());
    }

    // convert back the final string to DNA by parametric constructor
    return DNAseq(lhsStr);
}

// prints the sequence, based on lecture slides
ostream& operator<<(ostream& os, const DNAseq& rhs) {

        for (int i = 0; i < rhs.getLength(); ++i) {
            os << nucleotideToChar(rhs.getSequence()[i]);
        }

    return os;
}