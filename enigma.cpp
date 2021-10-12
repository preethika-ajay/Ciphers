#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#define alpha "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define alpha2 "abcdefghijklmnopqrstuvwxyz"

using namespace std;

//ENIGMA
//reflector of enigma cipher - ref to readme to know abouthe working of our enigma cipher
class reflector
{
protected:
    char wallleft[27];  //refers to left wall of reflector
    char wallright[27]; //refers to right wall of reflector
public:
    int reflect(int a);
    void input_reflector(char l[27])
    {
        strcpy(wallleft, l);
        strcpy(wallright, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"); //right wall contains letters in alphabetical order
    }
};

//fn to find the alphabet that the reflector reflects to
int reflector::reflect(int a)
{
    char tofind = alpha[a];
    int i;
    for (i = 0; i < 26; i++)
        if (wallleft[i] == tofind)
            return i;
}

//class rotor of enigma cipher - ref to readme to know abouthe working of our enigma cipher
class rotor
{
protected:
    char left[27];  //left wall of rotor
    char right[27]; //right wall of rotor
public:
    int look(int a, int bias);
    void input_rotor(char l[27])
    {
        strcpy(left, l);
        strcpy(right, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"); //right wall contains letters in alphabetical order
        //cout<<left;
    }
};

//fn to look for the alphabet rotor/inverter points to
int rotor::look(int a, int bias)
{
    //bias 0 indicates it is a rotor
    if (bias == 0)
    { //left=0,right=1{
        char tofind = alpha[a];
        int i;
        for (i = 0; i < 26; i++)
            if (left[i] == tofind)
                return i;
    }

    //bias 1 indicates it is a inverter
    else if (bias == 1)
    {
        char tofind = left[a];
        int s = tofind;
        s -= 65;
        return s;
    }
}

class enigma : protected rotor, protected reflector
{
    char plaintext_enigma[200];
    char ciphertext_enigma[200];
    rotor R1, R2; //enigma contains two rotors
    reflector R;

public:
    void init();
    void input_plaintext_enigma();
    void process_plaintext_enigma();
    void display_ciphertext_enigma();
    void enigma_info();
};

//fn to initialize the left walls of the rotor and reflector - alphabet array obtained from file secretkey.txt
void enigma ::init()
{
    fstream fin("secretkey.txt", ios::in);
    char temp[27];
    fin.getline(temp, 27, '\n');
    R1.input_rotor(temp);
    fin.getline(temp, 27, '\n');
    R2.input_rotor(temp);
    fin.getline(temp, 27, '\n');
    R.input_reflector(temp);
    fin.close();
}

//fn to input plaintext form user and convert to upper case for ease of encryption
void enigma ::input_plaintext_enigma()
{
    cout << "Kindly enter message of a maximum of 200 characters : \n";
    fflush(stdin);
    gets(plaintext_enigma);
    int i;
    for (i = 0; i < strlen(plaintext_enigma); i++)
        plaintext_enigma[i] = toupper(plaintext_enigma[i]);
}

//fn to encrypt the plaintext according to the rules of enigma
void enigma ::process_plaintext_enigma()
{
    int i;
    int s;
    for (i = 0; i < strlen(plaintext_enigma); i++)
    {
        //if the character is not an alphabet no encryption is done
        if (plaintext_enigma[i] < 'A' || plaintext_enigma[i] > 'Z')
        {
            ciphertext_enigma[i] = plaintext_enigma[i];
        }
        else
        {
            s = plaintext_enigma[i] - 65;
            s = R1.look(s, 0);
            s = R2.look(s, 0);
            s = R.reflect(s);
            s = R2.look(s, 1);
            s = R1.look(s, 1);
            ciphertext_enigma[i] = alpha[s];
        }
    }
    ciphertext_enigma[strlen(plaintext_enigma)] = '\0';
}

//fn to print the ciphertext
void enigma ::display_ciphertext_enigma()
{
    cout << "\nThe encrypted code is: " << ciphertext_enigma << endl;
    cout << "\n\nEnter any key to know about the working of ENIGMA: ";
    char ch;
    cin >> ch;
    enigma_info();
}

//fn to obtain information about enigma stored in a file
void enigma::enigma_info()
{
    system("cls");
    cout << "Plaintext:  " << plaintext_enigma << '\n';
    cout << "Ciphertext: " << ciphertext_enigma << "\n";
    fstream fenig("enigexplain.txt", ios::in);
    while (!fenig.eof())
    {
        char line[700];
        fenig.getline(line, 700, '\n');
        cout << line << endl;
    }
    fenig.close();
} //end of void

//CEASER CIPHER
class ceaser
{
    int key;             //shift of alphabet(user input)
    char word[50];       //user input of plaintext
    char input_copy[50]; //copy of plaintext for reference
public:
    void encrypt_ceaser();
    void info_ceaser();
} c1;

//fn that performs encryption acccording to the rules of ceaser cipher(to know working of cipher, refer to readme)
void ceaser::encrypt_ceaser()
{
    cout << "Enter your message:" << endl;
    fflush(stdin);
    gets(word);
    strcpy(input_copy, word);
    cout << "Enter shift of each letter (a number) : " << endl;
    cin >> key;
    key = key % 26;
    int i, j, l;
    l = strlen(word);
    cout << "\nThe encrypted message is: ";
    for (int i = 0; word[i] != '\0'; ++i)
    {
        char ch;
        ch = word[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
                ch = ch - 'z' + 'a' - 1;
            word[i] = ch;
        }
        //encrypt for uppercase letter
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
            word[i] = ch;
        }
        cout << word[i];
    }
    cout << "\n\nEnter any key to know about the working of CEASER'S SHIFT: ";
    char ch;
    cin >> ch;
    info_ceaser();
} //end of void encrypt_ceaser

//fn that contains information about the ceaser cipher
void ceaser::info_ceaser()
{
    system("cls");
    cout << "Plaintext  : " << input_copy << '\n';
    cout << "Ciphertext : " << word << "\n\n";
    cout << "    The Caesar cipher is one of the earliest known and simplest ciphers.";
    cout << " It is a type of substitution cipher in which each letter in the plaintext is 'shifted' by a certain number of places down the alphabet.";
    cout << " For example, with a shift of 1, A would be replaced by B, B would become C, and so on.\n\n";
    cout << "    Mathematical Description :\n        e(x)=(x+k)(mod 26)\n        Where k is the key (the shift) applied to each letter. \n\n";
    cout << "    The decryption function is :\n        e(x)=(x-k)(mod 26)\n\n";
    cout << "    In this case, the key entered is " << key << ", the substitution will be as such:\n";
    cout << "        ABCDEFGHIJKLMNOPQRSTUVWXYZ\n        ";
    int i;
    for (i = 0; i < 26; i++)
    {
        char ch = alpha[i];
        ch = ch + key;
        if (ch > 'Z')
            ch = ch - 'Z' + 'A' - 1;
        cout << ch;
    }
    cout << "\n\n";
} //end of void

//ATBASH CIPHER
class atbash
{
    char plaintext_atbash[50];
    char ciphertext_atbash[50];

public:
    void processatbash();
    void doyouwanttoknowatbash();
} blue; //end of class at bash

//fn that performs encryption acccording to the rules of atbash cipher(to know working of cipher, refer to readme)
void atbash::processatbash()
{
    cout << "Enter your message:\n";
    fflush(stdin);
    gets(plaintext_atbash);
    int i;
    cout << "\nThe encrypted message is: ";
    for (i = 0; i < strlen(plaintext_atbash); i++)
    {
        if ('a' <= plaintext_atbash[i] && plaintext_atbash[i] <= 'z')
            ciphertext_atbash[i] = 'a' + 'z' - plaintext_atbash[i];
        else if ('A' <= plaintext_atbash[i] && plaintext_atbash[i] <= 'Z')
            plaintext_atbash[i] = 'A' + 'Z' - plaintext_atbash[i];
        else
            ciphertext_atbash[i] = plaintext_atbash[i];
        cout << ciphertext_atbash[i];
    }
    cout << "\n\nEnter any key to know about the working of the ATBASH CIPHER: ";
    char ch;
    cin >> ch;
    doyouwanttoknowatbash();
} //end of process at bash

//fn that prints the information about atbash cipher
void atbash::doyouwanttoknowatbash()
{
    system("cls");
    cout << "Plaintext:  " << plaintext_atbash << '\n';
    cout << "Ciphertext: " << ciphertext_atbash << "\n";
    cout << "\n    The Atbash cipher is a particular type of monoalphabetic cipher formed "
            "by taking the alphabet and mapping it to its reverse, so that "
            "the first letter becomes the last letter, the second letter becomes the second to last letter, etc.\n\n";
    cout << "    The cipher is:\n        Plain	ABCDEFGHIJKLMNOPQRSTUVWXYZ\n        Cipher	ZYXWVUTSRQPONMLKJIHGFEDCBA\n";
} //end of void

//PLAYFAIR CIPHER
class playfair
{
    char grid[5][5];
    char key[200];
    char inp_key[200];
    char inp_text[200];
    char outp[200];
    void generate_key();
    void generate_grid();

public:
    playfair() { key[0] = '\0'; }
    void inputplay();
    void processplay();
    void outputplay();
    void doyouwanttoknowplay();
};

void playfair ::inputplay()
{
    cout << "Enter key of maximum 200 characters: ";
    fflush(stdin);
    gets(inp_key);
    cout << "\nEnter message of maximum 200 characters: ";
    fflush(stdin);
    gets(inp_text);
    // Convert all letters to lowercase
    int i;
    for (i = 0; i < strlen(inp_key); i++)
        inp_key[i] = tolower(inp_key[i]);
    //Remove all spaces and numbers from inp_text, insert 'x' between repeated letters
    char temp[200];
    int k = 0;
    for (i = 0; i < strlen(inp_text); i++)
    {
        if (inp_text[i] < 'a' || inp_text[i] > 'z')
            continue;
        else
        {
            temp[k++] = inp_text[i];
            if (inp_text[i] == inp_text[i + 1])
                temp[k++] = 'x';
        }
    }
    temp[k] = '\0';
    strcpy(inp_text, temp);
    // Make number of letters in inp_text even
    int l = strlen(inp_text);
    if (l % 2 == 1)
    {
        inp_text[l++] = 'x';
        inp_text[l] = '\0';
    }
    generate_key();
    generate_grid();
}

void playfair ::generate_key()
{
    int i, k = 0;
    for (i = 0; i < strlen(inp_key); i++)
    {
        // Check if character going to repeat
        int j, repeat = 0;
        for (j = 0; j < strlen(key); j++)
            if (inp_key[i] == key[j])
                repeat++;
        if (repeat || inp_key[i] == 'j' || inp_key[i] < 'a' || inp_key[i] > 'z')
            continue;
        // If not repeated enter into key
        key[k++] = inp_key[i];
    }
    key[k] = '\0';
}

void playfair ::generate_grid()
{
    int i, k = 0; //k iterates through the alphabet
    for (i = 0; i < strlen(key); i++)
        grid[i / 5][i % 5] = key[i];
    char temp[26];
    int o = 0; //o iterates through temp
    for (i = 0; i < 26; i++)
    {
        int j, repeat = 0;
        for (j = 0; j < strlen(key); j++)
            if (alpha2[k] == key[j])
                repeat++;
        if (repeat || alpha2[k] == 'j')
        {
            k++;
            continue;
        }
        temp[o++] = alpha2[k++];
    }
    temp[o] = '\0';
    o = 0;
    for (i = strlen(key); i < 26; i++)
    {
        grid[i / 5][i % 5] = temp[o++];
    }
}

void playfair ::processplay()
{
    int i;
    for (i = 0; i < strlen(inp_text); i += 2)
    {
        char a = inp_text[i], b = inp_text[i + 1];
        //Find indices of a and b
        int j, ai, aj, bi, bj;
        for (j = 0; j < 5; j++)
        {
            int k;
            for (k = 0; k < 5; k++)
            {
                if (grid[j][k] == a)
                {
                    ai = j;
                    aj = k;
                }
                else if (grid[j][k] == b)
                {
                    bi = j;
                    bj = k;
                }
            }
        }
        //Process each digram and write into outp
        if (ai == bi)
        { //Case 1 : Same row
            outp[i] = grid[ai][(aj + 1) % 5];
            outp[i + 1] = grid[bi][(bj + 1) % 5];
        }
        else if (aj == bj)
        { //Case 2 : Same column
            outp[i] = grid[(ai + 1) % 5][aj];
            outp[i + 1] = grid[(bi + 1) % 5][bj];
        }
        else
        { //Case 3 : rectangle
            outp[i] = grid[ai][bj];
            outp[i + 1] = grid[bi][aj];
        }
    }
    outp[strlen(inp_text)] = '\0';
}

void playfair ::outputplay()
{
    cout << "\nThe encrypted message is: " << outp << '\n';
    cout << "\n\nEnter any key to know about the working of the PLAYFAIR CIPHER";
    char ch;
    cin >> ch;
    doyouwanttoknowplay();
}

void playfair::doyouwanttoknowplay()
{
    system("cls");
    cout << "Plaintext:  " << inp_text << '\n';
    cout << "Ciphertext: " << outp << "\n\n";
    fstream fplay("playexplain.txt", ios::in);
    while (!fplay.eof())
    {
        char line[700];
        fplay.getline(line, 700, '\n');
        cout << line << endl;
    }
    fplay.close();
    cout << "      Grid: \n       ";
    int i;
    for (i = 0; i < 5; i++)
    {
        int j;
        for (j = 0; j < 5; j++)
            cout << grid[i][j] << "  ";
        cout << "\n       ";
    }
} //end of void do you want to know

//VIGENERE CIPHER
class vig
{
    char ciphertext_vig[50];
    char key[25];
    char cipher[27][27];//to store the vigenere alphabet matrix
    char plaintext_vig[50];

public:
    void vigprocess();
    void vigmatrice();
    void doyouwanttovig();
} v;

//fn to create the vigenere alphabet matrix
void vig::vigmatrice()
{
    int i, j, k = 0;
    char alph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (i = 0; i < 26; i++)
    {
        for (j = 0; j < 26; j++)
        {
            if ((j + k) < 26)
                cipher[i][j] = alph[j + k];
            else
                cipher[i][j] = alph[j + k - 26];
        }
        k++;
    }
}

//fn that performs encryption acccording to the rules of vigenere cipher(to know working of cipher, refer to readme)
void vig::vigprocess()
{
    vigmatrice();
    cout << "Enter a message:\n";
    fflush(stdin);
    gets(ciphertext_vig);
    strcpy(plaintext_vig, ciphertext_vig);

    cout << "Enter key:\n";
    fflush(stdin);
    gets(key);
    char tempkey[30];
    strcpy(tempkey, key);

    cout << "\nThe encrypted message is: ";
    int i, o = 0;

    //loop to make all alphabets in input to upper case for ease of encryption
    for (i = 0; i < strlen(ciphertext_vig); i++)
        ciphertext_vig[i] = toupper(ciphertext_vig[i]);

    //loop to convert all characters in key to upper case and validate that the key has only alphabets
    for (i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
        if (key[i] < 'A' || key[i] > 'Z')
            continue;
        tempkey[o++] = key[i];
    }
    tempkey[o] = '\0';
    strcpy(key, tempkey);

    int l = strlen(key);
    for (i = 0; i < strlen(ciphertext_vig); i++)
    {
        if (ciphertext_vig[i] >= 'A' && ciphertext_vig[i] <= 'Z')
        {
            int word_letter = ciphertext_vig[i] - 65;
            int cipher_letter = key[i % l] - 65;
            ciphertext_vig[i] = cipher[word_letter][cipher_letter];
        }
        cout << ciphertext_vig[i];
    }
    cout << "\n\nEnter any key to know about the working of VIGNERE CIPHER";
    char ch;
    cin >> ch;
    doyouwanttovig();
}

void vig::doyouwanttovig()
{
    system("cls");
    cout << "Plaintext: " << plaintext_vig;
    cout << "\nCiphertext:" << ciphertext_vig << endl;
    vigmatrice();
    fstream fvig("vigexplain.txt", ios::in);
    while (!fvig.eof())
    {
        char line[700];
        fvig.getline(line, 700, '\n');
        cout << line << endl;
    }
    fvig.close();
} //end of vig

void menu()
{
    char choice;
    cout << "\nEncryption is the process of encoding a message or information in such a way that"
            " only authorized parties can access it and those who are not authorized cannot."
            " Encryption does not itself prevent interference, but denies the intelligible content to "
            "a would-be interceptor. In an encryption scheme, the intended information or message, referred"
            " to as plaintext, is encrypted using an encryption algorithm a cipher,  generating ciphertext "
            "that can be read only if decrypted.\n\n        PLEASE NOTE THAT ONLY LETTERS WILL BE ENCRYPTED.\n";
    int flag = 0;
    while (!flag)
    {
        cout << "\nHere are the various ways in which you can encrypt a message:\n"
                "1. ENIGMA\n2. CAESER'S SHIFT\n3. ATBASH CIPHER\n"
                "4. THE VIGENERE CIPHER\n5. PLAYFAIR CIPHER\n6. EXIT\n";
        cout << "\nSelect the cipher you would like to work with\n";
        cin >> choice;
        switch (choice)
        {
        case '1':
        {
            enigma machine;
            machine.init();
            machine.input_plaintext_enigma();
            machine.process_plaintext_enigma();
            machine.display_ciphertext_enigma();
            cout << "Enter any key to continue\n";
            char c1a;
            cin >> c1a;
            system("cls");
        }
        break;
        case '2':
        {
            c1.encrypt_ceaser();
            cout << "Enter any key to continue\n";
            char c1a;
            cin >> c1a;
            system("cls");
        }
        break;
        case '3':
        {
            blue.processatbash();
            cout << "Enter any key to continue\n";
            char c1a;
            cin >> c1a;
            system("cls");
        }
        break;
        case '4':
        {
            v.vigprocess();
            cout << "Enter any key to continue\n";
            char c1a;
            cin >> c1a;
            system("cls");
        } //end of switch
        break;
        case '5':
        {
            playfair hebrew;
            hebrew.inputplay();
            hebrew.processplay();
            hebrew.outputplay();
            cout << "\nEnter any key to continue\n";
            char c5a;
            cin >> c5a;
            system("cls");
        }
        break;
        case '6':
            flag++;
            break;
        default:
            cout << "Invalid choice. Try again.";
        } //end of switch
    }
} //end of void menu

int main()
{
    menu();
}
