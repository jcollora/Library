/** @file bookfactory.cpp
 * @author Joseph Collora and Josh Helzerman
 *
 * Description:
 *   - A BookFactory object represents the factory class that creates Book
 *  objects in their different subtypes to be stored in the books database.
 *   - Can create a book and correctly classify it as the right type using
 * string data provided by the LibraryBuilder.
 *   - Holds three types of books: Fiction, Periodicals, and Children.
 *
 *
 * Implementation:
 *   - This a factory class following the factory design pattern.
 *   - Contains one function used to create and classify a book using
 * string data.
 *   - Classifies each type of book and creates the correct sub-class of
 * book for each string passed in.
 */

#include "book.h"
#include "fiction.h"
#include "periodical.h"
#include "children.h"
#include <iostream>
#include "bookfactory.h"
#include "constants.h"

using namespace std;

BookFactory::BookFactory() {
   // type's Ascii value - hash_start ascii value (defined in constants.h)
   bookTypes[FICTION_CODE - HASH_START] = new Fiction();
   bookTypes[PERIODICAL_CODE - HASH_START] = new Periodical();
   bookTypes[CHILDREN_CODE - HASH_START] = new Children();

}

BookFactory::~BookFactory() {
   for (const Book* ptr : bookTypes) {
      if (ptr != nullptr) {
         delete ptr;
      }
   }
}

Book* BookFactory::createBook(istream& is) const {
   char type = toupper(is.get());
   
   string line;
   int index = type - HASH_START;
   if (index < 0 || index >= HASH_SIZE) {
      getline(is, line);
      return nullptr; //character is out of range
   }
   if (bookTypes[index] == nullptr) {
      getline(is, line);
      return nullptr; //no booktype exists
   }

   Book* newBook = bookTypes[index]->create();

   if (!newBook->setData(is)) { //improper input
      delete newBook;
      return nullptr;
   }

   return newBook;
}

int BookFactory::getHash(const Book& book) const {
   string type = book.getType();
   return type[0] - HASH_START;
}


