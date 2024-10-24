#include <string.h>
#include <iostream>
#include <fstream>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
struct Letters // Linked list for letters
{
    char letter = '\0';
    Letters *next = nullptr;
};
struct Words // Linked list for words
{
    char *word = nullptr;
    Words *next = nullptr;
};

class Functions
{
public:
    int random()
    {
        std::uniform_int_distribution<> dist(97, 112); // generates an lowercase letter
        return dist(gen);
    }
    char *removeDuplicates(char *input)
    {
        bool seen[256] = {false};
        int len = strlen(input);
        char *result = new char[len + 1];
        int index = 0;

        for (int i = 0; i < len; ++i)
        {
            if (!seen[static_cast<unsigned char>(input[i])])
            {
                result[index++] = input[i];
                seen[static_cast<unsigned char>(input[i])] = true;
            }
        }
        result[index] = '\0';
        return result;
    }
    bool presentInDict(char *wordToCheck)
    {
        std::string line;
        int flen = 0;
        int len = strlen(wordToCheck);
        for (int i = 0; i < len; i++)
            tolower(wordToCheck[i]);
        std::ifstream words("words.txt");
        if (words)
        {
            while (getline(words, line))
            {
                flen = line.length();
                if (len == flen)
                {
                    if (line == wordToCheck)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool filePresent()
    {
        std::ifstream words("words.txt");
        if (words)
        {
            words.close();
            return true;
        }
        else
        {
            std::cout << "File <words.txt> does not exsist" << "\n";
            words.close();
            return false;
        }
    }
    void welcomeMessage()
    {
        std::cout << "Welcome to another game by yours truly" << "\n";
        std::cout << "But theres a catch! You can only match with letters that are not adjacent to each other" << "\n";
        std::cout << "The objective of the game is to use all the letters to form multiple words\n";
        std::cout << "Let the games begin" << "\n";
    }
    void printOptions()
    {
        std::cout << "1 - Add a letter" << "\n";
        std::cout << "2 - Delete a letter" << "\n";
        std::cout << "3 - Submit word" << "\n";
        std::cout << "4 - Quit the game" << "\n";
    }
};
class LinkedListWords
{
private:
    // initializing the start node as nullptr
    Words *words = nullptr;

public:
    void AddWord(Words *newNode, char *toAdd)
    {
        newNode->word = new char[20];
        strcpy(newNode->word, toAdd); // copying the word to the node
        // if the list is empty
        if (words == nullptr)
        {
            words = newNode;
            return;
        }
        // if the list is not empty
        Words *temp = words;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    void DisplayWord()
    {
        if (words == nullptr)
        {
            std::cout << "No words entered" << "\n";
            return;
        }
        // if there is only one word
        if (words->next == nullptr)
        {
            std::cout << words->word << "\n";
            return;
        }
        Words *temp = words;
        while (temp->next != nullptr)
        {
            std::cout << temp->word << ".";
            temp = temp->next;
        }
        std::cout << temp->word << "\n"; // printing the last word
    }
    // function to the sum of all the words in LinkedList
    char *getCurrentString()
    {
        int totalLength = 0;
        Words *temp = words;
        while (temp != nullptr)
        {
            totalLength += strlen(temp->word);
            temp = temp->next;
        }

        char *result = new char[totalLength + 1];
        result[0] = '\0';

        temp = words;
        while (temp != nullptr)
        {
            strcat(result, temp->word);
            temp = temp->next;
        }
        return result;
    }
    ~LinkedListWords()
    {
        Words *temp = words;
        while (temp->next != nullptr)
        {
            Words *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
        delete temp;
        words = nullptr;
    }
};
class LinkedListLetters
{
private:
    Letters *letters = nullptr;

public:
    bool isContinued = false;
    bool isEmpty()
    {
        if (letters == nullptr)
        {
            return true;
        }
        return false;
    }
    char getLastLetter()
    {
        if (letters == nullptr)
        {
            return '\0';
        }
        if (letters->next == nullptr)
        {
            return letters->letter;
        }
        Letters *temp = letters;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        return temp->letter;
    }
    void AddNode(Letters *newNode, char toAdd)
    {
        newNode->letter = toAdd;
        if (letters == nullptr)
        {
            letters = newNode;
            return;
        }
        Letters *temp = letters;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    // function to get the sum of all letters
    char *getword()
    {
        char *words = new char[20];
        for (int i = 0; i < 20; i++)
        {
            words[i] = '\0';
        }
        Letters *temp = letters;
        int i = 0;
        while (temp->next != nullptr)
        {
            words[i] = temp->letter;
            temp = temp->next;
            i++;
        }
        words[i] = temp->letter;
        return words;
    }
    void Display()
    {
        if (letters == nullptr)
        {
            std::cout << "No letters entered" << "\n";
            return;
        }
        Letters *temp = letters;
        while (temp->next != nullptr)
        {
            std::cout << temp->letter;
            temp = temp->next;
        }
        std::cout << temp->letter << std::endl;
    }
    void deleteLetter()
    {
        if (letters == nullptr)
        {
            std::cout << "No letters entered to delete" << "\n";
            system("read");
            return;
        }
        Letters *temp = letters;
        if (isContinued && temp->next == nullptr)
        {
            std::cout << "You must start the next word starting with the last letter of the previous word" << "\n";
            system("read");
            return;
        }
        if (temp->next == nullptr)
        {
            delete temp;
            letters = nullptr;
            return;
        }
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
    void deleteLinkedList()
    {
        Letters *temp = letters;
        while (temp->next != nullptr)
        {
            Letters *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
        delete temp;
        letters = nullptr;
    }
    ~LinkedListLetters()
    {
        deleteLinkedList();
    }
};
class Matrix
{
private:
    char arr[5][5] = {'\0'};
    char rand = '\0';
    Functions func;

public:
    // constructor to initialize the matrix with random letters
    Matrix()
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (i == 0 || j == 0 || i == 4 || j == 4)
                {
                    if (i == 0 && j == 0 || i == 0 && j == 4 || i == 4 && j == 0 || i == 4 && j == 4)
                    {
                        continue;
                    }
                    rand = func.random();
                    while (checkForLetter((char)rand))
                    {
                        rand = func.random();
                    }
                    arr[i][j] = (char)rand;
                }
            }
        }
    }
    bool checkForWin(char *currentString)
    {
        if (strlen(currentString) == 12)
        {
            return true;
        }
        return false;
    }
    void display()
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                std::cout << arr[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
    // does a linear search to check if the letter is present in the matrix
    bool checkForLetter(char toCheck)
    {
        int *indices = new int[2];
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (i == 0 || j == 0 || i == 4 || j == 4)
                {
                    if (i == 0 && j == 0 || i == 0 && j == 4 || i == 4 && j == 0 || i == 4 && j == 4)
                    {
                        continue;
                    }
                    if (arr[i][j] == toCheck)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    int *getIndices(char toCheck)
    {
        int *indices = new int[2]; // to store the indices of the letter
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (i == 0 || j == 0 || i == 4 || j == 4)
                {
                    if (i == 0 && j == 0 || i == 0 && j == 4 || i == 4 && j == 0 || i == 4 && j == 4)
                    {
                        continue;
                    }
                    if (arr[i][j] == toCheck)
                    {
                        indices[0] = i;
                        indices[1] = j;
                        return indices;
                    }
                }
            }
        }
        indices[0] = -1;
        indices[1] = -1;
        return indices;
    }
    bool isValidMove(char startLetter, char endLetter)
    {
        int *startIndices = getIndices(startLetter);
        int *endIndices = getIndices(endLetter);
        // if the letters are on the same row or column and are on the border
        if ((startIndices[1] == 0 && endIndices[1] == 4) || (startIndices[1] == 4 && endIndices[1] == 0) ||
            (startIndices[0] == 0 && endIndices[0] == 4) || (startIndices[0] == 4 && endIndices[0] == 0))
        {
            delete startIndices;
            delete endIndices;
            return true;
        }
        // if the letters are on the same row or column
        else if (startIndices[0] == endIndices[0] || startIndices[1] == endIndices[1] ||
                 startIndices[1] == -1 || endIndices[1] == -1 || startIndices[0] == -1)
        {
            delete startIndices;
            delete endIndices;
            return false;
        }
        // if the letters are not on the same row or column
        else
        {
            delete startIndices;
            delete endIndices;
            return true;
        }
    }
};
int main()
{
    Functions *func = new Functions;
    if (!func->filePresent()) // checking if the file is present
    {
        std::cout << "The file <Words.txt> not present please check again" << "\n";
        delete func;
        return 1;
    }
    // creating the objects
    Matrix *mat = new Matrix;
    LinkedListLetters *listLetters = new LinkedListLetters;
    LinkedListWords *listWords = new LinkedListWords;
    // creating the pointers
    Letters *newLetter = nullptr;
    Words *newWord = nullptr;
    // initializing the variables
    bool gameOver = false;
    bool startOfGame = true;
    char choice = '\0';
    char startLetter, endLetter;
    char *currentWord = new char[100];
    func->welcomeMessage();
    while (!gameOver)
    {
        if (!startOfGame) // clear must only work after the first iteration
        {
            system("clear");
        }
        if (startOfGame)
        {
            startOfGame = false;
        }
        func->printOptions();
        mat->display();
        std::cout << "Your current word - " << " ";
        listLetters->Display();
        std::cout << "The words you have entered is " << " ";
        listWords->DisplayWord();
        choice = getchar();
        if (choice == '1')
        {
            std::cout << "Enter the letter you want to enter" << "\n";
            std::cin >> startLetter;
            if (listLetters->isEmpty())
            {
                if (!mat->checkForLetter(startLetter))
                {
                    std::cout << "The letter is not in the puzzle" << "\n";
                    system("read");
                    continue;
                }
                newLetter = new Letters;
                listLetters->AddNode(newLetter, startLetter);
                continue;
            }
            else
            {
                endLetter = listLetters->getLastLetter();
                if (mat->isValidMove(startLetter, endLetter))
                {
                    newLetter = new Letters;
                    listLetters->AddNode(newLetter, startLetter);
                    continue;
                }
                else
                {
                    std::cout << "Invalid move " << "\n";
                    system("read");
                    continue;
                }
            }
        }
        else if (choice == '2')
        {
            if (listLetters->isEmpty())
            {
                std::cout << "No pair to delete" << "\n";
                system("read");
                continue;
            }
            else
            {
                listLetters->deleteLetter();
                continue;
            }
        }
        else if (choice == '3')
        {
            strcpy(currentWord, listLetters->getword());
            if (func->presentInDict(currentWord))
            {
                std::cout << "Entered word is correct" << "\n";
                newWord = new Words;
                listWords->AddWord(newWord, currentWord);
                listLetters->deleteLinkedList();
                newLetter = new Letters;
                listLetters->AddNode(newLetter, currentWord[strlen(currentWord) - 1]);
                listLetters->isContinued = true;
                currentWord = listWords->getCurrentString();
                currentWord = func->removeDuplicates(currentWord);
                if (mat->checkForWin(currentWord))
                {
                    std::cout << "You have won the game" << "\n";
                    std::cout << "YAYYY" << std::endl;
                    gameOver = true;
                    break;
                }
                system("read");
                continue;
            }
            else
            {
                std::cout << "Entered word is incorrect" << "\n";
                system("read");
                continue;
            }
        }
        else if (choice == '4')
        {
            std::cout << "Quitting the game" << "\n";
            gameOver = true;
            break;
        }
        else
        {
            std::cout << "Your option is wrong try again" << "\n";
        }
    }
    free(mat);
    free(listLetters);
    free(listWords);
    free(func);
    free(currentWord);
    free(newLetter);
    free(newWord);
}