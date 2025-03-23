
void generateBinaryStrings(int n, string str){
    if(str.length() == n){
        cout << str << endl;
    } else{
        generateBinaryStrings(n, str + "0");
        generateBinaryStrings(n, str + "1");
    }
}
