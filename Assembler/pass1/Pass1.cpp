#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "At line 1\n";
    map<string, pair<string, string>> opcode;

    opcode["STOP"] = {"IS", "00"};
    opcode["ADD"] = {"IS", "01"};
    opcode["SUB"] = {"IS", "02"};
    opcode["MULT"] = {"IS", "03"};
    opcode["MOVER"] = {"IS", "04"};
    opcode["MOVEM"] = {"IS", "05"};
    opcode["COMP"] = {"IS", "06"};
    opcode["BC"] = {"IS", "07"};
    opcode["DIV"] = {"IS", "08"};
    opcode["READ"] = {"IS", "09"};
    opcode["PRINT"] = {"IS", "10"};
    opcode["START"] = {"AD", "01"};
    opcode["END"] = {"AD", "02"};
    opcode["ORIGIN"] = {"AD", "03"};
    opcode["EQU"] = {"AD", "04"};
    opcode["LTORG"] = {"AD", "05"};
    opcode["DC"] = {"DL", "01"};
    opcode["DS"] = {"DL", "02"};

    opcode["AREG"] = {"1", ""};
    opcode["BREG"] = {"2", ""};
    opcode["CREG"] = {"3", ""};
    opcode["DREG"] = {"4", ""};

    opcode["LT"] = {"1", ""};
    opcode["LE"] = {"2", ""};
    opcode["EQ"] = {"3", ""};
    opcode["GT"] = {"4", ""};
    opcode["GE"] = {"5", ""};
    opcode["ANY"] = {"6", ""};

    ifstream fin;
    fin.open("input2.txt");

    ofstream fout;
    fout.open("output.txt");

    string line, word;

    // SYMBOL TABLE 
    // symbol -> list count , index (1 start )
    map<string, pair<int, string>> symtab;


    vector<pair<string, int>> littab;
    vector<string> pooltab;
    int litindex = 0;
    int lc = -1;
    while (getline(fin, line))
    {
        stringstream st(line);
        st >> word;
        string label = "";

        cout<<word<<endl;
        // FIRST WORD OF INSTRUCTION : IF IT IS NOT A INSTRUCTION THEN CAN ONLY BE SYMBOL
        // NOTHING TO PRINT IN OUTPUT 
        if (opcode.count(word) == 0)
        {
            if (symtab.count(word) == 0)
            {
                symtab[word] = {lc, to_string(symtab.size() + 1)};
            }
            else
            {
                symtab[word].first = lc;
            }
            label = word;
            st >> word;
        }
        // TAKE NEXT WORD IN SYMBOL 

        string operation = word;
        if (operation == "START")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

            st >> word;
            // TALKE CONSTANT AND GO TO NEXT LINE 
            fout << "( C, " << word << ") ";
            lc = stoi(word);
        }
        else if (operation == "END")
        {   

            // PROCESS LITERAL TABLE AND PULL TABLE 
            
            // use DC and C as constant and value of the literal 
            pooltab.push_back("#" + to_string(litindex + 1));
            for (; litindex < littab.size(); litindex++)
            {
                fout << lc << " ";
                fout << "(" << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                littab[litindex].second = lc;
                string literal = littab[litindex].first;
                string sublit = literal.substr(2, literal.length() - 3);
                fout << "(C, " << sublit << ") ";
                fout << endl;
                lc++;
            }
            fout << "    ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
          //  fout << endl;
        }
        else if (operation == "LTORG")
        {
            // same as previous 
            // DC AND USE C and value of literal 
            fout << "    ";
            fout << "( " << opcode[word].first << ", " << opcode[word].second << ") ";
            fout << endl;
            pooltab.push_back("#" + to_string(litindex + 1));
            for (; litindex < littab.size(); litindex++)
            {
                fout << lc << " ";
                fout << "(" << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                littab[litindex].second = lc;
                string literal = littab[litindex].first;
                string sublit = literal.substr(2, literal.size() - 3);
                fout << "(C, " << sublit << ")";
                if(litindex!=littab.size()-1)
                {
                    fout<<endl;
                }
                
                lc++;
            }
            //litindex++;
        }
        else if (operation == "EQU")
        {
            fout << "    ";
            fout << "No IC generated";
            fout << endl;
            st >> word;
            int plusminusindex = 0;
            for (int i = 0; i < word.length(); i++)
            {
                /* code */
                if (word[i] == '+' || word[i] == '-')
                {
                    plusminusindex = i;
                    break;
                }
            }
            char plusminus = '0';
            string aftersign;
            string beforesign;
            if (plusminusindex != 0)
            {
                plusminus = word[plusminusindex];
                aftersign = word.substr(plusminusindex + 1);
                beforesign = word.substr(0, plusminusindex);
            }
            else
            {
                beforesign = word.substr(0, word.length());
            }
            symtab[label].first = symtab[beforesign].first;
            if (plusminus != '0')
            {
                if (plusminus == '+')
                {
                    symtab[label].first += stoi(aftersign);
                }
                else
                {
                    symtab[label].first -= stoi(aftersign);
                }
            }
        }
        else if (operation == "ORIGIN")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
            fout << endl;
            st >> word;
            int plusminusindex = 0;
            for (int i = 0; i < word.length(); i++)
            {
                if (word[i] == '+' || word[i] == '-')
                {
                    plusminusindex = i;
                    break;
                }
            }
            char plusminus = '0';
            string beforesign, aftersign;
            if (plusminusindex != 0)
            {
                plusminus = word[plusminusindex];
                aftersign = word.substr(plusminusindex + 1);
                beforesign = word.substr(0, plusminusindex);
            }
            else
            {
                beforesign = word.substr(0, word.length());
            }
            lc = symtab[beforesign].first;
            if (plusminus == '+')
            {
                lc += stoi(aftersign);
            }
            else if (plusminus == '-')
            {
                lc -= stoi(aftersign);
            }
        }
        else
        {
            fout << lc << " ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

            while (st >> word)
            {
                if (operation == "DC")
                {
                    word = word.substr(1, word.length() - 2);
                    fout << "(C, " << word << ") ";
                    // symtab[label].first = lc;
                }
                else if (operation == "DS")
                {
                    fout << "(C, " << word << ") ";
                    // symtab[label].first = lc;
                    // lc += stoi(word) - 1;
                }
                else if (word[0] == '=')
                {
                    littab.push_back({word, lc});
                    fout << "(L, " << littab.size() << ") ";
                }
                else if (opcode.count(word) > 0)
                {
                    fout << "(" << opcode[word].first << ", "<<opcode[word].second<<")";
                }
                else
                {
                    if (symtab.count(word) == 0)
                    {
                        symtab[word] = {lc, to_string(symtab.size() + 1)};
                    }
                    fout << "(S, " << symtab[word].second << ") ";
                }
            }
            lc++;
        }
        fout << endl;
    }
    fin.close();
    fout.close();

    ofstream sout;
    sout.open("symbol_table.txt"); // writing to symbol table file

    for (auto i : symtab)
    {
        sout << i.second.second << " " << i.first << " " << i.second.first;
        sout << endl;
    }

    sout.close();

    ofstream lout;
    lout.open("literal_table.txt"); // writing to literal table file

    for (auto i : littab)
    {
        lout << i.first << " " << i.second;
        lout << endl;
    }

    lout.close();

    ofstream pout;
    pout.open("pool_table.txt"); // writing to pool table file

    for (auto i : pooltab)
    {
        pout << i;
        pout << endl;
    }

    pout.close();

    cout << "\nProgram Excuted!!" << endl;

    return 0;
}