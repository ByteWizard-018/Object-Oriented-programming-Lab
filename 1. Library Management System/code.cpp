#include <bits/stdc++.h>
using namespace std;

class Book{

    public:

    string title;
    string author;

    Book():title("UnknownTitle"),author("UnknownAuthor"),isbn("ISBN"),copiesAvailable(0),totalCopies(5){};
    Book(string t ,string a ,string isbn ,int cA ,int tC):title(t),author(a),isbn(isbn),copiesAvailable(cA),totalCopies(tC){};
    Book(Book& book, string newisbn)
    {
        title = book.title;
        author = book.author;
        isbn = newisbn;
        copiesAvailable = book.copiesAvailable;
        totalCopies = book.totalCopies;
    }
    string getisbn()
    {
        return isbn;
    }

    int getcopiesAvailable()
    {
        return copiesAvailable;
    }

    int gettotalCopies()
    {
        return totalCopies;
    }

    void updateCopies(int count)
    {
        int c = copiesAvailable + count;
        int t = totalCopies + count;

        if(t>=0 && c>=0)
        {
            copiesAvailable = c;
            totalCopies = t;
        }
        else
        {
            cout<<"Invalid request! Count becomes negative"<<endl;
        }
    }

    bool borrowBook()
    {
        if(copiesAvailable>0)
        {
            copiesAvailable--; return true;
        }
        else
        {
            return false;
        }
    }

    bool returnBook()
    {
        int c = copiesAvailable+1;

        if(c<=totalCopies)
        {
            copiesAvailable++;return true;
        }
        else
        {
            return false;
        }
    }

    void printDetails()
    {
        cout<< title<<" "<<author<<endl;
    }

    private:

    string isbn;
    int copiesAvailable;
    int totalCopies;


};


class Member{

    private:
    
    string memberID;
    map<string,int> borrowedBooks;
    int borrowLimit;

    public:

    string name;

    Member(string mID ,string n ,int bLimit):memberID(mID),name(n),borrowLimit(bLimit){};
    Member(string mID ,string n):memberID(mID),name(n),borrowLimit(3){};

    string getMemberId()
    {
        return memberID;
    }

    bool borrowBook(string isbn)
    {
        int sum =0;
        for(auto& it :borrowedBooks){
            sum+=it.second;
        }
        if(sum>=borrowLimit)
        {
            cout<<"Invalid request! Borrow limit exceeded"<<endl; return false; 
        }
        else
        {
            borrowedBooks[isbn]++;return true;
        }
    }

    bool returnBook(string isbn)
    {
        if(borrowedBooks.count(isbn))
        {
            borrowedBooks[isbn]--;
            if(!borrowedBooks[isbn]){
                borrowedBooks.erase(isbn);
            }
            return true;
        }
        else
        {
            cout<<"Invalid request! Book not borrowed"<<endl;return false;
        }
    }

    void printDetails()
    {
        for(auto& it:borrowedBooks){
            cout<<memberID<<" "<<name<<" "<<it.first<<" "<<it.second<<endl;
        }
    }

};


class Libary{
    public:

    bool addBook(Book& book)
    {
        for(auto& it: books){
            if(it.getisbn()== book.getisbn())
            {
                cout<<"Invalid request! Book with same isbn already exists"<<endl;return false;
            }
        }
        books.push_back(book);return true;
    }

    bool registerMember(Member& member)
    {
        for(auto& it: members){
            if(it.getMemberId()==member.getMemberId())
            {
                cout<<"Invalid request! Member with same id already exists"<<endl;return false;
            }
        }
        members.push_back(member);return true;
    }

    bool borrowBook(string memberID, string isbn)
    {   
        for(auto& it:books){
            if(it.getisbn() == isbn)
            {
                int p = it.getcopiesAvailable();
                if(p>0)
                {
                    for(auto& it2 : members)
                    {
                        if(it2.getMemberId() == memberID)
                        {
                            if(it2.borrowBook(isbn))
                            {
                                it.borrowBook();return true;
                            }
                        }
                    }
                }
                else
                {
                    cout<<"Invalid request! Copy of book not available"<<endl;
                }
            }
        }return false;
    }

    bool returnBook(string memberID,string isbn)
    {
        for(auto& it : books){
            if(it.getisbn() == isbn)
            {
                int c = it.getcopiesAvailable()+1;
                int t = it.gettotalCopies();

                if(c<=t)
                {
                    for(auto& it2 : members){
                        if(it2.getMemberId()== memberID)
                        {
                            if(it2.returnBook(isbn))
                            {
                                it.returnBook();return true;
                            } 
                        }  
                    }
                }
                else
                {
                     cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
                }
            }
        }return false;
    }

    void printLibraryDetails()
    {
        for(auto it: books){
            cout<< it.title<<" "<<it.author<<" "<<it.getcopiesAvailable()<<endl;
        }

        for(auto it: members){
            cout<< it.getMemberId()<<" "<<it.name<<endl;
        }
    }

    Book& getBook(string isbn)
    {
        for(auto& it : books ){
            if(it.getisbn()==isbn)
            {
                return it;
            }
        }
        Book b;
        return b;
    }
    Member getmember(string memid)
    {
        for(auto& it : members){
            if(it.getMemberId()==memid){
                return it;
            }
        }
        Member m("a","b");
        return m;
    }
    private:

    vector<Book> books;
    vector<Member> members;
};


int main(){
    string str;
    Libary l;
    
    
    while(true)
    {
        cin>>str;
        if(str=="Done")
        {
            break;
        }
        else if(str == "Book")
        {
            string s;
            cin>>s;
            if(s == "ExistingBook")
            {
                string oldIsbn,newIsbn;
                cin>>oldIsbn>>newIsbn;
                Book b1;
                b1= l.getBook(oldIsbn);
                Book b2(b1,newIsbn);
                l.addBook(b2);
            }
            else if(s == "None")
            {
                Book b; l.addBook(b);
            }
            else
            {
                string Auth,isbn;
                int copA,totC;
                cin>>Auth>>isbn>>copA>>totC;
                Book b(s,Auth,isbn,copA,totC);
                l.addBook(b);
            }
        }
        else if(str == "UpdateCopiesCount")
        {
            string isbn;
            int NewCount;
            cin>>isbn>>NewCount;
            Book& b = l.getBook(isbn);
            b.updateCopies(NewCount);
        }
        else if(str == "Borrow")
        {
            string memId,isbn;
            cin>>memId>>isbn;
            l.borrowBook(memId,isbn);
        }
        else if(str == "Return")
        {
            string memId,isbn;
            cin>>memId>>isbn;
            l.returnBook(memId,isbn);
        }
        else if(str == "PrintBook")
        {
            string isbn;
            cin>>isbn;
            Book b = l.getBook(isbn);
            b.printDetails();
        }
        else if(str == "PrintMember")
        {
            string memid;
            cin>>memid;
            Member m = l.getmember(memid);
            m.printDetails();
        }
        else if(str == "PrintLibrary")
        {
            l.printLibraryDetails();
        }
        else if(str == "Member")
        {
            string s;
            cin>>s;
            if(s=="NoBorrowLimit")
            {
                string memid,name;
                cin>>memid>>name;
                Member m(memid,name);
                l.registerMember(m);
            }
            else
            {
                string name;
                int BorL;
                cin>>name>>BorL;
                Member m2(s,name,BorL);
                l.registerMember(m2);
            }
        }
    }
}

