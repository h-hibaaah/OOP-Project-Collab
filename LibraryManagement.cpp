#include<iostream>
using namespace std;
class library
{
	public:

	void menu()
	{
		//Open file, also mentioning total number of books in library
		
	}
};
class staff:public library
{
	protected:
		int total_books;
		int books_given=0;
		int books_return=0;
		public:
	void category_staff()
	{
	
	}
	void DataEntry()
	{
		cout<<"How many Books are given to students today?";
		cin>>books_given;
		total_books-=books_given;
		cout<<"How many Books are returned by students today?";
		cin>>books_return;
		total_books+=books_return;
	}
	void total()
	{
	
		{
			cout<<"Total books are "<<total_books;
		}
		
	}
};
class student:public library
{
	protected:
		int b_borrow;
		int b_return;
		int choice;
		public:
	void book_borrow()
	{
	cout<<"How many books you want to borrow";
cin>>b_borrow;
}
void book_return()
{
cout<<"How many books you want to return";
cin>>b_return;
}
};
int main()
{
	int choice;
	int role;
	student o1;
	staff o2;
	cout<<"Choose your role:\n1. Student\n2. Staff\n";
	cin>>role;
	if (role == 1) {
        do {
            cout << "\nEnter according to your choice:\n"
                 << "1. Book Menu\n2. Return a Book\n3. Borrow a Book\n4. Exit\n";
            cin >> choice;

            if (choice == 1) {
                o1.menu();
            } else if (choice == 2) {
                o1.book_return();
            } else if (choice == 3) {
                o1.book_borrow();
            }

        } while (choice != 4);  
    }

    else if (role == 2) {
        do {
            cout << "\nEnter according to your choice:\n"
                 << "1. Book Menu\n2. Data Entry\n3. Total Books\n4. Exit\n";
            cin >> choice;

            if (choice == 1) {
                o2.menu();
            } else if (choice == 2) {
                o2.DataEntry();
            } else if (choice == 3) {
                o2.total();
            }

        } while (choice != 4);
    }

    else {
        cout << "Invalid role selected.\n";
    }
}
