#include <vector>
#include <map>
#include <clocale>
#include <iostream>

/**
 * @brief Проверяет есть ли элемент в массиве
 *
 * @tparam T тип элементов в массиве
 * @param a массив, в котором надо найти элемент
 * @param e элемент, который надо найти
 * @return true если элемент найден
 * @return false если элемент не найден
 */
template<typename T>
bool found(const std::vector<T> &a, const T &e) {
	return std::any_of(a.begin(), a.end(), [&e](const T &element) {
		return element == e;
	});
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
std::vector<T> unite(const std::vector<T> &x, const std::vector<T> &y) {
	std::vector<T> result = x;
	
	for (size_t i = 0; i < y.size(); i++) {
		if (!found(result, y[i])) {
			result.push_back(y[i]);
		}
	}
	
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
std::vector<T> intersect(const std::vector<T> &x, const std::vector<T> &y) {
	std::vector<T> result;
	
	for (size_t i = 0; i < x.size(); i++) {
		if (found(y, x[i])) {
			result.push_back(x[i]);
		}
	}
	
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
std::vector<T> difference(const std::vector<T> &x, const std::vector<T> &y) {
	std::vector<T> result;
	
	for (size_t i = 0; i < x.size(); i++) {
		if (!found(y, x[i])) {
			result.push_back(x[i]);
		}
	}
	
	return result;
}

/**
 * @brief Инверсия пары
 *
 * @param p пара
 * @return std::pair<int, int> инвертированная пара
 */
std::pair<int, int> inversion(const std::pair<int, int>& p) {
	return {p.second, p.first};
}

/**
 * @brief Инверсия графика
 *
 * @param p график
 * @return std::vector< std::pair<int, int> > инвертированный график
 */
std::vector< std::pair<int, int> > inversion(const std::vector< std::pair<int, int> >& p) {
	std::vector< std::pair<int, int> > q(p.size());
	
	for (int i = 0; i < p.size(); i++) {
		q[i] = inversion(p[i]);
	}
	
	return q;
}

std::vector< std::pair<int, int> > composition(
		const std::vector< std::pair<int, int> >& p,
		const std::vector< std::pair<int, int> >& q
) {
	std::vector< std::pair<int, int> > result;
	
	for (const std::pair<int, int>& currentP : p) {
		for (const std::pair<int, int>& currentQ : q) {
			if (currentP.second == currentQ.first) {
				if (!found(result, {currentP.first, currentQ.second})) {
					result.emplace_back(currentP.first, currentQ.second);
				}
			}
		}
	}
	
	return result;
}

/**
 * @brief Соответствие
 *
 */
class Accordance {
private:
	std::vector<int> departureArea;
	std::vector<int> arrivalArea;
	std::vector< std::pair<int, int> > graph;
public:
	Accordance(
			const std::vector<int> &departureArea = std::vector<int>(),
			const std::vector<int> &arrivalArea = std::vector<int>(),
			const std::vector< std::pair<int, int> > &graph = std::vector< std::pair<int, int> >()
	)
	: departureArea(departureArea), arrivalArea(arrivalArea), graph(graph) {}
	
	explicit Accordance(const std::vector< std::vector<bool> > &matrix) {
		for (size_t i = 0; i < matrix.size(); i++) {
			for (size_t j = 0; j < matrix[i].size(); j++) {
				if (matrix[i][j]) {
					if (!found(this->departureArea, (int)(1 + i))) {
						this->departureArea.push_back(1 + i);
					}
					if (!found(this->arrivalArea, (int)(1 + j))) {
						this->arrivalArea.push_back(1 + j);
					}
					if (!found(this->graph, {1 + i, 1 + j})) {
						this->graph.emplace_back(1 + i, 1 + j);
					}
				}
			}
		}
	}
	
	explicit Accordance(const std::vector< std::vector<int> > &graph) {
		for (size_t i = 0; i < graph.size(); i++) {
			if (!found(this->departureArea, (int)(1 + i))) {
				this->departureArea.push_back(1 + i);
			}
			
			for (size_t j = 0; j < graph[i].size(); j++) {
				if (!found(this->arrivalArea, graph[i][j])) {
					this->arrivalArea.push_back(graph[i][j]);
				}
				if (!found(this->graph, {1 + i, graph[i][j]})) {
					this->graph.emplace_back(1 + i, graph[i][j]);
				}
			}
		}
	}
	
	/**
	 * @brief Область отправления соответствия
	 *
	 * @return std::vector<int> область отправления соответствия
	 */
	std::vector<int> getDepartureArea() const {
		return this->departureArea;
	}
	
	/**
	 * @brief Область прибытия соответствия
	 *
	 * @return std::vector<int> область прибытия соответствия
	 */
	std::vector<int> getArrivalArea() const {
		return this->arrivalArea;
	}
	
	/**
	 * @brief График соответствия
	 *
	 * @return std::vector< std::pair<int, int> > соответствия
	 */
	std::vector< std::pair<int, int> > getGraph() const {
		return this->graph;
	}
	
	/**
	 * @brief Область определения соответствия
	 *
	 * @return std::vector<int> область определения соответствия
	 */
	std::vector<int> definitionArea() const {
		std::vector<int> result;
		
		for (size_t i = 0; i < this->graph.size(); i++) {
			if (!found(result, this->graph[i].first)) {
				result.push_back(this->graph[i].first);
			}
		}
		
		return result;
	}
	
	/**
	 * @brief Область значений соответствия
	 *
	 * @return std::vector<int> область значений соответствия
	 */
	std::vector<int> valueArea() const {
		std::vector<int> result;
		
		for (size_t i = 0; i < this->graph.size(); i++) {
			if (!found(result, this->graph[i].second)) {
				result.push_back(this->graph[i].second);
			}
		}
		
		return result;
	}
	
	/**
	 * @brief Проверка, является ли соответствие всюду определённым
	 *
	 * @return true если соответствие является всюду определённым
	 * @return false если нет
	 */
	bool isEverywhereDefined() const {
		return this->definitionArea() == this->departureArea;
	}
	
	/**
	 * @brief Проверка, является ли соответствие сюръективным
	 *
	 * @return true если соответствие является сюръективным
	 * @return false если нет
	 */
	bool isSurjective() const {
		return this->valueArea() == this->arrivalArea;
	}
	
	/**
	 * @brief Проверка, является ли соответствие функциональным
	 *
	 * @return true если соответствие является функциональным
	 * @return false если нет
	 */
	bool isFunctional() const {
		std::map<int, int> firstCount;
		
		for (size_t i = 0; i < this->graph.size(); i++) {
			++firstCount[this->graph[i].first];
		}
		
		for (auto current : firstCount) {
			if (current.second > 1) {
				return false;
			}
		}
		return true;
	}
	
	/**
	 * @brief Проверка, является ли соответствие инъективным
	 *
	 * @return true если соответствие является инъективным
	 * @return false если нет
	 */
	bool isInjective() const {
		std::map<int, int> secondCount;
		
		for (size_t i = 0; i < this->graph.size(); i++) {
			++secondCount[this->graph[i].second];
		}
		
		for (auto current : secondCount) {
			if (current.second > 1) {
				return false;
			}
		}
		return true;
	}
	
	/**
	 * @brief Проверка, является ли соответствие отображением X в Y
	 *
	 * @return true если соответствие является отображением X в Y
	 * @return false если нет
	 */
	bool isMappingIn() const {
		return this->isEverywhereDefined() && this->isFunctional();
	}
	
	/**
	 * @brief Проверка, является ли соответствие отображением X на Y
	 *
	 * @return true если соответствие является отображением X на Y
	 * @return false если нет
	 */
	bool isMappingTo() const {
		return this->isEverywhereDefined() && this->isFunctional() && this->isSurjective();
	}
	
	/**
	 * @brief Проверка, является ли соответствие взаимно однозначным
	 *
	 * @return true если соответствие является взаимно однозначным
	 * @return false если нет
	 */
	bool isOneToOne() const {
		return this->isFunctional() && this->isInjective();
	}
	
	/**
	 * @brief Проверка, является ли соответствие биекцией
	 *
	 * @return true если соответствие является биекцией
	 * @return false если нет
	 */
	bool isBijection() const {
		return (this->isEverywhereDefined() && this->isSurjective() &&
		        this->isFunctional() && this->isInjective());
	}
	
	/**
	 * @brief Находит образ множества А
	 *
	 * @param a множество А
	 * @return std::vector<int> образ множества А
	 */
	std::vector<int> findImage(const std::vector<int> &a) {
		std::vector<int> gammaB;
		
		for (size_t i = 0; i < this->graph.size(); i++) {
			if (found(a, this->graph[i].first)) {
				gammaB.push_back(this->graph[i].second);
			}
		}
		
		return gammaB;
	}
	
	/**
	 * @brief Находит прообраз множества B
	 *
	 * @param b множество B
	 * @return std::vector<int> прообраз множества B
	 */
	std::vector<int> findPrototype(const std::vector<int> &b) {
		std::vector<int> gammaMinus1B;
		
		for (size_t i = 0; i < this->graph.size(); i++) {
			if (found(b, this->graph[i].second)) {
				gammaMinus1B.push_back(this->graph[i].first);
			}
		}
		
		return gammaMinus1B;
	}
	
	friend Accordance unite(const Accordance &x, const Accordance &y);
	friend Accordance intersect(const Accordance &x, const Accordance &y);
	friend Accordance difference(const Accordance &x, const Accordance &y);
	friend Accordance inverse(const Accordance &x);
	friend Accordance composition(const Accordance &x, const Accordance &y);
};

/**
 * @brief Объединение двух соответствий
 *
 * @param x первое соответствие
 * @param y второе соответствие
 * @return Accordance соотв-ие, являющееся объединением соответствий X и Y
 */
Accordance unite(const Accordance &x, const Accordance &y) {
	return Accordance(
			unite(x.getDepartureArea(), y.getDepartureArea()),
			unite(x.getArrivalArea(), y.getArrivalArea()),
			unite(x.getGraph(), y.getGraph())
	);
}

/**
 * @brief Пересечение двух соответствий
 *
 * @param x первое соответствие
 * @param y второе соответствие
 * @return Accordance соотв-ие, являющееся пересечением соответствий X и Y
 */
Accordance intersect(const Accordance &x, const Accordance &y) {
	return Accordance(
			intersect(x.getDepartureArea(), y.getDepartureArea()),
			intersect(x.getArrivalArea(), y.getArrivalArea()),
			intersect(x.getGraph(), y.getGraph())
	);
}

/**
 * @brief Разность двух соответствий
 *
 * @param x первое соответствие
 * @param y второе соответствие
 * @return Accordance соотв-ие, являющееся разностью соответствий X и Y
 */
Accordance difference(const Accordance &x, const Accordance &y) {
	return Accordance(
			difference(x.getDepartureArea(), y.getDepartureArea()),
			difference(x.getArrivalArea(), y.getArrivalArea()),
			difference(x.getGraph(), y.getGraph())
	);
}

/**
 * @brief Инверсия соответствия X
 *
 * @param x соответствие X
 * @return Accordance соотв-ие, являющееся инверсией соответствия X
 */
Accordance inverse(const Accordance &x) {
	return Accordance(
			x.getArrivalArea(),
			x.getDepartureArea(),
			inversion(x.getGraph())
	);
}

/**
 * @brief Композиция двух соответствий
 *
 * @param x первое соответствие
 * @param y второе соответствие
 * @return Accordance соотв-ие, являющееся композицией соответствий X и Y
 */
Accordance composition(const Accordance &x, const Accordance &y) {
	return Accordance(
			x.getDepartureArea(),
			y.getArrivalArea(),
			composition(x.getGraph(), y.getGraph())
	);
}

/**
 * @brief Ввод элементов множества целых чисел
 *
 * @param s множество
 * @param name имя множества
 */
void inputSet(std::vector<int>& s, const std::string& whatArea)
{
	int option = -1;
	while (!(1 <= option && option <= 2)) {
		std::cout << "Выберите способ задания множества, являюегося областью " << whatArea <<
		          " данного соответствия.\n"
		          "1. Традиционный.\n"
		          "2. Высказывательный.\n";
		std::cin >> option;
		
		switch (option) {
			case 1: {
				std::cout << "Введите размер множества, являющегося областью " << whatArea <<
				          " (помните, что после ввода повторяющиеся элементы множества удаляются,"
				          "что может привести к несоответствию желаемых и действительных размеров "
				          "множества): ";
				size_t size;
				std::cin >> size;
				s.reserve(size);
				
				std::cout << "Введите множество:\n";
				for (int i = 0; i < size; i++) {
					int x;
					std::cin >> x;
					if (!found(s, x)) {
						s.push_back(x);
					}
				}
			}
				break;
			case 2: {
				int option1 = -1;
				while (!(1 <= option1 && option1 <= 3)) {
					std::cout << "Выберите одно из трёх возможных высказываний, по которому вы хотите "
					             "заполнить множество:\n"
					             "1. Квадраты натуральных чисел в промежутке [a;b].\n"
					             "2. Чётные числа в промежутке [a;b].\n"
					             "3. Нечётные числа в промежутке [a;b].\n";
					std::cin >> option1;
					int a, b;
					std::cout << "Введите a: ";
					std::cin >> a;
					std::cout << "Введите b: ";
					std::cin >> b;
					switch (option1) {
						case 1:
							for (int i = a; i <= b; i++) {
								s.push_back(i * i);
							}
							break;
						case 2:
							a += (a % 2);
							for (int i = a; i <= b; i += 2) {
								s.push_back(i);
							}
							break;
						case 3:
							a += ((a + 1) % 2);
							for (int i = a; i <= b; i += 2) {
								s.push_back(i);
							}
							break;
						default:
							std::cout << "Выберите один из предложенных вариантов!\n";
					}
				}
			}
				break;
			default:
				std::cout << "Выберите один из предложенных вариантов!\n";
		}
	}
}

/**
 * @brief Ввод элементов графика
 *
 * @param g график
 * @param name имя графика
 */
void inputGraph(std::vector< std::pair<int, int> >& g)
{
	std::cout << "Введите размер графика соответствия (помните, что после "
	             "ввода повторяющиеся элементы графика удаляются, что может "
	             "привести к несоответствию желаемых и действительных размеров "
	             "графика): ";
	int size;
	std::cin >> size;
	g.reserve(size);
	
	std::cout << "Введите график соответствия (помните, что элементы графика "
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
 * @brief Ввод соответствия
 *
 * @param a соответствие
 * @param name имя соответствия
 */
void inputAccordance(Accordance &a, const std::string name) {
	int option = -1;
	while (!(1 <= option && option <= 3)) {
		std::cout << "Выберите способ задания соответствия " << name << ":\n"
					 "1. Теоретический.\n"
		             "2. Матричный.\n"
		             "3. Графический.\n";
		std::cin >> option;
		
		switch (option) {
			case 1:
			{
				std::vector<int> x;
				inputSet(x, "отправления");
				std::vector<int> y;
				inputSet(y, "прибытия");
				std::vector< std::pair<int, int> > g;
				inputGraph(g);
				
				a = Accordance(x, y, g);
			}
				break;
			case 2:
			{
				size_t n, m;
				std::cout << "Введите количество строк матрицы соответствия: ";
				std::cin >> n;
				std::cout << "Введите количество столбцов матрицы соответствия: ";
				std::cin >> m;
				
				std::cout << "Введите матрицу соответствия:\n";
				std::vector< std::vector<bool> > matrix(n, std::vector<bool>(m));
				for (size_t i = 0; i < n; i++) {
					for (size_t j = 0; j < m; j++) {
						int aij;
						std::cin >> aij;
						matrix[i][j] = static_cast<bool>(aij);
					}
				}
				
				a = Accordance(matrix);
			}
				break;
			case 3:
			{
				std::cout << "Введите количество элементов в области отправления соответствия: ";
				size_t n;
				std::cin >> n;
				std::vector< std::vector<int> > g(n);
				
				for (size_t i = 0; i < n; i++) {
					std::cout << "Введите количество элементов в области прибытия соответствия, "
								 "с которыми есть связь у " << 1 + i << "-го элемента\n";
					size_t m;
					std::cin >> m;
					std::cout << "Введите номера элементов в области прибытия соответствия, "
					             "с которыми есть связь у " << 1 + i << "-го элемента\n";
					for (size_t j = 0; j < m; j++) {
						int gij;
						std::cin >> gij;
						g[i].push_back(gij);
					}
				}
				
				a = Accordance(g);
			}
				break;
			default:
				std::cout << "Выберите один из предложенных вариантов!\n";
		}
	}
}

/**
 * @brief Печатает множество на консоль
 *
 * @tparam T тип элементов в множестве
 * @param s множество
 */
template<typename T>
void printSet(const std::vector<T>& s) {
	std::cout << "{ ";
	for (size_t i = 0; i < s.size(); i++) {
		std::cout << s[i] << ((i + 1 != s.size()) ? ", " : " ");
	}
	std::cout << "}\n";
}

/**
 * @brief Вывод графика на консоль
 *
 * @param g график
 */
void printGraph(const std::vector< std::pair<int, int> >& g)
{
	std::cout << "{";
	for (int i = 0; i < g.size(); i++)
	{
		std::cout << "<" << g[i].first << ", " << g[i].second << ">";
		if (i + 1 < g.size())
		{
			std::cout << ", ";
		}
	}
	std::cout << "}\n";
}

/**
 * @brief Печатает соответствие на консоль
 *
 * @param a соответствие
 * @param name имя соответствия
 */
void printAccordance(const Accordance &a, const std::string &name) {
	std::cout << "Область отправления соответствия " << name << ":\n";
	printSet(a.getDepartureArea());
	std::cout << "Область прибытия соответствия " << name << ":\n";
	printSet(a.getArrivalArea());
	std::cout << "График соответствия " << name << ":\n";
	printGraph(a.getGraph());
}

int main() {
	setlocale(LC_ALL, "rus");
	
	int option = 1;
	while (1 <= option && option <= 8) {
		std::cout << "Выберите нужную операцию:\n"
		             "1. Объединение соответствий.\n"
		             "2. Пересечение соответствий.\n"
		             "3. Разность соответствий.\n"
		             "4. Инверсия соответствия.\n"
		             "5. Композиция соответствий.\n"
		             "6. Вся информация о соответствии.\n"
		             "7. Найти образ множества при соответствии.\n"
		             "8. Найти прообраз множества при соответствии.\n"
		             "Любое другое число - выход из программы.\n";
		std::cin >> option;
		
		switch (option) {
			case 1:
			{
				Accordance a, b;
				inputAccordance(a, "A");
				inputAccordance(b, "B");
				
				Accordance c = unite(a, b);
				
				std::cout << "Результатом объединения соответствий A и B является соответствие С.\n";
				printAccordance(c, "C");
			}
				break;
			case 2:
			{
				Accordance a, b;
				inputAccordance(a, "A");
				inputAccordance(b, "B");
				
				Accordance c = intersect(a, b);
				
				std::cout << "Результатом пересечения соответствий A и B является соответствие С.\n";
				printAccordance(c, "C");
			}
				break;
			case 3:
			{
				Accordance a, b;
				inputAccordance(a, "A");
				inputAccordance(b, "B");
				
				Accordance c = difference(a, b);
				
				std::cout << "Результатом выполнения операции разности на соответствиях A и "
				             "B является соответствие С.\n";
				printAccordance(c, "C");
			}
				break;
			case 4:
			{
				Accordance a;
				inputAccordance(a, "A");
				
				Accordance aMinus1 = inverse(a);
				
				std::cout << "Инверсией соответствия А является соответствие B.\n";
				printAccordance(aMinus1, "B");
			}
				break;
			case 5:
			{
				Accordance a, b;
				inputAccordance(a, "A");
				inputAccordance(b, "B");
				
				Accordance c = composition(a, b);
				
				std::cout << "Результатом выполнения операции композиции на соответствиях A и "
				             "B является соответствие С.\n";
				printAccordance(c, "C");
			}
				break;
			case 6:
			{
				Accordance a;
				inputAccordance(a, "A");
				
				std::cout << "Соответствие A:\n";
				
				if (a.isEverywhereDefined()) {
					std::cout << "1. Всюду определено.\n";
				} else {
					std::cout << "1. Не является всюду определенным.\n";
				}
				
				if (a.isSurjective()) {
					std::cout << "2. Сюръективно.\n";
				} else {
					std::cout << "2. Несюръективно.\n";
				}
				
				if (a.isFunctional()) {
					std::cout << "3. Функционально.\n";
				} else {
					std::cout << "3. Нефункционально.\n";
				}
				
				if (a.isInjective()) {
					std::cout << "4. Инъективно\n";
				} else {
					std::cout << "4. Неинъективно.\n";
				}
				
				if (a.isMappingIn()) {
					std::cout << "5. Является отображением X в Y ";
				} else {
					std::cout << "5. Не является отображением X в Y ";
				}
				std::cout << "(где X - область отправления, Y - область прибытия).\n";
				
				if (a.isMappingTo()) {
					std::cout << "6. Является отображением X на Y.\n";
				} else {
					std::cout << "6. Не является отображением X на Y.\n";
				}
				
				if (a.isOneToOne()) {
					std::cout << "7. Является взаимно однозначным.\n";
				} else {
					std::cout << "7. Не является взаимно однозначным.\n";
				}
				
				if (a.isBijection()) {
					std::cout << "8. Является биекцией.\n";
				} else {
					std::cout << "8. Не является биекцией.\n";
				}
			}
				break;
			case 7:
			{
				Accordance gamma;
				inputAccordance(gamma, "Г");
				
				std::vector<int> a;
				inputSet(a, "A");
				
				std::cout << "Образом множества A при соответствии Г является множество:\n";
				printSet(gamma.findImage(a));
			}
				break;
			case 8:
			{
				Accordance gamma;
				inputAccordance(gamma, "Г");
				
				std::vector<int> b;
				inputSet(b, "B");
				
				std::cout << "Прообразом множества B при соответствии Г является множество:\n";
				printSet(gamma.findPrototype(b));
			}
				break;
			default:
				std::cout << "Выход из программы...\n";
			std::cout << '\n';
		}
	}
	
	return EXIT_SUCCESS;
}