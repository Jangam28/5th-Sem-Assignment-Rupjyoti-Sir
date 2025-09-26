#include <fst/fstlib.h>
#include <iostream>
#include <string>

using namespace fst;
using namespace std;

int main() {
    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    StdVectorFst fst;
    auto s = fst.AddState();
    fst.SetStart(s);

    for (char c : input) {
        if (c != '0' && c != '1') {
            cerr << "Invalid input: " << c << " (must be 0 or 1)\n";
            return 1;
        }

        auto n = fst.AddState();
        char output = (c == '0') ? '1' : '0';

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
    
    fst.Write("biComp.fst");
    cout << "Complement: " << output << "\n";
    return 0;
}
