#include <bits/stdc++.h>

using namespace std;

int main()
{

    // open all the files

    ifstream fin("input.txt");

    ifstream symout("SYMBOL_TABLE.txt");
    ifstream litout("LITERAL_TABLE.txt");
    ofstream fout("output.txt");

    map<int, string> symbols;
    map<int, string> literals;

    string line, word;
    int ind = 1;
    while (getline(symout, line))
    {
        stringstream st(line);
        st >> word;

        int i = 0;
        for (int j = 0; j < word.size(); j++)
        {
            if (word[j] == ',')
            {
                i = j;
                break;
            }
        }

        symbols[ind] = word.substr(i + 1);
        ind++;
    }

    ind = 1;
    while (getline(litout, line))
    {
        stringstream st(line);
        st >> word;

        int i = 0;
        for (int j = 0; j < word.size(); j++)
        {
            if (word[j] == ',')
            {
                i = j;
                break;
            }
        }

        literals[ind] = word.substr(i + 1);
        ind++;
    }

    while (getline(fin, line))
    {
        stringstream st(line);

        fout << "+ ";

        st >> word;

        int i = 0;
        for (int j = 0; j < word.size(); j++)
        {
            if (word[j] == ',')
            {
                i = j;
                break;
            }
        }

        string opcd = word.substr(1, i - 1);
        string opnum = word.substr(i + 1, word.size() - 5);

        if (opcd == "AD")
        {
            fout << endl;
            continue;
        }
        else if (opnum == "0")
        {
            fout << "00"
                 << " "
                 << "0"
                 << " "
                 << "000" << endl;
            continue;
        }
        else if (opcd == "DL" && opnum == "2")
        {
            fout << endl;
            continue;
        }
        else if (opcd == "DL")
        {
            fout << "00"
                 << " ";
        }
        else
        {

            if (opnum.size() == 2)
            {
                fout << opnum << " ";
            }
            else
            {
                fout << "0" + opnum << " ";
            }
        }

        st >> word;

        // check for registers or BC Satements
        if (word.size() == 3)
        {
            string reg = word.substr(1, word.size() - 2);

            fout << reg << " ";
        }
        else
        {
            fout << "0 ";
        }

        if (word.size() == 3)
        {
            st >> word;
        }

        i = 0;
        for (int j = 0; j < word.size(); j++)
        {
            if (word[j] == ',')
            {
                i = j;
                break;
            }
        }

        string op = word.substr(1, i - 1);
        string opn = word.substr(i + 1, word.size() - 4);

        string lcs;
        if (op == "L" || op == "S")
        {

            if (op == "L")
            {
                lcs = literals[stoi(opn)];
            }
            else
            {
                lcs = symbols[stoi(opn)];
            }

            if (lcs.size() == 3)
            {
                fout << lcs << endl;
            }
            else
            {
                if (lcs.size() == 2)
                {
                    lcs = "0" + lcs;
                    fout << lcs << lcs;
                }
                else
                {
                    fout << "00" << lcs << endl;
                }
            }
        }
        else if (op == "C")
        {
            string lcs = opn;

            if (lcs.size() == 3)
            {
                fout << lcs << endl;
            }
            else
            {
                if (lcs.size() == 2)
                {
                    lcs = "0" + lcs;
                    fout << lcs << endl;
                }
                else
                {
                    fout << "00" << lcs << endl;
                }
            }
        }
    }

    fout.close();
       
    symout.close();
    litout.close();
    fin.close();

    cout << "INTERPRETED SUCCESSFULLY" << endl;
}