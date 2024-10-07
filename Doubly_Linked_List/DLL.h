namespace DLL {

	template <typename T>
	class List {

		template <typename T>
		class Node {
			friend List;

			T data;
			Node<T>* next;
			Node<T>* prev;

			Node(T data) {
				this->data = data;
				next = nullptr;
				prev = nullptr;
			}
		};

		size_t size;
		Node<T>* head;
		Node<T>* tail;

	public:
		List() {
			size = 0;
			head = nullptr;
			tail = nullptr;
		}

		// Add new element at the begining of the list, time complexity: theta = 1 (2b)
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

		// Add new element at the end of the list, time complexity: theta = 1 (2a)
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

		// Remove first element, time complexity: theta = 1 (2d)
		void remove_at_head() {
			if (size > 1) {
				Node<T>* temp = head->next;

				delete head;
				head = temp;
				size--;
			}
			else if (size == 1) {
				delete head;
				head = tail = nullptr;
				size--;
			}
			else {
				throw std::underflow_error("List is empty");
			}
		}

		// Remove last element, time complexity: theta = 1 (2c)
		void remove_at_tail() {
			if (size > 1) {
				Node<T>* temp = tail->prev;

				delete tail;
				tail = temp;
				size--;
			}
			else if (size == 1) {
				delete tail;
				head = tail = nullptr;
				size--;
			}
			else {
				throw std::underflow_error("List is empty");
			}
		}

		// Get node data by index, time complexity: O = n/2 (2e)
		T get_data_by_index(size_t index) {
			if (index > size - 1) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node<T>* temp;

				if (index < size / 2) {
					temp = head;
					for (size_t i = 0; i < index; i++) {
						temp = temp->next;
					}
				}
				else {
					temp = tail;
					for (size_t i = size - 1; i > index; i--) {
						temp = temp->prev;
					}
				}

				return temp->data;
			}	
		}

		// Set node data by index, time complexity: O = n/2 (2f)
		void set_data_by_index(size_t index, T data) {
			if (index > size - 1) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node<T>* temp;

				if (index < size / 2) {
					temp = head;
					for (size_t i = 0; i < index; i++) {
						temp = temp->next;
					}
				}
				else {
					temp = tail;
					for (size_t i = size - 1; i > index; i--) {
						temp = temp->prev;
					}
				}

				temp->data = data;
			}
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

		// Delete all list elements, time complexity: theta = n (2j)
		void erase() {
			if (size > 0) {
				Node<T>* temp = tail;

				while (temp != nullptr) {
					Node<T>* temp2 = temp->prev;
					delete temp;
					temp = temp2;
					size--;
				}
			}
		}

		// Zwrocenie napisowej reprezentacji listy (2k) (XD?)
		void idk2() {

		}
	};
}