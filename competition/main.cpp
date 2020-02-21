#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm> 
#include <time.h>

using namespace std;

struct Book
{
    int id;
    int value;
    bool scanned;
};

struct Library
{
	int id;
	int checked = false;
	int signupTime;
	int nbBookPerDay;
    vector<Book*> books = vector<Book*>(0);
    int maxValue = 0;
	int maxNbBooks;

	int getUncheckedBooks()
	{
		int uncheckedBooks = 0;
		for (Book* b : books)
		{
			if (!b->scanned)
			uncheckedBooks++;
		}

		return uncheckedBooks;
	}

	void calculateMaxNbBooks(int nbDays)
	{
		maxNbBooks = (nbDays - signupTime) * nbBookPerDay;

		int unchecked = getUncheckedBooks();
		if (unchecked < maxNbBooks)
			maxNbBooks = unchecked;
	}

	void calculateMaxValue(int nbDays)
	{
		if (checked)
			return;

		maxValue = 0;

		calculateMaxNbBooks(nbDays);
		int remainingBooks = maxNbBooks;

		for (int i = 0; i < books.size(); ++i)
		{
			if (remainingBooks && !books[i]->scanned)
			{
				maxValue += books[i]->value;
				remainingBooks--;
			}
		}
	}

	vector<int> getBooks()
	{
		vector<int> chosenBooks;
		int remainingBooks = maxNbBooks;

		for (int i = 0; i < books.size(); ++i)
		{
			if (remainingBooks && !books[i]->scanned)
			{
				chosenBooks.push_back(books[i]->id);
				books[i]->scanned = true;
			}
		}

		return chosenBooks;
	}


};

bool compareBook(Book* first, Book* second)
{
	return first->value > second->value;
}

bool compareLibrary(Library& first, Library& second)
{
	if (first.maxNbBooks/first.signupTime == second.maxNbBooks/second.signupTime)
		return first.signupTime < second.signupTime;
	else
		return first.maxNbBooks/first.signupTime > second.maxNbBooks/second.signupTime;
}

vector<Book*> createBooks(vector<int> bookValues)
{
    vector<Book*> books(bookValues.size());

    for (int i = 0; i < bookValues.size(); ++i)
    {
        books[i] = new Book();
        books[i]->id = i;
        books[i]->value = bookValues[i];
    }

    return books;
}

int calculateValue(vector<Book*> books, vector<vector<int>> chosenBooks)
{
	int maxValue = 0;
	for (int i = 0; i < chosenBooks.size(); ++i)
	{
		for (int j = 0; j < chosenBooks[i].size(); ++j)
		{
			maxValue += books[chosenBooks[i][j]]->value;
		}
	}

	return maxValue;
}

void printLibraries(vector<Library>& libraries)
{
	for (int i = 0; i < libraries.size(); ++i)
	{
		cout << "Library " << i << endl;
		cout << "Signup Time "<< libraries[i].signupTime << endl;
		cout << "Books per day " <<  libraries[i].nbBookPerDay << endl;
		cout << "MaxValue " <<  libraries[i].maxValue << endl;
		
		for (int j = 0; j < libraries[i].books.size(); ++j)
		{ 
			cout << libraries[i].books[j]->id << " ";
		}
	
		cout << endl;

		cout << "MaxNbBooks " <<  libraries[i].maxNbBooks << endl << endl;

	}
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    string path;
    bool showNewBest = false;

	path = argv[1];

    int nbBooks, nbLibraries, nbDays;
    ifstream infile(path);
    string line;
	
	//Read
    getline(infile, line);
    istringstream iss(line);
    iss >> nbBooks >> nbLibraries >> nbDays;

	// sort(best_decks.begin(), best_decks.end(), compareDeck);
    // Read the books
    getline(infile, line);
    iss = istringstream(line);
    vector<int> bookValues = vector<int>(istream_iterator<int>(iss), istream_iterator<int>());
	
	vector<Book*> books = createBooks(bookValues);

    vector<Library> libraries(nbLibraries);

    for (int i = 0; i < nbLibraries; ++i)
    {
		int nbBooksInLibrary, signupTime, booksPerDay, bookId;
        getline(infile, line);
        iss = istringstream(line);
		iss >> nbBooksInLibrary >> signupTime >> booksPerDay;
	
		libraries[i].id = i;
		libraries[i].signupTime = signupTime;
		libraries[i].nbBookPerDay = booksPerDay;

		getline(infile, line);
        iss = istringstream(line);

		for(int j = 0; j < nbBooksInLibrary; ++j) {
    		iss >> bookId;
			libraries[i].books.push_back(books[bookId]);
		}
    }

	vector<vector<int>> bestChosenBooks;
	vector<int> bestChosenLibraries;
	int bestValue = 0;
	int iter = 0;
	while(iter < 1)
	{
		iter++;
		int remainingDays = nbDays;
		vector<vector<int>> chosenBooks;
		vector<int> chosenLibraries;

		while(remainingDays > 0)
		{
			float libValue = 0;
			float signUpTime = 0;
			Library* chosenLibrary = nullptr;
			for (Library& l : libraries)
			{
				l.calculateMaxValue(remainingDays);
				libValue += l.maxValue;	
				signUpTime += l.signupTime;
			}

			libValue /= nbLibraries;
			signUpTime/= nbLibraries;

			sort(libraries.begin(), libraries.end(), compareLibrary);

			for (int i = 0; i < libraries.size(); ++i)
			{
				if (!libraries[i].checked && libraries[i].signupTime < remainingDays && libraries[i].maxNbBooks > 0 && libValue/(float)libraries[i].maxValue < 1.2 && (float)libraries[i].signupTime/signUpTime < 1.2 )
				{
					chosenLibrary = &libraries[i];
					libraries[i].checked = true;

					break;
				}
			}

			if (chosenLibrary == nullptr)
			{
				break;
			}

			remainingDays -= chosenLibrary->signupTime;

			chosenBooks.push_back(chosenLibrary->getBooks());
			chosenLibraries.push_back(chosenLibrary->id);	
		}

		int newValue = calculateValue(books, chosenBooks);

		if (newValue > bestValue)
		{
			bestChosenBooks = chosenBooks;
			bestChosenLibraries = chosenLibraries;
			bestValue = newValue;
		}
	}

	if(true)
	{
		cout << bestChosenBooks.size() << endl;
		for (int i =0; i < bestChosenBooks.size(); ++i)
		{
			cout << bestChosenLibraries[i] << " " << bestChosenBooks[i].size() << endl;
			for (int j = 0; j < bestChosenBooks[i].size(); ++j)
			{
				cout << bestChosenBooks[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}