#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream symbolIn("SYMBOL_TABLE.txt");
    ifstream literalIn("LITERAL_TABLE.txt");
    ifstream intemediateIn("input.txt");
    ofstream machineOut("machineCode.txt");

    string line, word;
    vector<pair<string, int>> symtab;
    vector<pair<string, int>> littab;

    while (!symbolIn.eof())
    {
        string line;
        getline(symbolIn, line);
        // cout << line << endl;
        string symbol = "", address = "";
        int i = 0;
        for (; i < line.length(); i++)
        {
            if (line[i] == ',')
                break;
            symbol += line[i];
        }
        i++;
        for (; i < line.length(); i++)
        {
            address += line[i];
        }
        cout << symbol << " " << address << endl;
        symtab.push_back({symbol, stoi(address)});
    }
    symbolIn.close();

    while (!literalIn.eof())
    {
        string line;
        getline(literalIn, line);
        // cout << line << endl;
        string symbol = "", address = "";
        int i = 0;
        for (; i < line.length(); i++)
        {
            if (line[i] == ',')
                break;
            symbol += line[i];
        }
        i++;
        for (; i < line.length(); i++)
        {
            address += line[i];
        }
        cout << symbol << " " << address << endl;
        littab.push_back({symbol, stoi(address)});
    }
    literalIn.close();

    // int lc = -1;

    while (!intemediateIn.eof())
    {
        string line;
        getline(intemediateIn, line);
        string cls = "", mnemonic = "", op1 = "", op2 = "";
        // cout<<line<<endl;
        int index = line.find('(');
        int i = 1;
        for (; i < line.length(); i++)
        {
            if (line[i] == ',')
                break;
            cls += line[i];
        }
        i++;
        for (; i < line.length(); i++)
        {
            if (line[i] == ')')
                break;
            mnemonic += line[i];
        }
        i += 3;

        cout << cls << " " << mnemonic << endl;
        if (cls == "AD")
        {
            machineOut << "+" << endl;
        }
        else if (cls == "IS")
        {
            machineOut << "+"
                 << "\t";
            machineOut << mnemonic << "\t";

            if (mnemonic == "0")
            { // Stop
                machineOut << "0\t000" << endl;
                continue;
            }
            machineOut << line[i] << "\t";

            i += 4;
            if (line[i] == 'S')
            {
                int ind = line[i + 2] - '0';
                machineOut << setw(3) << setfill('0') << symtab[ind - 1].second << endl;
            }
            else // it is a literal -> then print its value only
            {
                i += 3;
                while (i < line.length())
                {
                    if (line[i] == ')')
                        break;
                    op2 += line[i];
                    i++;
                }
                machineOut << setw(3) << setfill('0') << op2 << endl;
            }
        }
        else if (cls == "DL")
        {
            if (mnemonic == "2")
            {
                machineOut << "+" << endl;
            }
            else
            {
                machineOut << "+"
                     << "\t";
                for (int j = line.length() - 2; j >= 0; j--)
                {
                    if (line[j] == ',')
                        break;
                    op2 += line[j];
                }
                reverse(op2.begin(), op2.end());
                machineOut << 0 << "\t" << 00 << "\t" << setw(3) << setfill('0') << op2 << endl;
            }
        }
    }

    machineOut.close();
    intemediateIn.close();
    cout << "\nProgram Executed\n";

    return 0;
}