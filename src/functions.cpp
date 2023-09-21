#include "functions.hpp"
#define K 20
#define ALL 1

void makeHeap(vector<pair <string,int>> &heapWord){

    pair <string,int> father, sonRight;
    int end = heapWord.size(); 
    int size = (heapWord.size()-1)/2; 

    for(int i=size; i >= 0; i--){ 
        father = heapWord[i]; 
        int son = 2*i+1;
        while(son<end){ 

            if(son < end){
                if(((son+1) < end) && (heapWord[son].second > heapWord[son+1].second)){
                    son++;
                }
            }

            if(father.second > heapWord[son].second){
                heapWord[i] = heapWord[son];
                i = son;
                son = 2*i + 1;
            }
            else{
                son = end + 1;
            }
        }
        heapWord[i] = father;
    }
}

void lookInTheHeap(pair <string,int> auxHeapWord, vector<pair <string,int>> &heapWord){
    if(auxHeapWord.second > heapWord[0].second){
        heapWord[0] = auxHeapWord;
        makeHeap(heapWord);
    }
}

vector<pair<string,int>> returnHeap(map <string,int> wordHash, int j){

    int i = 0;
    vector<pair <string,int>> heapWord;
    pair <string,int> auxHeapWord;

    for(auto it = wordHash.begin(); it != wordHash.end(); it++){
        if(i > K+j){
            auxHeapWord.first = it->first;
            auxHeapWord.second = it->second;
            lookInTheHeap(auxHeapWord,heapWord);
        }
        else if(i == K+j){
            makeHeap(heapWord);
            auxHeapWord.first = it->first;
            auxHeapWord.second = it->second;
            lookInTheHeap(auxHeapWord,heapWord);
            i++;
        }
        else{
            auxHeapWord.first = it->first;
            auxHeapWord.second = it->second;
            heapWord.push_back(auxHeapWord);
            i++;
        }
        
    }

    return heapWord;
}

unordered_map <string,int> returnAllStopWord(){

    ifstream fileStopWord;
    string line, stopWord;
    unordered_map <string,int> allStopWords;

    fileStopWord.open("input/stopWord.txt");
	if(fileStopWord.is_open()){
        while(getline(fileStopWord, line)){
            istringstream stopWordToken(line);
            while(stopWordToken >> stopWord ){
                if(!(allStopWords.find(stopWord) != allStopWords.end())){
                    allStopWords[stopWord] = 2;
                } 
            }
	    }
        
    }
    else{
        cout << "\n\t - [Error] : I'm having trouble reading the document of the StopWords ! " << endl;
    }

	fileStopWord.close();
    return allStopWords;
}

void cleanLine(string &line){
    line.erase(remove(line.begin(),line.end(),','),line.end());
    line.erase(remove(line.begin(),line.end(),'\''),line.end());
    line.erase(remove(line.begin(),line.end(),'"'),line.end());
    line.erase(remove(line.begin(),line.end(),'.'),line.end());
    line.erase(remove(line.begin(),line.end(),'!'),line.end());
    line.erase(remove(line.begin(),line.end(),'?'),line.end());
    line.erase(remove(line.begin(),line.end(),'('),line.end());
    line.erase(remove(line.begin(),line.end(),')'),line.end());    
    line.erase(remove(line.begin(),line.end(),';'),line.end());
    line.erase(remove(line.begin(),line.end(),'/'),line.end());
    line.erase(remove(line.begin(),line.end(),'\\'),line.end());
    line.erase(remove(line.begin(),line.end(),':'),line.end());
    line.erase(remove(line.begin(),line.end(),'1'),line.end());
}

string toLowercase(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

void updateWord(string word, map <string,int> &wordHash, unordered_map <string,int> &allStopWords ){
    
    word = toLowercase(word);
    if(word != "-"){
        if(allStopWords.find(word) != allStopWords.end()){
            return;
        }
        else{
            if(wordHash.find(word) != wordHash.end()){
                wordHash[word]++;
            }
            else{
                wordHash[word] = 1;
            }
        } 
    }      
}

vector<string> returnResearchWords(){

    ifstream file;
    string word, line;
    vector<string> researchWord;
    file.open("input/input.data");

    if(file.is_open()){
        while(getline(file, line)){
            cleanLine(line);
            istringstream wordToken(line);
            while(wordToken >> word){
                if(word!="—"){
                    researchWord.push_back(word);
                }
            }
        }
    }
    else{
        cout << "\n\t - [Error] : I'm having trouble reading the document ! " << endl;
    }
    
    file.close();
    return researchWord;
}

Data takeDados(vector<pair <string,int>> heapWord, int i){
    Data aux;
    aux.word = heapWord[i].first;
    aux.ocorrencia = heapWord[i].second;
    return aux;
}

bool TreeEmpty(Tree **t){
  return *t == NULL;
}

void InsertTree(Tree **originalBinary, Data record){
    if(TreeEmpty(originalBinary)){
        *originalBinary = new Tree();
        (*originalBinary)->right = NULL;
        (*originalBinary)->left = NULL;
        (*originalBinary)->infos = record;
    }
    else{
        if(record.ocorrencia <= (*originalBinary)->infos.ocorrencia){
            InsertTree(&(*originalBinary)->left,record);
        }

        if(record.ocorrencia > (*originalBinary)->infos.ocorrencia){
            InsertTree(&(*originalBinary)->right,record);
        }  
    }
}

Tree* binaryTree(vector<pair <string,int>> heapWord, bool deleteWord, string word){

    Tree *originalBinary = NULL;
    Data record;

    if(deleteWord == false){
        for(int i=0; i<(int)heapWord.size(); i++){
            record.word = heapWord[i].first;
            record.ocorrencia = heapWord[i].second;
            InsertTree(&originalBinary,record);
        }
    }else{
        for(int i=0; i<(int)heapWord.size(); i++){
            if(heapWord[i].first != word){
                record.word = heapWord[i].first;
                record.ocorrencia = heapWord[i].second;
                InsertTree(&originalBinary,record);
            }
            
        }
    }

    return originalBinary;
}

int getIndex(AVL **originalAVL){
    if(*originalAVL==NULL){
        return -1;
    }
    return (*originalAVL)->index;
}

int getMaxIndex(int tamLeft, int tamRight){
    if(tamLeft > tamRight){
        return tamLeft;
    }
    return tamRight;
}

void spinSimple_Left(AVL **originalAVL){
    AVL *aux;
    aux = (*originalAVL)->sonRight;
    (*originalAVL)->sonRight = aux->sonLeft;
    aux->sonLeft = (*originalAVL); 
    int sumLeft = getIndex(&(*originalAVL)->sonLeft);
    int sumRight = getIndex(&(*originalAVL)->sonRight);
    (*originalAVL)->index = getMaxIndex(sumLeft,sumRight) + 1;
    sumLeft = getIndex(&aux->sonLeft);
    sumRight = getIndex(&aux->sonRight);
    aux->index = getMaxIndex(sumLeft,sumRight) + 1;
    (*originalAVL) = aux;
}

void spinDouble_Left(AVL **originalAVL){
    spinSimple_Right(&(*originalAVL)->sonRight);
    spinSimple_Left(originalAVL);
}

void spinSimple_Right(AVL **originalAVL){
    AVL *aux;
    aux = (*originalAVL)->sonLeft;
    (*originalAVL)->sonLeft = aux->sonRight;
    aux->sonRight = (*originalAVL); 
    int sumLeft = getIndex(&(*originalAVL)->sonLeft);
    int sumRight = getIndex(&(*originalAVL)->sonRight);
    (*originalAVL)->index = getMaxIndex(sumLeft,sumRight) + 1;
    sumLeft = getIndex(&aux->sonLeft);
    sumRight = getIndex(&aux->sonRight);
    aux->index = getMaxIndex(sumLeft,sumRight) + 1;
    (*originalAVL) = aux;
}

void spinDouble_Right(AVL **originalAVL){
    spinSimple_Left(&(*originalAVL)->sonLeft);
    spinSimple_Right(originalAVL);
}

void insertTree_AVL(AVL **originalAVL, Data record){

    if(*originalAVL == NULL){
        *originalAVL = new AVL();
        (*originalAVL)->sonLeft = NULL;
        (*originalAVL)->sonRight = NULL;
        (*originalAVL)->index = 0;
        (*originalAVL)->infos = record;
    }
    else{

        if(record.ocorrencia <= (*originalAVL)->infos.ocorrencia){
            insertTree_AVL(&(*originalAVL)->sonLeft, record);
            int sum = getIndex(&(*originalAVL)->sonLeft) - getIndex(&(*originalAVL)->sonRight);
            if(sum == 2){
                if(record.ocorrencia <= (*originalAVL)->sonLeft->infos.ocorrencia){
                    spinSimple_Right(originalAVL);
                }
                else{
                    spinDouble_Right(originalAVL);
                }
            }
        }

        if(record.ocorrencia > (*originalAVL)->infos.ocorrencia){
            insertTree_AVL(&(*originalAVL)->sonRight,record);
            int sum2 = getIndex(&(*originalAVL)->sonRight) - getIndex(&(*originalAVL)->sonLeft);
            if(sum2 == 2){
                if(record.ocorrencia > (*originalAVL)->sonRight->infos.ocorrencia){
                    spinSimple_Left(originalAVL);
                }
                else{
                    spinDouble_Left(originalAVL);
                }
            }
        }
    }

    int sumLeft = getIndex(&(*originalAVL)->sonLeft);
    int sumRight = getIndex(&(*originalAVL)->sonRight);
    (*originalAVL)->index = getMaxIndex(sumLeft,sumRight) +1 ;
}

void saveWidthBinary(ofstream &file, Tree *root){

    if(root == nullptr) {
        return;
    }

    queue<Tree *> q;
    q.push(root);

    while(!q.empty()) {
        Tree *aux = q.front();
        q.pop();

        file <<"- Word: " << setiosflags(ios::left) <<setw(20) << setfill(' ') << aux->infos.word <<"Occurrences: " << aux->infos.ocorrencia << endl;
        if (aux->left != NULL){
            q.push(aux->left);
        }
        if (aux->right != NULL){
            q.push(aux->right);
        }   
    }

    file << endl;
}

void saveWidthAVL(ofstream &file, AVL *root){

    if(root == nullptr) {
        return;
    }

    queue<AVL *> q;
    q.push(root);

    while(!q.empty()) {
        AVL *aux = q.front();
        q.pop();

        file <<"- Word: " << setiosflags(ios::left) <<setw(20) << setfill(' ') << aux->infos.word <<"Occurrences: " << aux->infos.ocorrencia << endl;
        if (aux->sonLeft != NULL){
            q.push(aux->sonLeft);
        }
        if (aux->sonRight != NULL){
            q.push(aux->sonRight);
        }   
    }

    file << endl;

}

AVL* AVL_Tree(vector<pair <string,int>> heapWord, bool deleteWord, string word){

    AVL *originalAVL = NULL;
    Data record;
    if(deleteWord == false){
        for(int i=0; i<(int)heapWord.size(); i++){
            record.word = heapWord[i].first;
            record.ocorrencia = heapWord[i].second;
            insertTree_AVL(&originalAVL,record);
        }
    }
    else{
        for(int i=0; i<(int)heapWord.size(); i++){
            if(heapWord[i].first != word){
                record.word = heapWord[i].first;
                record.ocorrencia = heapWord[i].second;
                insertTree_AVL(&originalAVL,record);
            }
        }

    }
    return originalAVL;
}

Huffman* takeNO(Huffman aux){
    Huffman *no = new Huffman();
    no->left = aux.left;
    no->right = aux.right;
    no->nick = aux.nick;
    no->occurrences = aux.occurrences;
    return no;
}

Huffman HuffmanTree(priority_queue<Huffman, vector<Huffman>, pair_maior> queueWords){

    Huffman *first, *second, *newNode, original;
    string code="";

    while(queueWords.size()>1){
        first = takeNO(queueWords.top());
        queueWords.pop();
        second = takeNO(queueWords.top());
        queueWords.pop();
        newNode = new Huffman();
        newNode->nick = '!';
        newNode->occurrences = first->occurrences + second->occurrences;
        newNode->tam = getMaxIndex(first->tam,second->tam) + 1;
        newNode->left = first;
        newNode->right = second;
        queueWords.push((*newNode));
    }
   
    original = queueWords.top();
    decoderHuffman(&original,code);

    return original;
}

priority_queue<Huffman, vector<Huffman>, pair_maior> returnQueue(vector<pair <string,int>> heapWord){

    priority_queue<Huffman, vector<Huffman>, pair_maior> queueWord;
    Huffman aux;

    for(int i=0; i<(int)heapWord.size(); i++){
        aux.nick = heapWord[i].first;
        aux.occurrences = heapWord[i].second;
        aux.left = NULL;
        aux.right = NULL;
        aux.tam = 0;
        queueWord.push(aux);
    }

    return queueWord;
}

priority_queue<Huffman, vector<Huffman>, pair_maior> returnQueueMore(vector<pair <string,int>> heapWord, string word){

    priority_queue<Huffman, vector<Huffman>, pair_maior> queueWord;
    Huffman aux;

    for(int i=0; i<(int)heapWord.size(); i++){
        if(heapWord[i].first != word){
            aux.nick = heapWord[i].first;
            aux.occurrences = heapWord[i].second;
            aux.left = NULL;
            aux.right = NULL;
            queueWord.push(aux);
        }
    }
    
    return queueWord;
}

void saveWidthHuffman(ofstream &output, Huffman root){

    queue<Huffman > q;
    q.push(root);

    while (!q.empty()){
       
        Huffman aux = q.front();
        q.pop();

        if(aux.nick!="!")
            output << "- word: " << setiosflags(ios::left) << setw(20) << setfill(' ')  << aux.nick << " occourences: " << setiosflags(ios::left) << setw(6) << setfill(' ') << aux.occurrences <<  "   code: " << aux.code <<endl;

        if (aux.left != NULL) {
            q.push((*aux.left));
        }

        if (aux.right != NULL) {
            q.push((*aux.right));
        }
        
    }
}

void decoderHuffman(Huffman *tree, string &code){

    string codeaux = code;

    if(tree->left == NULL && tree->right == NULL){
        tree->code = code;
        code.clear();
    }
    else{
        decoderHuffman(tree->left,(code+='0'));
        decoderHuffman(tree->right,(codeaux+='1'));
    }
}

void toCreateTree(map<string,int> wordHash, string nomeFile, ofstream &output){

    vector<string> all_ResearchWord;
    vector<pair <string,int>> heapWord, heapWord_moreWord;
    priority_queue<Huffman, vector<Huffman>, pair_maior> queueWords, queueMoreWords;
    HistoryAllText vetor;
    ResultWordResearch aux;

    heapWord = returnHeap(wordHash,0);
    queueWords = returnQueue(heapWord);
    heapWord_moreWord = returnHeap(wordHash,1);
    all_ResearchWord = returnResearchWords();

    vetor.nameFile = nomeFile;
    for(int i=0; i<(int)all_ResearchWord.size(); i++){
        string word = all_ResearchWord[i];
        aux.wordResearch.word = word;
        if(wordHash.find(word) != wordHash.end()){
            aux.wordResearch.ocorrencia = wordHash[word];
            if(wordHash[word] < heapWord[0].second){ 
                aux.treeBINARY = binaryTree(heapWord,false,word);
                aux.treeAVL = AVL_Tree(heapWord,false,word);
                aux.treeHuffman = HuffmanTree(queueWords);
            }
            else{
                queueMoreWords = returnQueueMore(heapWord_moreWord,word);
                aux.treeBINARY = binaryTree(heapWord_moreWord,true,word);
                aux.treeAVL = AVL_Tree(heapWord_moreWord,true,word);
                aux.treeHuffman = HuffmanTree(queueMoreWords);
            }
            vetor.HistoryAllWord.push_back(aux);
        }
        else{
            aux.wordResearch.word = word;
            aux.wordResearch.ocorrencia = 0;
            aux.treeAVL = NULL;
            aux.treeBINARY = NULL;
            aux.treeHuffman.nick = "nullInTree";
            vetor.HistoryAllWord.push_back(aux);
        }
    }
    saveOutput(output,vetor);
}

void saveOutput(ofstream &output, HistoryAllText vetor){
    output << "\n=================================================================================================================================================================" << endl;
    output << "                                                           ### FILE : "<< vetor.nameFile <<" ###                                                           " << endl;
    output << "=================================================================================================================================================================" << endl;
    for(int i=0; i<(int)vetor.HistoryAllWord.size(); i++){
        output << "\n[WORD RESEARCH] : " << vetor.HistoryAllWord[i].wordResearch.word << "      [OCCURRENCES]: "<< vetor.HistoryAllWord[i].wordResearch.ocorrencia << endl;
        output << "_________________________________________________________________________________________________________________________________________________________________" << endl << endl;
        if(vetor.HistoryAllWord[i].wordResearch.ocorrencia != 0 ){
            output << "----------[BINARY TREE]--[WIDTH]---------------------------------------------------------------------------------------------------------------------------------\n" << endl;
            saveWidthBinary(output,vetor.HistoryAllWord[i].treeBINARY);
            output << "----------[AVL TREE]--[WIDTH]------------------------------------------------------------------------------------------------------------------------------------\n" << endl;
            saveWidthAVL(output,vetor.HistoryAllWord[i].treeAVL);
            output << "----------[HUFFMAN TREE]--[WIDTH]--------------------------------------------------------------------------------------------------------------------------------\n" << endl;
            saveWidthHuffman(output,vetor.HistoryAllWord[i].treeHuffman);
        }
    }
}

void returnHash(){

    ifstream file;
    ofstream output("output/output.data");
	string line, word, base = "input/textos/", pwd = "";
    vector<string> textos = {"filosofia.txt","filosofia2.txt","globalizacao.txt","politica.txt","ti.txt","ti2.txt"};
    unordered_map <string,int> allStopWords;
    map <string,int> wordHash;
	allStopWords = returnAllStopWord();

    for(int i=0; i<ALL; i++){
        pwd = base + textos[i];
        file.open(pwd);
        if(file.is_open()){
            while(getline(file, line)){
                cleanLine(line);
                istringstream wordToken(line);
                while(wordToken >> word){
                    if(word!="—"){
                        if(word.size() > 2 && word.substr(0,2) == "--"){
                            word = word.substr(2);
                            updateWord(word,wordHash,allStopWords);
                        }
                        else{
                            updateWord(word,wordHash,allStopWords);
                        }
                    }
                }

            }

            toCreateTree(wordHash,textos[i],output);
            wordHash.clear();

        }
        else{
            cout << "\n\t - [Error] : I'm having trouble reading this document ! " << textos[i] <<endl;
        }

        pwd.clear();
        file.close();
    }	
}
