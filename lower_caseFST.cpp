#include <fst/fstlib.h>
#include <iostream>
#include <string>
#include <cctype>  

using namespace fst;
using namespace std;

int main() {
    string input;
    cout << "Enter a lowercase string: ";
    cin >> input;

    StdVectorFst fst;
    auto s = fst.AddState();
    fst.SetStart(s);

    for (char c : input) {
        if (!islower(c)) {
            cerr << "Invalid input: " << c << " (must be lowercase a-z)\n";
            return 1;
        }

        auto n = fst.AddState();
        char output = toupper(c);

        fst.AddArc(s, StdArc(c, output, TropicalWeight::One(), n));
        s = n;
    }

    fst.SetFinal(s, TropicalWeight::One());

    string output;
    auto state = fst.Start();
    while (fst.Final(state) == TropicalWeight::Zero()) {
        for (ArcIterator<StdVectorFst> aiter(fst, state); !aiter.Done(); aiter.Next()) {
            const auto &arc = aiter.Value();
            if (arc.olabel != 0) {
                output.push_back(static_cast<char>(arc.olabel));
            }
            state = arc.nextstate;
            break;
        }
    }
    
    fst.Write("lowerToUpper.fst");
    cout << "Uppercase: " << output << "\n";
    return 0;
}
