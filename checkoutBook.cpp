/** @file checkoutBook.cpp
 * @author Josh Helzerman
 *
 * Description:
 *   - Command for library manager. checks out book for patron from library
 *
 * Implementation
 *   - inherits from Command interface.
 *   - removes a copy of an existing book to the library
 */



#include "checkoutBook.h"
#include <iostream>
#include "constants.h"
#include "book.h"
#include "patron.h"

using namespace std;

CheckoutBook::CheckoutBook(BookDatabase* books, PatronDatabase* patrons) {
   bookDB = books;
   patronDB = patrons;
   type = TYPE_CHECKOUT;
   commandCode = CHECKOUT_CODE;
}

LibraryCommand* CheckoutBook::create() const {
   return new CheckoutBook(bookDB, patronDB);
}

void CheckoutBook::execute() {
   

   if (!book->removeBook()) {
      cout << "ERROR: Patron " << patron->getID()
           << "Can't checkout book, library contains no books left titled: "
           << book->getTitle() << endl;
      delete this;
      return;
   }
   patron->addBook(book);
   patron->addCommand(this); //if all functions successfull, store command
}