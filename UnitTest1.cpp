#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <set>
#include <string>

#include "Header.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Task1Tests
{
    TEST_CLASS(Task1Tests)
    {
    public:

        // Тест 1: Перевірка базової логіки (унікальність та пропуск заголовку)
        TEST_METHOD(TestGetUniqueAuthors_ValidData)
        {
            // 1. Створюємо тимчасовий файл
            string testFile = "test_valid.csv";
            ofstream out(testFile);
            out << "title,author,year,isbn\n"; // Заголовок (має пропуститися)
            out << "1984,George Orwell,1949,1111\n";
            out << "Animal Farm,George Orwell,1945,2222\n"; // Дубль (має проігноруватися set-ом)
            out << "Dune,Frank Herbert,1965,3333\n";
            out.close();

            // 2. Викликаємо функцію
            set<string> authors = getUniqueAuthors(testFile);

            // 3. Перевіряємо результати
            Assert::AreEqual(size_t(2), authors.size());
            Assert::IsTrue(authors.find("George Orwell") != authors.end());
            Assert::IsTrue(authors.find("Frank Herbert") != authors.end());
        }

        // Тест 2: Перевірка обробки неправильного формату рядків (RowFormatException)
        TEST_METHOD(TestGetUniqueAuthors_SkipBadRows)
        {
            string testFile = "test_bad_rows.csv";
            ofstream out(testFile);
            out << "Foundation,Isaac Asimov,1951,5555\n"; // Правильний
            out << "Just Some Random Text Without Commas\n"; // Поганий рядок
            out << "Missing,Columns,1999\n"; // Тільки 3 колонки, теж поганий
            out << "Fahrenheit 451,Ray Bradbury,1953,4444\n"; // Правильний
            out.close();

            // Функція має внутрішньо відловити RowFormatException і повернути лише правильні дані
            set<string> authors = getUniqueAuthors(testFile);

            // Має бути лише 2 автори
            Assert::AreEqual(size_t(2), authors.size());
            Assert::IsTrue(authors.find("Isaac Asimov") != authors.end());
            Assert::IsTrue(authors.find("Ray Bradbury") != authors.end());
        }

        // Тест 3: Перевірка відсутності файлу (FileNotFoundException)
        TEST_METHOD(TestFileNotFoundException)
        {
            // Перевіряємо, чи функція кидає наш власний виняток, якщо файлу немає
            auto func = [] { getUniqueAuthors("non_existent_fake_file.csv"); };
            Assert::ExpectException<FileNotFoundException>(func);
        }
    };
}