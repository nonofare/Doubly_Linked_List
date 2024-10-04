namespace DLL {

	template <typename T>
	class List {

		template <typename T>
		class Node {
			friend List;

		private:
			T data;
			Node<T>* next;
			Node<T>* prev;

		public:
			Node(T data) {
				this->data = data;
				next = nullptr;
				prev = nullptr;
			}
		};

	private:
		size_t size;
		Node<T>* head;
		Node<T>* tail;

	public:
		List() {
			size = 0;
			head = nullptr;
			tail = nullptr;
		}

		// Dodawanie nowego elementu na poczatku listy (2b)
		void add_at_head(T data) {
			Node<T>* newNode = new Node<T>(data);
			if (size > 0) {
				head->prev = newNode;
				newNode->next = head;
				head = newNode;
			}
			else {
				head = newNode;
				tail = newNode;
			}
			size++;
		}

		// Dodawanie nowego elementu na koncu listy (2a)
		void add_at_tail(T data) {
			Node<T>* newNode = new Node<T>(data);
			if (size > 0) {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
			else {
				head = newNode;
				tail = newNode;
			}
			size++;
		}

		// Usiniecie pierwszego elementu (2d)
		bool remove_at_head() {
			if (size > 1) {
				Node<T>* temp = head->next;
				delete head;
				head = temp;
				size--;

				return true;
			}
			else if (size == 1) {
				delete head;
				head = tail = nullptr;
				size--;

				return true;
			}
			else {
				return false;
			}
		}

		// Usiniecie ostatniego elementu (2c)
		bool remove_at_tail() {
			if (size > 1) {
				Node<T>* temp = tail->prev;
				delete tail;
				tail = temp;
				size--;

				return true;
			}
			else if (size == 1) {
				delete tail;
				head = tail = nullptr;
				size--;

				return true;
			}
			else {
				return false;
			}
		}

		// Zwrocenie danych i-tego elementu listy (2e)
		bool get_data_by_index(size_t index) {
			if (size < index + 1 || index < 0) {
				return false;
			}
			else {
				
			}
		}

		// Ustawienie danych i-tego elementu listy(2f)
		void set_data_by_index(T data) {

		}

		// Wyszukiwanie elementu (2g)
		void find() {

		}

		// Wyszukiwanie i usiniecie elementu (2h)
		void find_and_delete() {

		}

		// Dodanie nowego elementu z wymuszeniem porzadku (2i)
		void idk() {

		}

		// Usuniecie wszystkich elementow listy (2j)
		void erase() {

		}

		// Zwrocenie napisowej reprezentacji listy (2k) (XD?)
		void idk2() {

		}
	};
}