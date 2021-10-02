#include<fstream>
#include<iostream>
#include<string.h>
#include<string>
#include <cstdlib>
#include<iomanip>
#define alpha "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define alpha2 "abcdefghijklmnopqrstuvwxyz"

using namespace std;

class reflector {
    protected:
        char wallleft[27];
        char wallright[27];
    public:
        int reflect(int a);
        void inpre(char l[27]) {
            strcpy(wallleft,l);
            strcpy(wallright, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        }
};

int reflector::reflect(int a){
    char tofind = alpha[a];
    int i;
    for(i = 0; i< 26; i++)
        if (wallleft[i] == tofind)
            return i;
}

class rotor {
    protected:
        char left[27];
        char right[27];
    public:
        int look(int a,int bias);
        void inpro(char l[27]) {
            strcpy(left,l);
            strcpy(right, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            //cout<<left;
        }
};

int rotor::look(int a, int bias) {
    if(bias==0){//left=0,right=1{
        char tofind = alpha[a];
        int i;
        for(i = 0; i< 26; i++)
            if (left[i] == tofind)
                return i;
    }
    else if (bias == 1){
        char tofind = left[a];
        int s = tofind;
        s -= 65;
        return s;
    }
}

class enigma : protected rotor, protected reflector {
        char yoursecret[200];
        char thicc[200];
        rotor R1, R2;
        reflector R;
    public:
        void init();
        void input_secret();
        void process_secret();
        void output_secret();
        void doyouwanttoknow();
};

void enigma  :: init() {
    fstream fin("secretkey.txt", ios::in);
    char temp[27];
    fin.getline(temp, 27, '\n');
    R1.inpro(temp);
    fin.getline(temp, 27, '\n');
    R2.inpro(temp);
    fin.getline(temp, 27, '\n');
    R.inpre(temp);
    fin.close();
}

void enigma :: input_secret () {
    cout << "Kindly enter message of a maximum of 200 characters : \n";
    fflush(stdin);
    gets(yoursecret);
    int i;
    for(i=0;i<strlen(yoursecret);i++)
        yoursecret[i] = toupper(yoursecret[i]);
}

void enigma :: process_secret () {
    int i;
    int s ;
    for( i=0; i<strlen(yoursecret); i++){
        if(yoursecret[i] < 'A' || yoursecret[i] > 'Z'){
            thicc[i]=yoursecret[i];
        }
        else{
            s = yoursecret[i]- 65;
            s = R1.look(s,0);
            s=R2.look(s,0);
            s = R.reflect(s);
            s = R2.look(s,1);
            s=R1.look(s,1);
            thicc[i]=alpha[s];
        }
    }
    thicc[strlen(yoursecret)] = '\0';
}

void enigma :: output_secret() {
    cout<<"\nThe encrypted code is: "<<thicc<<endl;
    cout<<"\n\nEnter any key to know about the working of ENIGMA: ";
    char ch;
    cin>>ch;
    doyouwanttoknow();
}

void enigma::doyouwanttoknow(){
    system("cls");
    cout<<"Plaintext:  "<<yoursecret<<'\n';
    cout<<"Ciphertext: "<<thicc<<"\n";
    fstream fenig("enigexplain.txt",ios::in);
    while(!fenig.eof()){
        char line[700];
        fenig.getline(line,700,'\n');
        cout<<line<<endl;
    }
    fenig.close();
}//end of void

class ceaser {
       int key;
       char word[50];
       char wordi[50];
    public:
       void perform();
       void doyouwanttoknowcaeser();
}c1;

void ceaser::perform() {
    cout<<"Enter your message:"<<endl;
    fflush(stdin);
    gets(word);
    strcpy(wordi, word);
    cout<<"Enter shift of each letter (a number) : "<<endl;
    cin>>key;
    key = key%26;
    int i, j, l;
    l = strlen(word);
    cout<< "\nThe encrypted message is: ";
    for(int i = 0; word[i] != '\0'; ++i) {
        char ch;
        ch = word[i];
        if (ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            if (ch > 'z')
               ch = ch - 'z' + 'a' - 1;
            word[i] = ch;
        }
         //encrypt for uppercase letter
        else if (ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if (ch > 'Z'){
               ch = ch - 'Z' + 'A' - 1;
            }
            word[i] = ch;
        }
        cout<<word[i];
    }
    cout<<"\n\nEnter any key to know about the working of CEASER'S SHIFT: ";
    char ch;
    cin>>ch;
    doyouwanttoknowcaeser();
}//end of void perform

void ceaser::doyouwanttoknowcaeser(){
    system("cls");
    cout<<"Plaintext  : "<<wordi<<'\n';
    cout<<"Ciphertext : "<<word<<"\n\n";
    cout<<"    The Caesar cipher is one of the earliest known and simplest ciphers.";
    cout<<" It is a type of substitution cipher in which each letter in the plaintext is 'shifted' by a certain number of places down the alphabet.";
    cout<<" For example, with a shift of 1, A would be replaced by B, B would become C, and so on.\n\n";
    cout<<"    Mathematical Description :\n        e(x)=(x+k)(mod 26)\n        Where k is the key (the shift) applied to each letter. \n\n";
    cout<<"    The decryption function is :\n        e(x)=(x-k)(mod 26)\n\n";
    cout<<"    In this case, the key entered is "<<key<<", the substitution will be as such:\n";
    cout<<"        ABCDEFGHIJKLMNOPQRSTUVWXYZ\n        ";
    int i;
    for(i=0; i<26; i++){
        char ch = alpha[i];
        ch = ch + key;
        if (ch > 'Z')
           ch = ch - 'Z' + 'A' - 1;
        cout<<ch;
    }
    cout<<"\n\n";
}//end of void

class atbash {
        char word1[50];
        char bla[50];
    public:
        void processatbash();
        void doyouwanttoknowatbash();
}blue;//end of class at bash

void atbash::processatbash(){
    cout<<"Enter your message:\n";
    fflush(stdin);
    gets(word1);
    int i;
    cout<<"\nThe encrypted message is: ";
    for ( i = 0; i <strlen(word1); i++ ){
        if ( 'a' <= word1[i] && word1[i] <= 'z' )
            bla[i] = 'a' + 'z' - word1[i];
        else if ( 'A' <= word1[i] && word1[i] <= 'Z' )
            word1[i] = 'A' + 'Z' - word1[i];
        else
            bla[i] = word1[i];
        cout<<bla[i];
    }
    cout<<"\n\nEnter any key to know about the working of the ATBASH CIPHER: ";
    char ch;
    cin>>ch;
    doyouwanttoknowatbash();
}//end of process at bash

void atbash::doyouwanttoknowatbash(){
    system("cls");
    cout<<"Plaintext:  "<<word1<<'\n';
    cout<<"Ciphertext: "<<bla<<"\n";
    cout<<"\n    The Atbash cipher is a particular type of monoalphabetic cipher formed "
        "by taking the alphabet and mapping it to its reverse, so that "
        "the first letter becomes the last letter, the second letter becomes the second to last letter, etc.\n\n";
    cout<<"    The cipher is:\n        Plain	ABCDEFGHIJKLMNOPQRSTUVWXYZ\n        Cipher	ZYXWVUTSRQPONMLKJIHGFEDCBA\n";
}//end of void

class playfair {
        char grid[5][5];
        char key[200];
        char inp_key[200];
        char inp_text[200];
        char outp[200];
        void generate_key();
        void generate_grid();
    public:
        playfair () { key[0] = '\0'; }
        void inputplay();
        void processplay();
        void outputplay();
        void doyouwanttoknowplay();
};

void playfair :: inputplay () {
    cout << "Enter key of maximum 200 characters: ";
    fflush(stdin);
    gets(inp_key);
    cout << "\nEnter message of maximum 200 characters: ";
    fflush(stdin);
    gets(inp_text);
    // Convert all letters to lowercase
    int i;
    for(i=0; i<strlen(inp_key); i++)
        inp_key[i] = tolower(inp_key[i]);
    //Remove all spaces and numbers from inp_text, insert 'x' between repeated letters
    char temp[200];
    int k=0;
    for(i=0; i<strlen(inp_text); i++){
        if (inp_text[i] < 'a' || inp_text[i] > 'z')
            continue;
        else{
            temp[k++] = inp_text[i];
            if (inp_text[i] == inp_text[i+1])
                temp[k++] = 'x';
        }
    }
    temp[k] = '\0';
    strcpy(inp_text, temp);
    // Make number of letters in inp_text even
    int l = strlen(inp_text);
    if( l % 2 == 1){
        inp_text[l++] = 'x';
        inp_text[l] = '\0';
    }
    generate_key();
    generate_grid();
}

void playfair :: generate_key () {
    int i, k=0;
    for(i=0;i<strlen(inp_key);i++){
        // Check if character going to repeat
        int j, repeat = 0;
        for(j=0; j<strlen(key); j++)
            if ( inp_key[i] == key[j] )
                repeat ++;
        if (repeat || inp_key[i]=='j'|| inp_key[i]<'a'|| inp_key[i]>'z')
            continue;
        // If not repeated enter into key
        key[k++] = inp_key[i];
    }
    key[k] = '\0';
}

void playfair :: generate_grid () {
    int i,k=0;//k iterates through the alphabet
    for(i=0; i<strlen(key); i++)
        grid[i/5][i%5] = key[i];
    char temp[26]; int o=0;//o iterates through temp
    for(i=0;i<26;i++){
        int j, repeat = 0;
        for(j=0; j<strlen(key); j++)
            if ( alpha2[k] == key[j] )
                repeat ++;
        if (repeat || alpha2[k]=='j'){
            k++;
            continue;
        }
        temp[o++] = alpha2[k++];
    }
    temp[o] = '\0';
    o=0;
    for(i=strlen(key); i<26; i++){
        grid[i/5][i%5] = temp[o++];
    }
}

void playfair :: processplay () {
    int i;
    for(i=0; i<strlen(inp_text); i+=2){
        char a = inp_text[i], b = inp_text[i+1];
        //Find indices of a and b
        int j, ai, aj, bi, bj;
        for(j=0; j<5; j++){
            int k;
            for(k=0; k<5; k++){
                if(grid[j][k] == a){
                    ai = j; aj = k;
                } else if(grid[j][k] == b){
                    bi = j; bj = k;
                }
            }
        }
        //Process each digram and write into outp
        if(ai == bi){  //Case 1 : Same row
            outp[i] = grid[ai][(aj+1)%5];
            outp[i+1] = grid[bi][(bj+1)%5];
        }
        else if(aj == bj){ //Case 2 : Same column
            outp[i] = grid[(ai+1)%5][aj];
            outp[i+1] = grid[(bi+1)%5][bj];
        }
        else {   //Case 3 : rectangle
            outp[i] = grid[ai][bj];
            outp[i+1] = grid[bi][aj];
        }
    }
    outp[strlen(inp_text)] = '\0';
}

void playfair :: outputplay() {
    cout<<"\nThe encrypted message is: " << outp <<'\n';
    cout<<"\n\nEnter any key to know about the working of the PLAYFAIR CIPHER";
    char ch;
    cin>>ch;
    doyouwanttoknowplay();
}

void playfair::doyouwanttoknowplay(){
    system("cls");
    cout<<"Plaintext:  "<<inp_text<<'\n';
    cout<<"Ciphertext: "<<outp<<"\n\n";
    fstream fplay("playexplain.txt",ios::in);
    while(!fplay.eof()){
        char line[700];
        fplay.getline(line,700,'\n');
        cout<<line<<endl;
    }
    fplay.close();
    cout<<"      Grid: \n       ";
    int i;
    for(i=0;i<5;i++){
        int j;
        for(j=0;j<5;j++)
            cout<< grid[i][j]<<"  ";
        cout<<"\n       ";
    }
}//end of void do you want to know

class vig{
        char word[50];
        char key[25];
        char cipher[27][27];
        char blabla[50];
    public:
        void vigprocess();
        void vigmatrice();
        void doyouwanttovig();
}v;

void vig::vigmatrice(){
    int i,j,k=0;
    char alph[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(i=0;i<26;i++){
       for(j=0;j<26;j++){
        if((j+k)<26)
        cipher[i][j]=alph[j+k];
       else
        cipher[i][j]=alph[j+k-26];
       }
       k++;
    }
}

void vig::vigprocess(){
    vigmatrice();
    cout<<"Enter a message:\n";
    fflush(stdin);
    gets( word);
    strcpy(blabla,word);
    cout<<"Enter key:\n";
    fflush(stdin);
    gets(key);
    char tempkey[30];
    strcpy(tempkey,key);
    cout<<"\nThe encrypted message is: ";
    int i,o=0;
    for(i=0; i<strlen(word); i++)
        word[i] = toupper(word[i]);
    for(i=0; i<strlen(key); i++){
        key[i] = toupper(key[i]);
        if(key[i] < 'A' || key[i] > 'Z')
            continue;
        tempkey[o++] = key[i];
    }
    tempkey[o] = '\0';
    strcpy(key, tempkey);
    int l = strlen(key);
    for(i=0; i<strlen(word); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z'){
            int word_letter = word[i] - 65;
            int cipher_letter = key[i%l] - 65;
            word[i] = cipher[word_letter][cipher_letter];
        }
        cout<<word[i];
    }
    cout<<"\n\nEnter any key to know about the working of VIGNERE CIPHER";
    char ch;
    cin>>ch;
    doyouwanttovig();
}

void vig::doyouwanttovig(){
    system("cls");
    cout<<"Plaintext: "<<blabla;
    cout<<"\nCiphertext:"<<word<<endl;
    vigmatrice();
    fstream fvig("vigexplain.txt",ios::in);
    while(!fvig.eof()){
        char line[700];
        fvig.getline(line,700,'\n');
        cout<<line<<endl;
    }
    fvig.close();
 }//end of vig

void menu() {
        char choice;
        cout<<"\nEncryption is the process of encoding a message or information in such a way that"
        " only authorized parties can access it and those who are not authorized cannot."
        " Encryption does not itself prevent interference, but denies the intelligible content to "
        "a would-be interceptor. In an encryption scheme, the intended information or message, referred"
        " to as plaintext, is encrypted using an encryption algorithm a cipher,  generating ciphertext "
        "that can be read only if decrypted.\n\n        PLEASE NOTE THAT ONLY LETTERS WILL BE ENCRYPTED.\n";
        int flag = 0;
        while(!flag){
            cout<<"\nHere are the various ways in which you can encrypt a message:\n"
            "1. ENIGMA\n2. CAESER'S SHIFT\n3. ATBASH CIPHER\n"
            "4. THE VIGENERE CIPHER\n5. PLAYFAIR CIPHER\n6. EXIT\n";
            cout<<"\nSelect the cipher you would like to work with\n";
            cin>>choice;
            switch(choice){
            case '1': {
                enigma machine;
                machine.init();
                machine.input_secret();
                machine.process_secret();
                machine.output_secret();
                cout<<"Enter any key to continue\n";
                char c1a;
                cin>>c1a;
                system("cls");
            }
            break;
            case '2':{
                c1.perform();
                cout<<"Enter any key to continue\n";
                char c1a;
                cin>>c1a;
                system("cls");
            }
            break;
            case '3':{
                blue.processatbash();
                cout<<"Enter any key to continue\n";
                char c1a;
                cin>>c1a;
                system("cls");
            }
            break;
            case '4':{
                v.vigprocess();
                cout<<"Enter any key to continue\n";
                char c1a;
                cin>>c1a;
                system("cls");
            }//end of switch
            break;
            case '5':{
                playfair hebrew;
                hebrew.inputplay();
                hebrew.processplay();
                hebrew.outputplay();
                cout<<"\nEnter any key to continue\n";
                char c5a;
                cin>>c5a;
                system("cls");
            }
            break;
            case '6':
                flag++;
            break;
            default:
                cout<<"Invalid choice. Try again.";
            }//end of switch
        }
    }//end of void menu
int main() {
    menu();
}
