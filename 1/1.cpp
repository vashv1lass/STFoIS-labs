#include <iostream> // std::cin, std::cout
#include <cstdlib> // EXIT_SUCCESS, std::size_t
#include <vector> // std::vector
#include <algorithm> // std::sort, std::erase, std::unique, std::find
#include <clocale> // std::setlocale

using std::size_t;

/**
 * @brief Удаление из множества повторяющихся элементов
 *
 * @tparam T тип элементов множества
 * @param x множество
 */
template<typename T>
inline void normalize(std::vector<T>& x)
{
    std::sort(x.begin(), x.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
}

/**
 * @brief Проверяет есть ли элемент в массиве
 *
 * @tparam T тип элементов в массиве
 * @param x массив, в котором надо найти элемент
 * @param element элемент, который надо найти
 * @return true если элемент найден
 * @return false если элемент не найден
 */
template<typename T>
inline bool found(const std::vector<T>& x, const T& element)
{
    return std::find(x.begin(), x.end(), element) != x.end();
}

/**
 * @brief Задание универсального множества. В данном случае - целые числа
 *        диапазона [1;100]
 *
 * @return std::vector<int> универсальное множество
 */
std::vector<int> generateUniversum()
{
    std::vector<int> universum(100);
    for (int i = 0; i < 100; i++)
    {
        universum[i] = i + 1;
    }
    return universum;
}

// Универсальное множество
const std::vector<int> UNIVERSUM = generateUniversum();

/**
 * @brief Печатает массив на консоль
 * 
 * @tparam T тип элементов в массиве
 * @param s массив
 */
template<typename T>
void printArray(const std::vector<T>& s)
{
    std::cout << "{ ";
    for (size_t i = 0; i < s.size(); i++)
    {
       std::cout << s[i] << ((i + 1 != s.size()) ? ", " : " ");
    }
    std::cout << "}\n";
}

/**
 * @brief Объединение двух множеств
 *
 * @tparam T тип элементов множества
 * @param x первое множество
 * @param y второе множество
 * @return std::vector<T> мн-во, являющееся объединением мн-в x и y
 */
template<typename T>
std::vector<T> unite(const std::vector<T>& x, const std::vector<T>& y)
{
    std::vector<T> result = x; // добавляем все элементы из мн-ва x
    // Добавляем все эл-ты их мн-ва y
    for (size_t i = 0; i < y.size(); i++)
    {
        result.push_back(y[i]);
    }

    // Удаляем из множества все повторяющиеся элементы
    normalize(result);
    return result;
}

/**
 * @brief Пересечение двух множеств
 *
 * @tparam T тип элементов множества
 * @param x первое множество
 * @param y второе множество
 * @return std::vector<T> мн-во, являющееся пересечением мн-в x и y
 */
template<typename T>
std::vector<T> intersect(const std::vector<T>& x, const std::vector<T>& y)
{
    std::vector<T> result;
    for (size_t i = 0; i < x.size(); i++)
    {
        if (found(y, x[i])) // если элемент найден в обоих множествах
        {
            result.push_back(x[i]);
        }
    }

    normalize(result);
    return result;
}

/**
 * @brief Разность двух множеств
 *
 * @tparam T тип элементов множества
 * @param x первое множество
 * @param y второе множество
 * @return std::vector<T> мн-во, являющееся разностью мн-в x и y
 */
template<typename T>
std::vector<T> difference(const std::vector<T>& x, const std::vector<T>& y)
{
    // Реализация аналогична реализации алгоритма пересечения
    std::vector<T> result;
    
    for (size_t i = 0; i < x.size(); i++)
    {
        if (!found(y, x[i]))
        {
            result.push_back(x[i]);
        }
    }

    normalize(result);
    return result;
}

/**
 * @brief Симметричная разность двух множеств
 *
 * @tparam T тип элементов множества
 * @param x первое множество
 * @param y второе множество
 * @return std::vector<T> мн-во, являющееся симметричной разностью мн-в x и y
 */
template<typename T>
std::vector<T> symmetricalDifference(const std::vector<T>& x,
                                     const std::vector<T>& y)
{
    std::vector<T> xyDifference = difference(x, y);
    std::vector<T> yxDifference = difference(y, x);
    
    std::vector<T> result = unite(xyDifference, yxDifference);

    normalize(result);
    return result;
}

/**
 * @brief Дополнение множества x к универсуму
 *
 * @tparam T тип элементов множества
 * @param x множество
 * @return std::vector<T> мн-во, являющееся дополнением к универсуму мн-ва x
 */
template<typename T>
inline std::vector<T> additionToTheUniversum(const std::vector<T>& x)
{
    std::vector<T> result = difference(UNIVERSUM, x);
    
    normalize(result);
    return result;
}

int main()
{
    std::setlocale(LC_ALL, "rus");

    // Ввод множества X
    std::cout << "Введите мощность множества X: ";
    size_t sizeX;
    std::cin >> sizeX;
    
    std::cout << "Введите множество X: ";
    std::vector<int> x(sizeX);
    for (size_t i = 0; i < sizeX; i++)
    {
        std::cin >> x[i];
    }

    // Ввод множества Y
    std::cout << "Введите мощность множества Y: ";
    size_t sizeY;
    std::cin >> sizeY;
    
    std::cout << "Введите множество Y: ";
    std::vector<int> y(sizeY);
    for (size_t i = 0; i < sizeY; i++)
    {
        std::cin >> y[i];
    }
    
    bool terminated = false;
    while (true)
    {
        // Выбор операции:
        std::cout << ("Выберите операцию которую вы хотите провести с множеством"
                      " (число от 1 до 5):\nОбъединение (1);\nПересечение (2);\n"
                      "Разность (3);\nСимметрическая разность (4);\nДополнение к"
                      " универсуму (5);\nПрервать выполнение программы - любое"
                      " другое число.\n");
        int operation;
        std::cin >> operation;

        switch (operation)
        {
        case 1: // Объединение
            std::cout << "Объединение множеств X и Y: ";
            printArray(unite(x, y));
            std::cout << "\n";
            break;
        case 2: // Пересечение
            std::cout << "Пересечение множеств X и Y: ";
            printArray(intersect(x, y));
            std::cout << "\n";
            break;
        case 3: // Разность X\Y и Y\X
            std::cout << "Разность множеств X и Y: ";
            printArray(difference(x, y));
            std::cout << "Разность множеств Y и X: ";
            printArray(difference(y, x));
            std::cout << "\n";
            break;
        case 4: // Симметрическая разность X и Y
            std::cout << "Симметрическая разность множеств X и Y: ";
            printArray(symmetricalDifference(x, y));
            std::cout << "\n";
            break;
        case 5: // Дополнение до универсума множества X и множества Y
            std::cout << "Дополнение до универсума множества X: ";
            printArray(additionToTheUniversum(x));
            std::cout << "Дополнение до универсума множества Y: ";
            printArray(additionToTheUniversum(y));
            std::cout << "\n";
            break;
        default:
            std::cout << "Выполнение программы завершено!\n";
            terminated = true;
            break;
        }
        
        if (terminated)
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}