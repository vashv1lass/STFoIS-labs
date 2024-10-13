// CLANG

#include <iostream> // std::cin, std::cout
#include <vector> // std::vector
#include <utility> // std::pair
#include <string> // std::string

/**
 * @brief Проверяет, наличие элемента в массиве
 *
 * @tparam T тип хранимых элементов
 * @param a массив
 * @param e элемент
 * @return true если элемент найден
 * @return false иначе
 */
template<typename T>
inline bool found(const std::vector<T>& a, const T& e)
{
	return std::any_of(a.begin(), a.end(), [e](const T& element)
	{
		return element == e;
	});
}

/**
 * @brief Ввод элементов множества целых чисел
 *
 * @param s множество
 * @param name имя множества
 */
void inputSet(std::vector<int>& s, const std::string& name)
{
	std::cout << "Введите размер множества " << name << " (помните, что после "
	             "ввода повторяющиеся элементы множества удаляются, что может "
	             "привести к несоответствию желаемых и действительных размеров "
	             "множества): ";
	int size;
	std::cin >> size;
	s.reserve(size); // резервируем память для множества (для более быстрой работы ф-ции push_back)
	
	std::cout << "Введите множество " << name << ":\n";
	for (int i = 0; i < size; i++)
	{
		int x;
		std::cin >> x;
		if (!found(s, x)) // если элемент уже был введен, то не добавляем его второй раз
		{
			s.push_back(x);
		}
	}
}

/**
 * @brief Вывод элементов множества на экран
 *
 * @param s множество
 */
void printSet(const std::vector<int>& s)
{
	std::cout << "{"; // множество заключается в фигурные скобки
	for (int i = 0; i < s.size(); i++)
	{
		std::cout << s[i];
		if (i + 1 < s.size()) // после последнего элемента запятую не ставим
		{
			std::cout << ", ";
		}
	}
	std::cout << "}\n"; // переходим на след. строку после вывода множества
}

/**
 * @brief Ввод элементов графика
 *
 * @param g график
 * @param name имя графика
 */
void inputGraph(std::vector< std::pair<int, int> >& g, const std::string& name)
{
	std::cout << "Введите размер графика " << name << " (помните, что после "
	             "ввода повторяющиеся элементы графика удаляются, что может "
	             "привести к несоответствию желаемых и действительных размеров "
	             "графика): ";
	int size;
	std::cin >> size;
	g.reserve(size);
	
	std::cout << "Введите график " << name << " (помните, что элементы графика "
	                                          "вводятся попарно):\n";
	for (int i = 0; i < size; i++)
	{
		int x, y;
		std::cin >> x >> y;
		if (!found(g, {x, y}))
		{
			g.emplace_back(x, y);
		}
	}
}

/**
 * @brief Вывод графика в консоль
 *
 * @param g график
 */
void printGraph(const std::vector< std::pair<int, int> >& g)
{
	std::cout << "{";
	for (int i = 0; i < g.size(); i++)
	{
		std::cout << "<" << g[i].first << ", " << g[i].second << ">"; // элементы графика (пары) заключаем в угловые скобки
		if (i + 1 < g.size())
		{
			std::cout << ", ";
		}
	}
	std::cout << "}\n";
}

/**
 * @brief Область определения графика
 *
 * @param g график
 * @return std::vector<int> область определения графика
 */
std::vector<int> domainOfDefinition(const std::vector< std::pair<int, int> >& g)
{
	std::vector<int> d;
	d.reserve(g.size());
	
	for (const std::pair<int, int>& current : g)
	{
		if (!found(d, current.first))
		{
			d.push_back(current.first);
		}
	}
	
	return d;
}

/**
 * @brief Область значений графика
 *
 * @param g график
 * @return std::vector<int> область значений графика
 */
std::vector<int> range(const std::vector< std::pair<int, int> >& g)
{
	std::vector<int> e;
	e.reserve(g.size());
	
	for (const std::pair<int, int>& current : g)
	{
		if (!found(e, current.second))
		{
			e.push_back(current.second);
		}
	}
	
	return e;
}

/**
 * @brief Инверсия пары
 *
 * @param p пара
 * @return std::pair<int, int> инвертированная пара
 */
inline std::pair<int, int> inversion(const std::pair<int, int>& p)
{
	return {p.second, p.first};
}

/**
 * @brief Инверсия графика
 *
 * @param p график
 * @return std::vector< std::pair<int, int> > инвертированный график
 */
std::vector< std::pair<int, int> > inversion(const std::vector< std::pair<int, int> >& p)
{
	std::vector< std::pair<int, int> > q(p.size());
	
	for (int i = 0; i < p.size(); i++)
	{
		q[i] = inversion(p[i]);
	}
	
	return q;
}

/**
 * @brief Проверяет график на симметричность
 *
 * @param p график
 * @return true если график симметричен
 * @return false иначе
 */
bool isSymmetrical(const std::vector< std::pair<int, int> >& p)
{
	return !std::any_of(p.begin(), p.end(), [p](const std::pair<int, int>& element)
	{
		return !found(p, inversion(element));
	});
}

/**
 * @brief диагональ множества
 *
 * @param m множество
 * @return std::vector< std::pair<int, int> > график, являющийся диагональю множества
 */
std::vector< std::pair<int, int> > diagonal(const std::vector<int>& m)
{
	std::vector< std::pair<int, int> > dm(m.size());
	
	for (int i = 0; i < dm.size(); i++)
	{
		dm[i] = {m[i], m[i]};
	}
	
	return dm;
}

/**
 * @brief Композиция двух графиков
 *
 * @param p график 1
 * @param q график 2
 * @return std::vector< std::pair<int, int> > композиция графиков P и Q
 */
std::vector< std::pair<int, int> > composition(const std::vector< std::pair<int, int> >& p,
                                               const std::vector< std::pair<int, int> >& q)
{
	std::vector< std::pair<int, int> > result;
	
	for (const std::pair<int, int>& currentP : p)
	{
		for (const std::pair<int, int>& currentQ : q)
		{
			if (currentP.second == currentQ.first)
			{
				if (!found(result, {currentP.first, currentQ.second})) // не добавляем по 2 раза
				{
					result.emplace_back(currentP.first, currentQ.second);
				}
			}
		}
	}
	
	return result;
}

int main()
{
	std::cout << "Выберите операцию, которую хотите произвести (для выбора "
	             "введите номер пункта соответствующей операции):\n"
	             "\t1. Инверсия графика.\n"
	             "\t2. Проверка графика на симметричность.\n"
	             "\t3. Нахождение диагонали множества.\n"
	             "\t4. Композиция графиков.\n"
	             "\t5. Нахождение области определения графика.\n"
	             "\t6. Нахождение области значений графика.\n"
	             "Операция: ";
	int operation;
	std::cin >> operation;
	
	switch (operation) {
		case 1:
		{
			std::vector<std::pair<int, int> > p;
			inputGraph(p, "P");
			
			std::vector<std::pair<int, int> > q = inversion(p);
			
			std::cout << "Инверсией графика P является график Q, который выгдядит "
			             "следующим образом:\n";
			printGraph(q);
		}
			break;
		case 2:
		{
			std::vector<std::pair<int, int> > p;
			inputGraph(p, "P");
			
			std::cout << "График P " << (isSymmetrical(p) ? "" : "не ") << "является "
			                                                               "симметричным.";
		}
			break;
		case 3:
		{
			std::vector<int> m;
			inputSet(m, "M");
			
			std::vector<std::pair<int, int> > dm = diagonal(m);
			
			std::cout << "Диагональю множества M является график, который "
			             "выглядит следующим образом:\n";
			printGraph(dm);
		}
			break;
		case 4:
		{
			std::vector<std::pair<int, int> > p, q;
			inputGraph(p, "P");
			inputGraph(q, "Q");
			
			std::vector<std::pair<int, int> > r1 = composition(p, q);
			std::vector<std::pair<int, int> > r2 = composition(q, p);
			
			std::cout << "Композицией графиков P и Q является график R, "
			             "выглядещий следующим образом:\n";
			printGraph(r1);
			std::cout << "Композиция графиков Q и P:\n";
			printGraph(r2);
		}
			break;
		case 5:
		{
			std::vector<std::pair<int, int> > p;
			inputGraph(p, "P");
			
			std::vector<int> dp = domainOfDefinition(p);
			
			std::cout << "Областью определения графика P является множество "
			             "чисел: ";
			printSet(dp);
		}
			break;
		case 6:
		{
			std::vector<std::pair<int, int> > p;
			inputGraph(p, "P");
			
			std::vector<int> ep = range(p);
			
			std::cout << "Областью значений графика P является множество "
			             "чисел: ";
			printSet(ep);
		}
			break;
		default:
			std::cout << "Ошибка! Неизвестная операция.\n";
	}
	return 0;
}