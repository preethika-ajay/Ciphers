class vig
{
    char ciphertext_vig[50];
    char key[25];
    char cipher[27][27];//to store the vigenere alphabet matrix
    char plaintext_vig[50];

public:
    void vigprocess();
    void vigmatrice();
    void display_vig();
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
    display_vig();
}

void vig::display_vig()
{
    system("cls");
    cout << "Plaintext: " << plaintext_vig;
    cout << "\nCiphertext:" << ciphertext_vig << endl;
} //end of vig